#pragma once
class Options
{
private:
	char* title;
	int x, y, w, h;
	bool def;
public:
	
	Options(){}


	void Window_position(int arg1, int arg2)
	{
		x = arg1;
		y = arg2;
	}
	void Window_size(int arg1, int arg2)
	{
		w = arg1;
		h = arg2;
	}
	void Window_full_Screen(bool arg)
	{
		if (arg)
		{
			x = 0;
			y = 0;
		}
	}

	void Check_options(){}
};