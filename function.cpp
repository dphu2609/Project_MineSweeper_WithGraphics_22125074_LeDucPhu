#include <bits/stdc++.h>
#include <graphics.h>
#include "function.h"
 
using namespace std;


void menu() {
    initwindow(600,600,"MineSweeper");
    char a[20]="MINE SWEEPER";
    char b[20]="NEW GAME";
    char c[20]="CONTINUE PLAYING";
    char d[20]="HIGH SCORE";
    char e[20]="EXIT";
    settextstyle(EUROPEAN_FONT,HORIZ_DIR,5);
    rectangle(70,140,540,205);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(70,140,BLACK);
    outtextxy(80,150,a);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(245,290,b);
    outtextxy(205,330,c);
    outtextxy(240,370,d);
    outtextxy(280,410,e);   
    while (1) {
        if (MouseLeft()) {
            GetCursorPos(&mouse);
            if (mouse.x>220 && mouse.x<380 && mouse.y>305 && mouse.y<345) {
                newGame();
                break;
            }
            else if (mouse.x>180 && mouse.x<420 && mouse.y>345 && mouse.y<385) cout << "CONTINUE PLAYING" << endl;
            else if (mouse.x>215 && mouse.x<385 && mouse.y>385 && mouse.y<425) cout << "HIGH SCORE" << endl;
            else if (mouse.x>255 && mouse.x<345 && mouse.y>425 && mouse.y<465) cout << "EXIT" << endl;
        }
        delay(100);
    }
    getch();
    closegraph();
}

void newGame() {
    cleardevice();
    delay(100);
    char a[20]="CHOOSE DIFFICULTY";
    char b[20]="BEGINNER";
    char c[20]="INTERMIDIATE";
    char d[20]="EXPERT";
    char e[20]="CUSTOM";
    settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
    rectangle(70,140,540,205);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(70,140,BLACK);
    outtextxy(80,150,a);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(245,290,b);
    outtextxy(225,330,c);
    outtextxy(255,370,d);
    outtextxy(250,410,e);   
    while (1) {
        if (MouseLeft()) {
            GetCursorPos(&mouse);
            if (mouse.x>220 && mouse.x<380 && mouse.y>305 && mouse.y<345) play(9,9,10);
            else if (mouse.x>180 && mouse.x<420 && mouse.y>345 && mouse.y<385) cout << "CONTINUE PLAYING" << endl;
            else if (mouse.x>215 && mouse.x<385 && mouse.y>385 && mouse.y<425) cout << "HIGH SCORE" << endl;
            else if (mouse.x>255 && mouse.x<345 && mouse.y>425 && mouse.y<465) cout << "EXIT" << endl;
        }
        delay(100);
    }
}

void createAnswer(int height, int width, int bombs) {
    srand(time(0));
    int count = 1;
    while (count <= bombs) {
        int i=rand()%height;
        int j=rand()%width;
        if (checkRandomBombs[i][j]) continue;
        else {
            checkRandomBombs[i][j]=true;
            count++;
            answer[i][j]='B';
        }
    }
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            count = 0;
            if (answer[i][j]=='B') continue;
            if (answer[i-1][j-1]=='B') count++;
            if (answer[i-1][j]=='B') count++;
            if (answer[i-1][j+1]=='B') count++;
            if (answer[i][j-1]=='B') count++;
            if (answer[i][j+1]=='B') count++;
            if (answer[i+1][j-1]=='B') count++;
            if (answer[i+1][j]=='B') count++;
            if (answer[i+1][j+1]=='B') count++;
            if (count==0) answer[i][j]=' ';
            else answer[i][j]=count+48;
        }
    }
}

void createDisplay(int height, int width) {
    closegraph();
    if (width<=16) SquareSize=40;
    else SquareSize=30;
    initwindow(width*SquareSize+240, height*SquareSize+240, "MineSweeper");
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            readimagefile("images\\unopened.gif",j*SquareSize+120,i*SquareSize+120,j*SquareSize+120+SquareSize,i*SquareSize+120+SquareSize);
        }
    }
}

void play(int height, int width, int bombs) {
    int x,y;
    createDisplay(height,width);
    createAnswer(height,width,bombs);
    while(1) {
        if (MouseLeft()) GetCursorPos(&mouse);
        else continue;
        x=(mouse.y-20-120)/SquareSize;
        y=(mouse.x-120)/SquareSize;
        if (answer[x][y]==' ') readimagefile("images\\num0.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='1') readimagefile("images\\num1.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='2') readimagefile("images\\num2.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='3') readimagefile("images\\num3.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='4') readimagefile("images\\num4.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='5') readimagefile("images\\num5.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='6') readimagefile("images\\num6.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='7') readimagefile("images\\num7.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='8') readimagefile("images\\num8.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        else if (answer[x][y]=='B') readimagefile("images\\bomb.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
        delay(100);
    }
    getch();
}