------------
SUMMARY
------------
convert binary strings to hex ascii

binary -> ascii hex
ascii hex -> binary
ascii stream -> binary
  
for little endian, (or big endian with correct length)

------------
USAGE
------------
code has 3 macros to use:

BINTOASCHEX(TBL,LI)
ASCHEXTOBIN(LI,TBL)
STRASCHEXTOBIN(LI,TBL)

------------

BINTOASCHEX(TBL,LI)
convert binary string LI to ascii TBL

ASCHEXTOBIN(LI,TBL)
convert ascii string TBL to binary LI
for correct work string should has one number ending with 0,
other way, behawior is undefined

STRASCHEXTOBIN(LI,TBL)
find and convert in the ascii string TBL to binary LI and return:
- pointer after at the places of number or:
- 0 , find no number

----------------------------------
