.object drawTest
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
; allocate space for outgoing arguments (20 bytes)
SUBC $31 $31 20
; procedure body
; storing argument #0 for procedure clearAll
SETW $1 0
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; call procedure clearAll
CALL $30 clearAll
; storing argument #0 for procedure drawLine
SETW $1 0
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawLine
SETW $1 0
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawLine
SETW $1 639
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawLine
SETW $1 479
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; storing argument #4 for procedure drawLine
SETW $1 16711935
SUBC $29 $29 12
STW $1 $29
ADDC $29 $29 12
; call procedure drawLine
CALL $30 drawLine
; storing argument #0 for procedure drawLine
SETW $1 0
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawLine
SETW $1 479
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawLine
SETW $1 639
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawLine
SETW $1 0
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; storing argument #4 for procedure drawLine
SETW $1 16776960
SUBC $29 $29 12
STW $1 $29
ADDC $29 $29 12
; call procedure drawLine
CALL $30 drawLine
; storing argument #0 for procedure drawCircle
SETW $1 320
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawCircle
SETW $1 240
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawCircle
SETW $1 40
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawCircle
SETW $1 65535
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure drawCircle
CALL $30 drawCircle
; storing argument #0 for procedure drawCircle
SETW $1 320
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawCircle
SETW $1 240
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawCircle
SETW $1 80
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawCircle
SETW $1 16711680
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure drawCircle
CALL $30 drawCircle
; storing argument #0 for procedure drawCircle
SETW $1 320
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawCircle
SETW $1 240
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawCircle
SETW $1 120
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawCircle
SETW $1 65280
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure drawCircle
CALL $30 drawCircle
; storing argument #0 for procedure drawCircle
SETW $1 320
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawCircle
SETW $1 240
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawCircle
SETW $1 160
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawCircle
SETW $1 16777215
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure drawCircle
CALL $30 drawCircle
; storing argument #0 for procedure drawCircle
SETW $1 320
SUBC $29 $29 28
STW $1 $29
ADDC $29 $29 28
; storing argument #1 for procedure drawCircle
SETW $1 240
SUBC $29 $29 24
STW $1 $29
ADDC $29 $29 24
; storing argument #2 for procedure drawCircle
SETW $1 200
SUBC $29 $29 20
STW $1 $29
ADDC $29 $29 20
; storing argument #3 for procedure drawCircle
SETW $1 255
SUBC $29 $29 16
STW $1 $29
ADDC $29 $29 16
; call procedure drawCircle
CALL $30 drawCircle
; procedure epilogue
; restore return register
ADDC $31 $31 20
LDW $30 $31
ADDC $31 $31 4
; restore old frame pointer
LDW $29 $31
ADDC $31 $31 4
; return to caller
JMPR $30


