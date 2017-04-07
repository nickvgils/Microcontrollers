start:
ldi R16, 0
ldi R17, 7
out PORTA, R16

loop:
inc R16
out PORTA, R16
dec R17
brne loop

back:
ldi R17, 7

secondloop:
dec R16
out PORTA, R16
dec R17
brne secondloop

end:
rjmp start