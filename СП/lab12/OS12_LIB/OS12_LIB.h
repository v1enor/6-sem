#pragma once

class IAdder;
class IMultiplier;

#define OS12HANDEL void*

namespace OS12_LIB
{
	OS12HANDEL Init();

	namespace Adder
	{
		double Add(OS12HANDEL, double, double);
		double Sub(OS12HANDEL, double, double);
	}

	namespace Multiplier
	{
		double Mul(OS12HANDEL, double, double);
		double Div(OS12HANDEL, double, double);
	}

	void Dispose(OS12HANDEL);
	void OutputErrorHandle(int);

	IAdder *p_adder;
	IMultiplier* p_multiplier;
}