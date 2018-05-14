

#ifndef _BINHEXCONV_H
#define _BINHEXCONV_H

#define _HEXOP_VER 003
#define SIZCHAR 0

#if SIZCHAR==0
void b2ah (char * str, void * bin , unsigned int size );
void ah2b ( void * bin, char * str, unsigned int size );
void * sah2b ( void * bin, char * str, unsigned int size );
#else
void b2ah (char * str, void * bin , unsigned char size );
void ah2b ( void * bin, char * str, unsigned char size );
void * sah2b ( void * bin, char * str, unsigned char size );
#endif

#define BINTOASCHEX(TBL,LI) b2ah(TBL,(void*)&LI,sizeof(LI))
#define ASCHEXTOBIN(LI,TBL) ah2b((void*)&LI,TBL,sizeof(LI))
#define STRASCHEXTOBIN(LI,TBL) sah2b((void*)&LI,TBL,sizeof(LI))

#endif
