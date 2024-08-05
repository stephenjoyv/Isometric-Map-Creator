#include "Jammed.h"

Jammed::Jammed()
{
	condition = false;
	frequency = 0;
	counter = 1;
	func = []() {};
}

Jammed::Jammed(int range, float freq, function<void()> func) : Jammed()
{
	this->frequency = freq;
	this->range = range;
	this->func = func;
}

void Jammed::enable()
{
	condition = true;
}

void Jammed::disable()
{
	condition = false;
	counter = 1;
}

void Jammed::exec()
{
	if (condition==true)
	{
		if (counter > range+1) counter = 1;
		//cout << "||||FREQ = " << (int)100 * frequency << " ||||\n";
		if (counter % (int)(100 * frequency) == 0) {
			func();
		}
		//cout << "|||COUNTER = " << counter << "|||\n";
		counter++;
	}
	
}


