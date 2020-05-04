	.arch msp430g2553
	.p2align 1,0
	.data
switch_state_changed:
	.word
jt:	
	.word case01
	.word case02
	.word case03
	.word case04

	.text
	.global switch_state_machine_assembly
switch_state_machine_assembly:
	;; mov r12, 0(r1)
	cmp #5, r12
	jc default
	add r12, r12
	mov jt(r12), r0
case01:
	mov.b #1, &switch_state_changed
	call #blinkLEDS
	call #twinkle
	jmp end
case02:
	mov.b #1, &switch_state_changed
	call #blinkLEDS
	call #twinkle
	jmp end
case03:
	mov.b #1, &switch_state_changed
	call #blinkLEDS
	jmp end
case04:
	mov.b #1, &switch_state_changed
	call #blinkLEDS
	call #twinkle
	jmp end
default:
	jmp end
	
end:
	ret
