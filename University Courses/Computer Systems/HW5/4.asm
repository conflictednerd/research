.text
#Loading example values in t0, t1
li $t0, 63
li $t1, 0x00010000

###Main code:
sll $t0, $t0, 26
andi $t1, 0x03ffffff 
add $t1, $t1, $t0
