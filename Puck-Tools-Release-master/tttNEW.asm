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
; allocate space for local variables (4 bytes)
SUBC $31 $31 4
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 8
; procedure body
SUBC $1 $29 4
SETW $2 0
STW $2 $1
JMP l0
l1: 
SUBC $1 $29 4
LDW $1 $1
SETW $2 2
LTI $1 $1 $2
BRF $1 l2
l2:
l0:
SUBC $1 $29 4
LDW $1 $1
SETW $2 3
LTI $1 $1 $2
BRT $1 l1
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 8
; return to caller
JMPR $30

