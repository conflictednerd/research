.text

#read number of terms
li $v0, 5
syscall
move $s0, $v0

sll $s0, $s0, 1
addi $s0, $s0, 1	#s0 = 2n+1

li $t0, 1		#t0 is loop counter
li $t1, 1		#constant 1
mtc1 $t1, $f4		#set f4 to 1(int)
cvt.s.w $f4, $f4	#convert f4(=1(int)) to float
#f4 is constant 1(float)
li $t2, 1	#flag. if = 1 then add the fraction else subtract it

LOOP:
	beq $t0, $s0, END_LOOP
	
	mtc1 $t0, $f6
	cvt.s.w $f6, $f6	# move loop counter to FPU register and convert it to float so that it can be used in float division.
	div.s $f2, $f4, $f6	#calculate 1/(2i-1) and store it in f2
	
	beq $t2, 0, CONDITION	#if you had to subtract, jump
	add.s $f0, $f0, $f2
	add.s $f0, $f0, $f2
	CONDITION:
	sub.s $f0, $f0, $f2

	addi $t0, $t0, 2	#add to loop counter
	sub $t2, $t1, $t2	#flag = t2 <- 1-t2 = not flag
	j LOOP
END_LOOP:
#multiply the result by 4 to obtain PI.
li $t0, 4
mtc1 $t0, $f2
cvt.s.w $f2, $f2
mul.s $f0, $f0, $f2

#print the result
mov.s $f12, $f0
li $v0, 2
syscall

EXIT:
li $v0, 17
li $a0, 0
syscall