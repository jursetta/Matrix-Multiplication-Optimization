//
//  matCalc.c
//  Final_Project
//
//  Created by Jake Ursetta on 5/1/17.
//  Copyright © 2017 Jake Ursetta. All rights reserved.
//

#include "matCalc.h"

void matCalc(float n, float m, float p, int ia, int ja, int ib, int jb, double *C, double *A, double *B, int m0, int n0, int p0){
    int n1; int n2; int p1; int p2; int m1; int m2;
    
    if(n <= 16 && m <= 16 && p <= 16){
        if((int)n % 2 == 0 && (int)p % 2 == 0){
            double acc00, acc01, acc10, acc11;
            for (int i = 0; i < n; i += 2){
                for (int j = 0; j < p; j += 2){
                    acc00 = acc01 = acc10 = acc11 = 0;
                    for (int k = 0; k < m; k++){
                        acc00 += A[ia*m0 + i*m0     + ja + k] * B[ib*p0 + k*p0 + jb + j  ];
                        acc01 += A[ia*m0 + i*m0     + ja + k] * B[ib*p0 + k*p0 + jb + j+1];
                        acc10 += A[ia*m0 + (i+1)*m0 + ja + k] * B[ib*p0 + k*p0 + jb + j  ];
                        acc11 += A[ia*m0 + (i+1)*m0 + ja + k] * B[ib*p0 + k*p0 + jb + j+1];
                    }
                    C[ia*p0 + i*(int)p0     + jb + j  ] += acc00;
                    C[ia*p0 + i*(int)p0     + jb + j+1] += acc01;
                    C[ia*p0 + (i+1)*(int)p0 + jb + j  ] += acc10;
                    C[ia*p0 + (i+1)*(int)p0 + jb + j+1] += acc11;
                }
            }
        }
        else{
            double acc00;
            for (int i = 0; i < n; i += 1){
                for (int j = 0; j < p; j += 1){
                    acc00 = 0;
                    for (int k = 0; k < m; k++){
                        acc00 += A[ia*m0 + i*m0 + ja + k] * B[ib*p0 + k*p0 + jb + j  ];
                    }
                    C[ia*p0 + i*(int)p0 + jb + j] += acc00;
                }
            }
        }
        return;
    }
    
    if(n >= m && n >= p){
        n1 = (int)floor(n/2);;
        n2 = (int)ceil(n/2);
        matCalc(n1, m, p, ia     , ja, ib, jb, C, A, B, m0,  n0,  p0);
        matCalc(n2, m, p, ia + n1, ja, ib, jb, C, A, B, m0,  n0,  p0);
    }
    else if(p >= n && p >= m){
        p1 = (int)floor(p/2);;
        p2 = (int)ceil(p/2);
        matCalc(n, m, p1, ia, ja, ib, jb     , C, A, B, m0,  n0,  p0);
        matCalc(n, m, p2, ia, ja, ib, jb + p1, C, A, B, m0,  n0,  p0);
    }
    else if(m >=n && m >= p){
        m1 = (int)floor(m/2);
        m2 = (int)ceil(m/2);
        matCalc(n, m1, p, ia, ja     , ib     , jb, C, A, B, m0,  n0,  p0);
        matCalc(n, m2, p, ia, ja + m1, ib + m1, jb, C, A, B, m0,  n0,  p0);
    }
    return;
}
