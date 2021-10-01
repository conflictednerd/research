#ATTENTION!!
#This code will not work as it is. To make it work, you should replace fin and fouts strings with proper addresses relative to your computers path system.
.data
fin: .asciiz "F:\\University\\ComputerSystems\\HW7\\input.txt"
.word 0
fout: .asciiz "F:\\University\\ComputerSystems\\HW7\\output.txt"
buffer: .space 1024

.text
MAIN:
#open files:
li $v0, 13	#syscall code for opening file
la $a0, fin	#file name
li $a1, 0	#open for read
li $a2, 0	#mode
syscall
move $s0, $v0	#input file descriptor is saved in s0

li $v0, 13	#syscall code for opening file
la $a0, fout	#file name
li $a1, 1	#open for write
li $a2, 0	#mode
syscall
move $s1, $v0	#output file descriptor is saved in s1
###################################

#PART 1: READ TO BUFFER
READ_LOOP:
li $v0, 14	#syscall code for reading from file
move $a0, $s0	#file descirptor
la $a1, buffer	#buffer address
li $a2, 1024	#hardcoded buffer size
syscall
#v0 now holds the number of characters read from file. if v0 = 1024 then there might be more to the file.
move $s2, $v0	#effective buffer size is stored in s2
beq $v0, 0, END_READ_LOOP	#if v0 = 0 then we have reached end of file

#PART 2: PROCESS
li $t0, 0 #t0 is loop counter
la $t1, buffer	#t1 is buffers posiotion in the loop
LOOP:
	beq $t0, $v0, END_LOOP		#if youve read the whole buffer, then exit the loop
	lb $t2, ($t1)			#t2 is the byte(char) read from buffer
	blt $t2, 'a' LABEL		#if uppercase skip the next line.
	subi $t2, $t2, 32		#convert lower case to uppercase
	sb $t2, ($t1)			#replace the lower cased letter with its coresponding uppercase letter in the buffer.
	LABEL:
	addi $t0, $t0, 1
	addi $t1, $t1, 1
	j LOOP
END_LOOP:

#PART 3: WRITE TO FILE
li $v0, 15	#syscall code for writing to buffer
move $a0, $s1	#load file desicriptor into a0
la $a1, buffer	#loads the address of buffer into a1
move $a2, $s2	#load buffer length into a2
syscall		#write to file
##########

beq $s2, 1024, READ_LOOP	#if buffer was full, read more from the file
END_READ_LOOP:

# Close files
li $v0, 16       # system call for close file
move $a0, $s0      # file descriptor to close
syscall            # close file

li $v0, 16
move $a0, $s1
syscall

#exit
li $v0, 17
li $a0, 0
syscall