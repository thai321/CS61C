# CS61C Sp14 Project 1-2
# Task A: The Collatz conjecture

.globl main
.include "collatz_common.s"

main:
	jal read_input			# Get the number we wish to try the Collatz conjecture on
	move $a0, $v0			# Set $a0 to the value read
	la $a1, collatz_recursive	# Set $a1 as ptr to the function we want to execute
	jal execute_function		# Execute the function
	li $v0, 10			# Exit
	syscall
	
# --------------------- DO NOT MODIFY ANYTHING ABOVE THIS POINT ---------------------

# Returns the stopping time of the Collatz function (the number of steps taken till the number reaches one)
# using an RECURSIVE approach. This means that if the input is 1, your function should return 0.
#
# The current value is stored in $a0, and you may assume that it is a positive number.
#
# Make sure to follow all function call conventions.
collatz_recursive:
	# YOUR CODE HERE
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	addi $v0, $zero , 0
	beq $a0, 1, done
	
	addi $t0, $zero, 2
	div $a0, $t0
	mfhi $t0
	bne $t0, 0, Else
	mflo $a0
	j continute
	
	Else:
		addi $t0, $zero, 3
		mult $a0, $t0
		mflo $a0
		addi $a0, $a0, 1
		#j continute
	
	continute:
		jal collatz_recursive
		addi $v0, $v0, 1
	
	done:
		lw $ra, 0($sp)
		addiu $sp, $sp, 4
		jr $ra

