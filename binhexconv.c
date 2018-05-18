/*-----------------------------------------------

author: Tomasz C.
trol.six www.elektroda.pl
aktyn www.gentoo.org

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

#if _USE_BINTOASCHEX

void b2ah (char * str, void * bin , WORKSIZ size) {
	unsigned char tmp, b;
	unsigned char * lb;
	
	lb = (unsigned char *) bin;
	
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

#endif

/*-----------------------------------------------
 
-----------------------------------------------*/

#if _USE_STRASCHEXTOBIN
static unsigned char hashexdigit ( unsigned char tmp2 ) {
	if ( ( tmp2 >= '0' ) && ( tmp2 <= '9' ) ) return tmp2 - ('0'-0);
	if ( ( tmp2 >= 'a' ) && ( tmp2 <= 'f' ) ) return tmp2 - ('a'-10);
	if ( ( tmp2 >= 'A' ) && ( tmp2 <= 'F' ) ) return tmp2 - ('A'-10);
	return 0x80;
}
#else
static inline unsigned char hashexdigit ( unsigned char tmp2 ) {	
	if (tmp2 >= 'a') tmp2 -= 'a' - 'A';
	if (tmp2 >= 'A') tmp2 -= 'A' - '9' - 1;
	tmp2 -= '0';
	return tmp2;	
}
#endif

/*-----------------------------------------------
 read ascii number with end of string
-----------------------------------------------*/

#if _USE_ASCHEXTOBIN && _MAX_BYTES>4
#if !(_MERGE_IF_POSSIBILE && _USE_STRASCHEXTOBIN)

void ah2b ( void * bin, const char * str, WORKSIZ size ) {
	WORKSIZ lstr;
	unsigned char tmp3;
	unsigned char *lb;

	lb = (unsigned char*) bin;
	lstr = 0;
	tmp3 = 0;
	
	while ( *str != 0 ) { ++str; ++lstr; }
	
	while ( size && lstr-- ) {		
		tmp3 = hashexdigit(*--str);
		--size;

		if ( lstr == 0 ) {
			*lb++ = tmp3;
			break;
		}
		tmp3 |= hashexdigit(*--str) << 4;
		*lb++ = tmp3;
		--lstr;
	}
	
	while (size--) *lb++ = 0;
}
#endif
#endif

/*-----------------------------------------------
find hex digit in the string and
read ascii number from string and return:
pointer after at the places of number
or:
0 (null pointer) - find no number
-----------------------------------------------*/

#if _USE_STRASCHEXTOBIN && _MAX_BYTES>4

void * sah2b ( void * bin, const char * str, WORKSIZ size ) {
	WORKSIZ lstr;
	unsigned char tmp3;
	unsigned char * lb;

	lb = (unsigned char*) bin;
	lstr = 0;
	tmp3 = 0;

	if( !str ) return (void*)0;

	while (1) {
		tmp3 = *str;
		if ( !tmp3 ) return (void*)0;
		if ( (hashexdigit(tmp3) & 0x80) == 0 ) break;
		++str;
	}	
	for ( lstr=0; tmp3; ++lstr, ++str ) {
		tmp3 = *str;
		if ( hashexdigit(tmp3) & 0x80 ) break;
	}	
	
	bin = (void*) str;
	
	while ( size && lstr-- ) {
		tmp3 = hashexdigit(*--str);
		--size;
		
		if ( lstr == 0 ) {
			*lb++ = tmp3;
			break;
		}
		tmp3 |= hashexdigit(*--str) << 4;
		*lb++ = tmp3;
		--lstr;
	}

	while (size--) *lb++ = 0;
	
	return bin;
}

#endif

/*-----------------------------------------------
 only max 4 bytes
-----------------------------------------------*/

#if _MAX_BYTES<=4

#include <stdint.h>

#if _USE_ASCHEXTOBIN && !(_MERGE_IF_POSSIBILE && _USE_STRASCHEXTOBIN)

void ah2b ( void * bin, const char * str, WORKSIZ size ) {
	
	union {
		uint8_t tn[4];
		uint32_t t32;
	} ttt;
	unsigned char tmp3;
	unsigned char *lb;

	if ( !str ) return;

	while ( 0 != (tmp3 = *str++ ) ) {
		tmp3 = hashexdigit(tmp3);
		ttt.t32 = ttt.t32 << 4 | tmp3;
	}
	
	lb = (unsigned char*) bin;
	for ( tmp3=0; tmp3<size; tmp3++ ) lb[tmp3] = ttt.tn[tmp3];
}
#endif

#if _USE_STRASCHEXTOBIN

void * sah2b ( void * bin, const char * str, WORKSIZ size ) {
	unsigned char tmp3, *lb;

	union {
		uint8_t tn[4];
		uint32_t t32;
	} ttt;

	if ( !str ) return (void*)0;
	while (1) {
		tmp3 = *str;
		if ( !tmp3 ) return (void*)0;
		if ( (hashexdigit(tmp3) & 0x80) == 0 ) break;
		++str;
	}
	while (1) {
		tmp3 = hashexdigit(*str);
		if ( 0x80 & tmp3 ) break;
		ttt.t32 = ttt.t32 << 4 | tmp3;
		++str;
	}

	lb = (unsigned char*)bin;
	for ( tmp3=0; tmp3<size; tmp3++ ) lb[tmp3] = ttt.tn[tmp3];

	return (void*)str;
}

#endif

#endif

/*-----------------------------------------------

-----------------------------------------------*/
