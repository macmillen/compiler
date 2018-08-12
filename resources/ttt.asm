.object tttNEW
.import spllib printi
.import spllib printc
.import spllib readi
.import spllib readc
.import spllib exit
.import spllib indexError

ackermann:
; procedure prologue
; allocate space for local variables (4 bytes)
SUBC $31 $31 4
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 8
; save return register (ackermann calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (12 bytes)
SUBC $31 $31 12
; procedure body
ADDC $1 $29 0
LDW $1 $1
SETW $2 0
EQ $1 $1 $2
BRF $1 l0
ADDC $1 $29 8
LDW $1 $1
ADDC $2 $29 4
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
JMP l1
l0:
ADDC $1 $29 4
LDW $1 $1
SETW $2 0
EQ $1 $1 $2
BRF $1 l2
; storing argument #0 for procedure ackermann
ADDC $1 $29 0
LDW $1 $1
SETW $2 1
SUB $1 $1 $2
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #1 for procedure ackermann
SETW $1 1
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #2 for procedure ackermann
ADDC $1 $29 8
LDW $1 $1
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure ackermann
CALL $30 ackermann
JMP l3
l2:
; storing argument #0 for procedure ackermann
ADDC $1 $29 0
LDW $1 $1
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #1 for procedure ackermann
ADDC $1 $29 4
LDW $1 $1
SETW $2 1
SUB $1 $1 $2
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #2 for procedure ackermann
SUBC $1 $29 4
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure ackermann
CALL $30 ackermann
; storing argument #0 for procedure ackermann
ADDC $1 $29 0
LDW $1 $1
SETW $2 1
SUB $1 $1 $2
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #1 for procedure ackermann
SUBC $1 $29 4
LDW $1 $1
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #2 for procedure ackermann
ADDC $1 $29 8
LDW $1 $1
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure ackermann
CALL $30 ackermann
l3:
l1:
; procedure epilogue
; restore return register
ADDC $31 $31 12
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 8
; return to caller
JMPR $30


.executable main
main:
; procedure prologue
; allocate space for local variables (12 bytes)
SUBC $31 $31 12
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 16
; save return register (main calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (4 bytes)
SUBC $31 $31 4
; procedure body
SUBC $1 $29 4
SETW $2 0
STW $2 $1
JMP l4
l5:
SUBC $1 $29 8
SETW $2 0
STW $2 $1
JMP l6
l7:
; storing argument #0 for procedure ackermann
SUBC $1 $29 4
LDW $1 $1
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #1 for procedure ackermann
SUBC $1 $29 8
LDW $1 $1
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #2 for procedure ackermann
SUBC $1 $29 12
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure ackermann
CALL $30 ackermann
; storing argument #0 for procedure printi
SUBC $1 $29 4
LDW $1 $1
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 32
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure printc
CALL $30 printc
; storing argument #0 for procedure printi
SUBC $1 $29 8
LDW $1 $1
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 32
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure printc
CALL $30 printc
; storing argument #0 for procedure printi
SUBC $1 $29 12
LDW $1 $1
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 10
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure printc
CALL $30 printc
SUBC $1 $29 8
SUBC $2 $29 8
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l6:
SUBC $1 $29 8
LDW $1 $1
SETW $2 6
LEI $1 $1 $2
BRT $1 l7
SUBC $1 $29 4
SUBC $2 $29 4
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l4:
SUBC $1 $29 4
LDW $1 $1
SETW $2 3
LEI $1 $1 $2
BRT $1 l5
; procedure epilogue
; restore return register
ADDC $31 $31 4
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 16
; return to caller
JMPR $30


