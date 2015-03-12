/**********************************************************************
 
 biggestInt.c
 
 This file is a program that finds some information about a system's
 C data types.  It does this by initializing a variable of each type
 to 1 and counting or shifting until that type wraps around.  When
 it discovers the value, it prints it to the screen.
 
 **********************************************************************/

/* include I/O routines. */
#include <stdio.h>

int main() {
    
    /* declare the variables */
    unsigned int next_uint, biggest_uint;
    long next_long, biggest_long;
    int negative_int, double_negative_int;
    
    /**********************************************************************
     TEST UNSIGNED INT DATA TYPE
     
     Here we shift the value 1 left until it becomes zero.  This way,
     the value just before the shift that zeros the variable has 1 as
     its MSB and 0 for all other bits.  (i.e., 0x80000...).
     **********************************************************************/
    
    /* Start the variable of interest at 1 */
    next_uint=1;
    
    /* Test the next value of the varible.  If it is still greater than
     zero, we haven't wrapped around yet so shift it right and try
     again. */
    while( next_uint > 0 ) {

        /* remember the current value */
        biggest_uint = next_uint;
        
        /* shift to find the next value */
        next_uint=next_uint<<1;
        
    }
    // There are 32 bits for unsign int, shift 1 bit to the right each time means multiply by the power of 2
    // till it the last bit which is 31th (from 0 to 31) ----> 1 000...00 ----> value of biggest_uint = 1* 2^31 + 0... = 2^31
    
    /* Print the final value */
    printf("\nThe most significant bit of an unsigned int is %u\n\n",
           biggest_uint);  // 2^31
    
    /**********************************************************************
     TEST SIGNED LONG DATA TYPE
     
     Here we shift the value 1 left and OR in a 1 in the LSB until it
     becomes negative.  This way the value just before the negative
     value is the largest positive value.  (i.e., 0x7FFFFF...).  NOTE:
     Counting to this value from 1 would take a long time!
     **********************************************************************/
    
    /* Start the variable of interest at 1 */
    next_long=1;
    
    /* Test the next value of the varible.  If it is still greater than
     zero, we haven't wrapped around yet so shift it left and try
     again. */
    
    while( next_long > 0 ) {
        
        /* remember the current value */
        biggest_long = next_long;
//        printf("biggest_long = %ld \n",biggest_long);
        
        /* shift a 1 into the LSB to find the next value */
        next_long=next_long<<1;
        next_long=next_long | 1;
        
    }
    //There are 64 bits C have for long, each shift 1 bit to the right and turn on all the bits
    // ---> till the last bit 31 ---->  2^64
    
    /* Print the largest value */
    printf("\nThe largest signed long is %ld\n\n", biggest_long);
    
    /**********************************************************************
     TEST SIGNED INT DATA TYPE
     
     Here we shift the value 1 left until it becomes negative (i.e.,
     0x80000...).  This way we can find the most negative representable
     value.
     **********************************************************************/
    
    /* Start the variable of interest at 1 */
    negative_int=1;
    
    /* Test the next value of the varible.  If it is still greater than
     zero, we haven't reached the MSB yet so shift it left and try
     again. */
    while( negative_int > 0 ) {
        
        /* shift to find the next value */
        negative_int=negative_int<<1;
        
    }
    
    /* Print the largest value */
    printf("\nThe largest negative signed int is %d\n\n", negative_int);
    
    /**********************************************************************
     BONUS
     
     2's Complement number lines have one more negative number than they
     do positive numbers.  That is, the most negative number does not
     have a positive counter part.  If you attempt to negate the most
     negative number, what do you get?
     **********************************************************************/
    
    /* Invert the most negative int */
    double_negative_int = -negative_int;
    
    /* Print the answer */
    printf("\nIf you perform two's complement negation on the most negative signed int you get %d\n\n", 
           double_negative_int);
    
    return 0;

    //#3 Same 
    //#4 Different computer ---> different system ---> different bits
    //#5
    
}