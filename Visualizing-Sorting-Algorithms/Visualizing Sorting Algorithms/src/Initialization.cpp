#include "..\Headers\Header.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
int BarWidth;
int BarPadding;

//Initialization function Definitions
bool init()
{
	//Seed the random number generator
	srand((unsigned int)time(NULL));

	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	else
	{
		//Create Window
		gWindow = SDL_CreateWindow("Sorting Arrays", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created. SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize Renderer color
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xff);
			}
		}
	}
	return success;
}

void close()
{
	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL Subsystem
	SDL_Quit();
}

void DrawBars(int ScreenWidth, int NumberofBars)
{
	BarWidth = round(float(0.9 * ScreenWidth) / NumberOfBars);
	BarPadding = round(float(0.1 * ScreenWidth) / NumberOfBars);

	unsigned int low_limit = 10;
	unsigned int high_limit = 610;

	std::vector<unsigned int> heights;

	int distri = round(float(high_limit - low_limit) / NumberOfBars);

	for (int i = low_limit; i < high_limit; i += distri) {
		heights.push_back(i);
	}

	std::shuffle(heights.begin(), heights.end(), std::default_random_engine());

	SDL_Rect DrawClips[NumberOfBars];

	int cnt = 0;
	int i = 5;
	for (auto& n : heights)
	{
		int Height = n;
		DrawClips[cnt] = { i, ScreenHeight - 20, BarWidth, -Height };
		bar[cnt].bPosition = i;
		bar[cnt].bHeight = Height;
		cnt++;
		i += BarWidth + BarPadding;

	}
	SDL_SetRenderDrawColor(gRenderer, 105, 105, 105, 0xff);
	SDL_RenderFillRects(gRenderer, DrawClips, NumberOfBars);
	SDL_RenderPresent(gRenderer);

}

SDL_Rect* CompareBars(LBar i, LBar j)
{
	//Setting the clipping areas for bars under comparison
	SDL_Rect Clips[2];
	Clips[0] = { i.bPosition, ScreenHeight - 20, BarWidth, -i.bHeight };
	Clips[1] = { j.bPosition, ScreenHeight - 20, BarWidth, -j.bHeight };

	//Color the bars under comparison from gray to blue
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
	SDL_RenderFillRect(gRenderer, &Clips[0]);
	SDL_RenderFillRect(gRenderer, &Clips[1]);
	frames++;
	if (frames >= speed)
	{
		frames = 0;
		SDL_RenderPresent(gRenderer);
		SDL_Delay(50);
	}
	return Clips;
}

void Revertbars(SDL_Rect Clip_i, SDL_Rect Clip_j)
{
	if ((Clip_j.x == EmptyRect.x) && (Clip_j.y == EmptyRect.y)
		&& (Clip_j.w == EmptyRect.w) && (Clip_j.h == EmptyRect.h)) {
		SDL_SetRenderDrawColor(gRenderer, 105, 105, 105, 0xff);
		SDL_RenderFillRect(gRenderer, &Clip_i);
		SDL_RenderPresent(gRenderer);
	}

	else {
		SDL_SetRenderDrawColor(gRenderer, 105, 105, 105, 0xff);
		SDL_RenderFillRect(gRenderer, &Clip_i);
		SDL_RenderPresent(gRenderer);

		SDL_SetRenderDrawColor(gRenderer, 105, 105, 105, 0xff);
		SDL_RenderFillRect(gRenderer, &Clip_j);
		SDL_RenderPresent(gRenderer);
	}

}

void SwapBars(LBar* i, LBar* j, int nHeight) {

	if (j != NULL && nHeight == 0)
	{
		//Color the bars being swapped maroon
		SDL_SetRenderDrawColor(gRenderer, 139, 0, 0, 0xff);
		SDL_Rect clip_i = { i->bPosition, ScreenHeight - 20, BarWidth, -i->bHeight };
		SDL_Rect clip_j = { j->bPosition, ScreenHeight - 20, BarWidth, -j->bHeight };
		SDL_RenderFillRect(gRenderer, &clip_i);
		SDL_RenderFillRect(gRenderer, &clip_j);
		frames++;
		if (frames >= speed / 2)
		{
			frames = 0;
			SDL_RenderPresent(gRenderer);
			SDL_Delay(50);
		}

		//Erase the bars -> change colors of bar to background color
		SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xff);
		SDL_RenderFillRect(gRenderer, &clip_i);
		SDL_RenderFillRect(gRenderer, &clip_j);
		//SDL_RenderPresent(gRenderer);


		//Swapping them simply means interchanging their heights
		SDL_SetRenderDrawColor(gRenderer, 105, 105, 105, 0xff);
		SDL_Rect clip_i_modified = { i->bPosition, ScreenHeight - 20, BarWidth, -j->bHeight };
		SDL_Rect clip_j_modified = { j->bPosition, ScreenHeight - 20, BarWidth, -i->bHeight };
		SDL_RenderFillRect(gRenderer, &clip_i_modified);
		SDL_RenderFillRect(gRenderer, &clip_j_modified);
		frames++;
		if (frames >= speed)
		{
			frames = 0;
			SDL_RenderPresent(gRenderer);
			SDL_Delay(50);
		}

		//swapping the heights of the bar objects in the array.
		int tmp;
		tmp = i->bHeight;
		i->bHeight = j->bHeight;
		j->bHeight = tmp;
	}

	else if (j == NULL)
	{
		//Erasing the initial bar
		SDL_Rect clip_i = { i->bPosition, ScreenHeight - 20, BarWidth, -i->bHeight };
		SDL_SetRenderDrawColor(gRenderer, 220, 220, 220, 0xff);
		SDL_RenderFillRect(gRenderer, &clip_i);
		frames++;
		if (frames >= speed)
		{
			frames = 0;
			SDL_RenderPresent(gRenderer);
			SDL_Delay(50);
		}

		//Draw New bar in it's place
		SDL_Rect clip_i_modified = { i->bPosition, ScreenHeight - 20, BarWidth, -nHeight };
		SDL_SetRenderDrawColor(gRenderer, 139, 0, 0, 0xff);
		SDL_RenderFillRect(gRenderer, &clip_i_modified);
		frames++;
		if (frames >= speed)
		{
			frames = 0;
			SDL_RenderPresent(gRenderer);
			SDL_Delay(50);
		}

		//Changing height of bar object in array
		i->bHeight = nHeight;

		//Revert Bar
		Revertbars(clip_i_modified, EmptyRect);
	}

}