#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ITERATIONS 2000 
#define X 500 
#define Y 500

int FISH = 50000; 
int SHARKS = 5000; 
int FISH_breed = 30; 
int SHARKS_breed = 40; 
int SHARKS_starve = 25; 
int FISH_death_age = 100;
int SHARKS_death_age = 200;
int step[X][Y]; 
int fish[X][Y]; 
int sharks[X][Y]; 
int starve[X][Y]; 
int age[X][Y]; 
int i, j;

enum { empty = -1, marked, unmarked };

void initialization()
{
	int random_x, random_y;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			fish[i][j] = empty;
			sharks[i][j] = empty;
			starve[i][j] = empty;
			age[i][j] = empty;
			step[i][j] = unmarked;
		}
	}
	for (i = 0; i < SHARKS; i++) {
		do {
			random_x = rand() % X;
			random_y = rand() % Y;
		} while ((fish[random_x][random_y] != empty) && (sharks[random_x][random_y] != empty));
		sharks[random_x][random_y] = rand() % SHARKS_breed;
		age[random_x][random_y] = rand() % SHARKS_death_age;
		starve[random_x][random_y] = rand() % SHARKS_starve;
	}
	for (i = 0; i < FISH; i++) {
		do {
			random_x = rand() % X;
			random_y = rand() % Y;
		} while ((fish[random_x][random_y] != empty) && (sharks[random_x][random_y] != empty));
		fish[random_x][random_y] = rand() % FISH_breed;
		age[random_x][random_y] = rand() % FISH_death_age;
	}
}

void Fishstep()
{
	static int new_x, new_y;
	static int random_way, num_tries, tmp;
	FISH = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			step[i][j] = unmarked;
		}
	}
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			if ((fish[i][j] != empty) && (step[i][j] == unmarked)) {
				age[i][j]++;
				if ((age[i][j] < FISH_death_age)) {
					new_x = i;
					new_y = j;
					num_tries = 0;
					FISH++;
					while (num_tries < 4) {
						random_way = rand() % 4;
						if (random_way == 0) {
							tmp = (i == 0) ? X : i;
							tmp--;
							if ((fish[tmp][j] == empty) && (sharks[tmp][j] == empty)) {
								new_x = tmp;
								new_y = j;
								fish[new_x][new_y] = fish[i][j];
								age[new_x][new_y] = age[i][j];
								fish[i][j] = empty;
								age[i][j] = empty;
								step[new_x][new_y] = marked;
								num_tries = 4;
							}
							else {
								num_tries++;
							}
						}
						else if (random_way == 1) {
							tmp = (i == X - 1) ? -1 : i;
							tmp++;
							if ((fish[tmp][j] == empty) && (sharks[tmp][j] == empty)) {
								new_x = tmp;
								new_y = j;
								fish[new_x][new_y] = fish[i][j];
								age[new_x][new_y] = age[i][j];
								fish[i][j] = empty;
								age[i][j] = empty;
								step[new_x][new_y] = marked;
								num_tries = 4;
							}
							else {
								num_tries++;
							}
						}
						else if (random_way == 2) {
							tmp = (j == 0) ? Y : j;
							tmp--;
							if ((fish[i][tmp] == empty) && (sharks[i][tmp] == empty)) {
								new_x = i;
								new_y = tmp;
								fish[new_x][new_y] = fish[i][j];
								age[new_x][new_y] = age[i][j];
								fish[i][j] = empty;
								age[i][j] = empty;
								step[new_x][new_y] = marked;
								num_tries = 4;
							}
							else {
								num_tries++;
							}
						}
						else if (random_way == 3) {
							tmp = (j == Y - 1) ? -1 : j;
							tmp++;
							if ((fish[i][tmp] == empty) && (sharks[i][tmp] == empty)) {
								new_x = i;
								new_y = tmp;
								fish[new_x][new_y] = fish[i][j];
								age[new_x][new_y] = age[i][j];
								fish[i][j] = empty;
								age[i][j] = empty;
								step[new_x][new_y] = marked;
								num_tries = 4;
							}
							else {
								num_tries++;
							}
						}
					}
					fish[new_x][new_y]++;
					if (fish[new_x][new_y] == FISH_breed) {
						fish[new_x][new_y] = 0;
						fish[i][j] = 0;
						age[i][j] = 0;
						step[i][j] = marked;
					}
				}
				else {
					fish[i][j] = empty;
					age[i][j] = empty;
				}
			}
		}
	}
}

void Sharkstep()
{
	static int new_x, new_y;
	static int random_way, num_tries, tmp;
	static int is_moved;
	SHARKS = 0;
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			step[i][j] = unmarked;
		}
	}
	for (i = 0; i < X; i++) {
		for (j = 0; j < Y; j++) {
			if ((sharks[i][j] != empty) && (step[i][j] == unmarked)) {
				age[i][j]++;
				if (age[i][j] < SHARKS_death_age) {
					starve[i][j]++;
					if (starve[i][j] < SHARKS_starve) {
						new_x = i;
						new_y = j;
						num_tries = 0;
						is_moved = 0;
						SHARKS++;
							random_way = rand() % 4;
							while (num_tries < 4) {
							if (random_way == 0) {
								tmp = (i == 0) ? X : i;
								tmp--;
								if ((sharks[tmp][j] == empty) && (fish[tmp][j] != empty)) {
									new_x = tmp;
									new_y = j;
									fish[new_x][new_y] = empty;
									FISH--;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = 0;
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									is_moved = 1;
									step[new_x][new_y] = marked;
									num_tries = 4;
								}
								else {
									random_way = 1;
									num_tries++;
								}
							}
							else if (random_way == 1) {
								tmp = (i == X - 1) ? -1 : i;
								tmp++;
								if ((sharks[tmp][j] == empty) && (fish[tmp][j] != empty)) {
									new_x = tmp;
									new_y = j;
									fish[new_x][new_y] = empty;
									FISH--;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = 0;
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
									is_moved = 1;
									num_tries = 4;
								}
								else {
									random_way = 2;
									num_tries++;
								}
							}
							else if (random_way == 2) {
								tmp = (j == 0) ? Y : j;
								tmp--;
								if ((sharks[i][tmp] == empty) && (fish[i][tmp] != empty)) {
									new_x = i;
									new_y = tmp;
									fish[new_x][new_y] = empty;
									FISH--;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = 0;
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									is_moved = 1;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
									num_tries = 4;
								}
								else {
									random_way = 3;
									num_tries++;
								}
							}
							else if (random_way == 3) {
								tmp = (j == Y - 1) ? -1 : j;
								tmp++;
								if ((sharks[i][tmp] == empty) && (fish[i][tmp] != empty)) {
									new_x = i;
									new_y = tmp;
									fish[new_x][new_y] = empty;
									FISH--;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = 0;
									age[new_x][new_y] = age[i][j];
									is_moved = 1;
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
									num_tries = 4;
								}
								else {
									random_way = 0;
									num_tries++;
								}
							}
						}
						if (is_moved == 0) {
							random_way = rand() % 4;
							if (random_way == 0) {
								tmp = (i == 0) ? X : i;
								tmp--;
								if ((sharks[tmp][j] == empty) && (fish[tmp][j] == empty)) {
									new_x = tmp;
									new_y = j;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = starve[i][j];
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
								}
							}
							else if (random_way == 1) {
								tmp = (i == X - 1) ? -1 : i;
								tmp++;
								if ((sharks[tmp][j] == empty) && (fish[tmp][j] == empty)) {
									new_x = tmp;
									new_y = j;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = starve[i][j];
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
								}
							}
							else if (random_way == 2) {
								tmp = (j == 0) ? Y : j;
								tmp--;
								if ((sharks[i][tmp] == empty) && (fish[i][tmp] == empty)) {
									new_x = i;
									new_y = tmp;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = starve[i][j];
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
								}
							}
							else if (random_way == 3) {
								tmp = (j == Y - 1) ? -1 : j;
								tmp++;
								if ((sharks[i][tmp] == empty) && (fish[i][tmp] == empty)) {
									new_x = i;
									new_y = tmp;
									sharks[new_x][new_y] = sharks[i][j];
									starve[new_x][new_y] = starve[i][j];
									age[new_x][new_y] = age[i][j];
									sharks[i][j] = empty;
									starve[i][j] = empty;
									age[i][j] = empty;
									step[new_x][new_y] = marked;
								}
							}
						}		
						sharks[new_x][new_y]++;
						if (sharks[new_x][new_y] == SHARKS_breed) {
							sharks[new_x][new_y] = 0;
							sharks[i][j] = 0;
							age[i][j] = 0;
							starve[i][j] = 0;
							step[i][j] = marked;
						}
					}
					else {
						sharks[i][j] = empty;
						age[i][j] = empty;
						starve[i][j] = empty;
						step[i][j] = marked;
					}
				}
				else {
					sharks[i][j] = empty;
					age[i][j] = empty;
					starve[i][j] = empty;
					step[i][j] = marked;
				}
			}
		}
	}
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	initialization();
	printf("\nCalculating...\n");
	FILE* file = fopen("RESULT.txt", "w");
	int iterations = 0;
	for (int q = 0; q < ITERATIONS; q++) {
		if ((SHARKS > 0) && (FISH > 0)) {
			iterations++;
			fprintf(file, "%d\t%d\t%d\n", q, FISH, SHARKS);
			Fishstep();
			Sharkstep();
		}
	}
	fclose(file);
	return 0;
}