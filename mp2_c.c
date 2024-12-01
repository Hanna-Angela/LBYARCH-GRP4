#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// declares an external function
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

// converting int pixels to float pixels
void solveExpectedValue(int* intPixels, int width, int height, float* expectedPixels) {
	float temp = (float)1.0f / 255.0f;
	float expectedValue = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			expectedValue = intPixels[i * width + j] * temp;
			expectedPixels[i * width + j] = expectedValue;
		}
	}
}

// validates that all float pixel values are equal to 0.33
int validateFloatPixels(int* intPixels, float* pixels, int width, int height, float* expectedPixels) {

	float expectedValue = 0, actualValue = 0, roundedActual = 0, roundedExpected = 0;

	solveExpectedValue(intPixels, width, height, expectedPixels);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			//calculating the expected value
			expectedValue = expectedPixels[i * width + j];

			// round the floating point values to 2 decimal places
			actualValue = pixels[i * width + j];
			roundedActual = (float)(round(actualValue * 100) / 100);
			roundedExpected = (float)(round(expectedValue * 100) / 100);

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

	int* intPixels;
	float* floatPixels;
	float* expectedPixels;

	int image_sizes[3][2] = { {10, 10}, {100, 100}, {1000, 1000} };

	for (int i = 0; i < 3; i++) {
		avg_time_taken = 0;
		time_taken = 0;
		width = image_sizes[i][0];
		height = image_sizes[i][1];

		// initialize the arrays
		intPixels = (int*)malloc(width * height * sizeof(int));
		floatPixels = (float*)malloc(width * height * sizeof(float));
		expectedPixels = (float*)malloc(width * height * sizeof(float));

		// fill intPixels with values
		randomPixels(intPixels, width, height);

		// print integer pixel values
		if (i == 0) {
			printf("First 10 integer pixel values:\n");
			printInt(intPixels, width, height);
		}

		printf("\n---------- %dx%d ----------\n", width, height);

		// loop for timing the function call
		for (int i = 0; i < 30; i++) {
			start = clock();
			imgCvtGrayInttoFloat(intPixels, floatPixels, width, height);
			end = clock();

			//validity check
			isValid = validateFloatPixels(intPixels, floatPixels, width, height, expectedPixels);

			if (i == 0) {
				printf("\n[x86-64] First 10 float pixel values:\n");
				printFloat(floatPixels, width, height);

				printf("\nFor correctness check:");
				printf("\n[C] First 10 float pixel values:\n");
				printFloat(expectedPixels, width, height);
				printf("\n");
			}

			if (isValid == 0) {
				printf("Incorrect output [%d].\n", i+1);
			}

			time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
			avg_time_taken += time_taken;
		}

		// get average execution time
		avg_time_taken /= 30;
		printf("Average execution time for %dx%d image: %.5lf ms\n", width, height, avg_time_taken);

		//free the allocated memory
		free(intPixels);
		free(floatPixels);
	}

	return 0;
}
