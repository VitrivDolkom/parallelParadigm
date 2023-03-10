#ifndef PIXEL_H_
#define PIXEL_H_

class Pixel {
public:
	Pixel(int r, int g, int b, int index) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->index = index;
	}

	int getR() {
		return r;
	}

	int getG() {
		return g;
	}

	int getB() {
		return b;
	}

	int getIndex() {
		return index;
	}

private:
	int r, g, b, index;
};

#endif /* PIXEL_H_ */
