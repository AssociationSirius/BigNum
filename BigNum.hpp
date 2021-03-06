/*
 * Pedagogical BigNum 
 * 
 * Copyright 2017 olivier <olivier@asso-sirius.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
 
#ifndef _BIG_NUM_HPP_
#define _BIG_NUM_HPP_

#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#define MAX_DIGITS 1000

class BigNum
{
public:
	BigNum();
	// Constructors from primitive integer types
	BigNum(unsigned long  x);
	BigNum(unsigned int   x);
	BigNum(unsigned short x);
	BigNum(long  x);
	BigNum(int   x);
	BigNum(short x);
	BigNum(std::string s);

	// Copy constructor
	BigNum(const BigNum &n);
	BigNum(const BigNum* n);

	// Assignment operator
	void operator=(const BigNum &x);
	BigNum operator -() const;

	// Ordinary comparison operators
	bool operator ==(const BigNum &n) const;
	bool operator !=(const BigNum &n) const;
	bool operator < (const BigNum &n) const { return compareTo(n) == CompRes::LESS; }
	bool operator <=(const BigNum &n) const { return compareTo(n) != CompRes::GREATER; }
	bool operator >=(const BigNum &n) const { return compareTo(n) != CompRes::LESS; }
	bool operator > (const BigNum &n) const { return compareTo(n) == CompRes::GREATER; }

	// Normal operator
	BigNum operator +(const BigNum &x) const;
	BigNum operator -(const BigNum &x) const;
	BigNum operator *(const BigNum &x) const;
	BigNum operator /(const BigNum &x) const;
	BigNum operator %(const BigNum &x) const;

	void operator +=(const BigNum &x);
	void operator -=(const BigNum &x);
	void operator *=(const BigNum &x);

	void operator ++();
	void operator --();
	void operator ++(int);
	void operator --(int);


	//ostream
	friend std::ostream & operator << (std::ostream& sortie , const BigNum & n);
	void print();

	// functions
	void opp();
	void add(const BigNum &a, const BigNum &b);
	void sou(const BigNum &a, const BigNum &b);
	void mul(const BigNum &n, const BigNum &b);
	void div(const BigNum &_a, const BigNum &_b, BigNum &r);

	void mulByChar(const BigNum &n, const char a);
	void digitShift(int d);
private:
	//Enums Sign
	enum class Sign : char { NUL = 0, PLUS = 1, MINUS = -1 };

	// Enums Results of comparisons
	enum class CompRes : char { LESS = -1, EQUAL = 0, GREATER = 1 };

	void initialize();
	void normalize();
	void copy(const BigNum &n);
	void absolute(const BigNum &n);
	void add_pos(const BigNum &a, const BigNum &b);
	void sou_pos(const BigNum &a, const BigNum &b);
	BigNum::CompRes absCompareTo(const BigNum &n) const;
	template <class X> void initFromSigned (X x);
	template <class X> void initFromUnSigned (X x);
	char digits[MAX_DIGITS]={0};
	Sign sign=Sign::NUL;
	unsigned int lastDigit=0;
	CompRes compareTo(const BigNum &n) const;
};

#endif //_BIG_NUM_HPP_
