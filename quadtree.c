#include "quadtree_header.h"
/* should work with:
gcc -ansi -Wall quadtree.c -o t
t input.txt
(#instead of i < input.txt) */

int init(int *width, int *pix, FILE *input_file, const char *filename){/* designed to initialise the variables from the the file */
	if (!input_file){
		/* Argument is non-existing file */
		/* give error message and exit */
		fprintf(stderr, "Can't read %s\n", filename);
		return 0;
	}
	if ((fscanf(input_file, "%d", width) + fscanf(input_file, "%d", pix)) != 2){
		/* scans the width and number of black pixels while checking for errors */
		fprintf(stderr, "Invalid input\n");
		return 0;
	}
	return 1;
}

void add_black(int ** image_array, int black, FILE *input_file){
	int k, r, c;
	for (k = 0; k < black; k++){
		fscanf(input_file, "%d %d", &r, &c);
		image_array[c][r] = 1;
	}/* itterates through input file and adds in black pixels */
}

int check_color(int ** image_array, int top, int left, int size){
	int i, j, black = 0, white = 0;
	for (i = left; i < (size+left); i++){
		for (j = top; j < (size+top); j++){
			if (image_array[i][j] == 0){
				white++;
			} else if (image_array[i][j] == 1){
				black++;
			}
		}
	}/* counts the ammount of black & white pixles in the quadrant supplied */

	if ((black == 0) && (white != 0)){
		return 0;
	} else if ((black != 0) && (white == 0)){
		return 1;
	} else if ((black != 0) && (white != 0)){
		return 2;
	}else{
		return 3;
	}/* tells quadtree whether the quadrant is black, white or mixed */
}

void quadtree(int top, int left, int size, int ** image_array){
	switch(check_color(image_array, top, left, size)){
		case 0:
			break;/* ignores white nodes */
		case 1:
			printf("Black terminal node at position (%d,%d) with size %d\n", top, left, size);
			break;/* outputs location of black nodes */
		case 2:
			quadtree(top,left,size/2, image_array);  /* north-west */
			quadtree(top,left+size/2,size/2, image_array); /* north-east */
			quadtree(top+size/2,left,size/2, image_array); /* south-west */
			quadtree(top+size/2,left+size/2,size/2, image_array);  /* south-east */
			break;/* recursive algorithm to split into quadrants */
		default:
			fprintf(stderr, "Data Error Occured\n");
	}
}

int main(int argc, char const *argv[]){
	int size, black, i, j;
	FILE *input_file;

	if (argc < 2){
		fprintf(stderr, "No read file\n");
		return 0;
	}

	input_file = fopen(argv[1], "r");

	if (init(&size, &black, input_file, argv[1]) == 0){
		return 0 ;
	} /* ititialises variables */

	int ** image = (int**)malloc(sizeof(int*)*size);
	for(i =0 ; i <size;i++){
		*(image+i) = (int*)malloc(sizeof(int)*size);
	}/* sets up dynamic 2d array */
	for(i =0 ; i <size;i++){
			for(j =0 ; j <size;j++){
				image[i][j]=0;
			}/* fills in white 2d array */
		}

	add_black(image, black, input_file);
	quadtree(0, 0, size, image);
	printf("\n");

	for(i = 0; i < size; i++){
		free(image[i]);
	}/* Dealocates the memory previously allocated to the 2d array by malloc */
	free(image);
	fclose(input_file);

	return 0;
}