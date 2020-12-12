	.arch msp430g2553
	.p2align 1,0
	.data

s:
	.word 0
	
jt:
	.word default		; jump to default if s == 0
	.word case1
	.word case2 
	.word case3
	.word case4
	
	.text
	
	.extern green_on
	.extern led_update
	
	.global led_on

led_on:
	Mov &s, r12		; temporary var
	add r12, r12 		; make space by s*2
	
	cmp #4, &s		; s - 4 dont borrow if s > 3
	jhs default		; jmp if s > 3 if not c then s is greater than 4
	mov jt(r12), r0		; move into pc to save 

case1:
	
case2:
	add #1, &s
	mov #1, &green_on	; green_on = 1
	call #led_update
	jmp end

case3:

case4:
	add #1, &s
	mov #0, &green_on
	call #led_update
	jmp end

default:
	mov #0, &s

end:
	pop r0
