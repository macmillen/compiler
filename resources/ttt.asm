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
; save return register (main calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (4 bytes)
SUBC $31 $31 4
; procedure body
; storing argument #0 for procedure andere
SETW $1 5
SUBC $29 $29 12
STW $1 $29
ADDC $29 $29 12
; call procedure andere
CALL $30 andere
; procedure epilogue
; restore return register
ADDC $31 $31 4
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 4
; return to caller
JMPR $30


andere:
; procedure prologue
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 4
; procedure body
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 4
; return to caller
JMPR $30


