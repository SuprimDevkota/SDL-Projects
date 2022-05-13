#include <SDL.h>
#include <math.h>
#include <string>
typedef long double ld;

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 1000;


//A long double function that maps x from input_min to input_max to a value between output_min and output_max;
ld map(int x, ld input_min, ld input_max, ld output_min, ld output_max) {
	return (x - input_min) * ((output_max - output_min) / (input_max - input_min)) + output_min;
}


int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* gWindow;
	SDL_Renderer* gRenderer;
	SDL_Event e;
	int MAX_ITERATIONS = 200;

	//For viewing uncomment this line comment the one below -----> SDL_CreateWindowAndRenderer(1920, 1080, 0, &gWindow, &gRenderer);
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &gWindow, &gRenderer);
	SDL_RenderSetLogicalSize(gRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);

	bool quit = false;

	//closer min and max are to each other, deeper you zoom into the fractal
	ld min = -2.0;
	ld max = 1.5;
	ld factor = 1.0;
	int count = 0;
	while (!quit) {

		//as we zoom into the fractal we want to change the parameters that affect its visualization
		max -= 0.1 * factor;
		min += 0.15 * factor;
		factor *= 0.9349;
		MAX_ITERATIONS+= 5;

		//after every 30 frames increase the iteration count by 1.02 times
		if (count > 30) {
			MAX_ITERATIONS *= 1.02;
		}

		//This loop calculates the colour of every pixel on the window
		for (int x = 0; x < SCREEN_WIDTH; ++x) {
			for (int y = 0; y < SCREEN_HEIGHT; ++y) {

				//for every co-ordinate get the real part (a) and imaginary part(b) from our mapping function
				ld a = map(x, 0, SCREEN_WIDTH, min, max);
				ld b = map(y, 0, SCREEN_HEIGHT, min, max);


				//For the fractal function f(z) = z^2 + c, constreal and constimag denote the real and imaginary constant, feel free to play around with these values
				ld constreal = -0.8;
				ld constimag = 0;

				//n keeps track of the iteration
				int n = 0;

				for (int i = 0; i < MAX_ITERATIONS; ++i) {

					//simple formula for multiplication of two complex numbers (a + bi) * (a + bi)
					ld real = a * a - b * b;
					ld imag = 2 * a * b;

					//iterative step where the result is passed back to the fractal function as it's parameter
					a = real + constreal;
					b = imag + constimag;

					//checks if for a certain value, the function diverges to infinity
					if (a + b > 2) {
						break;
					}
					++n;
				}

				//for every pixel we'll assign a brightness value depending upon the value of n reached, higher n = more bright
				ld brightness = map(n, 0, MAX_ITERATIONS, 0, 255);

				//these particular values lie inside our fractal function, brightness condition is just for visuals
				if (n == MAX_ITERATIONS || brightness < 20) {
					brightness = 0;
				}

				int red, green, blue;
				
				//Again feel free to play around with these valueus. They affect the color of the fractal visualized
				red = brightness;
				green = map(brightness * brightness, 0, 255 * 255, 0, 255);
				blue = map(sqrt(brightness), 0, sqrt(255), 0, 255);
				
				SDL_SetRenderDrawColor(gRenderer, red, green, blue, 255);
				SDL_RenderDrawPoint(gRenderer, x, y);

				//This just displays a dot at the center of window
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			}
		SDL_RenderPresent(gRenderer);
		}

		while(SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			if (e.key.keysym.sym == SDLK_q) {
				quit = true;
			}
		}

		//Function to save the bmps
		/*SDL_Surface* sshot = SDL_GetWindowSurface(gWindow);
		SDL_RenderReadPixels(gRenderer, NULL, SDL_PIXELFORMAT_ARGB8888, sshot->pixels, sshot->pitch);
		std::string file = std::to_string(count) + ".bmp";
		SDL_SaveBMP(sshot, file.c_str());
		SDL_FreeSurface(sshot);
		count++;*/
	}
	return 0;
}