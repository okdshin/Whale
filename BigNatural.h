#pragma once
//BigNatural:20130710
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <cassert>
#include "FundamentalTypes.h"

namespace whale{

class BigNatural{
public:
	using BaseType = uint32_t;
	using FigureList = std::vector<BaseType>;
	//figure_list_'s begin ------------------> end
	//            lower figure            upper figure

	BigNatural(BaseType num);
	BigNatural(const BigNatural&) = default;
	auto operator=(const BigNatural&) -> BigNatural&  = default;
	
	explicit BigNatural(const FigureList& figure_list);

	explicit BigNatural(const ByteArray& byte_array);
	explicit BigNatural(const std::string& num_str);

	auto Output(std::ostream& os)const -> void;

	auto ToByteArray()const -> ByteArray;

	auto operator==(const BigNatural& right)const -> bool;
	auto operator!=(const BigNatural& right)const -> bool;
	auto operator<(const BigNatural& right)const -> bool;
	auto operator>(const BigNatural& right)const -> bool;
	auto operator>=(const BigNatural& right)const -> bool;
	auto operator<=(const BigNatural& right)const -> bool;

	auto operator+=(BigNatural right) -> BigNatural&;
	auto operator-=(BigNatural right) -> BigNatural&;
	auto operator*=(const BigNatural& right) -> BigNatural&;
	auto operator/=(const BigNatural& right) -> BigNatural&;
	auto operator%=(const BigNatural& right) -> BigNatural&;
	auto operator<<=(BaseType right) -> BigNatural&;
	auto operator>>=(BaseType right) -> BigNatural&;
	auto operator&=(BigNatural right) -> BigNatural&;
	
	auto operator+(BigNatural right)const -> BigNatural;
	auto operator-(const BigNatural& right)const -> BigNatural;
	auto operator*(BigNatural right)const -> BigNatural;
	auto operator/(const BigNatural& right)const -> BigNatural;
	auto operator%(const BigNatural& right)const -> BigNatural;
	auto operator<<(BaseType right)const -> BigNatural;
	auto operator>>(BaseType right)const -> BigNatural;
	auto operator&(BigNatural right)const -> BigNatural;

	auto MultiplyBySimple(BigNatural right) -> BigNatural&;
	auto MultiplyByKaratsuba(BigNatural right) -> BigNatural&;
	
	static auto MultiplyBySimple(BigNatural left, const BigNatural& right) -> BigNatural {
		return left.MultiplyBySimple(right);
	}

	static auto MultiplyByKaratsuba(BigNatural left, const BigNatural& right) -> BigNatural {
		return left.MultiplyByKaratsuba(right);
	}


	auto IsOdd()const -> bool;

	auto ShiftLeftAlittle(unsigned int num) -> void;	
	auto ShiftRightAlittle(unsigned int num) -> void;

	auto AppendFigureLower(BaseType append_num) -> void;
	auto AppendFigureUpper(BaseType append_num) -> void;
	
	static auto Power(BigNatural base, BigNatural exponent) -> BigNatural;

	static auto PowerModulate(BigNatural base, BigNatural exponent, const BigNatural& n) 
			-> BigNatural;
	
	static auto DivideModulate(const BigNatural& left, const BigNatural& right) 
			-> std::pair<BigNatural, BigNatural>;

	friend auto operator>>(std::istream& is, BigNatural& val) -> std::istream&;
	friend auto operator<<(std::ostream& os, BigNatural val) -> std::ostream&;

private:
	static auto DoMultiplyByKaratsuba(BaseType* a, BaseType* b, unsigned int len, BaseType* res) -> void {
		if(len <= 8){
			for(unsigned int i = 0; i < len; ++i){
				for(unsigned int j = 0; j < len; ++j){
					res[i+j] += a[i]*b[j];
				}	
			}
			return;
		}
		unsigned int half_len = len >> 1;
		BaseType* a0 = &a[0];
		BaseType* a1 = &a[half_len];
		BaseType* b0 = &b[0];
		BaseType* b1 = &b[half_len];
		BaseType* v = &res[len*5];
		BaseType* w = &res[len*5+half_len];
		for(unsigned int i = 0; i < half_len; ++i){
			v[i] = a1[i] + a0[i];
			w[i] = b1[i] + b0[i];
		}
		BaseType* x0 = &res[0];
		BaseType* x2 = &res[len];
		BaseType* x1 = &res[len*2];
		DoMultiplyByKaratsuba(a0, b0, half_len, x0);
		DoMultiplyByKaratsuba(a1, b1, half_len, x2);
		DoMultiplyByKaratsuba(v, w, half_len, x1);
		for(unsigned int i = 0; i < len; ++i){
			x1[i] -= (x0[i]+x2[i]);	
		}
		for(unsigned int i = 0; i < len; ++i){
			res[i+half_len] += x1[i];	
		}
	}

	static const BaseType BASE_NUM = 65536;
	static const BaseType BASE_BIT_NUM = 16;
	static const BaseType MAX_NUM = 65535;
	auto Normalize() -> void;

	FigureList figure_list_;
};
	
BigNatural::BigNatural(const FigureList& figure_list) : figure_list_(figure_list){
	Normalize();
}

auto operator>>(std::istream& is, BigNatural& val) -> std::istream& {
	std::string num_str;
	is >> num_str;
	val = BigNatural(num_str);
	return is;
}

auto operator<<(std::ostream& os, BigNatural val) -> std::ostream& {
	std::vector<char> dec_figure_list;
	while(val >= 10){
		auto p = BigNatural::DivideModulate(val, 10);
		val = p.first;
		dec_figure_list.push_back(p.second.figure_list_.front());
	}
	dec_figure_list.push_back(val.figure_list_.front());
	std::reverse(dec_figure_list.begin(), dec_figure_list.end());
	for(auto dec_figure : dec_figure_list){
		os << static_cast<unsigned int>(dec_figure);
	}

	return os;
}

auto BigNatural::AppendFigureLower(BaseType append_num) -> void {
	figure_list_.insert(figure_list_.begin(), append_num, 0);
}

auto BigNatural::AppendFigureUpper(BaseType append_num) -> void {	
	figure_list_.insert(figure_list_.end(), append_num, 0);
}

auto BigNatural::Normalize() -> void {
	assert(!figure_list_.empty());
	auto iter = figure_list_.end()-1; 
	while(!(*iter) && iter != figure_list_.begin()){
		--iter;
	}
	figure_list_.erase(iter+1, figure_list_.end());
	figure_list_.shrink_to_fit();
}


auto BigNatural::DivideModulate(const BigNatural& left, 
		const BigNatural& right) -> std::pair<BigNatural, BigNatural> {
	BigNatural x(right), q(0), r(0);
	for(int i = left.figure_list_.size()-1; i >= 0; --i){
		r = r*BigNatural(BASE_NUM)+left.figure_list_[i];
		BaseType smaller(0), bigger(MAX_NUM);
		if(r >= x){
			while(smaller+1 < bigger){
				BaseType mid = (smaller + bigger) >> 1;
				if(x*mid > r){
					bigger = mid;
				}
				else {
					smaller = mid;
				}
			}
			r -= x*smaller;
		}
		q.figure_list_.push_back(smaller);
	}
	std::reverse(q.figure_list_.begin(), q.figure_list_.end());
	q.Normalize();
	r.Normalize();
	return std::make_pair(q, r);
}

auto BigNatural::Power(BigNatural base, BigNatural exponent) -> BigNatural {
	BigNatural res(1);
	while(exponent > 0){
		if(exponent.IsOdd()){
			res *= base;
		}
		exponent.ShiftRightAlittle(1);
		base *= base;
	}
	return res;
}

auto BigNatural::PowerModulate(BigNatural base, 
		BigNatural exponent, const BigNatural& n) -> BigNatural {
	BigNatural res(1);
	while(exponent > 0){
		if(exponent.IsOdd()){
			res *= base;
			res %= n;
		}
		exponent.ShiftRightAlittle(1);
		base *= base;
		base %= n;
	}
	return res;
}


BigNatural::BigNatural(BaseType num) : figure_list_() {
	figure_list_.push_back(num);
	while(figure_list_.back() >= BASE_NUM){
		auto temp = figure_list_.back();
		figure_list_.back() &= MAX_NUM;
		figure_list_.push_back(temp >> BASE_BIT_NUM);
	}
}

BigNatural::BigNatural(const ByteArray& byte_array) : figure_list_() {
	assert(byte_array.size()%2 == 0);
	for(int i = byte_array.size()-1; i > 0; i -= 2){
		figure_list_.push_back(
			(static_cast<BaseType>(byte_array.at(i)) << 0)
			|(static_cast<BaseType>(byte_array.at(i-1)) << 8)
		);	
	}
	Normalize();
}

auto BigNatural::ToByteArray()const -> ByteArray {
	ByteArray res;
	for(int i = figure_list_.size()-1; i >= 0; --i){
		auto figure = figure_list_.at(i);
		res.push_back(static_cast<uint8_t>((figure >> 8) & 0xff));
		res.push_back(static_cast<uint8_t>(figure & 0xff));
	}
	return res;	
}

BigNatural::BigNatural(const std::string& num_str) : figure_list_() {
	int begin = 0;
	BigNatural dec_figure(1);
	for(int i = num_str.size()-1; i >= begin; --i){
		const char c = num_str[i]; 
		int x = c - '0';
		if(x < 0 || 9 < x){
			std::cerr << "ParseError" << num_str << std::endl;	
			exit(1);
		}
		*this += dec_figure*BigNatural(x);
		dec_figure *= 10;
	}
}

auto BigNatural::Output(std::ostream& os)const -> void {
	os << "{";
	for(unsigned int i = 0; i < figure_list_.size(); ++i){
		os << figure_list_[i];
		if(i != figure_list_.size() -1){
			os << " ";
		}
	}
	os << "}";
}

auto BigNatural::operator==(const BigNatural& right)const -> bool {
	if(figure_list_.size() != right.figure_list_.size()){
		return false;	
	}
	for(unsigned int i = 0; i < figure_list_.size(); ++i){
		if(figure_list_[i] != right.figure_list_[i]){
			return false;
		}
	}
	return true;
}

auto BigNatural::operator!=(const BigNatural& right)const -> bool {
	return !((*this) == right);
}

auto BigNatural::operator<(const BigNatural& right)const -> bool {
	if(figure_list_.size() < right.figure_list_.size()){
		return true;
	}
	if(figure_list_.size() > right.figure_list_.size()){
		return false;
	}
	for(int i = figure_list_.size()-1; i >= 0; --i){
		if(figure_list_[i] > right.figure_list_[i]){
			return false;
		}
		if(figure_list_[i] < right.figure_list_[i]){
			return true;
		}
	}
	return false;
}

auto BigNatural::operator>(const BigNatural& right)const -> bool {
	return right < (*this);	
}

auto BigNatural::operator>=(const BigNatural& right)const -> bool {
	return (*this) > right || (*this) == right;	
}

auto BigNatural::operator<=(const BigNatural& right)const -> bool {
	return (*this) < right || (*this) == right;	
}

auto BigNatural::operator-=(BigNatural right) -> BigNatural& {
	if(*this < right){
		std::swap(*this, right);
	}
	const auto size = 
		std::max(figure_list_.size(), right.figure_list_.size());
	figure_list_.resize(size);
	right.figure_list_.resize(size);
	for(unsigned int i = 0; i < size; ++i){
		if(figure_list_[i] >= right.figure_list_[i]){
			figure_list_[i] -= right.figure_list_[i];
		}
		else {
			figure_list_[i] += BASE_NUM;
			figure_list_[i] -= right.figure_list_[i];
			for(unsigned int j = i+1; j < size; ++j){
				if(figure_list_[j] != 0){
					figure_list_[j] -= 1;
					break;
				}
				else {
					figure_list_[j] = MAX_NUM;	
				}
			}
		}
	}
	Normalize();
	return *this;
}

auto BigNatural::operator+=(BigNatural right) -> BigNatural& {
	const auto size = 
		1+std::max(figure_list_.size(), right.figure_list_.size());
	figure_list_.resize(size);
	right.figure_list_.resize(size);
	int carry = 0;
	for(unsigned int i = 0; i < size; ++i){
		figure_list_[i] += right.figure_list_[i] + carry;
		if(figure_list_[i] >= BASE_NUM){
			figure_list_[i] -= BASE_NUM;
			carry = 1;	
		}
		else{
			carry = 0;	
		}
	}
	Normalize();
	return *this;
}

auto BigNatural::MultiplyBySimple(BigNatural right) -> BigNatural& {
	FigureList res(figure_list_.size()+right.figure_list_.size());//TODO?
	for(unsigned int i = 0; i < figure_list_.size(); ++i){
		BaseType carry = 0;
		for(unsigned int j = 0; j < right.figure_list_.size(); ++j){
			BaseType val = figure_list_[i]*right.figure_list_[j] + res[i+j] + carry;
			res[i+j] = val & MAX_NUM;
			carry = val >> BASE_BIT_NUM;
		}
		res[i+right.figure_list_.size()] += carry;
		assert(!res.empty());
	}
	std::swap(figure_list_, res);
	Normalize();
	return *this;
}

auto BigNatural::MultiplyByKaratsuba(BigNatural right) -> BigNatural& {
	unsigned int longer_size = 
		std::max(figure_list_.size(), right.figure_list_.size());
	unsigned int count = 0;
	while(longer_size){
		longer_size >>= 1;	
		++count;
	}
	unsigned int sq_size = 1 << count;
	figure_list_.resize(sq_size);
	right.figure_list_.resize(sq_size);
	FigureList result_figure_list(sq_size*6);

	DoMultiplyByKaratsuba(&figure_list_.front(), &right.figure_list_.front(), 
		sq_size, &result_figure_list.front());
	result_figure_list.erase(
		result_figure_list.begin()+sq_size*2+1, result_figure_list.end());
	
	result_figure_list.back() = 0;
	for(unsigned int i = 0; i < result_figure_list.size()-1; ++i){
		result_figure_list[i+1] += result_figure_list[i] >> BASE_BIT_NUM;
		result_figure_list[i] &= MAX_NUM;
	}
	std::swap(figure_list_, result_figure_list);
	Normalize();
	return *this;
}

auto BigNatural::operator*=(const BigNatural& right) -> BigNatural& {
#ifdef MULTIPLY_KARATSUBA
	return MultiplyByKaratsuba(right);
#endif
#ifdef MULTIPLY_SIMPLE
	return MultiplyBySimple(right);
#endif
	return right.figure_list_.size() < 100 || figure_list_.size() < 100 ? 
		MultiplyBySimple(right) : MultiplyByKaratsuba(right);
}

auto BigNatural::operator<<=(BaseType right) -> BigNatural& {
	BaseType append_num = right/BASE_BIT_NUM;
	right %= BASE_BIT_NUM;
	AppendFigureLower(append_num);
	ShiftLeftAlittle(right);
	return *this;
}

auto BigNatural::operator>>=(BaseType right) -> BigNatural& {
	BaseType erase_num = right/BASE_BIT_NUM;
	right %= BASE_BIT_NUM;
	if(erase_num >= figure_list_.size()){
		*this = 0;
		Normalize();
		return *this;
	}
	figure_list_.erase(figure_list_.begin(), figure_list_.begin()+erase_num);
	ShiftRightAlittle(right);
	return *this;
}

auto BigNatural::operator*(BigNatural right)const -> BigNatural {
	right *= (*this);
	return right;
}

auto BigNatural::operator+(BigNatural right)const -> BigNatural {
	right += (*this);
	return right;
}

auto BigNatural::operator-(const BigNatural& right)const -> BigNatural {
	auto temp = *this;
	temp -= right;
	return temp;
}

auto BigNatural::operator<<(BaseType right)const -> BigNatural {
	auto temp = *this;
	temp <<= right;
	return temp;
}

auto BigNatural::operator>>(BaseType right)const -> BigNatural {
	auto temp = *this;
	temp >>= right;
	return temp;
	
}

auto BigNatural::operator/=(const BigNatural& right) -> BigNatural& {
	(*this) = DivideModulate(*this, right).first;
	return *this;
}

auto BigNatural::operator%=(const BigNatural& right) -> BigNatural& {
	(*this) = DivideModulate(*this, right).second;
	return *this;
}

auto BigNatural::operator/(const BigNatural& right)const -> BigNatural {
	auto temp = *this;
	temp /= right;
	return temp;
}

auto BigNatural::operator%(const BigNatural& right)const -> BigNatural {
	auto temp = *this;
	temp %= right;
	return temp;
}

auto BigNatural::operator&=(BigNatural right) -> BigNatural& {
	if(figure_list_.size() < right.figure_list_.size()){
		right.figure_list_.resize(figure_list_.size());	
	}
	else {
		figure_list_.resize(right.figure_list_.size());	
	}
	for(unsigned int i = 0; i < figure_list_.size(); ++i){
		figure_list_[i] &= right.figure_list_[i];
	}
	return *this;
}

auto BigNatural::operator&(BigNatural right)const -> BigNatural {
	right &= *this;
	return right;
}

auto BigNatural::ShiftLeftAlittle(unsigned int num) -> void {
	AppendFigureUpper(1);
	BaseType carry = 0;
	for(unsigned int i = 0; i < figure_list_.size(); ++i){
		auto before_val = figure_list_[i];
		figure_list_[i] <<= num;
		figure_list_[i] |= carry;	
		figure_list_[i] &= MAX_NUM;	
		carry = (before_val >> (BASE_BIT_NUM-num)) & MAX_NUM; 
	}
	Normalize();
}

auto BigNatural::ShiftRightAlittle(unsigned int num) -> void {
	BaseType carry = 0;
	for(int i = figure_list_.size()-1; i >= 0; --i){
		auto before_val = figure_list_[i];
		figure_list_[i] >>= num;
		figure_list_[i] |= carry;	
		figure_list_[i] &= MAX_NUM;	
		carry = (before_val << (BASE_BIT_NUM-num)) & MAX_NUM; 	
	}
	Normalize();
}

auto BigNatural::IsOdd()const -> bool {
	return figure_list_.front() & 1;	
}


}
