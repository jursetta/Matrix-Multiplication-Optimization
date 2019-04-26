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
#include <mpi.h>
#include "createMat.h"
#include "matCalc.h"
#include "initMatLoc.h"

int main(int argc, char ** argv) {
    
    int myrank, nprocs;
    const int serverRank = 0;
	int mpi_error_code;
    
    MPI_Status status;
    
    mpi_error_code = MPI_Init(&argc,&argv);
    mpi_error_code = MPI_Comm_size(MPI_COMM_WORLD,&nprocs);
    mpi_error_code = MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    
    
    if (myrank == serverRank){
        

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

        FILE *A_file;
        FILE *B_file;
        FILE *C_file;

        A_file = fopen(argv[1],"r");
        B_file = fopen(argv[2],"r");
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
        

		int **splitInfo = buildMatrixInt(2,nprocs);
        
    	initMatLoc(nprocs, mA, *splitInfo);

        
        for(i = 1; i < nprocs; i++){
            MPI_Send((splitInfo[1]+i)        ,1                   ,MPI_INT   , i,0,MPI_COMM_WORLD); 
            MPI_Send(&nA                     ,1                   ,MPI_INT   , i,1,MPI_COMM_WORLD);
            MPI_Send(&nB                     ,1                   ,MPI_INT   , i,2,MPI_COMM_WORLD);
            MPI_Send(&A[*(splitInfo[0]+i)][0],*(splitInfo[1]+i)*nA,MPI_DOUBLE, i,3,MPI_COMM_WORLD);  
            MPI_Send(&B[0][0]                ,mB*nB               ,MPI_DOUBLE, i,4,MPI_COMM_WORLD);
        }
        
        matCalc(*(splitInfo[1]), nA, nB, 0.0, 0.0, 0.0, 0.0, *C, *A, *B, nA,  *(splitInfo[1]),  nB);

        for(i = 1; i < nprocs; i++){
			MPI_Recv(C[*(splitInfo[0]+i)], *(splitInfo[1]+i)*nB, MPI_DOUBLE, i, 5, MPI_COMM_WORLD,&status);
        }

        
        
        //MPI_Gather(&C[0][0],*(splitInfo[1])*nA, MPI_DOUBLE, &Cout[0][0], *(splitInfo[1])*nA, MPI_DOUBLE, 0, MPI_COMM_WORLD);

         //GATHER SOME STUFF
        
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
        
    }
    
    else{

        // RECIEVE SOME STUFF
        int mA, nA, nB, i, j;
        MPI_Recv(&mA, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
        MPI_Recv(&nA, 1, MPI_INT, 0, 1, MPI_COMM_WORLD,&status);
        MPI_Recv(&nB, 1, MPI_INT, 0, 2, MPI_COMM_WORLD,&status);
                
        double ** A  = buildMatrix(mA, nA);
        double ** B  = buildMatrix(nA, nB);
        double ** C  = buildMatrix(mA, nB);
                
        MPI_Recv(A[0], mA*nA, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD,&status);
        MPI_Recv(B[0], nA*nB, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD,&status);

        matCalc(mA, nA, nB, 0.0, 0.0, 0.0, 0.0, *C, *A, *B, nA,  mA,  nB);




		MPI_Send(&C[0][0], mA*nB, MPI_DOUBLE, 0, 5, MPI_COMM_WORLD);

        	        
        //MPI_Gather(&C[0][0],mA*nB, MPI_DOUBLE, &Cout[splitRow-1][0], mA*nB, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    }
    
    MPI_Finalize();
 
    
    return 0;
}
