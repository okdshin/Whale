#pragma once
//BenchMark:20131016
#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
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

auto MultiplyBenchmark2(int bit_size) -> void {
	srand(time(NULL));

	BigNatural::FigureList fl1(static_cast<unsigned int>(ceil(bit_size/16.0)));
	for(auto& f : fl1){
		f = rand()&65535;
	}
	BigNatural num1(fl1);

	BigNatural::FigureList fl2(static_cast<unsigned int>(ceil(bit_size/16.0)));
	for(auto& f : fl2){
		f = rand()&65535;
	}
	BigNatural num2(fl2);
	//num1.Output(std::cout);
	{
		auto start = clock();
		for(unsigned int i = 0; i < 10000; ++i){
			auto num = BigNatural::MultiplyBySimple(num1, num2);
		}
		auto end = clock();
		std::cout << "simp: " << end - start << std::endl;
	}
	{
		auto start = clock();
		for(unsigned int i = 0; i < 10000; ++i){
			auto num = BigNatural::MultiplyByKaratsuba(num1, num2);
		}
		auto end = clock();
		std::cout << "kara: " << end - start << std::endl;
	}
}

auto MultiplyBenchMark() -> void {
	std::vector<BigNatural> num_list;
	for(int i = 0; i < 20; ++i){
		num_list.push_back((BigNatural(2) << i*5000) -1);
	}
	for(unsigned int i = 0; i < num_list.size(); ++i){
		auto start = clock();
		for(unsigned int j = 0; j < 100; ++j){
			auto num = BigNatural::MultiplyByKaratsuba(BigNatural("12345678"), num_list[i]);
			//auto num = BigNatural::MultiplyBySimple(BigNatural("12345678"), num_list[i]);
		}
		auto end = clock();
		std::cout<< (i*500+1) << " " << end - start << std::endl;
	}
}

auto MultiplyCheck() -> void {
	std::vector<BigNatural> num_list;
	for(int i = 100000; i >= 0; --i){
		num_list.push_back(BigNatural(i));
	}
	for(unsigned int i = 0; i < num_list.size(); ++i){
		for(unsigned int j = 0; j < num_list.size(); ++j){
			auto num = BigNatural::MultiplyByKaratsuba(num_list[i], num_list[j]);
			std::cout << num_list[i] << " * " << num_list[j] << std::endl;
			if(num != BigNatural::MultiplyBySimple(num_list[i], num_list[j])){
				std::cout << "ERROR" << std::endl;
				break;
			}
		}
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

