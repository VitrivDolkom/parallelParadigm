#ifndef CONSECUTIVEFILTERS_H_
#define CONSECUTIVEFILTERS_H_

#include <iostream>

#include <algorithm>
#include <vector>
#include <time.h>

#include "Pixel.h"
#include "FilterHelpers.h"
#include "Defines.h"

void medianFilterConsistently(unsigned char* rgb, const int& n, const int& width, const int& filterSize) {
	const int shift = (filterSize / 2);
	int medianIndex, l;

	for (int i = 0; i < n; i += CHANNEL_NUM) {
		std::vector<Pixel> locality;

		for (int j = -shift; j <= shift; ++j) {
			for (int k = -shift; k <= shift; ++k) {
				l = i + width * j * CHANNEL_NUM + k * CHANNEL_NUM;

				if (l > -1 && l < (n - 2)) {
					Pixel p(rgb[l], rgb[l + 1], rgb[l + 2], l);
					locality.push_back(p);
				}
			}
		}

		std::nth_element(locality.begin(), locality.begin() + locality.size() / 2, locality.end(),
				comparaTwoPixels);

		medianIndex = locality[locality.size() / 2].getIndex();
		rgb[i] = rgb[medianIndex];
		rgb[i + 1] = rgb[medianIndex + 1];
		rgb[i + 2] = rgb[medianIndex + 2];

		locality.clear();
		locality.shrink_to_fit();
	}
}

void negativeFilterConsistently(unsigned char* rgb, const int& width, const int& height) {
	const int RGB_MAX = 255;
	const int n = width * height * CHANNEL_NUM;

	for (int i = 0; i < n; ++i) {
		rgb[i] = RGB_MAX - rgb[i];
	}
}

#endif /* CONSECUTIVEFILTERS_H_ */
