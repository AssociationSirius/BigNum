/*
 * Pedagogical bigNum 
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

#define MAX_DIGITS 1000

//Enums Sign
enum class Sign : char { NUL = 0, PLUS = 1, MINUS = -1 };

// Enums Results of comparisons
enum class CompRes : char { LESS = -1, EQUAL = 0, GREATER = 1 };


class BigNum
{
public:
	BigNum();
	// Constructors from primitive integer types
	BigNum(unsigned long  x);
	BigNum(unsigned int   x);
	BigNum(unsigned short x);
	BigNum(         long  x);
	BigNum(         int   x);
	BigNum(         short x);
	BigNum(std::string    s);

	// Copy constructor
	BigNum(const BigNum &n);
	BigNum(const BigNum* n);

	// Assignment operator
	void operator=(const BigNum &x);

	// Ordinary comparison operators
	bool operator ==(const BigNum &x) const;
	bool operator !=(const BigNum &x) const;
	bool operator < (const BigNum &x) const { return compareTo(x) == CompRes::LESS; }
	bool operator <=(const BigNum &x) const { return compareTo(x) != CompRes::GREATER; }
	bool operator >=(const BigNum &x) const { return compareTo(x) != CompRes::LESS; }
	bool operator > (const BigNum &x) const { return compareTo(x) == CompRes::GREATER; }

	friend std::ostream & operator << (std::ostream& sortie , const BigNum & n);
	void print();
private:
	void initialize();
	template <class X> void initFromSignedPrimitive (X x);
	template <class X> void initFromUnSignedPrimitive (X x);
	char digits[MAX_DIGITS]={0};
	Sign sign;
	unsigned int lastDigit;
	CompRes compareTo(const BigNum &n) const;
};

// Constructor

BigNum::BigNum()
{
	sign=Sign::NUL;
	lastDigit=0;
}

BigNum::BigNum(unsigned long  x) { sign=Sign::PLUS; initFromSignedPrimitive(x); }
BigNum::BigNum(unsigned int   x) { sign=Sign::PLUS; initFromSignedPrimitive(x); }
BigNum::BigNum(unsigned short x) { sign=Sign::PLUS; initFromSignedPrimitive(x); }
BigNum::BigNum(         long  x) { initFromUnSignedPrimitive(x); }
BigNum::BigNum(         int   x) { initFromUnSignedPrimitive(x); }
BigNum::BigNum(         short x) { initFromUnSignedPrimitive(x); }

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
			printf("error charactere\n");
			digits[lastDigit-i]=0; //TODO déclanchement d'erreur
		}
	}
}


// Copy constructor
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

// Copy constructor
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


// Assignment operator
inline void BigNum::operator=(const BigNum &n) {
	this->initialize();
	this->sign=n.sign;
	this->lastDigit= n.lastDigit;
	for(unsigned int i=0; i<=n.lastDigit; i++)
		this->digits[i]=n.digits[i];
}


// templates

template <class X> void BigNum::initFromSignedPrimitive (X x)
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

template <class X> void BigNum::initFromUnSignedPrimitive (X x)
{
	//signe
	if (x>0) {
		sign=Sign::PLUS;
		initFromSignedPrimitive(x);
	}
	else
	if (x<0) {
		sign=Sign::MINUS;
		initFromSignedPrimitive(-x);
	}
}


// operator <<
std::ostream & operator << (std::ostream& sortie , const BigNum & n)
{
	std::stringstream oss;
	if (n.sign==Sign::MINUS)
		oss << "-";
	char a;
	for(int tmp=n.lastDigit; tmp>=0; tmp--) {
		a= n.digits[tmp]+'0';
		oss << a;
	}
	sortie << oss.str();
	return sortie;
}

// fonctions

CompRes BigNum::compareTo(const BigNum &n) const
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


// printf -- obsolete --
void BigNum::print()
{
	if (this->sign==Sign::MINUS)
		printf("-");
	for(int tmp=lastDigit; tmp>=0; tmp--) {
		printf("%i", digits[tmp]);
	}
	printf("\n");
}


int main(int argc, char **argv)
{
	//~ printf("Size of BigNum : %lu\n", sizeof(BigNum));

	//~ // empty constructor
	//~ BigNum test1;
	//~ test1.print();

	//~ // constructor with 1 digit
	//~ BigNum test2(6);
	//~ test2.print();

	//~ // constructorwith  more digits
	//~ BigNum test3(175846);
	//~ test3.print();

	//~ // Test negative number
	//~ int i=-57;
	//~ BigNum test4(i);
	//~ test4.print();

	//~ int j= -564879564;
	//~ BigNum test5(j);
	//~ test5.print();
	//~ std::cout << test5 << std::endl;

	//~ long k = 978564879564;
	//~ BigNum test6(k);
	//~ test6.print();

	//~ int kk = -34;
	//~ BigNum test7(kk);
	//~ test7.print();


	//~ std::cout << "test7 " << test7 << std::endl;

	BigNum* test9= new BigNum("-123456789");
	test9->print();
	//~ std::cout << std::endl << "test string :  " << test9 << std::endl;

	BigNum test10(test9);
	BigNum test11;
	test11 = test9;

	delete test9;
	test10.print();
	test11.print();


	return 0;
}

