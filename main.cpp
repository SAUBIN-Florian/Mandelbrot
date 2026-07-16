#include <iostream>

#include <SFML/Graphics.hpp>

#define WIDTH 800
#define HEIGHT 600
#define MAX_ITER 500


struct Complex {
	double re;
	double im;
};

Complex multiply(Complex a, Complex b) {
	return {
		a.re * b.re - a.im * b.im,
		a.re * b.im + a.im * b.re
	};
}

Complex square(Complex c) {
	return {
		c.re * c.re - c.im * c.im,
		2 * c.re * c.im
	};
}

void mandelbrot(sf::Image& image) {
	const double re_min = -2.0, re_max = 1.0;
	const double im_min = -1.5, im_max = 1.5;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			const double real = re_min + x * ((re_max - re_min) / WIDTH);
			const double imag = im_max - y * ((im_max - im_min) / HEIGHT);
			Complex z = {0, 0};
			Complex c = {real, imag};

			int iter = 0;
			while (iter < MAX_ITER) {
				z = square(z);
				z.re += c.re;
				z.im += c.im;

				iter++;
				double delta = z.re * z.re + z.im * z.im;

				if (delta > 4) break;
			}

			if (iter == MAX_ITER) {
				image.setPixel(x, y, sf::Color::Black);
			} else {
				image.setPixel(x, y, sf::Color(iter - 255, 10, iter));
			}
		}
	}
}


int main() {
	std::cout << "Mandelbrot Visualizer" << std::endl;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Visualizer");
	window.setFramerateLimit(60);

	sf::Image image;
	image.create(WIDTH, HEIGHT,	sf::Color::Black);
	mandelbrot(image);

	sf::Texture texture;
	texture.loadFromImage(image);

	sf::Sprite sprite(texture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color(38, 38, 38, 255));

		window.draw(sprite);

		window.display();
	}

	return 0;
}
