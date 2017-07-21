/*
 * bigNum.cpp
 * 
 * Copyright 2017 olivier <olivier@orion>
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
	BigNum(std::string    x);

	friend std::ostream & operator << (std::ostream& sortie , const BigNum & n);
	void print();
private:
	template <class X> void initFromSignedPrimitive (X x);
	template <class X> void initFromUnSignedPrimitive (X x);
	char digits[MAX_DIGITS];
	char sign;
	unsigned int lastDigit;
};

// gestion des constructeurs

BigNum::BigNum()
{
	sign=0;
	lastDigit=0;
	digits[0]=0;
}

BigNum::BigNum(unsigned long  x) { sign=1; initFromSignedPrimitive(x); }
BigNum::BigNum(unsigned int   x) { sign=1; initFromSignedPrimitive(x); }
BigNum::BigNum(unsigned short x) { sign=1; initFromSignedPrimitive(x); }
BigNum::BigNum(         long  x) { initFromUnSignedPrimitive(x); }
BigNum::BigNum(         int   x) { initFromUnSignedPrimitive(x); }
BigNum::BigNum(         short x) { initFromUnSignedPrimitive(x); }

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
		sign=1;
		initFromSignedPrimitive(x);
	}
	else
	if (x<0) {
		sign=-1;
		initFromSignedPrimitive(-x);
	}
}


// printf -- obsolete --
void BigNum::print()
{
	if (this->sign==-1)
		printf("-");
	for(int tmp=lastDigit; tmp>=0; tmp--) {
		printf("%i", digits[tmp]);
	}
	printf("\n");
}

// implémentation du << pour affichage
std::ostream & operator << (std::ostream& sortie , const BigNum & n)
{
	std::stringstream oss;
	// affichage signe et des digits
	if (n.sign==-1)
		oss << "-";
	char a;
	for(int tmp=n.lastDigit; tmp>=0; tmp--) {
		a= n.digits[tmp]+'0';
		oss << a;
	}
	sortie << oss.str();
	return sortie;
}


int main(int argc, char **argv)
{
	printf("taille de l'objet: %lu\n", sizeof(BigNum));

	// constructeur vide
	BigNum test1;
	test1.print();

	// constructeur 1 digit
	BigNum test2(6);
	test2.print();

	// constructeur more digit
	BigNum test3(175846);
	test3.print();

	// test nombre négatif
	int i=-57;
	BigNum test4(i);
	test4.print();

	int j= -564879564;
	BigNum test5(j);
	test5.print();
	std::cout << test5 << std::endl;

	long k = 978564879564;
	BigNum test6(k);
	test6.print();

	int kk = -34;
	BigNum test7(kk);
	test7.print();


	std::cout << "test7 " << test7 << std::endl;

	//~ BigNum test4("564879564651323");
	return 0;
}

