  l1: EQU 1 ;comment
  L2: EQU 1
  l3:

  EQU 0x1
SECTION text
SUB O
public temp
A: extern
b: EXTERN
public N
TROCA: MACRO
COPY A, TEMP
COPY B, TEMP
ENDMACRO
ABC: MACRO
OUTPUT TEMP
ENDmacro
IF L1
LOAD N ;lolol
IF L2
INPUT N
TROCA
ADD O
sub B
if L3
OUTPUT N
ABC

SECtion DATA
TEMP: CONST 0x1
O: CONST L1
N: SPACE
