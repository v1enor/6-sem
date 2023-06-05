#include <iostream>
#pragma comment(lib, "../x64/Debug/OS12_LIB.lib")
#include "OS12_LIB.h"

int main()
{
	try
	{
		OS12HANDEL h1 = OS12_LIB::Init();
		OS12HANDEL h2 = OS12_LIB::Init();

		std::cout << std::endl << "OS12_LIB::Adder::Add(h1, 2, 3) = " << OS12_LIB::Adder::Add(h1, 2, 3) << "\n";
		std::cout << "OS12_LIB::Adder::Add(h2, 2, 3) = " << OS12_LIB::Adder::Add(h2, 2, 3) << "\n";

		std::cout << "OS12_LIB::Adder::Sub(h1, 2, 3) = " << OS12_LIB::Adder::Sub(h1, 2, 3) << "\n";
		std::cout << "OS12_LIB::Adder::Sub(h2, 2, 3) = " << OS12_LIB::Adder::Sub(h2, 2, 3) << "\n";

		std::cout << "OS12_LIB::Multiplier::Mul(h1, 2, 3) = " << OS12_LIB::Multiplier::Mul(h1, 2, 3) << "\n";
		std::cout << "OS12_LIB::Multiplier::Mul(h2, 2, 3) = " << OS12_LIB::Multiplier::Mul(h2, 2, 3) << "\n";

		std::cout << "OS12_LIB::Multiplier::Div(h1, 2, 3) = " << OS12_LIB::Multiplier::Div(h1, 2, 3) << "\n";
		std::cout << "OS12_LIB::Multiplier::Div(h2, 2, 3) = " << OS12_LIB::Multiplier::Div(h2, 2, 3) << "\n";

		OS12_LIB::Dispose(h1);
		OS12_LIB::Dispose(h2);

	}
	catch (int e) { std::cout << "OS12_LIB: error = " << e << "\n"; }

}


