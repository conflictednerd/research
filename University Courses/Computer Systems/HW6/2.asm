.text
#Input a, r, n
#s0 = a
#s1 = r
#s2 = n
#Sequence is a, ar, ar^2, ...
#0th term is a and first term is ar etc.
MAIN:
	li $v0, 5
	syscall
	move $s0, $v0
	
	li $v0, 5
	syscall
	move $s1, $v0
	
	li $v0, 5
	syscall
	move $s2, $v0	
	
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
	
#a0 = a, ,a1 = r, a2 = n
N_TH_TERM:
	move $v0, $a0
	move $t1, $zero #t1 is loop counter
	BEGIN_LOOP_1:
		beq $t1, $a2, END_LOOP_1
		mul $v0, $v0, $a1	#v0 = v0*r
		addi $t1, $t1, 1
		j BEGIN_LOOP_1
	END_LOOP_1:
	jr $ra


#a0 = a, ,a1 = r, a2 = n
SUM:
	move $t0, $a1
	move $t1, $zero #t1 is loop counter
	#After this loop t0 = r^{n+1}
	BEGIN_LOOP_2:
		beq $t1, $a2, END_LOOP_2
		mul $t0, $t0, $a1
		addi $t1, $t1, 1
		j BEGIN_LOOP_2
	END_LOOP_2:
	addi $t0, $t0, -1
	mul $t0, $t0, $a0	#t0 = a(r^{n+1}-1)
	addi $t2, $a1, -1	#t2 = r-1
	div $t0, $t2		
	mflo $v0		#transfer the quotient to v0
	jr $ra