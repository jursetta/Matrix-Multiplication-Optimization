
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "createMat.h"

//double A[2000][2000];
//double B[2000][2000];
//double C[2000][2000];

int main(int argc, char * argv[]) {
// Compute matrix product
    FILE *A_file;
    FILE *B_file;
    FILE *C_file;

    A_file = fopen(argv[1],"r");
    B_file = fopen(argv[2],"r");
    
    char * directName = dirname((char*)argv[0]);
    
    int len1 = (int)strlen(basename((char*)argv[1]));
    int len2 = (int)strlen(basename((char*)argv[2]));
    int dir  = (int)strlen(directName);
    char output[dir + 7];
    sprintf(output, "%s/Output",directName);
    mkdir(output,07777);
    char *arg1p = basename((char*)argv[1]);
    char *arg2p = basename((char*)argv[2]);

    char fileName[dir + len1 + len2 + 6];
    sprintf(fileName, "%s/Output/%s_Mult_%s",  directName, arg1p, arg2p);
    C_file = fopen(fileName,"w");
    int mA, nA, mB, nB, i, j, k;   
	//char str1[10], str2[10], str3[10], str4[10];
   	fscanf(A_file,"%d %d",&mA,&nA);
    fscanf(B_file,"%d %d",&mB,&nB);
	//mA = atof(str1);
	//nA = atof(str2);
	//mB = atof(str3);
	//nB = atof(str4);

	double ** A = buildMatrix(mA,nA);
	double ** B = buildMatrix(mB,nB);
	double ** C = buildMatrix(mA,nB);

// Reading into A and B matrices
    for (i = 0; i < mA; i++){
        for (j = 0; j < nA; j++){
            fscanf(A_file,"%lf",A[i]+j);
        }
    }
    
    for (i = 0; i < mB; i++){
        for (j = 0; j < nB; j++){
            fscanf(B_file,"%lf",B[i]+j);
        }
    }

// Update progress
	printf("Computing matrix product...\n");

	// Begin clock
	clock_t begin, end;
	double time_spent;
	begin = clock();

// Calculating matrix-matrix multipication
	for (i = 0; i < mA; i++)
	{
		for (j = 0; j < nB; j++)
		{
			for (k = 0; k < nA; k++)
			{
				*(C[i]+j) += *(A[i]+k)* *(B[k]+j);
			}
		}
	}


// Stop clock
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Time spent computing matrix product: %lf\n",time_spent);

// Printing to output file
    fprintf(C_file, "%d %d\n",mA,nB);
    for(i = 0; i < mA; i++){
        for(j = 0; j < nB; j++){
            fprintf(C_file, "%lf ",*(C[i]+j));
        }
        fprintf(C_file, "\n");
    }
    
    
    fclose(A_file);
    fclose(B_file);
    fclose(C_file);

	return 0;
}
