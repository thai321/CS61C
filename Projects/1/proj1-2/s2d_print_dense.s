##### Variables #####
.data
# Header for dense matrix
head:		.asciiz	"  -----0----------1----------2----------3----------4----------5----------6----------7----------8----------9-----\n"

##### print_dense function code #####
.text
# print_dense will have 3 arguments: $a0 = address of dense matrix, $a1 = matrix width, $a2 = matrix height
print_dense:
	### YOUR CODE HERE ###