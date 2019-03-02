#include <stdio.h>

#include "utilities.h"

#include "common.pb.h"
#include "lights.pb.h"

class OnBuilder {
public:
    OnBuilder& set_value(bool value) {
        _value = value;
        return* this;
    }

    std::unique_ptr<my_project::lights::On> build() {
        auto return_value = std::make_unique<my_project::lights::On>();
        return_value->set_value(_value);
        return return_value;
    }
private:
    bool _value;
};

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

template<typename ProtoType, typename Setter>
void set_value(ProtoType&& proto_object, Setter&& setter, tao::json::value& object, const std::vector<std::string>& path) {
    for (auto&& item : path) {

    }
}

std::unique_ptr<my_project::lights::LightService> transform(tao::json::value& object) {
    auto light_service = std::make_unique<my_project::lights::LightService>();
    set_value(light_service, &my_project::lights::LightService::set_allocated_on, object, {"on", "on"});
    return light_service;
}

int main() {
    auto factory_name = new my_project::lights::FactoryName{};
    factory_name->set_value("my_name");
    auto on = new my_project::lights::On{};
    on->set_value(true);
    auto brightness = new my_project::lights::Brightness{};
    brightness->set_value(32);
    auto xy = new my_project::lights::XY{};
    xy->set_x(10.8);
    xy->set_y(7.1);
    xy->set_valid(true);

    my_project::lights::LightService light_service;
    light_service.set_allocated_on(on);
    light_service.set_allocated_factoryname(factory_name);
    light_service.set_allocated_brightness(brightness);
    light_service.set_allocated_xy(xy);

    auto clip_light = transform(light_service);
    auto proto_light = transform(clip_light);
    auto clip_light_repetition = transform(*proto_light);

    std::cout << tao::json::to_string(clip_light) << std::endl;
//    std::cout << tao::json::to_string(clip_light_repetition) << std::endl;

    return 0;
}