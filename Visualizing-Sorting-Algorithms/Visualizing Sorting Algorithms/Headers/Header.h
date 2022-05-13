#pragma once
#include <stdio.h>
#include <SDL.h>
#include <vector>
#include <random>

//SCREEN AND BAR DIMENSIONS
constexpr int ScreenWidth = 1010;
constexpr int ScreenHeight = 650;
constexpr int NumberOfBars = 100;

//Bar struct
struct LBar
{
	int bHeight;
	int bPosition;
};

//Function Prototypes
bool init();
void DrawBars(int ScreenWidth, int NumberOfBars);
void SwapBars(LBar* bar1, LBar* bar2, int nHeight = 0);
SDL_Rect* CompareBars(LBar bar1, LBar bar2);
void Revertbars(SDL_Rect clip_i, SDL_Rect clip_j);
void close();

//Sorting algorithms(to be added)
void bubble_sort(int NumberOfBars);
void selection_sort(int NumberOfBars);
void insertion_sort(int NumberOfBars);
void merge(int l, int mid, int r);
void merge_sort(int l, int NumberOfBars);
int partition(int l, int NumberOfBars);
void quick_sort(int l, int NumberOfBars);

//Global Variables
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern int BarWidth;
extern int BarPadding;
extern LBar bar[];
extern int frames;
extern int speed;
extern SDL_Rect EmptyRect;
