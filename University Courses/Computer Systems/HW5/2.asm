.data
	A: .word 0,1,2,3,4,5,6,7,8,9
	B: .word 0:10
	i: .word 4
	j: .word 3
.text
	#Initializiations
	la $s0, A
	la $s1, B
	lw $t0, i
	lw $t1, j
	
	sll $t1, $t1, 2
	sll $t0, $t0, 2
	
	
	add $s0, $s0, $t1	#s0 = address of A[j]
	add $s1, $s1, $t0	#s1 = address of B[i]
	lw $t2, 4($s0)       	#t2 = A[j+1]
	lw $t3, -4($s0)		#t3 = A[j-1]
	add $t2, $t2, $t3	#t2 = A[j+1]+A[j-1]
	
	
	sw $t2, ($s1)
	
	
	