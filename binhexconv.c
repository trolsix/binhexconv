/*-----------------------------------------------

author: Tomasz C.
trol.six www.elektroda.pl
aktyn www.gentoo.org

-----------------------------------------------*/
/*-----------------------------------------------
MIT License

Copyright (c) 2018 trolsix

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------*/
/*-----------------------------------------------

conversion between:
binary -> ascii hex
ascii hex -> binary
ascii stream -> binary
  
for little endian (or big endian with correct length)

-----------------------------------------------*/

#include "binhexconv.h"

void b2ah (char * str, void * bin , int size) {
	unsigned char tmp, b;
	unsigned char * lb = bin;
	
	while(size--){
		b = lb[size];
		tmp = (b >> 4 ) & 0x0F;
		if(tmp>9) tmp += 'a' - 10;
		else tmp += '0';
		*str++ = tmp;
		tmp = b & 0x0F;
		if(tmp>9) tmp += 'a' - 10;
		else tmp += '0';
		*str++ = tmp;
	}
	*str = 0;
}

/*-----------------------------------------------
 read ascii number with end of string
-----------------------------------------------*/

#if SIZCHAR==0
void ah2b ( void * bin, char * str, unsigned int size ) {
#else
void ah2b ( void * bin, char * str, unsigned char size ) {
#endif
	unsigned char tmp, tmp2, tmp3;
	unsigned char * lb = bin;

	tmp = 0;
	tmp3 = 0;
	
	while(*str!=0) {
		++str;
		++tmp;
	}
	
	while(size) {		
		if ( tmp == 0 ) break;

		tmp2 = *--str;
		if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) ) tmp3 = tmp2 - '0';
		else if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) ) tmp3 = tmp2 - ('a'-10);
		else if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) ) tmp3 = tmp2 - ('A'-10);
		
		if ( --tmp == 0 ) {
			*lb++ = tmp3;
			--size;
			break;
		} else {
			tmp2 = *--str;
			if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) )
				tmp2 = tmp2 - '0';
			else if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) )
				tmp2 = tmp2 - ('a'-10);
			else if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) )
				tmp2 = tmp2 - ('A'-10);
		}
		
		tmp2 <<= 4;
		*lb++ = tmp3 | tmp2;
		--tmp;
		--size;
	}

	while(size--) {
		*lb++ = 0;
	}
}

/*-----------------------------------------------
read ascii number from string and return:
pointer after at the places of number
or:
0 - find no number
-----------------------------------------------*/

#if SIZCHAR==0
void * sah2b ( void * bin, char * str, unsigned int size ) {
#else
void * sah2b ( void * bin, char * str, unsigned char size ) {
#endif
	unsigned char tmp, tmp2, tmp3;
	unsigned char * lb = bin;

	tmp = 0;
	tmp3 = 0;

	if( !str ) return 0;
	
	while( 1 ) {
		tmp2 = *str;
		if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) ) break;
		else if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) ) break;
		else if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) ) break;
		if( !tmp2 ) return (void*)0;
		++str;
		continue;
	}
	
	for( tmp=0; tmp2; ++tmp, ++str ) {
		tmp2 = *str;
		if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) ) continue;
		else if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) ) continue;
		else if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) ) continue;
		break;
	}
	
	if(*str==0) bin = (void*)0;
	else bin = str;
	
	tmp3 = 0;

	while(size&&tmp) {
		if ( tmp == 0 ) break;

		tmp2 = *--str;
		if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) ) tmp3 = tmp2 - '0';
		else if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) ) tmp3 = tmp2 - ('a'-10);
		else if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) ) tmp3 = tmp2 - ('A'-10);
		
		if ( --tmp == 0 ) {
			*lb++ = tmp3;
			--size;
			break;
		} else {
			tmp2 = *--str;
			if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) )
				tmp2 = tmp2 - '0';
			else if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) )
				tmp2 = tmp2 - ('a'-10);
			else if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) )
				tmp2 = tmp2 - ('A'-10);
		}
		
		tmp2 <<= 4;
		*lb++ = tmp3 | tmp2;
		--tmp;
		--size;
	}

	while(size--) {
		*lb++ = 0;
	}
	return bin;
}


/*-----------------------------------------------

-----------------------------------------------*/
