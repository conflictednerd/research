.data
	f: .word 1
	g: .word 2
.text
	li $v0, 1
	lw $s0, f #s0 = f
	lw $s1, g #s1 = g
###################################### Main code:	
	add $s0, $s0, $s1 #s0 = f+g
	subu $s0, $zero, $s0 # s0 = f = -f-g
	sub $s0, $s1, $s0 # f = g-f
	addi $s0, $s0, -5 #f = f-5
####################################### End of Main code
	
	move $a0, $s0
	syscall