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

using namespace std;

int main(int argc, char **argv)
{
	if (0) {
		printf("Size of BigNum : %lu\n", sizeof(BigNum));
	}

	if(0) {
		// empty constructor
		BigNum test1;
		test1.print();
	
		// constructor with 1 digit
		BigNum test2(6);
		test2.print();
	
		// constructorwith  more digits
		BigNum test3(175846);
		test3.print();
	
		// Test negative number
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
	
		BigNum* test9= new BigNum("-123456789");
		test9->print();
	
		BigNum test10(test9);
		BigNum test11;
		test11 = test9;
	
		delete test9;
		test10.print();
		test11.print();
	}

	// compare tests
	if (0) {
		BigNum test1(542);
		BigNum test2(92);
		BigNum test3(-540);

		if (test1 < test2)
			cout << test1 << " < " << test2 << endl;
		else
			cout << test1 << " > " << test2 << endl;
	
		if (test2 < test3)
		cout << test2 << " < " << test3 << endl;
		else
			cout << test2 << " > " << test3 << endl;
	}
	
	if (0) {
		//normalize tests
		BigNum test= BigNum("-000123456789");
		test.print();
	
		BigNum testOpp = test;
		testOpp.opp();
		testOpp.print();
		
		BigNum testOpp1 = -test;
		testOpp1.print();
	}
	
	if (0) {
		//normalize tests
		BigNum a= BigNum("596516649");
		BigNum b= BigNum("1189641421");
		BigNum c= BigNum("9921");

		BigNum d,e;
		d.add(a,b);
		d.print();
		e.add(b,c);
		e.print();
	}

	if (1) {
		long a,b;
		BigNum aa,bb;
		for(long int i=0; i< 5000; i++) {
			a= rand()-RAND_MAX/2;
			//~ a= 0;
			b= rand()-RAND_MAX/2;
			//~ b= 0;
			BigNum aa(a);
			BigNum bb(b);
			BigNum cc(a+b);
			BigNum dd;
			dd.add(aa,bb);
			if (cc != dd) {
				printf("a = %li b=%li\nSomme:         : %li\n", a,b, a+b);
				printf("valeur trouvée : "); dd.print();
				printf("intermédiaire  : "); cc.print();
				printf("error : %li %li\n\n",a,b);
			}
		}
	}


	if (1) {
		long a,b;
		BigNum aa,bb;
		for(long int i=0; i< 5000; i++) {
			a= rand()-RAND_MAX/2;
			//~ a=0;
			b= rand()-RAND_MAX/2;
			//~ b=0;

			while(a<b) 
				a+=rand();

			BigNum aa(a);
			BigNum bb(b);
			BigNum cc(a-b);
			BigNum dd;
			dd.sou(aa,bb);
			if (cc != dd) {
				printf("a = %li b=%li\nDifférence:         : %li\n", a,b, a-b);
				printf("valeur trouvée : "); dd.print();
				printf("intermédiaire  : "); cc.print();
				printf("error : %li %li\n\n",a,b);
			}
		}
	}

	return 0;
}
