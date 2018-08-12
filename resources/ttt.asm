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
; allocate space for local variables (188 bytes)
SUBC $31 $31 188
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 192
; save return register (main calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (20 bytes)
SUBC $31 $31 20
; procedure body
SUBC $1 $29 188
SETW $2 0
STW $2 $1
JMP l0
l1:
SUBC $1 $29 32
; generating index
SUBC $2 $29 188
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
SUBC $1 $29 64
; generating index
SUBC $2 $29 188
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
SUBC $1 $29 188
SUBC $2 $29 188
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l0:
SUBC $1 $29 188
LDW $1 $1
SETW $2 8
LTI $1 $1 $2
BRT $1 l1
SUBC $1 $29 188
SETW $2 0
STW $2 $1
JMP l2
l3:
SUBC $1 $29 124
; generating index
SUBC $2 $29 188
LDW $2 $2
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
SUBC $1 $29 184
; generating index
SUBC $2 $29 188
LDW $2 $2
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
SUBC $1 $29 188
SUBC $2 $29 188
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l2:
SUBC $1 $29 188
LDW $1 $1
SETW $2 15
LTI $1 $1 $2
BRT $1 l3
; storing argument #0 for procedure try
SETW $1 0
SUBC $29 $29 216
STW $1 $29
ADDC $29 $29 216
; storing argument #1 for procedure try
SUBC $1 $29 32
SUBC $29 $29 212
STW $1 $29
ADDC $29 $29 212
; storing argument #2 for procedure try
SUBC $1 $29 64
SUBC $29 $29 208
STW $1 $29
ADDC $29 $29 208
; storing argument #3 for procedure try
SUBC $1 $29 124
SUBC $29 $29 204
STW $1 $29
ADDC $29 $29 204
; storing argument #4 for procedure try
SUBC $1 $29 184
SUBC $29 $29 200
STW $1 $29
ADDC $29 $29 200
; call procedure try
CALL $30 try
; procedure epilogue
; restore return register
ADDC $31 $31 20
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 192
; return to caller
JMPR $30


try:
; procedure prologue
; allocate space for local variables (4 bytes)
SUBC $31 $31 4
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 8
; save return register (try calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (20 bytes)
SUBC $31 $31 20
; procedure body
ADDC $1 $29 0
LDW $1 $1
SETW $2 8
EQ $1 $1 $2
BRF $1 l4
; storing argument #0 for procedure printboard
ADDC $1 $29 8
LDW $1 $1
SUBC $29 $29 32
STW $1 $29
ADDC $29 $29 32
; call procedure printboard
CALL $30 printboard
JMP l5
l4:
SUBC $1 $29 4
SETW $2 0
STW $2 $1
JMP l6
l7:
ADDC $1 $29 4
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
LDW $1 $1
SETW $2 0
EQ $1 $1 $2
BRF $1 l8
ADDC $1 $29 12
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
ADDC $3 $29 0
LDW $3 $3
ADD $2 $2 $3
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
LDW $1 $1
SETW $2 0
EQ $1 $1 $2
BRF $1 l9
ADDC $1 $29 16
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
SETW $3 7
ADDC $4 $29 0
LDW $4 $4
SUB $3 $3 $4
ADD $2 $2 $3
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
LDW $1 $1
SETW $2 0
EQ $1 $1 $2
BRF $1 l10
ADDC $1 $29 4
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 1
STW $2 $1
ADDC $1 $29 12
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
ADDC $3 $29 0
LDW $3 $3
ADD $2 $2 $3
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 1
STW $2 $1
ADDC $1 $29 16
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
SETW $3 7
ADDC $4 $29 0
LDW $4 $4
SUB $3 $3 $4
ADD $2 $2 $3
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 1
STW $2 $1
ADDC $1 $29 8
LDW $1 $1
; generating index
ADDC $2 $29 0
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SUBC $2 $29 4
LDW $2 $2
STW $2 $1
; storing argument #0 for procedure try
ADDC $1 $29 0
LDW $1 $1
SETW $2 1
ADD $1 $1 $2
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure try
ADDC $1 $29 4
LDW $1 $1
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure try
ADDC $1 $29 8
LDW $1 $1
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure try
ADDC $1 $29 12
LDW $1 $1
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; storing argument #4 for procedure try
ADDC $1 $29 16
LDW $1 $1
SUBC $29 $29 12
STW $1 $29
ADDC $29 $29 12
; call procedure try
CALL $30 try
ADDC $1 $29 4
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
ADDC $1 $29 12
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
ADDC $3 $29 0
LDW $3 $3
ADD $2 $2 $3
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
ADDC $1 $29 16
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
SETW $3 7
ADDC $4 $29 0
LDW $4 $4
SUB $3 $3 $4
ADD $2 $2 $3
; boundary check
SETW $3 15
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
SETW $2 0
STW $2 $1
l10:
l9:
l8:
SUBC $1 $29 4
SUBC $2 $29 4
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l6:
SUBC $1 $29 4
LDW $1 $1
SETW $2 8
LTI $1 $1 $2
BRT $1 l7
l5:
; procedure epilogue
; restore return register
ADDC $31 $31 20
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 8
; return to caller
JMPR $30


printboard:
; procedure prologue
; allocate space for local variables (8 bytes)
SUBC $31 $31 8
; save old frame pointer (4 bytes)
SUBC $31 $31 4
STW $29 $31
; set new frame pointer
ADDC $29 $31 12
; save return register (printboard calls at least one procedure in its body)
SUBC $31 $31 4
STW $30 $31
; allocate space for outgoing arguments (4 bytes)
SUBC $31 $31 4
; procedure body
SUBC $1 $29 4
SETW $2 0
STW $2 $1
JMP l11
l12:
SUBC $1 $29 8
SETW $2 0
STW $2 $1
JMP l13
l14:
; storing argument #0 for procedure printc
SETW $1 32
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; call procedure printc
CALL $30 printc
ADDC $1 $29 0
LDW $1 $1
; generating index
SUBC $2 $29 4
LDW $2 $2
; boundary check
SETW $3 8
LTU $3 $2 $3
BRF $3 indexError
SETW $3 4
MULU $2 $2 $3
ADD $1 $1 $2
LDW $1 $1
SUBC $2 $29 8
LDW $2 $2
EQ $1 $1 $2
BRF $1 l15
; storing argument #0 for procedure printc
SETW $1 48
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure printc
CALL $30 printc
JMP l16
l15:
; storing argument #0 for procedure printc
SETW $1 46
SUBC $29 $29 12
STW $1 $29
ADDC $29 $29 12
; call procedure printc
CALL $30 printc
l16:
SUBC $1 $29 8
SUBC $2 $29 8
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l12:
SUBC $1 $29 8
LDW $1 $1
SETW $2 8
LTI $1 $1 $2
BRT $1 l13
; storing argument #0 for procedure printc
SETW $1 10
SUBC $29 $29 8
STW $1 $29
ADDC $29 $29 8
; call procedure printc
CALL $30 printc
SUBC $1 $29 4
SUBC $2 $29 4
LDW $2 $2
SETW $3 1
ADD $2 $2 $3
STW $2 $1
l10:
SUBC $1 $29 4
LDW $1 $1
SETW $2 8
LTI $1 $1 $2
BRT $1 l11
; storing argument #0 for procedure printc
SETW $1 10
SUBC $29 $29 4
STW $1 $29
ADDC $29 $29 4
; call procedure printc
CALL $30 printc
; procedure epilogue
; restore return register
ADDC $31 $31 4
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 12
; return to caller
JMPR $30


