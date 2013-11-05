#pragma once
//BenchMark:20131016
#include <iostream>
#include <ctime>
#include <string>
#define MULTIPLY_SIMPLE
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
	for(int i = 0; i < 20; ++i){
		num_list.push_back((BigNatural(2) << i*500) -1);
	}
	for(unsigned int i = 0; i < num_list.size(); ++i){
		auto start = clock();
		for(unsigned int j = 0; j < 1; ++j){
			//auto num = BigNatural::MultiplyByKaratsuba(BigNatural("12345678"), num_list[i]);
			auto num = BigNatural::MultiplyBySimple(BigNatural("12345678"), num_list[i]);
		}
		auto end = clock();
		std::cout<< (i*500+1) << " " << end - start << std::endl;
	}
}

auto MultiplyCheck() -> void {
	std::vector<BigNatural> num_list;
	for(unsigned int i = 1; i < 100000; ++i){
		num_list.push_back(BigNatural(i)<<64);
	}
	for(unsigned int i = 0; i < num_list.size(); ++i){
		auto start = clock();
		auto num = BigNatural::MultiplyByKaratsuba(num_list[i]+1, num_list[i]);
		auto end = clock();
		if(num != BigNatural::MultiplyBySimple(num_list[i]+1, num_list[i])){
			std::cout << "ERROR" << std::endl;
			break;
		}
		std::cout << num_list[i] << "**2:" << num;//.Output(std::cout);
		std::cout<< "clock:" << end - start << std::endl;
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

