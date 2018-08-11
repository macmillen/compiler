.object tttNEW
.import spllib printi
.import spllib printc
.import spllib readi
.import spllib readc
.import spllib exit
.import spllib indexError

.executable main
main:
; procedure prologue
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 4
; procedure body
JMP l0
l1: 
l0:
SETW $1 1
SETW $2 8
LTI $1 $1 $2
BRT $1 l1
JMP l2
l3: 
l2:
SETW $1 1
SETW $2 15
LTI $1 $1 $2
BRT $1 l3
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 4
; return to caller
JMPR $30

