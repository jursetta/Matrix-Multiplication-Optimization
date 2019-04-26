//
//  main.c
//  Final_Project
//
//  Created by Jake Ursetta on 5/1/17.
//  Copyright © 2017 Jake Ursetta. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "createMat.h"
#include "matCalc.h"

int main(int argc, const char * argv[]) {
    
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
    
    int mA, nA, mB, nB, i, j;
    
    fscanf(A_file,"%d %d",&mA,&nA);
    fscanf(B_file,"%d %d",&mB,&nB);
    
    double ** A  = buildMatrix(mA, nA);
    double ** B  = buildMatrix(mB, nB);
    double ** C  = buildMatrix(mA, nB);
    
    
    
    for (i = 0; i < mA; i++){
        for (j = 0; j < nA; j++){
            fscanf(A_file,"%lf",&A[i][j]);
        }
    }
    
    for (i = 0; i < mB; i++){
        for (j = 0; j < nB; j++){
            fscanf(B_file,"%lf",&B[i][j]);
        }
    }
    
    matCalc(mA, nA, nB, 0.0, 0.0, 0.0, 0.0, *C, *A, *B, nA,  mA,  nB);
    
    fprintf(C_file, "%d %d\n",mA,nB);
    for(i = 0; i < mA; i++){
        for(j = 0; j < nB; j++){
            fprintf(C_file, "%f ",*(C[i] + j));
        }
        fprintf(C_file, "\n");
    }
    
    
    fclose(A_file);
    fclose(B_file);
    fclose(C_file);
    
    free(A);
    free(B);
    free(C);
    

    
    
    return 0;
}
