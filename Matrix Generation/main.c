
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
// Compute matrix product
    FILE *A_file;
    FILE *B_file;
	srand (100);

	A_file = fopen("A3","w");
	B_file = fopen("B3","w");

	//double a1,b1;

    fprintf(A_file, "%d %d\n",5000,5000);
	fprintf(B_file, "%d %d\n",5000,5000);
    for(int i = 0; i < 5000; i++){
        for(int j = 0; j < 5000; j++){
			//a1 = rand();
			//b1 = rand();
            fprintf(A_file, "%lf ",(float)rand()/100.0);
			fprintf(B_file, "%lf ",(float)rand()/100.0);
        }
        fprintf(A_file, "\n");
		fprintf(B_file, "\n");
    }
      
    fclose(A_file);
    fclose(B_file);


	return 0;
}
