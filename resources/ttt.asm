.import spllib printi
.import spllib printc
.import spllib readi
.import spllib readc
.import spllib exit
.import spllib indexError

.executable main
; procedure prologue
; allocate space for local variables (4 bytes)
SUBC $31 $31 4
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 8
save return register (main calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (8 bytes)
SUBC $31 $31 8
; procedure body
SUBC $1 $29 4
SETW $2 1
SETW $3 4
SETW $4 2
DIVI $3 $3 $4
ADD $2 $2 $3
STW $2 $1
; storing argument #0 for procedure andere
SETW $2 3
; storing argument #1 for procedure andere
SETW $3 4
SUBC $29 $29 8
; procedure prologue
; allocate space for local variables (0 bytes)
SUBC $31 $31 0
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 4
; allocate space for outgoing arguments (0 bytes)
SUBC $31 $31 0
; procedure body
