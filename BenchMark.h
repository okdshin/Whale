#pragma once
//BenchMark:20131016
#include <iostream>
#include <ctime>
#include <string>
#include "BigNatural.h"
namespace whale
{
class BenchMark{
public:
    BenchMark(){}
    BenchMark(const BenchMark&) = delete;
    auto operator=(const BenchMark&) -> BenchMark& = delete;
    ~BenchMark(){}

private:

};


auto MultiplyBenchMark() -> void {
	std::vector<BigNatural> num_list;
	num_list.push_back(1);
	for(unsigned int i = 1; i < 10000; ++i){
		num_list.push_back(num_list.back()<<32);
		//std::cout << num_list.back() << "\n";
	}
	for(unsigned int i = 0; i < num_list.size(); ++i){
		auto start = clock();
		auto num = num_list[i]*num_list[i];
		auto end = clock();
		std::cout << i << ": " << end - start << std::endl;
		//num.Output(std::cout);
		//std::cout << num << std::endl;//.Output(std::cout);
	}
}

auto PowerBenchMark() -> void {
	std::vector<BigNatural> num_list;
	std::string num_str;
	for(unsigned int i = 0; i < 100; ++i){
		num_str = num_str + "1";
		num_list.push_back(BigNatural(num_str));
		//std::cout << num_list.back() << "\n";
	}
	BigNatural base("11");
	for(unsigned int i = 0; i < num_list.size(); ++i){
		auto start = clock();
		auto num = BigNatural::Power(base, num_list[i]);
		auto end = clock();
		std::cout << i << " " << end - start << std::endl;
		//num.Output(std::cout);
		//std::cout << num << std::endl;//.Output(std::cout);
	}
}

}

