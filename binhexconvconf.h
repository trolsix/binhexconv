/*
Binhexconv has several function, which can get smaller or faster code
You need smaller and sometimes faster code, use only needed function
Of course everything depends from compilator and architecture
*/

#ifndef _BINHEXCONVCONF_H
#define _BINHEXCONVCONF_H    1004

/* You can choose which function need 1, or not need 0 */
#define _USE_BINTOASCHEX        1
#define _USE_ASCHEXTOBIN        1
#define _USE_STRASCHEXTOBIN     1

/*
Option _MERGE_IF_POSSIBILE changes macros to use
STRASCHEXTOBIN function also for read ASCHEXTOBIN
what should save some spaces but making
conversion ASCHEXTOBIN slower
option: 0 or 1
*/
#define _MERGE_IF_POSSIBILE     0

/*
Possibile option for max bytes to convert binary:
4 127 1<<14-1
*/
#define _MAX_BYTES            127


#endif
