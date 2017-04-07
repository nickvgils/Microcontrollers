start:

lds yh, $04
ldi yl, $00
ldd r14, Y+0
ldd r15, Y+1
ldd r12, Y+2
ldd r13, Y+3
ldd r10, Y+4
ldd r11, Y+5
ldd r8, Y+6
ldd r9, Y+7

mov r4, r10
add r4, r15

mov r5, r11
adc r5, r14

mov r6, r8
adc r6, r12

mov r7, r13
adc r7, r9

std Y+4, r4
std Y+5, r5
std Y+6, r6
std Y+7, r7

no_end:
rjmp no_end