.text
#Input a, r, n
#s0 = a
#s1 = r
#s2 = n
#Sequence is a, ar, ar^2, ...
#First term is a etc.
MAIN:
	#input a
	li $v0, 5
	syscall
	move $s0, $v0
	#input r
	li $v0, 5
	syscall
	move $s1, $v0
	#input n
	li $v0, 5
	syscall
	move $s2, $v0
	#nth term is ar^{n-1}
	subi $s2, $s2, 1
	
	#print nth term
	move $a0, $s0
	move $a1, $s1
	move $a2, $s2
	jal N_TH_TERM
	move $a0, $v0
	li $v0, 1
	syscall
	
	#print sum
	move $a0, $s0
	move $a1, $s1
	move $a2, $s2
	jal SUM
	move $a0, $v0
	li $v0, 1
	syscall
	
EXIT:
	li $v0, 10
	syscall
	
#a0 = a, a1 = r, a2 = n, v0 = result
N_TH_TERM:
#add return address to stack
	subi $sp, $sp, 4
	sw $ra, ($sp)
	
	beq $a2, $zero, DONE	#if n = 0
	
	mul $a0, $a0, $a1	#else a = ar
	subi $a2, $a2, 1	#n = n-1
	jal N_TH_TERM
	
	DONE:
	move $v0, $a0		#store the result
	lw $ra, ($sp)		#retrieve return address from stack
	addi $sp, $sp, 4	#pop from stack
	jr $ra
	
#a0 = a, a1 = r, a2 = n, v0 = result
#SUM(n=i) = a + ar + ar^2 + ... + ar^i
SUM:
#add return address and to stack
	subi $sp, $sp, 4
	sw $ra, ($sp)
	
	move $v0, $a0		#f(0) = a
	beq $a2, $zero, DONE1
	
	subi $a2, $a2, 1	#n = n-1
	jal SUM
	mul $v0, $v0, $a1	#v0 = r*f(n-1)
	add $v0, $v0, $a0	#v0 = a + r*f(n-1)
	
	DONE1:
	lw $ra, ($sp)
	addi $sp, $sp, 4
	jr $ra
	
