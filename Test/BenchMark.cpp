#ifdef BENCHMARK_UNIT_TEST
#include "../BenchMark.h"
#include <iostream>
using namespace whale;

int main(int argc, char* argv[])
{
	for(unsigned int i = 16; i < 4096; i+=500){
		MultiplyBenchmark2(i);
	}
	//MultiplyCheck();
	//MultiplyBenchMark();
	/*
	{
	BigNatural num("18446462594437808126728384");
	std::cout << num << std::endl;
	std::cout << (BigNatural::MultiplyBySimple(num, num) == BigNatural::MultiplyByKaratsuba(num, num)) << std::endl;
	std::cout << BigNatural::MultiplyBySimple(num, num) << std::endl;
	std::cout << BigNatural::MultiplyByKaratsuba(num, num) << std::endl;
	std::cout << "340271982247993231302280370063965608744627311251456" << std::endl;
	BigNatural::MultiplyByKaratsuba(num, num).Output(std::cout);
	std::cout << "\n";
	auto collect_ans = BigNatural("340271982247993231302280370063965608744627311251456");
	collect_ans.Output(std::cout);
	std::cout << "\n";
	std::cout << collect_ans << std::endl;
	std::cout << "\n";
	}
	//PowerBenchMark();
	{
	BigNatural num("1844646259");
	std::cout << num << std::endl;
	std::cout << (BigNatural::MultiplyBySimple(num, num) == BigNatural::MultiplyByKaratsuba(num, num)) << std::endl;
	std::cout << BigNatural::MultiplyBySimple(num, num) << std::endl;
	std::cout << BigNatural::MultiplyByKaratsuba(num, num) << std::endl;
	}
	*/
    return 0;
}

#endif
