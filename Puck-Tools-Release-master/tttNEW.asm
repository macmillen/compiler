.object tttNEW
.import spllib printi
.import spllib printc
.import spllib readi
.import spllib readc
.import spllib exit
.import spllib indexError

p:
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
ADDC $1 $29 0
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
; boundary check
SETW $3 7
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SUBC $2 $29 4
LDW $2 $2
STW $2 $1
SUBC $1 $29 4
SUBC $2 $29 4
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l0:
SUBC $1 $29 4
LDW $1 $1
SETW $2 7
LTI $1 $1 $2
BRT $1 l1
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 8
; return to caller
JMPR $30


.executable main
main:
; procedure prologue
; allocate space for local variables (148 bytes)
SUBC $31 $31 148
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 152
; save return register (main calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (4 bytes)
SUBC $31 $31 4
; procedure body
SUBC $1 $29 144
SETW $2 0
STW $2 $1
JMP l2
l3: 
SUBC $1 $29 148
SETW $2 0
STW $2 $1
JMP l4
l5: 
SUBC $1 $29 140
; generating index
SUBC $2 $29 144
LDW $2 $2
; boundary check
SETW $3 5
LTU $3 $2 $3
BRF $3 indexError
SETW $3 28
MULU $2 $2 $3
ADD $1 $1 $2
; generating index
SUBC $2 $29 148
LDW $2 $2
; boundary check
SETW $3 7
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
SUBC $1 $29 148
SUBC $2 $29 148
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l4:
SUBC $1 $29 148
LDW $1 $1
SETW $2 7
LTI $1 $1 $2
BRT $1 l5
SUBC $1 $29 144
SUBC $2 $29 144
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l2:
SUBC $1 $29 144
LDW $1 $1
SETW $2 5
LTI $1 $1 $2
BRT $1 l3
; storing argument #0 for procedure p
SUBC $1 $29 140
; generating index
SETW $2 2
; boundary check
SETW $3 5
LTU $3 $2 $3
BRF $3 indexError
SETW $3 28
MULU $2 $2 $3
ADD $1 $1 $2
SUBC $29 $29 160
STW $1 $29
ADDC $29 $29 160
; call procedure p
CALL $30 p
SUBC $1 $29 144
SETW $2 0
STW $2 $1
JMP l6
l7: 
SUBC $1 $29 148
SETW $2 0
STW $2 $1
JMP l8
l9: 
; storing argument #0 for procedure printi
SUBC $1 $29 140
; generating index
SUBC $2 $29 144
LDW $2 $2
; boundary check
SETW $3 5
LTU $3 $2 $3
BRF $3 indexError
SETW $3 28
MULU $2 $2 $3
ADD $1 $1 $2
; generating index
SUBC $2 $29 148
LDW $2 $2
; boundary check
SETW $3 7
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
LDW $1 $1
SUBC $29 $29 160
STW $1 $29
ADDC $29 $29 160
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 32
SUBC $29 $29 160
STW $1 $29
ADDC $29 $29 160
; call procedure printc
CALL $30 printc
SUBC $1 $29 148
SUBC $2 $29 148
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l8:
SUBC $1 $29 148
LDW $1 $1
SETW $2 7
LTI $1 $1 $2
BRT $1 l9
; storing argument #0 for procedure printc
SETW $1 10
SUBC $29 $29 160
STW $1 $29
ADDC $29 $29 160
; call procedure printc
CALL $30 printc
SUBC $1 $29 144
SUBC $2 $29 144
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l6:
SUBC $1 $29 144
LDW $1 $1
SETW $2 5
LTI $1 $1 $2
BRT $1 l7
; procedure epilogue
; restore return register
ADDC $31 $31 4
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 152
; return to caller
JMPR $30

