//
//  createMat.c
//  Final_Project
//
//  Created by Jake Ursetta on 5/1/17.
//  Copyright © 2017 Jake Ursetta. All rights reserved.
//

#include "createMat.h"

double ** buildMatrix(int Nrows, int Ncols){
    int n;
    double ** Mat = (double**)calloc(Nrows,sizeof(double*));
    Mat[0] = (double*) calloc(Nrows*Ncols, sizeof(double));
    
    for(n = 1 ; n < Nrows ; n++){
        Mat[n] = Mat[n-1]+Ncols;
    }
    
    return Mat;
}
