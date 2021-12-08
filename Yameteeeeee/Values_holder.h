#include <string>
#include <variant>
#include <map>
#include <iostream>

class Value {
private:
	std::variant<int, bool, std::string> v;
public:
	Value() = default;
	Value(std::string s) {
		if (Empty()) {
			v = s;
		}
		else {
			std::variant<int, bool, std::string> v1 = s;
			v = v1;
		}
	}
	Value(bool b) {
		if (Empty()) {
			v = b;
		}
		else {
			std::variant<int, bool, std::string> v1 = b;
			v = v1;
		}
	}
	Value(int i) {
		if (Empty()) {
			v = i;
		}
		else {
			std::variant<int, bool, std::string> v1 = i;
			v = v1;
		}
	}
	
	Value& operator=(std::string& s) {
		if (Empty()) {
			v = s;
		}
		else {
			std::variant<int, bool, std::string> v1 = s;
			v = v1;
		}
	}
	Value& operator=(bool& b) {
		if (Empty()) {
			v = b;
		}
		else {
			std::variant<int, bool, std::string> v1 = b;
			v = v1;
		}
	}
	Value& operator=(int& i) {
		if (Empty()) {
			v = i;
		}
		else {
			std::variant<int, bool, std::string> v1 = i;
			v = v1;
		}
	}
	int GetInt() {
		return std::get<int>(v);
	}
	bool GetBool() {
		return std::get<bool>(v);
	}
	std::string GetString() {
		return std::get<std::string>(v);
	}
	bool Empty() {
		int* i = std::get_if<int>(&v);
		bool* b = std::get_if<bool>(&v);
		
		std::string* s = std::get_if<std::string>(&v);
		if (i == nullptr && b == nullptr && s == nullptr) {
			return true;
		}
		else {
			
			return false;
		}

	}
};



class ValuesHolder {
private:
	std::map<const char*, Value> m;
public:
	ValuesHolder() = default;
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
};
