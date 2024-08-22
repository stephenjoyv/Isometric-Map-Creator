#pragma once
#include "Libs.h"
using namespace std;
class Jammed {
private :
	bool condition;
	float frequency;
	int range,
		counter;
	function<void()> func;
public:
	Jammed();
	Jammed(int range , float freq,function<void()> func);
	void enable();
	void disable();
	void exec();

	//~Jammed();
};