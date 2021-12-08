#pragma once
#include <iostream>
#include <string>
#include <map>

template <class T>
class ValuesHolder {
private:
    map<const char*, T> m;
public:
	ValuesHolder() = default;
	ValuesHolder(const ValuesHolder& other) = delete;
	ValuesHolder(ValuesHolder& other) = delete;
	ValuesHolder& operator= (const ValuesHolder& other) = delete;
	ValuesHolder& operator= (ValuesHolder& other) = delete;
	virtual void AddValue(const char* v_name, T val) {
        m.insert(std::make_pair(v_name, val));
	}
	T FindValue(const char* v_name) {
        return m[v_name];
	}
	virtual void ChangeValue(const char* v_name, T val) {
        m[v_name] = val;
	}
	virtual void DeleteValue(const char* v_name) {
        m.erase(v_name);
	}
};

