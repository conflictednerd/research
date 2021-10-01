.data
a: .word 5
b: .word 6
i: .word 0
j: .word 0
D: .word 0:100

.text
	#initialization
	la $s2, D
	lw $s0, a
	lw $s1, b
	lw $t0, i
	lw $t1, j
	
	
	BEGIN_LOOP_1:
		beq $t0, $s0, END_LOOP_1
		li $t1, 0			#setting j to zero and preparing for the next iteration of the second loop
		BEGIN_LOOP_2:
			beq $t1, $s1, END_LOOP_2
			
			mul $t2, $t0, $s1
			add $t2, $t2, $t1
			sll $t2, $t2, 2		#These three lines calculate the amount that should be added to the base 
						#address of D so that we have the address of i*b+j_th index of the array.
			add $t2, $t2, $s2	#t2 now holds the address of D[i*b+j]
			add $t3, $t0, $t1	#t3 now holds i+j which should be stored in D[i*b+j]
			sw $t3,($t2)		#storing the contents
	
			addi $t1, $t1, 1	#adding 1 ot j
			j BEGIN_LOOP_2		#repeating loop 2
		END_LOOP_2:
		
		addi $t0, $t0, 1		#adding 1 to i
		j BEGIN_LOOP_1			#repeating loop 1
	END_LOOP_1: