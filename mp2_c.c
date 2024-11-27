#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


extern void imgCvtGrayInttoFloat(int* intPixels, float* floatPixels, int width, int height);

// displays the first 10 integer pixel inputs
void printInt(int* pixels, int width, int height) {
	for (int i = 0; i < 10; i++) {
		printf("%d ", pixels[i]);
	}
	printf("\n");
}

// displays the first 10 float pixel outputs
void printFloat(float* pixels, int width, int height) {
	for (int i = 0; i < 10; i++) {
		printf("%.2f ", pixels[i]);
	}
	printf("\n");
}

// fills the the integer pixels array with the value 84
void randomPixels(int* pixels, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i * width + j] = 84;
		}
	}
}

// validates that all float pixel values are equal to 0.33
int validateFloatPixels(float* pixels, int width, int height) {
	float expectedValue = 0.33;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			// round the floating point values to 2 decimal places
			float actualValue = pixels[i * width + j];
			float roundedActual = round(actualValue * 100) / 100;
			float roundedExpected = round(expectedValue * 100) / 100;

			// compare
			if (roundedActual != roundedExpected) {
				return 0; // validation failed
			}
		}
	}
	
	return 1; // validation passed
}

int main() {
	int height = 0, width = 0, isValid = 0;
	clock_t start, end;
	double time_taken = 0, avg_time_taken = 0;

	int image_sizes[3][2] = { {10, 10}, {100, 100}, {1000, 1000} };

	for (int i = 0; i < 3; i++) {
		avg_time_taken = 0;
		time_taken = 0;
		width = image_sizes[i][0];
		height = image_sizes[i][1];

		// initialize the arrays
		int* intPixels = (int*)malloc(width * height * sizeof(int));
		float* floatPixels = (float*)malloc(width * height * sizeof(float));

		// fill intPixels with values
		randomPixels(intPixels, width, height);

		// print integer pixel values
		if (i == 0) {
			printf("First 10 integer pixel values:\n");
			printInt(intPixels, width, height);
		}

		printf("\n%dx%d: \n", width, height);

		// loop for timing the function call
		for (int i = 0; i < 30; i++) {
			start = clock();
			imgCvtGrayInttoFloat(intPixels, floatPixels, width, height);
			end = clock();

			

			//validity check
			isValid = validateFloatPixels(floatPixels, width, height);
			if (isValid == 0) {
				printf("Validation failed.\n");
			}
			else{
				// print float pixel values
				if (i == 0)
				{
					printf("\nFirst 10 float pixel values:\n");
					printFloat(floatPixels, width, height);
					printf("\n");
				}

				time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
				printf("time_taken [%d]: %.5lf ms\n", i+1, time_taken);
				avg_time_taken += time_taken;
			}
			
		}

		// get average execution time
		avg_time_taken /= 30;
		printf("\nAverage execution time for %dx%d image: %.5lf ms\n", width, height, avg_time_taken);

		

		//free the allocated memory
		free(intPixels);
		free(floatPixels);
	}
	
	return 0;
}
