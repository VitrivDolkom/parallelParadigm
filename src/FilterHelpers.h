#ifndef FILTERHELPERS_H_
#define FILTERHELPERS_H_

#include "Pixel.h"

bool comparaTwoPixels(Pixel p1, Pixel p2) {
	if (p1.getR() != p2.getR()) {
		return p1.getR() < p2.getR();
	}

	if (p1.getG() != p2.getG()) {
		return p1.getG() < p2.getG();
	}

	return p1.getB() < p2.getB();
}

#endif /* FILTERHELPERS_H_ */
