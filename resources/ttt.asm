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
; allocate space for local variables (500 bytes)
SUBC $31 $31 500
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 504
; procedure body
SUBC $1 $29 500
; generating index
SETW $2 0
; boundary check
SETW $3 5
LTU $3 $2 $3
BRF $3 indexError
SETW $3 100
MULU $2 $2 $3
ADD $1 $1 $2
; generating index
SETW $2 0
; boundary check
SETW $3 5
LTU $3 $2 $3
BRF $3 indexError
SETW $3 20
MULU $2 $2 $3
ADD $1 $1 $2
; generating index
SETW $2 0
; boundary check
SETW $3 5
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 10
STW $2 $1
; procedure epilogue
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 504
; return to caller
JMPR $30


