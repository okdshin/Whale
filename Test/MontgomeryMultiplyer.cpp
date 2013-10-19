#ifdef MONTGOMERYMULTIPLYER_UNIT_TEST
#include "../MontgomeryMultiplyer.h"
#include <iostream>
#include <boost/timer.hpp>
#include "Test.h"

using namespace whale;

int main(int argc, char* argv[])
{
	MontgomeryMultiplyer mm(BigNatural("1234567"));
	std::cout << mm << std::endl;
	//mm.Multiply(BigNatural("12"), BigNatural("3")).Output(std::cout);
	WHALE_CHECK_EQUAL(
		mm.Multiply(BigNatural("12345"), BigNatural("12345")),
		BigNatural("547284")
	);
	/*
	WHALE_CHECK_NOT_EQUAL(
		mm.Multiply(BigNatural("12345"), BigNatural("12345")),
		BigNatural("0")
	);
	*/
	//mm.Exponential(BigNatural("12345"), BigNatural("12345")).Output(std::cout);
	return 0;
}

#endif
