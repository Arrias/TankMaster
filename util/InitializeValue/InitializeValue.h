#pragma once

template<class T>
struct InitializeValue {
    T value;
    int wasInitialized = false;

    InitializeValue &operator=(T new_value) {
        value = new_value;
        wasInitialized = true;
        return *this;
    }

    bool operator==(const InitializeValue<T> &oth) const {
        return oth.value == value;
    }
};