.data
string1: .space 100
string2: .space 100

.text
MAIN:
#Getting user input
#string1
	la $a0, string1		#address of input buffer
	li $a1, 90		#max size of string
	li $v0, 8		#code for string input
	syscall
#string2
	la $a0, string2
	li $a1, 90
	li $v0, 8
	syscall

#Determine length of given strings and save them in s0, s1
	la $a0, string1
	jal LENGTH
	move $s0, $v0
	
	la $a0, string2
	jal LENGTH
	move $s1, $v0

#initializing arguments to call subroutine
	la $a0, string1
	la $a1, string2
	move $a2, $s0
	move $a3, $s1	
	
	jal FIND
#print result
	move $a0, $v0
	li $v0, 1
	syscall

EXIT:
	li $v0, 10
	syscall
LENGTH:
#a0 is the address of first string, length of the given string will be saved in $v0
	move $t0, $a0	#base string address
	li $v0, 0	#counter
	li $t2, '\n'	#endline char
	LOOP1:
	lb $t3, 0($t0)
	beq $t3, $t2 ENDLOOP1 #if char = \n end the loop
	addi $t0, $t0, 1
	addi $v0, $v0, 1
	j LOOP1
	
	ENDLOOP1:
	jr $ra

FIND:
#a0 is the address of first string, a1 is the address of second string, a2 is the length of a0, a3 is the length of a1
#t0 is the index from string1 from which weve started matching. t1 is the counter for matching

#if length of second string is more than the first one then no match can happen
	slt $t0, $a2, $a3
	beq $t0, 1, ENDOUTERLOOP 
#-----------------------------
	
	move $t0, $a0
	li $t5, 0					#counter for outerloop
	#t6 is the maximum idx from which a match can happen. used to terminate outerloop
	sub $t6, $a2, $a3
	addi $t6, $t6, 1
	OUTERLOOP:
		beq $t5, $t6, ENDOUTERLOOP		#if loop counter is equal to t6 then no more match can be found
		move $t2, $a1				#t2 is the beginning of string2
		
		move $t0, $a0				#t0 is the beginning of string1
		add $t0, $t0, $t5			#t0 is the address of some index of string1 from where we want to start matching
		
		li $t1, 0				#counter for inner loop is reset
		INNERLOOP:
			beq $t1, $a3, SUCCESS	#SUCCESS! if weve mathced all charachters of string2 then end the loop
			lb $t3, 0($t0)
			lb $t4, 0($t2)
			bne $t3, $t4 ENDINNERLOOP	#FAIL! a charachter doesn't match
			addi $t1, $t1, 1		#counter++
			addi $t0, $t0, 1		#idx(string1)++
			addi $t2, $t2, 1		#idx(string2)++
			j INNERLOOP
		ENDINNERLOOP:
	
		addi $t5, $t5, 1
		j OUTERLOOP
	ENDOUTERLOOP:
	#if we reach here without any SUCCESS, then no match is found.
	li $v0, -1
	jr $ra
				
	SUCCESS:
	#t5 stores the index of string1 from which a match was found
	move $v0, $t5
	jr $ra