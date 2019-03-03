// manually written utilities that are common for all proto to json transformers
// these utilities must be included in your project

#pragma once

#include <vector>

#include "tao/json.hpp"

template <typename SourceType>
static inline void set_value(tao::json::value& object, const std::vector<std::string>& path, bool condition, const SourceType& data) {
    if (condition && path.size()) {
        std::vector<decltype(std::cref(object[""]))> container;
        container.emplace_back(std::cref(object));
        for (int i = 0; i < path.size(); ++i) {
            container.emplace_back(const_cast<decltype(std::ref(object).get())>(container[i].get())[path[i]]);
        }
        const_cast<decltype(std::ref(object).get())>((*container.rbegin()).get()) = data;
    }
}

template <typename SourceType>
static inline void set_array(tao::json::value& object, const std::vector<std::string>& path, bool condition, const std::vector<SourceType> data) {
    std::vector<tao::json::value> array;
    for (auto&& item : data) {
        array.emplace_back(item);
    }
    set_value(object, path, condition, array);
}

template <typename SourceType, typename Converter>
static inline void set_value(tao::json::value& object, const std::vector<std::string>& path, bool condition,
                             const SourceType& data, Converter&& converter) {
    set_value(object, path, condition, converter(data));
}

template <typename SourceType, typename Converter>
static inline void set_array(tao::json::value& object, const std::vector<std::string>& path, bool condition,
                             const std::vector<SourceType> data, Converter&& converter) {
    std::vector<tao::json::value> array;
    for (auto&& item : data) {
        array.emplace_back(converter(item));
    }
    set_value(object, path, condition, array);
}

static inline void set_proto_value(const tao::json::value& object, const std::vector<std::string>& path, std::function<void(const tao::json::value& json)> transformer) {
    auto current_node = object.find(path[0]);
    for (int i = 1; i < path.size() && current_node; ++i) {
        current_node = current_node->find(path[i]);
    }
    if (current_node) {
        transformer(*current_node);
    }
}