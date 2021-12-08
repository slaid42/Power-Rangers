class ValuesHolder
{
private:

	std::map<const char*, int> int_map;

public:
	ValuesHolder(): int_map(){}

	void Add(const char* name, int value)
	{
		int_map.insert({ name, value });
	}
	int Get(const char* name)
	{
		if (int_map.find(name) != int_map.end())
		{
			return int_map.find(name)->second;
		}
		else
		{
			std::cerr << "invalid name of variable";
		}
	}

	void Change(const char* name, int value)
	{
		if (int_map.find(name) != int_map.end())
		{
			int_map.find(name)->second = value;
		}
		else
		{
			std::cerr << "invalid name of variable";
		}

	}
}; 
