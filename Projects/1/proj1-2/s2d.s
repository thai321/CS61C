##### sparse2dense function code #####
.text
# sparse2dense will have 2 arguments: $a0 = address of sparse matrix data, $a1 = address of dense matrix, $a2 = matrix width
# Recall that sparse matrix representation uses the following format:
# Row r<y> {int row#, Elem *node, Row *nextrow}
# Elem e<y><x> {int col#, int value, Elem *nextelem}
sparse2dense:
	### YOUR CODE HERE ###
	lw $t0, 0($a0)  #row
	lw $t1, 4($a0)  #*node  (Elem)
	lw $t2, 8($a0)  #*nextrow (Row)

	lw $t3, 0($t1) #col
	lw $t4, 4($t1) #value  (Elem)

	lw $t5, 0($t2)  # row of the nextrow
	