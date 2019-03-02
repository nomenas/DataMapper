#pragma once

#include <vector>

#include "tao/json.hpp"

// these utilities are common for all proto to json converters

template <typename JSONType>
static JSONType&& get_node(JSONType&& object, const std::vector<std::string>& path, int index) {
    if (index < path.size()) {
        return get_node(object[path[index]], path, index + 1);
    } else {
        return object;
    }
}

template <typename SourceType>
static inline void set_value(tao::json::value& object, const std::vector<std::string>& path, bool condition, const SourceType& data) {
    if (condition && path.size()) {
        get_node(object, path, 0) = data;
    }
}

template <typename SourceType>
static inline void set_array(tao::json::value& object, const std::vector<std::string>& path, bool condition, const std::vector<SourceType> data) {
    if (condition && path.size()) {
        std::vector<tao::json::value> array;
        for (auto&& item : data) {
            array.emplace_back(item);
        }
        get_node(object, path, 0) = array;
    }
}

template <typename SourceType, typename Converter>
static inline void set_value(tao::json::value& object, const std::vector<std::string>& path, bool condition,
                             const SourceType& data, Converter&& converter) {
    if (condition && path.size()) {
        get_node(object, path, 0) = converter(data);
    }
}

template <typename SourceType, typename Converter>
static inline void set_array(tao::json::value& object, const std::vector<std::string>& path, bool condition,
                             const std::vector<SourceType> data, Converter&& converter) {
    if (condition && path.size()) {
        std::vector<tao::json::value> array;
        for (auto&& item : data) {
            array.emplace_back(converter(item));
        }
        get_node(object, path, 0) = array;
    }
}