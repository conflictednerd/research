.data

.text
#Read Input
	li $v0, 5		#Read vectors size from input
	syscall			#Input will be stored in v0
	
#Allocate Memory
	move $a0, $v0		#a0 = size
	sll $a0, $a0, 2		#4*$a0 is the number of bytes we need to store a vector
	
	li $v0, 9		#code 9 will allocate $a0 bytes of memory from the heap and put the base address in $v0
	syscall
	move $a1, $v0		#a1 contains base address of first vectors array
	
	li $v0, 9
	syscall
	move $a2, $v0		#a2 now contains base address of second vectors array
	srl $a0, $a0, 2		#Restore size in a0 as an argument of inner_prod function
	
	#Input for first array
	li $t0, 0
	BEGIN_LOOP_1:
		beq $t0, $a0, END_LOOP_1
		li $v0, 5		#read int from input
		syscall
		sll $t1, $t0, 2		#t1 shows how many bytes away v1[$t0] is  from its base address (t1 = 4*t0)
		add $t1, $t1, $a1	#t1 now holds the address of v1[$t0]
		sw $v0, ($t1)
		addi $t0, $t0, 1
		j BEGIN_LOOP_1
	END_LOOP_1:
	
	#Input for second array
	li $t0, 0
	BEGIN_LOOP_2:
		beq $t0, $a0, END_LOOP_2
		li $v0, 5
		syscall
		sll $t1, $t0, 2		#t1 shows how many bytes away v2[$t0] is  from its base address (t1 = 4*t0)
		add $t1, $t1, $a2	#t1 now holds the address of v2[$t0]
		sw $v0, ($t1)
		addi $t0, $t0, 1
		j BEGIN_LOOP_2
	END_LOOP_2:
	
	#call the subroutine to caluclate the inner product
	jal INNER_PROD
	#Print the result
	move $a0, $v0
	li $v0, 1
	syscall
	
	EXIT:
		li $v0, 10
		syscall
	
	
	
	INNER_PROD:		#a0 = size, a1 = base address for first vector, a2 = base address for second vector
		li $t0, 0	#t0 is loop counter
		li $v0, 0	#v0 is the result
		
		BEGIN_FOR:
			beq $t0, $a0, END_FOR		#condition to break the loop
			addi $a1, $a1, 4
			addi $a2, $a2, 4
			
			lw $t1, -4($a1)			# we add -4 with the address so that it starts from the beginning	
			lw $t2, -4($a2)			#2 now stores the t0_th element of the second vector
			
			mul $t3, $t1, $t2		#calculate the product v1[i]*v2[i]
			add $v0, $v0, $t3		#add this to the sum 
			
			addi $t0, $t0, 1
			j BEGIN_FOR
		END_FOR:
		jr $ra
			
			
			
		
