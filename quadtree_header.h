#include <stdio.h>
#include <stdlib.h>

int init(int *width, int *pix, FILE *input_file, const char *filename);
/* designed to initialise the core variables (size and black) of the program from the the file */

void add_black(int ** image_array, int black, FILE *input_file);
/* itterates through input file scanning the coordinates on each line
 and then adds in black pixels to the 2D array*/

int check_color(int ** image_array, int top, int left, int size);
/* quadtree() passes along a quadrant of the 2D array to check_color() which then counts
 the number of black and white pixels contained in the area, it will then let quadtree()
  know if the quadrant provided is fully black, white or a mix of both  */

void quadtree(int top, int left, int size, int ** s);
/* quadtree() contains a recursive algorithm to split the 2D array in to 4 quadrant
 multiple times untill each quadrant only contains one color */