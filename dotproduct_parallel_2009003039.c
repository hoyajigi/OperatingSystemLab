/***************************************************************************
*   This is a simple serial program which computes the dot product of two  vectors.  *
****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define VECLEN 100000000
#define THREADLEN 8
/*   
The following structure contains the necessary information  
to allow the function "dotprod" to access its input data and 
place its output so that it can be accessed later. 
*/

typedef struct {
  double      *a;
  double      *b;
  double     sum; 
  int    veclen; 
} DOTDATA;


DOTDATA dotstr; 
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
/*
We will use a function (dotprod) to perform the scalar product. 
All input to this routine is obtained through a structure of 
type DOTDATA and all output from this function is written into
this same structure.  While this is unnecessarily restrictive 
for a sequential program, it will turn out to be useful when
we modify the program to compute in parallel.
*/

void dotprod(void *data) {
   int i,start,end;
   double mysum, *x, *y;
   start=*((int *)data);
   end = start+dotstr.veclen/THREADLEN;
   x = dotstr.a;
   y = dotstr.b;

/*
Perform the dot product and assign result
to the appropriate variable in the structure. 
*/

   mysum = 0.0;
   for (i=start; i<end ; i++) {
      mysum += (x[i] * y[i]);
    }
   pthread_mutex_lock( &mutex1 );
   dotstr.sum += mysum;
   pthread_mutex_unlock( &mutex1 );
}

/*
The main program initializes data and calls the dotprd() function.
Finally, it prints the result.
*/

int main (int argc, char *argv[]) {
	int i,len;
	double *a, *b;
	pthread_t thread[THREADLEN];
	int lens[THREADLEN];
	/* Assign storage and initialize values */
	len = VECLEN;
	a = (double*) malloc (len*sizeof(double));
	b = (double*) malloc (len*sizeof(double));
	  
	for (i=0; i<len; i++) {
	  a[i]=1;
	  b[i]=a[i];
	  }
	for(i=0;i<THREADLEN;i++){
		lens[i]=VECLEN/THREADLEN*i;
	}
	dotstr.veclen = len; 
	dotstr.a = a; 
	dotstr.b = b; 
	dotstr.sum=0;
	
	/* Perform the  dotproduct */
	for(i=0;i<THREADLEN;i++){
		pthread_create(&thread[i],NULL,(void *)&dotprod,(void*)&lens[i]);
	}
	
	for(i=0;i<THREADLEN;i++){
		pthread_join(thread[i],NULL);
	}
	/* Print result and release storage */
	printf ("Sum =  %lf \n", dotstr.sum);
	free (a);
	free (b);
	
	return 0;
}
