#pragma once
#include <unordered_map>
#include <functional>
#include "Character.h"
#include <string>

template <class T>
class ValuesHolder{
private:
	T h;
public:
	ValuesHolder() = default;
	ValuesHolder(const ValuesHolder& other) = delete;
	ValuesHolder(ValuesHolder& other) = delete;
	ValuesHolder& operator= (const ValuesHolder& other) = delete;
	ValuesHolder& operator= (ValuesHolder& other) = delete;
	virtual void AddValue(const char* v_name, T val) {
		h.AddValue(v_name, val);
	}
	auto FindValue(const char* v_name) {
		return h.FindValue(v_name);
	}
	virtual void ChangeValue(const char* v_name, T val) {
		h.ChangeValue(v_name, val);
	}
	virtual void DeleteValue(const char* v_name) {
		h.DeleteValue(v_name);
		m.erase(v_name);
	}
	~ValueHolder() = default;
};
class CharactersHolder;
class CharactersHolder: public ValuesHolder<CharactersHolder>{
private:
	std::map<const char*, Character> m;
public:
	void AddValue(const char* v_name, Character val) {
		m.insert(std::make_pair(v_name, val));
	}
	Character FindValue(const char* v_name) {
		return m[v_name];
	}
	void ChangeValue(const char* v_name, Character val) {
		m[v_name] = val;
	}
	void DeleteValue(const char* v_name) {
		m.erase(v_name);
	}
};
class IntHolder;
class IntHolder : public ValuesHolder<IntHolder> {
private:
	std::map<const char*, int> m;
public:
	void AddValue(const char* v_name, int val) {
		m.insert(std::make_pair(v_name, val));
	}
	int FindValue(const char* v_name) {
		return m[v_name];
	}
	void ChangeValue(const char* v_name, int val) {
		m[v_name] = val;
	}
	void DeleteValue(const char* v_name) {
		m.erase(v_name);
	}
};
class StringHolder;
class StringHolder : public ValuesHolder<StringHolder> {
private:
	std::map<const char*, std::string> m;
public:
	void AddValue(const char* v_name, std::string val) {
		m.insert(std::make_pair(v_name, val));
	}
	std::string FindValue(const char* v_name) {
		return m[v_name];
	}
	void ChangeValue(const char* v_name, std::string val) {
		m[v_name] = val;
	}
	void DeleteValue(const char* v_name) {
		m.erase(v_name);
	}
};
