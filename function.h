#pragma once

#include <bits/stdc++.h>
#include <fstream>
#include <time.h>
#include <graphics.h>
using namespace std;

bool playAgain;
bool isPlaying;
int againHeight, againWidth, againBombs;
int page;
int countMark;
int countMarkMatchBombs;
bool checkLose=false;
bool checkRandomBombs[50][50];
bool checkOpenedCell[50][50];
char display[50][50];
char answer[50][50];
int SquareSize=30;

ifstream fin;
ofstream fout;

clock_t Time;
vector<pair<int,int>> bombsPos;
vector<int> highscore;

void menu();
void newGame();
void loadGame();
void play(const int height,const int width,const int bombs);
void createDisplay(const int height, const int width, const int bombs);
void createAnswer(const int height, const int width, const int bombs);
void openBlankCell(int i, int j, int height, int width);
void openNumCell(int x, int y);
void loseGame(int x, int y,const int height, const int width, const int bombs);
bool checkWin(const int height, const int width, const int bombs);
void clickOpenedNumCell(int x, int y, int height, int width,int bombs);
void highScoreSave(int data, const int height, const int width, const int bombs);
void highScoreDisplay();
void PlayAgain(const int height, const int width, const int bombs);
void PlayGame(const int height,const int width,const int bombs);
void custom();
int Timer(clock_t time_since_epoch, clock_t now);
