.text
##
#Assume that:
#f <-> s0
#g <-> s1
#h <-> s2
#i <-> s3
#j <-> s4
#
#The code in the question basically runs the equivelant C statement below
#f= 2j+i-g
#It can be rewritten to reduce the number of registers used. In the code below we dont use s2
##

sll $s4, $s4, 1 	#s4 holds the value 2j
add $s0, $s4, $s3 	#s0 holds the value 2j+i
sub $s0, $s0, $s1 	#s0 ,or equivelantly f, holds the value 2j+i-g

#If there is no obligation to have the result stored in s0(or f), we can even remove s0 and just use s1, s3, s4