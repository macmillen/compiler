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
; allocate space for outgoing arguments (12 bytes)
SUBC $31 $31 12
; procedure body
SUBC $1 $29 4
SETW $2 10164
STW $2 $1
SUBC $1 $29 8
SETW $2 2646
STW $2 $1
; storing argument #0 for procedure gcd
SUBC $1 $29 4
LDW $1 $1
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; storing argument #1 for procedure gcd
SUBC $1 $29 8
LDW $1 $1
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #2 for procedure gcd
SUBC $1 $29 12
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; call procedure gcd
CALL $30 gcd
; storing argument #0 for procedure printi
SUBC $1 $29 4
LDW $1 $1
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 32
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printc
CALL $30 printc
; storing argument #0 for procedure printi
SUBC $1 $29 8
LDW $1 $1
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 32
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printc
CALL $30 printc
; storing argument #0 for procedure printi
SUBC $1 $29 12
LDW $1 $1
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printi
CALL $30 printi
; storing argument #0 for procedure printc
SETW $1 10
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printc
CALL $30 printc
; procedure epilogue
; restore return register
ADDC $31 $31 12
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 16
; return to caller
JMPR $30


gcd:
; procedure prologue
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 4
; procedure body
JMP l0
l1:
ADDC $1 $29 0
LDW $1 $1
ADDC $2 $29 4
LDW $2 $2
LTI $1 $1 $2
BRF $1 l2
ADDC $1 $29 4
ADDC $2 $29 4
LDW $2 $2
ADDC $3 $29 0
LDW $3 $3
SUB $2 $2 $3
STW $2 $1
JMP l3
l2:
ADDC $1 $29 0
ADDC $2 $29 0
LDW $2 $2
ADDC $3 $29 4
LDW $3 $3
SUB $2 $2 $3
STW $2 $1
l3:
l0:
ADDC $1 $29 0
LDW $1 $1
ADDC $2 $29 4
LDW $2 $2
NE $1 $1 $2
BRT $1 l1
ADDC $1 $29 8
LDW $1 $1
ADDC $2 $29 0
LDW $2 $2
STW $2 $1
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 4
; return to caller
JMPR $30


