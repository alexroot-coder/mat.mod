#include <iostream>
#include <conio.h>
#include <stdio.h>
#include<Windows.h>
#include <stdlib.h>
#include <time.h> 


using namespace std;
#define ITERATIONS 1000
#define X 30 
#define Y 30

char space[X][Y];
char temp_space[X][Y];
int close_point;

void initialization(){
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			space[i][j] = ' ';
		}
	}
}

void configurations(){
	space[3][6] = (char)253u;
	space[4][5] = (char)253u;
	space[4][6] = (char)253u;
	space[5][3] = (char)253u;
	space[5][6] = (char)253u;
	space[5][7] = (char)253u;
	space[6][4] = (char)253u;
	space[6][5] = (char)253u;
	space[6][7] = (char)253u;
	space[7][5] = (char)253u;
}


int FIND_POINTS(int i, int j){
	close_point = 0;
	if (space[i + 1][j + 1] == (char)253u)
	{
		close_point++;
	}
	if (space[i][j + 1] == (char)253u)
	{
		close_point++;
	}
	if (space[i - 1][j + 1] == (char)253u)
	{
		close_point++;
	}
	if (space[i+1][j] == (char)253u)
	{
		close_point++;
	}
	if (space[i - 1][j] == (char)253u)
	{
		close_point++;
	}
	if (space[i + 1][j-1] == (char)253u)
	{
		close_point++;
	}
	if (space[i][j - 1] == (char)253u)
	{
		close_point++;
	}
	if (space[i - 1][j - 1] == (char)253u)
	{
		close_point++;
	}
	return close_point;
}

void RULES(){
	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			FIND_POINTS(i,j);
			if (close_point < 2)
			{
				temp_space[i][j] = ' ';
			}
			else if (close_point > 3)
			{
				temp_space[i][j] = ' ';
			}
			else if ((close_point == 2) && (space[i][j] == (char)253u))
			{
				temp_space[i][j] = (char)253u;
			}
			else if (close_point == 3)
			{
				temp_space[i][j] = (char)253u;
			}
		}
	}
}

int main(){ 
	initialization();
	configurations();
	for (int k = 0; k < ITERATIONS; k++){
		RULES();
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				cout << space[i][j];
			}
			cout << " " << '\n';
		}
		for (int i = 0; i < X; i++) {
			for (int j = 0; j < Y; j++) {
				space[i][j] = temp_space[i][j];
			}
		}
		_getch();
		system("cls");
		cout<<"ITERATIONS : "<<k+1;
	}
	_getch();
}