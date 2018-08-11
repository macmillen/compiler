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
SUBC $2 $29 4
LDW $2 $2
SETW $3 2
LTI $2 $2 $3
BRF $2 l2
l2:
l0:
SUBC $0 $29 4
LDW $0 $0
SETW $1 3
LTI $0 $0 $1
BRT $0 l1
