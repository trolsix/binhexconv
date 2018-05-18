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

#ifndef _BINHEXCONV_H
#define _BINHEXCONV_H      1005

#include "binhexconvconf.h"

#if _BINHEXCONV_H != _BINHEXCONVCONF_H
#error Wrong configuration file: (binhexconvconf.h)
#endif

#if _MAX_BYTES>127
typedef unsigned int WORKSIZ;
#else
typedef unsigned char WORKSIZ;
#endif

#if _USE_BINTOASCHEX
#define BINTOASCHEX(TBL,LI) b2ah(TBL,(void*)&LI,sizeof(LI))
void b2ah (char * str, void * bin , WORKSIZ size );
#else
#define BINTOASCHEX(TBL,LI) _MACRO_BINTOASCHEX_IS_OFF_CHECK_binhexconvconf_h_FILE_
#endif


#if _USE_STRASCHEXTOBIN
#define STRASCHEXTOBIN(LI,TBL) sah2b((void*)&LI,TBL,sizeof(LI))
void * sah2b ( void * bin, const char * str, WORKSIZ size );
#else
#define STRASCHEXTOBIN(TBL,LI) _MACRO_STRASCHEXTOBIN_IS_OFF_CHECK_binhexconvconf_h_FILE_
#endif


#if _USE_ASCHEXTOBIN
#if _MERGE_IF_POSSIBILE && _USE_STRASCHEXTOBIN
#define ASCHEXTOBIN(LI,TBL) sah2b((void*)&LI,TBL,sizeof(LI))
#else
#define ASCHEXTOBIN(LI,TBL) ah2b((void*)&LI,TBL,sizeof(LI))
void ah2b ( void * bin, const char * str, WORKSIZ size );
#endif
#else
#define ASCHEXTOBIN(TBL,LI) _MACRO_ASCHEXTOBIN_IS_OFF_CHECK_binhexconvconf_h_FILE_
#endif


#endif
