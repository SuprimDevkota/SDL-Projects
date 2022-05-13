#include "..\Headers\Header.h"

int main(int argc, char* argv[])
{
	int c;
	printf("%s:\n", "Select the sorting algorithm you want to visualize");
	printf("%s - 1\n%s - 2\n%s - 3\n%s - 4\n%s - 5\n", "Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Quick Sort");
	scanf_s("%d", &c);

	//Starts up SDL and create window
	if (!init()) {
		printf("Failed to initialize!");
	}
	else
	{	
		//Clear screen
		SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xff);
		SDL_RenderClear(gRenderer);

		//Draw Bar graphs
		DrawBars(ScreenWidth, NumberOfBars);

		//Traverse bars and sort them;
		switch (c) {
		case 1: 
			bubble_sort(NumberOfBars);
			break;
		case 2:
			insertion_sort(NumberOfBars);
			break;
		case 3:
			selection_sort(NumberOfBars);
			break;
		case 4:
			merge_sort(0, NumberOfBars-1);
			break;
		case 5:
			quick_sort(0, NumberOfBars - 1);
			break;
		default:
			printf("%s", "Please enter a valid choice.");
			return 0;
			break;
		}
		
		//Update screen
		SDL_RenderPresent(gRenderer);

		//Quit when the user wants
		SDL_Event e;
		
		bool quit = false;
		while (!quit)
		{
			while (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT) {
					quit = true;
				}

				if (e.key.keysym.sym == SDL_SCANCODE_ESCAPE) {
					quit = true;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}