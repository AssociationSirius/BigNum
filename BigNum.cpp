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

#include <iostream>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "BigNum.hpp"

template <class T> const T& max (const T& a, const T& b) {
  return (a<b)?b:a;
}

////////////////////////////////////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////////////////////////////////////
BigNum::BigNum()
{
}

BigNum::BigNum(unsigned long  x) { sign=Sign::PLUS; initFromSigned(x); }
BigNum::BigNum(unsigned int   x) { sign=Sign::PLUS; initFromSigned(x); }
BigNum::BigNum(unsigned short x) { sign=Sign::PLUS; initFromSigned(x); }
BigNum::BigNum(long  x) { initFromUnSigned(x); }
BigNum::BigNum(int   x) { initFromUnSigned(x); }
BigNum::BigNum(short x) { initFromUnSigned(x); }

BigNum::BigNum(std::string    s)
{
	std::string x = s;
	//cas du moins
	if (x[0]=='-') {
		sign = Sign::MINUS;
		x=x.substr(1, x.length()-1);
	}
	else
		sign = Sign::PLUS;

	char c;
	lastDigit= x.length()-1;
	for (int i=x.length()-1; i>=0; i--) {
		c = x[i]-'0';
		if ((c>=0) && (c<=9))
			digits[lastDigit-i] = c;
		else {
			printf("char error not a digit\n");
			digits[lastDigit-i]=0; //TODO déclanchement d'erreur
		}
	}
	normalize();
}

////////////////////////////////////////////////////////////////////////////////
// Copy constructor
////////////////////////////////////////////////////////////////////////////////
BigNum::BigNum(const BigNum &n) {
		//cas n=n;
		if (this == &n)
		return;
	this->initialize();
	this->sign=n.sign;
	this->lastDigit= n.lastDigit;
	for(unsigned int i=0; i<=n.lastDigit; i++)
		this->digits[i]=n.digits[i];
}

BigNum::BigNum(const BigNum* n) {
		//cas n=n;
		if (this == n)
		return;
	this->initialize();
	this->sign=n->sign;
	this->lastDigit= n->lastDigit;
	for(unsigned int i=0; i<=n->lastDigit; i++)
		this->digits[i]=n->digits[i];
}

////////////////////////////////////////////////////////////////////////////////
// templates
////////////////////////////////////////////////////////////////////////////////
template <class X> void BigNum::initFromSigned(X x)
{
	//only digits
	int tmpDigits =-1;
	X t = x;
	while (t!=0) {
		tmpDigits++;
		digits[tmpDigits]=t%10;
		t=t/10;
	}
	lastDigit=abs(tmpDigits);
}

template <class X> void BigNum::initFromUnSigned(X x)
{
	//signe
	if (x>0) {
		sign=Sign::PLUS;
		initFromSigned(x);
	}
	else
	if (x<0) {
		sign=Sign::MINUS;
		initFromSigned(-x);
	}
}

////////////////////////////////////////////////////////////////////////////////
// operator
////////////////////////////////////////////////////////////////////////////////
inline void BigNum::operator=(const BigNum &n) {
	this->initialize();
	this->sign=n.sign;
	this->lastDigit= n.lastDigit;
	for(unsigned int i=0; i<=n.lastDigit; i++)
		this->digits[i]=n.digits[i];
}

std::ostream & operator << (std::ostream& sortie , const BigNum & n)
{
	std::stringstream oss;
	if (n.sign==BigNum::Sign::MINUS)
		oss << "-";
	char a;
	for(int tmp=n.lastDigit; tmp>=0; tmp--) {
		a= n.digits[tmp]+'0';
		oss << a;
	}
	sortie << oss.str();
	return sortie;
}

BigNum BigNum::operator -()
{
	BigNum n(this);
	n.opp();
	return n;
}

bool BigNum::operator !=(const BigNum &n) const{
	return !operator ==(n);
}

bool BigNum::operator ==(const BigNum &n) const{
	if (this->sign != n.sign)
		return false;
	if (this->lastDigit != n.lastDigit)
		return false;
	for(unsigned int i=0; i<=n.lastDigit; i++) {
		if (this->digits[i] != n.digits[i])
			return false;
		}
	return true;
}


////////////////////////////////////////////////////////////////////////////////
// fonctions
////////////////////////////////////////////////////////////////////////////////
BigNum::CompRes BigNum::compareTo(const BigNum &n) const
{
	// Study of signs
	if (this->sign < n.sign)
		return CompRes::LESS;
	if (this->sign > n.sign)
		return CompRes::GREATER;
	// case 0=0
	if ((this->sign == Sign::NUL) && (n.sign == Sign::NUL))
		return CompRes::EQUAL;

	//study of digits (BigNums have the same sing)
	if (this->lastDigit < n.lastDigit)
		return CompRes::LESS;
	else if (this->lastDigit > n.lastDigit)
		return CompRes::GREATER;
	else {
		// Compare digits one by one
		int i = this->lastDigit+1;
		while (i > 0) {
			i--;
			if (this->digits[i] == n.digits[i])
				continue;
			else if (this->digits[i] > n.digits[i])
				return CompRes::GREATER;
			else
				return CompRes::LESS;
		}
		// If no blocks differed, the numbers are equal.
		return CompRes::EQUAL;
	}
}


void BigNum::initialize()
{
	sign=Sign::NUL;
	lastDigit=0;
	for(int i=0; i<MAX_DIGITS; i++)
		digits[i]=0;
}


void BigNum::normalize()
{
	while ((this->lastDigit > 0) && (this->digits[ this->lastDigit ] == 0))
		this->lastDigit --;

	if ((this->lastDigit == 0) && (this->digits[0] == 0))
	this->sign = Sign::NUL;
}

// printf -- obsolete --
void BigNum::print()
{
	printf("Digits:  %i\n", this->lastDigit);
	if (this->sign==Sign::MINUS)
		printf("-");
	if (this->sign==Sign::PLUS)
		printf("+");
	if (this->sign==Sign::NUL)
		printf("o");
	for(int tmp=lastDigit; tmp>=0; tmp--) {
		printf("%i", digits[tmp]);
	}
	printf("\n");
}

void BigNum::opp()
{
	if (this->sign==Sign::NUL) return;
	if (this->sign==Sign::PLUS) {this->sign=Sign::MINUS; return;}
	if (this->sign==Sign::MINUS) {this->sign=Sign::PLUS; return;}
};


void BigNum::add_pos(const BigNum &a, const BigNum &b)
{
	if (a<0) return;
	if (b<0) return;

	unsigned int max_digits= max(a.lastDigit, b.lastDigit);
	//~ printf("max digits %i\n", max_digits);
	char tmp, carry=0;

	this->sign = Sign::PLUS;
	for (unsigned int i=0; i<=max_digits; i++) {
		tmp = a.digits[i]+b.digits[i]+carry;
		if (tmp>9) {
			this->digits[i]= tmp-10;
			carry = 1;
		} else {
			this->digits[i]= tmp;
			carry = 0;
		}
	}
	//~ printf("max digits %i\n", this->digits[max_digits]);
	if (carry !=0) {
		this->digits[max_digits+1]=carry;
		this->lastDigit = max_digits+1;
	}
	else
		this->lastDigit = max_digits;
}
