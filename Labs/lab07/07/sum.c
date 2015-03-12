#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <emmintrin.h> /* where intrinsics are defined */

#define CLOCK_RATE_GHZ 2.26e9

/* Time stamp counter */
static __inline__ unsigned long long RDTSC(void) {
    unsigned hi,lo;
    __asm__ volatile("rdtsc" : "=a"(lo),"=d"(hi));
    return ((unsigned long long) lo) | (((unsigned long long)hi) << 32);
}

/* Naive sum given in the lab doc */
int sum_naive( int n, int *a ) {
    int sum = 0;
    for( int i = 0; i < n; i++ ) {
        sum += a[i];
    }
    return sum;
}

/* Unrolled sum given in the lab doc */
int sum_unrolled( int n, int *a ) {
    int sum = 0;

    /* do the body of the work in a faster unrolled loop */
    for( int i = 0; i < n/4*4; i += 4 ) {
        sum += a[i+0];
        sum += a[i+1];
        sum += a[i+2];
        sum += a[i+3];
    }

    /* handle the small tail in a usual way */
    for( int i = n/4*4; i < n; i++ ) {
        sum += a[i];
    }

    return sum;
}

int sum_vectorized( int n, int *a ) {
    /* WRITE YOUR VECTORIZED CODE HERE */
    __m128i sum =  _mm_setzero_si128();
    __m128i sum2 = _mm_setzero_si128();
   int i =0, k = 0;
    for(i = 0; i < ((n>>2) << 2); i +=4) {
        __m128i e  = _mm_loadu_si128( a + i);
       sum = _mm_add_epi32(sum, e);
    }
    int j[4];
    _mm_storeu_si128(j, sum);
  
    int temp = 0;
    for(i ; i < n; i++) {
        temp += *(a + i);
    }
    int total = j[0] + j[1] + j[2] + j[3] + temp;

    // for(k = 0; k < n-i; k++) {
    //     __m128i e  = _mm_loadu_si128( a + k + i);
    //     sum2 = _mm_add_epi32(sum2, e);
    // }

    // int j[5];
    // _mm_storeu_si128(j, sum);
    // _mm_storeu_si128(j + 4, sum2);

    // int x = 0;
    // int total = 0;
    // for(x = 0; x < 5; x++) {
    //     total += j[x];
    // }
            
    return total;
}

int sum_vectorized_unrolled( int n, int *a ) {
    /* UNROLL YOUR VECTORIZED CODE HERE*/
    __m128i sum =  _mm_setzero_si128();
   int i =0, k = 0;
    for(i = 0; i < ((n>>4) << 4); i +=16) {
        __m128i e1  = _mm_loadu_si128( a + i);
       sum = _mm_add_epi32(sum, e1);

       __m128i e2  = _mm_loadu_si128( a + i + 4);
       sum = _mm_add_epi32(sum, e2);

       __m128i e3  = _mm_loadu_si128( a + i + 8);
       sum = _mm_add_epi32(sum, e3);

       __m128i e4  = _mm_loadu_si128( a + i + 12);
       sum = _mm_add_epi32(sum, e4);

    }
    int j[4];
    _mm_storeu_si128(j, sum);
  
    int temp = 0;
    for(i ; i < n; i++) {
        temp += *(a + i);
    }
    int total = j[0] + j[1] + j[2] + j[3] + temp;
  
    return total;
}

void benchmark( int n, int *a, int (*computeSum)(int,int*), char *name ) {
    /* warm up */
    int sum = computeSum( n, a );

    /* measure */
    unsigned long long cycles = RDTSC();
    sum += computeSum( n, a );
    cycles = RDTSC()-cycles;
    
    double microseconds = cycles/CLOCK_RATE_GHZ*1e6;
    
    /* report */
    printf( "%20s: ", name );
    if(sum == 2*sum_naive(n,a)) {
        printf("%.2f microseconds\n", microseconds);
    } else {
        printf("ERROR!\n");
    }
}

int main( int argc, char **argv ) {
    const int n = 7777; 
    
    /* init the array */
    srand48( time( NULL ) );
    int a[n] __attribute__ ((aligned (16))); /* align the array in memory by 16 bytes */
    for( int i = 0; i < n; i++ ) {
        a[i] = lrand48();
    }
    
    /* benchmark series of codes */
    benchmark( n, a, sum_naive, "naive" );
    benchmark( n, a, sum_unrolled, "unrolled" );
    benchmark( n, a, sum_vectorized, "vectorized" );
    benchmark( n, a, sum_vectorized_unrolled, "vectorized unrolled" );

    return 0;
}
