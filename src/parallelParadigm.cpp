// todo: includes
#include <iostream>
#include <filesystem>
#include <string>
#include <time.h>
#include <omp.h>

// todo: read and write png
#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"

//todo: namespaces
namespace fs = std::filesystem;

// todo: header files
#include "OpenMpFilters.h"
#include "ConsecutiveFilters.h"
#include "Defines.h"

// todo: defines
#define MEDIAN_FILTER_SIZE 7
#define EXECUTE_NUM 100

void timeit(void f(unsigned char* rgb, const int& n, const int& width, const int& filterSize),
		unsigned char* rgb, const int& n, const int& width, const int& filterSize) {

//	clock_t startTime = clock();
	double startTime = omp_get_wtime();

	for (int i = 0; i < EXECUTE_NUM; ++i) {
		f(rgb, n, width, filterSize);
	}

	double endTime = omp_get_wtime();
	double executeTime = (endTime - startTime) / EXECUTE_NUM;
	std::cout << executeTime << "\n";
//	clock_t endTime = clock();
//	double executeTime = (double) (endTime - startTime) / (CLOCKS_PER_SEC * EXECUTE_NUM);
}

void rgbaToRgb(unsigned char* img, unsigned char* rgb, const int& n, const int& channels) {
	int j = -1;

	for (int i = 0; i < n; i += channels) {
		rgb[++j] = img[i];
		rgb[++j] = img[i + 1];
		rgb[++j] = img[i + 2];
	}
}

void filterImage(const char* pathToImage, const char* pathToResult) {
	int width, height, channels;

	unsigned char* img = stbi_load(pathToImage, &width, &height, &channels, 0);
	int n = width * height * CHANNEL_NUM;
	unsigned char* rgb;

	if (channels > CHANNEL_NUM) {
		rgb = new unsigned char[n];
		rgbaToRgb(img, rgb, width * height * channels, channels);
	} else {
		rgb = img;
	}

//	timeit(negativeFilterConsistently, rgb, width, height);
//	timeit(negativeFilterOpenMp, rgb, width, height);
//	negativeFilterConsistently(rgb, width, height);
//	negativeFilterOpenMp(rgb, width, height);

	timeit(medianFilterOpenMp, rgb, n, width, MEDIAN_FILTER_SIZE);
//	timeit(medianFilterConsistently, rgb, n, width, MEDIAN_FILTER_SIZE);
//	medianFilterConsistently(rgb, n, width, MEDIAN_FILTER_SIZE);
//	medianFilterOpenMp(rgb, n, width, MEDIAN_FILTER_SIZE);

	stbi_write_png(pathToResult, width, height, CHANNEL_NUM, rgb, width * CHANNEL_NUM);
	stbi_image_free(img);
}

std::string getFileName(const std::string& path) {
	return path.substr(path.find_last_of("/\\") + 1);
}

int main() {
	std::string baseFolderPath = "./images/base/";
	std::string resultFolderPath = "./images/result/";
	std::string fileName;

// clear files in result folder
	for (const auto& file : fs::directory_iterator(resultFolderPath)) {
		fileName = getFileName(file.path().generic_string());
		fs::remove(resultFolderPath + fileName);
	}

// fill result folder with pictures
	for (const auto& file : fs::directory_iterator(baseFolderPath)) {
		fileName = getFileName(file.path().generic_string());
		filterImage((baseFolderPath + fileName).c_str(), (resultFolderPath + fileName).c_str());
	}

//	filterImage("./images/base/300x300.png", "./images/result/300x300.png");
	return 0;
}
