#include <stdio.h>
#include <stdlib.h>
#include <time.h>


extern void imgCvtGrayInttoFloat(int* intPixels, float* floatPixels, int width, int height);

void printInt(int* pixels, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%d ", pixels[i * width + j]);
		}
		printf("\n");
	}
}

void printFloat(float* pixels, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("%.2f ", pixels[i * width + j]);
		}
		printf("\n");
	}
}

void randomPixels(int* pixels, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixels[i * width + j] = 84;
		}
	}
}

int main() {
	int height = 0, width = 0;
	clock_t start, end;
	double time_taken = 0, avg_time_taken = 0;

	int image_sizes[3][2] = { {10, 10}, {100, 100}, {1000, 1000} };

	for (int i = 0; i < 3; i++) {
		avg_time_taken = 0;
		time_taken = 0;
		width = image_sizes[i][0];
		height = image_sizes[i][1];

		int* intPixels = (int*)malloc(width * height * sizeof(int));
		float* floatPixels = (float*)malloc(width * height * sizeof(float));

		randomPixels(intPixels, width, height);
		if (i==0){
			printf("Integer pixel values (10*10): \n");
			printInt(intPixels, width, height);

			imgCvtGrayInttoFloat(intPixels, floatPixels, width, height);

			printf("Single Float pixel values: \n");
			printFloat(floatPixels, width, height);
		}


		for (int i = 0; i < 30; i++) {
			start = clock();
			imgCvtGrayInttoFloat(intPixels, floatPixels, width, height);
			end = clock();

			time_taken = ((double)(end - start)) * 1000 / CLOCKS_PER_SEC;
			printf("time_taken: %.5lf ms\n", time_taken);
			avg_time_taken += time_taken;
		}

		avg_time_taken /= 30;
		printf("Average execution time for %dx%d image: %.5lf ms\n", width, height, avg_time_taken);

		free(intPixels);
		free(floatPixels);
	}

	

	return 0;
}
