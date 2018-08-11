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
; allocate space for local variables (44 bytes)
SUBC $31 $31 44
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 48
; save return register (main calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (0 bytes)
SUBC $31 $31 0
; procedure body
SUBC $1 $29 40
SETW $2 0
; generating index
SETW $3 10
; boundary check
LTI $3 $2 $3
BRF $3 indexError
SETW $3 4
MULTI $2 $2 3
ADD $1 $1 2
SETW $2 1
STW $2 $1
SUBC $1 $29 40
SETW $2 11
; generating index
SETW $3 10
; boundary check
LTI $3 $2 $3
BRF $3 indexError
SETW $3 4
MULTI $2 $2 3
ADD $1 $1 2
SETW $2 1
STW $2 $1
SUBC $1 $29 44
SETW $2 0
STW $2 $1
JMP l0
l1:
SUBC $1 $29 44
LDW $1 $1
SETW $2 2
LTI $1 $1 $2
BRF $1 l2
SUBC $1 $29 44
SUBC $2 $29 44
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l2:
l0:
SETW $1 2
SETW $2 3
LTI $1 $1 $2
BRT $1 l1
SUBC $1 $29 40
SETW $2 1
; generating index
SETW $3 10
; boundary check
LTI $3 $2 $3
BRF $3 indexError
SETW $3 4
MULTI $2 $2 3
ADD $1 $1 2
SETW $2 5
STW $2 $1
; call procedure andere
CALL $30 andere
; procedure epilogue
; restore return register
ADDC $31 $31 0
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 48
; return to caller
JMPR $30


andere:
; procedure prologue
; allocate space for local variables (40 bytes)
SUBC $31 $31 40
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 44
; procedure body
SUBC $1 $29 40
SETW $2 0
; generating index
SETW $3 10
; boundary check
LTI $3 $2 $3
BRF $3 indexError
SETW $3 4
MULTI $2 $2 3
ADD $1 $1 2
SETW $2 4
STW $2 $1
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 44
; return to caller
JMPR $30


