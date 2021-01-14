	.arch msp430g2553
	.p2align 1,0
	.data

s:
	.word 1
	
jt:
	.word default		; jump to default if s == 0
	.word case1
	.word case2 
	.word case3
	
	.text
	
	.extern green_on
	.extern led_update
	
	.global led_on

led_on:
	Mov &s, r12		;temporary variable
	cmp #3, &s		;if s is bigger than 3
	jhs default		;jump to default
	add r12, r12 		; make space by s*2 words are 2 bytes
	mov jt(r12), r0		; access the s entry into r0 

case1:	
	add #1, &s
	mov #1, &green_on	; green_on = 1
	call #led_update
	jmp end
case2:	

case3:
	add #1, &s
	mov #0, &green_on
	call #led_update
	jmp end

default:
	mov #0, &s

end:
	pop r0
