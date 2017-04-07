start:

lds R16, 10
ldi xh, $16
ldi xl, 00
ldi yh, $8B
ldi yl, 00

loop:
ld R17, X+
ST Y+, R17
dec R16
brne loop

end:

rjmp end
