------------
SUMMARY
------------
convert binary number (types) to hex ascii

- binary -> ascii hex
- ascii hex -> binary
- ascii stream -> binary
  
for little endian, (or big endian with correct length),
code should work with constant size types like number,
other way is risk improper coversion

------------
USAGE
------------
code has 3 macros to use:

- BINTOASCHEX(TBL,LI)
- ASCHEXTOBIN(LI,TBL)
- STRASCHEXTOBIN(LI,TBL)

------------

BINTOASCHEX(TBL,LI)
convert binary number LI to ascii TBL
TBL should has enought size to place string with the null byte ('\0')

ASCHEXTOBIN(LI,TBL)
convert ascii string TBL to binary number LI
for correct work string should has one number terminating null byte ('\0'), 
other way, behawior is undefined

STRASCHEXTOBIN(LI,TBL)
find in the ascii string TBL hexdigit, and convert to binary number LI and return:
- pointer after at the places of number or:
- 0 , find no number
