#include <stdio.h>

#include "transformers.h"

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
    auto ct = new my_project::lights::CT{};
    ct->set_value(60);
    ct->set_valid(true);
    auto ct_range = new my_project::lights::CTRange{};
    ct_range->set_min(0);
    ct_range->set_max(100);

    my_project::lights::LightService light_service;
    light_service.set_allocated_on(on);
    light_service.set_allocated_factoryname(factory_name);
    light_service.set_allocated_brightness(brightness);
    light_service.set_allocated_xy(xy);
    light_service.set_allocated_ct(ct);
    light_service.set_allocated_ctrange(ct_range);

    auto clip_light = transform(light_service);
    auto proto_light = transform(clip_light);
    auto clip_light_repetition = transform(*proto_light);

    std::cout << tao::json::to_string(clip_light) << std::endl;
    std::cout << tao::json::to_string(clip_light_repetition) << std::endl;

    return 0;
}