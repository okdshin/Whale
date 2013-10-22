#ifdef BIGNATURAL_UNIT_TEST
#include "../BigNatural.h"
#include <iostream>
#include <sstream>
#include "Test.h"

using namespace whale;

auto BigNaturalToDebugString(const BigNatural& target) -> std::string {
	std::ostringstream oss;
	target.Output(oss);
	oss << std::flush;
	return oss.str();
}

auto TestBigNaturalConstructor1() -> void {
	WHALE_CHECK_EQUAL(BigNatural(300), 300);
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(65535)), "{65535}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(65536)), "{1 0}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(65536*2)), "{2 0}");
}

auto TestBigNaturalConstructor2() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("300")), "{300}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("65535")), "{65535}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("65536")), "{1 0}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("65537")), "{1 1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("1208925819614629174706176")), "{1 0 0 0 0 0}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("18446744073709551616")), "{1 0 0 0 0}");
	/*
	for(unsigned int i = 0; i < 4294967296; ++i){
		std::ostringstream oss;
		oss << i;
		std::cout << oss.str() << std::endl;
		if(BigNatural(oss.str()) != BigNatural(i)){
			std::cout << "error: " << i << std::endl;	
			break;
		}
	}
	*/
}

auto TestBigNaturalConstructor3() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(ByteArray({0x00, 0x01}))), "{1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(ByteArray({0xff, 0xff}))), "{65535}");
}

auto TestBigNaturalToByteArray() -> void {
	WHALE_CHECK_EQUAL(BigNatural("1").ToByteArray(), 
		ByteArray({0x00, 0x01}));
	WHALE_CHECK_EQUAL(BigNatural("65535").ToByteArray(), 
		ByteArray({0xff, 0xff}));
	WHALE_CHECK_EQUAL(BigNatural(65536+65535).ToByteArray(), 
		ByteArray({0x00, 0x01, 0xff, 0xff}));
}

auto TestBigNaturalPlus() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("300")+BigNatural("20")), "{320}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65535")+BigNatural("65535")), "{1 65534}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65535")+BigNatural("65536")), "{1 65535}");
}

auto TestBigNaturalMinus() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("300")-BigNatural("20")), "{280}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65535")-BigNatural("65535")), "{0}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65536")-BigNatural("65535")), "{1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65537")-BigNatural("2")), "{65535}");
}

auto TestBigNaturalMultiply() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65537")*BigNatural("65537")), "{1 2 1}");	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("123456789")*BigNatural("123456789")), "{54 9762 38712 41913}");	
	WHALE_CHECK_EQUAL(BigNatural("1234567890")*BigNatural("1234567890"), BigNatural("1524157875019052100"));	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65535")*BigNatural("65535")), "{65534 1}");	
	BigNatural num(BigNatural::FigureList(2, 65535));
	//num.Output(std::cout);
	std::cout << BigNatural::MultiplyBySimple(num, num) << std::endl;
	std::cout << BigNatural::MultiplyByFft(num, num) << std::endl;
	//(BigNatural("1")*BigNatural("100000000000000")).Output(std::cout);	
	/*
	BigNatural("67890123456");
	BigNatural("59999999999");
	BigNatural("39999999999");
	BigNatural("11111111112");
	*/
	/*
	BigNatural num(1);
	for(unsigned int i = 0; i < 100000; ++i){
		//std::cout << num << std::endl;
		num *= 10;
		//num.Output(std::cout<<"aaaaa:");
		//std::cout << "::" << num << std::endl;
		//(BigNatural(1)*num).Output(std::cout<<"bbbbb:");
		//std::cout << "::" << BigNatural(1)*num << std::endl;
		//std::cout << "\n";
		std::cout << i << std::endl;
		assert(num == BigNatural(1)*num);
	}
	//num.Output(std::cout);
	//std::cout << "::" << num << std::endl;
	//(BigNatural("3")*num).Output(std::cout);
	//std::cout << "::" << BigNatural(3)*num << std::endl;
	*/
	/*
	auto num = BigNatural(BigNatural::FigureList({32768, 42182, 36222, 3}));
	num.Output(std::cout);
	std::cout << num << std::endl;
	auto multiplied = BigNatural(1)*num;
	multiplied.Output(std::cout);
	std::cout << multiplied << std::endl;
	*/
}

auto TestBigNaturalShiftAlttle() -> void {
	BigNatural num = BigNatural("65535");
	num.ShiftLeftAlittle(2);
	WHALE_CHECK_EQUAL(num, BigNatural("65535")*4);	
}

auto TestBigNaturalShift() -> void {
	WHALE_CHECK_EQUAL(BigNatural("123") << 1, BigNatural("246"));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 0, BigNatural("1234567890123"));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 1, BigNatural("1234567890123")*2);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 2, BigNatural("1234567890123")*4);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 3, BigNatural("1234567890123")*8);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 4, BigNatural("1234567890123")*16);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 5, BigNatural("1234567890123")*32);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 6, BigNatural("1234567890123")*64);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 7, BigNatural("1234567890123")*128);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 8, BigNatural("1234567890123")*256);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 9, BigNatural("1234567890123")*512);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 10, BigNatural("1234567890123")*1024);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 11, BigNatural("1234567890123")*2048);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 12, BigNatural("1234567890123")*4096);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 15, BigNatural("1234567890123")*32768);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 16, BigNatural("1234567890123")*65536);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") << 17, BigNatural("1234567890123")*65536*2);
	
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 0, BigNatural("1234567890123"));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 1, BigNatural("1234567890123")/2);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 2, BigNatural("1234567890123")/4);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 3, BigNatural("1234567890123")/8);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 4, BigNatural("1234567890123")/16);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 5, BigNatural("1234567890123")/32);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 6, BigNatural("1234567890123")/64);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 7, BigNatural("1234567890123")/128);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 8, BigNatural("1234567890123")/256);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 9, BigNatural("1234567890123")/512);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 10, BigNatural("1234567890123")/1024);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 11, BigNatural("1234567890123")/2048);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 12, BigNatural("1234567890123")/4096);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 13, BigNatural("1234567890123")/8192);
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 14, BigNatural("1234567890123")/(8192*2));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 15, BigNatural("1234567890123")/(8192*4));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 16, BigNatural("1234567890123")/(8192*8));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 17, BigNatural("1234567890123")/(8192*16));
	WHALE_CHECK_EQUAL(BigNatural("1234567890123") >> 18, BigNatural("1234567890123")/(8192*32));
}

auto TestBigNaturalDivide() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("10")/BigNatural("3")), "{3}");	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("123456789")/BigNatural("1234567")), "{100}");	
}

auto TestBigNaturalModulate() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("10")%BigNatural("3")), "{1}");	
}

auto TestBigNaturalBitAnd() -> void {
	//WHALE_CHECK_EQUAL(BigNatural(1)&BigNatural(2), BigNatural(0));	
	//WHALE_CHECK_EQUAL(BigNatural(3)&BigNatural(1), BigNatural(1));	
}

auto TestBigNaturalPower1() -> void {
	WHALE_CHECK_EQUAL(
		BigNatural::Power(BigNatural("123456789"), 3), 
		BigNatural("1881676371789154860897069"));	
}

auto TestBigNaturalPower2() -> void {
	/*
	WHALE_CHECK_EQUAL(
		BigNatural::Power(BigNatural("123456"), BigNatural("123456")), 
		BigNatural("1881676371789154860897069"));	
	*/
	//BigNatural::Power(BigNatural("123456"), BigNatural("123456")), 
}

auto TestBigNaturalPowerModulate1() -> void {
	WHALE_CHECK_EQUAL(
		BigNatural::PowerModulate(BigNatural("123456789"), 3, 1234), 
		BigNatural("817"));	
}

auto TestBigNaturalPowerModulate2() -> void {
	WHALE_CHECK_EQUAL(
		BigNatural::PowerModulate(BigNatural("1234567"), BigNatural("1234567"), BigNatural("123456789")), 
		BigNatural("46006624"));	
}

auto TestBigNaturalOutput() -> void {
	std::cout << BigNatural("12345678910") << std::endl;
	std::cout << BigNatural("1000000000") << std::endl;
	std::cout << BigNatural("30")+BigNatural("300") << std::endl;
	std::cout << BigNatural("30")-BigNatural("300") << std::endl;	
}

auto TestBigNaturalInput() -> void {
	std::istringstream iss("12345");
	BigNatural num(0);
	iss >> num;
	std::cout << num;
}

auto TestBigNaturalAppendFigure() -> void {
	auto num = BigNatural("12345");
	num.Output(std::cout);
	std::cout << num << std::endl;
	num.AppendFigureLower(1);
	num.Output(std::cout);
	std::cout << num << std::endl;
	num.AppendFigureUpper(2);
	num.Output(std::cout);
	std::cout << num << std::endl;	
}

int main(int argc, char* argv[])
{
	TestBigNaturalConstructor1();
	TestBigNaturalConstructor2();
	TestBigNaturalConstructor3();
	TestBigNaturalToByteArray();
	TestBigNaturalPlus();
	TestBigNaturalMinus();
	TestBigNaturalMultiply();
	TestBigNaturalDivide();
	//TestBigNaturalShiftAlittle();
	TestBigNaturalShift();
	TestBigNaturalModulate();
	//TestBigNaturalBitAnd();
	TestBigNaturalPower1();
	//TestBigNaturalPower2();
	TestBigNaturalPowerModulate1();
	TestBigNaturalPowerModulate2();
	TestBigNaturalOutput();
	//TestBigNaturalInput();
	return 0;
}

#endif
