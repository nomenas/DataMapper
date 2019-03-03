// Transformation model. Mapping and conversions has to be manually written.
//
// in this example I took the following cases:
// - incompatible types: xy in proto is float, in json is presented as int. In this case converter has to be injected.
// - array: xy is an array in json
// - different structure: ctrange is nested in ct in json.
// - empty element: username is not initially set in proto object

#pragma once

#include "utilities.h"
#include "proto_builders.h"

tao::json::value transform(my_project::lights::LightService& object) {
    tao::json::value json_object;
    set_value(json_object, {"on", "on"}, object.has_on(), object.on().value());
    set_value(json_object, {"config", "factoryName"}, object.has_factoryname(), object.factoryname().value());
    set_value(json_object, {"color", "brightness"}, object.has_brightness(), object.brightness().value());
    set_array(json_object, {"color", "xy"}, object.has_xy() && object.xy().valid(),
              std::vector<float>{object.xy().x(), object.xy().y()}, [](auto value){return std::ceil(value);});
    set_value(json_object, {"ct", "ct"}, object.has_ct() && object.ct().valid(), object.ct().value());
    set_value(json_object, {"ct", "range", "min"}, object.has_ctrange(), object.ctrange().min());
    set_value(json_object, {"ct", "range", "max"}, object.has_ctrange(), object.ctrange().max());
    set_value(json_object, {"config", "username"}, object.has_username(), object.username().value());
    return json_object;
}

std::unique_ptr<my_project::lights::LightService> transform(const tao::json::value& json_object) {
    auto light_service = std::make_unique<my_project::lights::LightService>();
    CTRangeBuilder ct_range_builder;
    set_proto_value(json_object, {"on", "on"}, [&](const tao::json::value& json) mutable {
        light_service->set_allocated_on(OnBuilder{}.set_value(json.as<bool>()).build().release());
    });
    set_proto_value(json_object, {"config", "factoryName"}, [&](const tao::json::value& json) mutable {
        light_service->set_allocated_factoryname(FactoryNameBuilder{}.set_value(json.as<std::string>()).build().release());
    });
    set_proto_value(json_object, {"color", "brightness"}, [&](const tao::json::value& json) mutable {
        light_service->set_allocated_brightness(BrightnessBuilder{}.set_value(json.as<::google::protobuf::uint32>()).build().release());
    });
    set_proto_value(json_object, {"color", "xy"}, [&](const tao::json::value& json) mutable {
        const auto array = json.get_array();
        const auto x = static_cast<float>(array[0].as<int>());
        const auto y = static_cast<float>(array[1].as<int>());
        light_service->set_allocated_xy(XYBuilder{}.set_valid(true).set_x(x).set_y(y).build().release());
    });
    set_proto_value(json_object, {"ct", "ct"}, [&](const tao::json::value& json) mutable {
        light_service->set_allocated_ct(CTBuilder{}.set_value(json.as<::google::protobuf::uint32>()).set_valid(true).build().release());
    });
    set_proto_value(json_object, {"ct", "range", "min"}, [&](const tao::json::value& json) mutable {
        ct_range_builder.set_min(json.as<::google::protobuf::uint32>());
    });
    set_proto_value(json_object, {"ct", "range", "max"}, [&](const tao::json::value& json) mutable {
        ct_range_builder.set_max(json.as<::google::protobuf::uint32>());
    });
    set_proto_value(json_object, {"config", "username"}, [&](const tao::json::value& json) mutable {
        light_service->set_allocated_username(UserNameBuilder{}.set_value(json.as<std::string>()).build().release());
    });

    if (!ct_range_builder.is_empty()) {
        light_service->set_allocated_ctrange(ct_range_builder.build().release());
    }

    return light_service;
}