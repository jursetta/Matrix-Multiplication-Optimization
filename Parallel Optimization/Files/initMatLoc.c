//
//  initMatLoc.c
//  Final_Project
//
//  Created by Jake Ursetta on 5/3/17.
//  Copyright © 2017 Jake Ursetta. All rights reserved.
//

#include "initMatLoc.h"

void initMatLoc(int proc, int matSize, int * indexMat){
    
    int div = floor((float)matSize/(float)proc);
    
    int rem = (matSize - div*proc);
    
    indexMat[0] = 0;
    
    for(int i = 0; i < proc; i++){
        if(i < rem){
            indexMat[proc + i] =  div + 1;
        }
        else{
            indexMat[proc + i] = div;
        }
    }
    
    for(int i = 1; i < proc; i++){
        indexMat[i] =  indexMat[i-1] + indexMat[proc + i-1];
    }
    
    return;
}
