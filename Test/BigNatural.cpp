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
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(65536)), "{0 1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural(65536*2)), "{0 2}");
}

auto TestBigNaturalConstructor2() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("300")), "{300}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("65535")), "{65535}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("65536")), "{0 1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural("65537")), "{1 1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("1208925819614629174706176")), "{0 0 0 0 0 1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("18446744073709551616")), "{0 0 0 0 1}");
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
		BigNatural("65535")+BigNatural("65535")), "{65534 1}");
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65535")+BigNatural("65536")), "{65535 1}");
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

auto TestBigNaturalMultiplyBySimple() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65537")*BigNatural("65537")), "{1 2 1}");	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("123456789")*BigNatural("123456789")), "{41913 38712 9762 54}");	
	WHALE_CHECK_EQUAL(BigNatural("1234567890")*BigNatural("1234567890"), BigNatural("1524157875019052100"));	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(
		BigNatural("65535")*BigNatural("65535")), "{1 65534}");	
	BigNatural num(BigNatural::FigureList({65535, 65535, 65535, 65535, 65535}));
	BigNatural num2(BigNatural::FigureList({65535, 65535, 65535, 65535, 65535, 0,0,0}));
}

auto TestBigNaturalMultiplyByKaratsuba() -> void {
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural::MultiplyByKaratsuba(
		BigNatural("2"), BigNatural("3"))), "{6}");	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural::MultiplyByKaratsuba(
		BigNatural("65537"), BigNatural("65537"))), "{1 2 1}");	
	BigNatural::MultiplyByKaratsuba(BigNatural("65537"), BigNatural("65537")).Output(std::cout);
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural::MultiplyByKaratsuba(
		BigNatural("123456789"), BigNatural("123456789"))), "{41913 38712 9762 54}");	
	WHALE_CHECK_EQUAL(BigNatural::MultiplyByKaratsuba(
		BigNatural("1234567890"), BigNatural("1234567890")), BigNatural("1524157875019052100"));	
	WHALE_CHECK_EQUAL(BigNaturalToDebugString(BigNatural::MultiplyByKaratsuba(
		BigNatural("65535"), BigNatural("65535"))), "{1 65534}");	
}

auto TestBigNaturalShiftAlittle() -> void {
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
	std::string num_str(
		"340271982247993231302280370063965608744627311251456");
	BigNatural num(num_str);
	std::ostringstream oss;
	oss << num;
	WHALE_CHECK_EQUAL(oss.str(), num_str);
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
	/*
	TestBigNaturalConstructor1();
	TestBigNaturalConstructor2();
	TestBigNaturalConstructor3();
	TestBigNaturalToByteArray();
	TestBigNaturalPlus();
	TestBigNaturalMinus();
	*/
	TestBigNaturalMultiplyBySimple();
	TestBigNaturalMultiplyByKaratsuba();
	/*
	TestBigNaturalDivide();
	TestBigNaturalShiftAlittle();
	TestBigNaturalShift();
	TestBigNaturalModulate();
	TestBigNaturalBitAnd();
	TestBigNaturalPower1();
	TestBigNaturalPower2();
	TestBigNaturalPowerModulate1();
	TestBigNaturalPowerModulate2();
	TestBigNaturalOutput();
	//TestBigNaturalInput();
	*/
	return 0;
}

#endif
