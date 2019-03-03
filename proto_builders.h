// These builders should be generated from proto files (check if there are existing tools for that)

#pragma once

#include <boost/optional.hpp>

#include "lights.pb.h"

class OnBuilder {
public:
    OnBuilder& set_value(bool value) {
        _value = value;
        return *this;
    }

    std::unique_ptr<my_project::lights::On> build() const {
        auto return_value = std::make_unique<my_project::lights::On>();
        if (_value) {
            return_value->set_value(*_value);
        }
        return return_value;
    }
private:
    boost::optional<bool> _value;
};

class FactoryNameBuilder {
public:
    FactoryNameBuilder& set_value(std::string value) {
        _value = std::move(value);
        return *this;
    }

    std::unique_ptr<my_project::lights::FactoryName> build() const {
        auto return_value = std::make_unique<my_project::lights::FactoryName>();
        if (_value) {
            return_value->set_value(*_value);
        }
        return return_value;
    }
private:
    boost::optional<std::string> _value;
};

class BrightnessBuilder {
public:
    BrightnessBuilder& set_value(::google::protobuf::uint32 value) {
        _value = value;
        return *this;
    }

    std::unique_ptr<my_project::lights::Brightness> build() const {
        auto return_value = std::make_unique<my_project::lights::Brightness>();
        if (_value) {
            return_value->set_value(*_value);
        }
        return return_value;
    }
private:
    boost::optional<::google::protobuf::uint32> _value;
};

class XYBuilder {
public:
    XYBuilder& set_x(float x) {
        _x = x;
        return *this;
    }

    XYBuilder& set_y(float y) {
        _y = y;
        return *this;
    }

    XYBuilder& set_valid(bool valid) {
        _valid = valid;
        return *this;
    }

    std::unique_ptr<my_project::lights::XY> build() const {
        auto return_value = std::make_unique<my_project::lights::XY>();
        if (_x) {
            return_value->set_x(*_x);
        }
        if (_y) {
            return_value->set_y(*_y);
        }
        if (_valid) {
            return_value->set_valid(*_valid);
        }
        return return_value;
    }
private:
    boost::optional<float> _x;
    boost::optional<float> _y;
    boost::optional<bool> _valid;
};

class CTBuilder {
public:
    CTBuilder& set_value(::google::protobuf::uint32 value) {
        _value = value;
        return *this;
    }

    CTBuilder& set_valid(bool valid) {
        _valid = valid;
        return *this;
    }

    std::unique_ptr<my_project::lights::CT> build() const {
        auto return_value = std::make_unique<my_project::lights::CT>();
        if (_value) {
            return_value->set_value(*_value);
        }
        if (_valid) {
            return_value->set_valid(*_valid);
        }
        return return_value;
    }
private:
    boost::optional<::google::protobuf::uint32> _value;
    boost::optional<bool> _valid;
};

class UserNameBuilder {
public:
    UserNameBuilder& set_value(std::string value) {
        _value = std::move(value);
        return *this;
    }

    std::unique_ptr<my_project::lights::UserName> build() const {
        auto return_value = std::make_unique<my_project::lights::UserName>();
        if (_value) {
            return_value->set_value(*_value);
        }
        return return_value;
    }
private:
    boost::optional<std::string> _value;
};

class CTRangeBuilder {
public:
    CTRangeBuilder& set_min(::google::protobuf::uint32 min) {
        _min = min;
        return *this;
    }

    CTRangeBuilder& set_max(::google::protobuf::uint32 max) {
        _max = max;
        return *this;
    }

    std::unique_ptr<my_project::lights::CTRange> build() const {
        auto return_value = std::make_unique<my_project::lights::CTRange>();
        if (_min) {
            return_value->set_min(*_min);
        }
        if (_max) {
            return_value->set_max(*_max);
        }
        return return_value;
    }

    bool is_empty() {
        return !_min || !_max;
    }
private:
    boost::optional<::google::protobuf::uint32> _min;
    boost::optional<::google::protobuf::uint32> _max;
};