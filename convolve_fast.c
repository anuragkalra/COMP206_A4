#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fast_filter.h"
#include <time.h>

FILE *input;
FILE *output;

int main(int argc, char* argv[]){
	
	clock_t begin, end;
	double time_spent;
	begin = clock();
	
	///////////////////Constructs img_data/////////////////////////////
	input = fopen(argv[1], "rb");//opens first arg in read binary mode
	fseek(input, 0, SEEK_END); //goes to the 0 position of the file
	long file_size = ftell(input);
	unsigned char img_data[file_size];
	fseek(input, 0, SEEK_SET); //goes to current location of pointer
	fread(img_data, file_size, 1, input); //places all data into img_data
	fclose(input);
	///////////////////////////////////////////////////////////////////
		

	//////////////saves filter_width and fills filter_weights array///
	int filter_width = atoi(argv[3]);
	int filter_width_squared = filter_width*2;
	float filter_weights[filter_width_squared];
	int i;
	for(i = 0; i < filter_width_squared; i++){
		filter_weights[i] = (float) atoi(argv[4 + i]);
	}
	///////////////////////////////////////////////////////////////////////
	
	output = fopen(argv[2], "wb");
		

	unsigned char out_img_data[file_size];
	doFiltering(img_data, filter_weights, filter_width, out_img_data);
	
	fwrite(out_img_data, 1, file_size + 1, output);
	fclose(output);

	//FUNCTION SIGNATURE//
	//void doFiltering( unsigned char* img_data, float* filter_weights, int filter_width, unsigned char* out_img_data);


	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("Total execution time = %f\n", time_spent);
	
	return 0;
}
