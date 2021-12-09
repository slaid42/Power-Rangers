#pragma once
#include <unordered_map>
#include <string>
#include <variant>
#include <map>
#include <fstream>


class Value {
private:
	std::variant<int, std::string> v;
	std::string value_type;
public:
	Value() = default;
	Value(std::string s) {
		if (Empty()) {
			v = s;
			
		}
		else {
			std::variant<int, std::string> v1 = s;
			v = v1;
		}
		value_type = "string";
	}
	Value(int i) {
		if (Empty()) {
			v = i;

		}
		else {
			std::variant<int, std::string> v1 = i;
			v = v1;
		}
		value_type = "int";
	}

	Value& operator=(std::string& s) {
		if (Empty()) {
			v = s;
		}
		else {
			std::variant<int, std::string> v1 = s;
			v = v1;
		}
	}
	Value& operator=(int& i) {
		if (Empty()) {
			v = i;
		}
		else {
			std::variant<int, std::string> v1 = i;
			v = v1;
		}
	}
	int GetInt() {
		return std::get<int>(v);
	}
	std::string GetString() {
		return std::get<std::string>(v);
	}
	bool Empty() {
		int* i = std::get_if<int>(&v);
		std::string* s = std::get_if<std::string>(&v);
		if (i == nullptr && s == nullptr) {
			return true;
		}
		else {

			return false;
		}

	}
	std::string Type() {
		return value_type;
	}
};



class ValuesHolder {
private:
	std::map<const char*, Value> m;
	const char* directive;
public:
	ValuesHolder(const char* _directive) {
		directive = _directive;
		Read();
	};
	ValuesHolder(const ValuesHolder& other) = delete;
	ValuesHolder(ValuesHolder& other) = delete;
	ValuesHolder& operator= (const ValuesHolder& other) = delete;
	ValuesHolder& operator= (ValuesHolder& other) = delete;
	void AddValue(const char* v_name, Value val) {
		m.insert(std::make_pair(v_name, val));

	}
	Value FindValue(const char* v_name) {
		return m[v_name];
	}
	void ChangeValue(const char* v_name, Value val) {
		m[v_name] = val;
	}
	void DeleteValue(const char* v_name) {
		m.erase(v_name);
	}
	void Read() {
		std::ifstream in(directive); // окрываем файл для чтения
		std::string name;
		std::string val;
		std::string indicator;
		while (in >> indicator >> name >> val)
		{	
			if (indicator == "int") {
				const char* v_name = name.c_str();
				int value = stoi(val);
				Value _value(value);
				m.insert(std::make_pair(v_name, _value));
			}
			if (indicator == "string") {
				const char* v_name = name.c_str();
				Value _value(val);
				m.insert(std::make_pair(v_name, _value));
			}
		}
		in.close();
	}
	void Write() {
		std::ofstream out(directive);
		if (out.is_open())
		{
			out << "Welcome to CPP" << std::endl;
		}

		for (auto i = m.begin(); i != m.end(); ++i) {
			if (((*i).second).Type() == "int") {
				out << "int" << " " << (*i).first << " " << ((*i).second).GetInt() << std::endl;
			}
			if (((*i).second).Type() == "string") {
				out << "string" << " " << (*i).first << " " << ((*i).second).GetString() << std::endl;
			}
		}
		out.close();
	}
};
