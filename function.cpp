#include <bits/stdc++.h>
#include <graphics.h>
#include "function.h"
#include <fstream>
#include <time.h>

using namespace std;

ifstream fin;
ofstream fout;
vector<pair<int,int>> bombsPos;
bool playAgain;
bool isPlaying;
int againHeight, againWidth, againBombs;

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
            if (mousex()>220 && mousex()<380 && mousey()>290 && mousey()<330) {
                newGame();
                break;
            }
            else if (mousex()>180 && mousex()<440 && mousey()>330 && mousey()<360) loadGame();
            else if (mousex()>215 && mousex()<385 && mousey()>360 && mousey()<400) highScoreDisplay();
            else if (mousex()>255 && mousex()<345 && mousey()>400 && mousey()<440) cout << "EXIT" << endl;
        }
        delay(100);
    }
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
            if (mousex()>220 && mousex()<380 && mousey()>290 && mousey()<330) {
                createDisplay(9,9,10);
                createAnswer(9,9,10);
                play(9,9,10);
                break;
            }
            else if (mousex()>180 && mousex()<440 && mousey()>330 && mousey()<360) {
                createDisplay(16,16,40);
                createAnswer(16,16,40);
                play(16,16,40);
                break;
            }
            else if (mousex()>215 && mousex()<385 && mousey()>360 && mousey()<400) {
                createDisplay(16,30,99);
                createAnswer(16,30,99);
                play(16,30,99);
                break;
            }
            else if (mousex()>255 && mousex()<345 && mousey()>400 && mousey()<440) cout << "EXIT" << endl;
        }
        delay(100);
    }
}

void createDisplay(int height, int width,int bombs) {
    closegraph();
    initwindow(width*SquareSize+240, height*SquareSize+240, "MineSweeper");
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            readimagefile("images\\unopened.gif",j*SquareSize+120,i*SquareSize+120,j*SquareSize+120+SquareSize,i*SquareSize+120+SquareSize);
        }
    }
}

void createAnswer(int height, int width, int bombs) {
    srand(time(0));
    for (int i=0;i<16;i++) {
        for (int j=0;j<30;j++) {
            checkBlankCell[i][j]=false;
            checkRandomBombs[i][j]=false;
            display[i][j]='*';
            answer[i][j]=' ';
        }
    }
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
    fout.open("data\\answer.txt");
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            if (answer[i][j]==' ') fout << '*' << endl;
            else fout << answer[i][j] << endl;
        }
    }
    fout.close();
    fout.open("data\\display.txt");
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            fout << display[i][j] << endl;
        }
    }
    fout.close();
    fout.open("data\\statistic.txt");
    fout << height << endl << width << endl << bombs << endl << 0 << endl << 0 << endl << 0;
    fout.close();
}

void openNumCell(int x, int y) {
    display[x][y]=answer[x][y];
    if (answer[x][y]=='1') readimagefile("images\\num1.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='2') readimagefile("images\\num2.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='3') readimagefile("images\\num3.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='4') readimagefile("images\\num4.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='5') readimagefile("images\\num5.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='6') readimagefile("images\\num6.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='7') readimagefile("images\\num7.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    else if (answer[x][y]=='8') readimagefile("images\\num8.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
}

void openBlankCell(int i, int j, int height, int width) {
    if (checkBlankCell[i][j]) return;
    if (i<0|| i>height-1 || j<0 || j>width-1) return;
    else if ((answer[i][j]==' ') && (checkBlankCell[i][j]==false)) {
        readimagefile("images\\num0.jpg",j*SquareSize+120,i*SquareSize+120,j*SquareSize+120+SquareSize,i*SquareSize+120+SquareSize);
        display[i-1][j-1]=answer[i-1][j-1];
        display[i-1][j]=answer[i-1][j];
        display[i-1][j+1]=answer[i-1][j+1];
        display[i][j-1]=answer[i][j-1];
        display[i][j]=answer[i][j];
        display[i][j+1]=answer[i][j+1];
        display[i+1][j-1]=answer[i+1][j-1];
        display[i+1][j]=answer[i+1][j];
        display[i+1][j+1]=answer[i+1][j+1];
        checkBlankCell[i][j]=true;
        openBlankCell(i,j-1,height,width);
        openBlankCell(i,j+1,height,width);
        openBlankCell(i+1,j,height,width);
        openBlankCell(i-1,j,height,width);
        openBlankCell(i-1,j-1,height,width);
        openBlankCell(i-1,j+1,height,width);
        openBlankCell(i+1,j-1,height,width);
        openBlankCell(i+1,j+1,height,width);
    } 
    else {
        checkBlankCell[i][j]=true;
        openNumCell(i,j);
        return;
    }
}

bool checkWin(int height, int width, int bombs) {
    bool checkwin=1;
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            if (display[i][j]=='*') {
                checkwin=0;
                break;
            }
        }
        if (checkwin==0) break;
    }
    return checkwin;
}

void clickOpenedNumCell(int x, int y, int height, int width,int bombs) {
    int countFlag=0;
    for (int i=x-1;i<=x+1;i++) {
        for (int j=y-1;j<=y+1;j++) {
            if (display[i][j]=='P') countFlag++;
        }
    }
    if (countFlag==(int)answer[x][y]-48) {
        for (int i=x-1;i<=x+1;i++) {
            for (int j=y-1;j<=y+1;j++) {
                if (display[i][j]=='P') continue;
                if (answer[i][j]==' ') openBlankCell(i,j,height,width);
                else if (answer[i][j]=='B') {
                    loseGame(i,j,height,width,bombs);
                    break;
                }
                else openNumCell(i,j);
            }
        }
    }
    else return;
}

clock_t Timer(clock_t time_since_epoch, clock_t now) {
    return (int)(now-time_since_epoch)/1000;
}

void play(int height, int width, int bombs) {
    isPlaying=true;
    int x,y,t;
    playAgain=false;
    char a[20];
    clock_t time_since_epoch=clock();
    bombsPos.clear();
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) if (answer[i][j]=='B') bombsPos.push_back(make_pair(i,j));
    }
    while(1) {
        if (checkLose) break;
        t=Time+Timer(time_since_epoch,clock());
        fout.open("data\\statistic.txt");
        fout << height << endl << width << endl << bombs << endl << t << endl << countMark << endl <<countMarkMatchBombs;
        fout.close();
        sprintf(a,"%d",t);
        settextstyle(3,HORIZ_DIR,4);
        if (t<10) outtextxy((width*SquareSize+240)/2-10,60,a);
        else if (t<100) outtextxy((width*SquareSize+240)/2-20,60,a);
        else if (t<1000) outtextxy((width*SquareSize+240)/2-30,60,a);
        else if (t<10000) outtextxy((width*SquareSize+240)/2-40,60,a);
        else if (t<100000) outtextxy((width*SquareSize+240)/2-50,60,a);
        else if (t<1000000) outtextxy((width*SquareSize+240)/2-60,60,a);
        delay(100);
        if (MouseLeft()) {
            delay(50);
            if (mousex()-120 < 0) continue;
            x=(mousey()-120)/SquareSize;
            y=(mousex()-120)/SquareSize;
            if (display[x][y]=='P') continue;
            else if (display[x][y]!='*') clickOpenedNumCell(x,y,height,width,bombs);
            if (answer[x][y]==' ') openBlankCell(x,y,height,width);
            else if (answer[x][y]=='B') {
                loseGame(x,y,height,width,bombs);
                break;
            }
            else openNumCell(x,y);
        }
        else if (MouseRight()) {
            delay(50);
            if (mousex()-120 < 0) continue;
            x=(mousey()-120)/SquareSize;
            y=(mousex()-120)/SquareSize;
            if (display[x][y]!='*' && display[x][y]!='P') continue;
            else if (display[x][y]=='P') {
                display[x][y]='*';
                readimagefile("images\\unopened.gif",y*SquareSize+121,x*SquareSize+121,y*SquareSize+119+SquareSize,x*SquareSize+119+SquareSize);
                countMark--;
                if (answer[x][y]=='B') countMarkMatchBombs--;
            }
            else {
                display[x][y]='P';
                readimagefile("images\\flag.jpg",y*SquareSize+121,x*SquareSize+121,y*SquareSize+119+SquareSize,x*SquareSize+119+SquareSize);
                countMark++;
                if (answer[x][y]=='B') countMarkMatchBombs++;
            }
        }
        fout.open("data\\display.txt");
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                if (display[i][j]==' ') fout << '.' << endl;
                else fout << display[i][j] << endl;
            }
        }
        fout.close();
        if (countMark==bombs && countMarkMatchBombs==bombs) {
            if (checkWin(height,width,bombs)) {
                char a[20]="YOU WIN";
                settextstyle(EUROPEAN_FONT,HORIZ_DIR,5);
                outtextxy((width*SquareSize+240)/2-140,height*SquareSize+240-90,a);
                fout.open("data\\statistic.txt");
                fout << 0;
                fout.close();
                highScoreSave(t,height,width,bombs);
                break;
            }
        }
    }
}

void loseGame(int x, int y,int height, int width, int bombs) {
    readimagefile("images\\bomb.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    delay(500);
    for (int i=0;i<bombsPos.size();i++) readimagefile("images\\bomb.jpg",bombsPos[i].second*SquareSize+120,bombsPos[i].first*SquareSize+120,bombsPos[i].second*SquareSize+120+SquareSize,bombsPos[i].first*SquareSize+120+SquareSize);
    char a[20]="YOU LOSE";
    settextstyle(3,HORIZ_DIR,5);
    outtextxy((width*SquareSize+240)/2-130,height*SquareSize+240-90,a);
    checkLose=true;
    fout.open("data\\statistic.txt");
    fout << 0;
    fout.close();
    delay(2500);
    cleardevice();
    char b[40]="DO YOU WANT TO PLAY AGAIN?";
    char c[4]="YES";
    char d[3]="NO";
    settextstyle(3,HORIZ_DIR,3);
    outtextxy((width*SquareSize+240)/2-150,(height*SquareSize+240)/2-80,b);
    outtextxy((width*SquareSize+240)/2-20,(height*SquareSize+240)/2-20,c);
    outtextxy((width*SquareSize+240)/2-15,(height*SquareSize+240)/2+20,d);
    while (isPlaying) {
        if (MouseLeft()) {
            if ((mousex()>(width*SquareSize+240)/2-40) && (mousex()<(width*SquareSize+240)/2+40) && ((mousey()>height*SquareSize+240)/2-20) && ((mousey()<height*SquareSize+240)/2+10)) {
                playAgain=true;
                isPlaying=false;
                againHeight=height;
                againWidth=width;
                againBombs=bombs;
            }
            else if ((mousex()>(width*SquareSize+240)/2-30) && (mousex()<(width*SquareSize+240)/2+30) && ((mousey()>height*SquareSize+240)/2+10) && ((mousey()<height*SquareSize+240)/2+40)) {
                playAgain=false;
                isPlaying=false;
                againHeight=height;
                againWidth=width;
                againBombs=bombs;
            }
        }
    }
}

void loadGame() {
    int height,width,bombs;
    fin.open("data\\statistic.txt");
    fin >> height;
    fin >> width;
    fin >> bombs;
    fin >> Time;
    fin >> countMark;
    fin >> countMarkMatchBombs;
    fin.close();
    if (height==0) newGame();
    else {
        fin.open("data\\answer.txt");
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                fin >> answer[i][j];
                if (answer[i][j]=='*') answer[i][j]=' ';
            }
        }
        fin.close();
        fin.open("data\\display.txt");
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                fin >> display[i][j];
                if (display[i][j]=='.') display[i][j]==' ';
            }
        }
        fin.close();
        createDisplay(height,width,bombs);
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                if (display[i][j]=='P') readimagefile("images\\flag.jpg",j*SquareSize+121,i*SquareSize+121,j*SquareSize+119+SquareSize,i*SquareSize+119+SquareSize);
                else if (display[i][j]=='.') readimagefile("images\\num0.jpg",j*SquareSize+120,i*SquareSize+120,j*SquareSize+120+SquareSize,i*SquareSize+120+SquareSize);
                else if (display[i][j]!='*') openNumCell(i,j);
            }
        }
        play(height,width,bombs);
    }
}

void highScoreSave(int data, int height, int width, int bombs) {
    if (height==9 && width==9 && bombs==10) fin.open("data\\highscore\\beginner.txt");
    else if (height==16 && width==16 && bombs==40) fin.open("data\\highscore\\intermidiate.txt");
    else if (height==9 && width==9 && bombs==10) fin.open("data\\highscore\\beginner.txt");
    int i=0, index;
    while(!fin.eof()) {
        fin >> highscore[i];
        i++;
    }
    if (highscore[0]==0) highscore[0]=999999999;
    fin.close();
    for (int i=0;i<5;i++) {
        if (data<highscore[i]) {
            index=i;
            break;
        }
    }
    for (int i=4;i>index;i--) {
        highscore[i]=highscore[i-1];
    }
    highscore[index]=data;
    if (height==9 && width==9 && bombs==10) fout.open("data\\highscore\\beginner.txt");
    else if (height==16 && width==16 && bombs==40) fout.open("data\\highscore\\intermidiate.txt");
    else if (height==9 && width==9 && bombs==10) fout.open("data\\highscore\\beginner.txt");
    for (int i=0;i<5;i++) {
        fout << highscore[i] << endl;
        highscore[i]=0;
    }
    fout.close();
}

void highScoreDisplay() {
    cleardevice();
    int temp;
    char a[20];
    char b[20];
    fin.open("data\\highscore\\beginner.txt");
    for (int i=0;i<5;i++) {
        fin >> temp;
        sprintf(a,"TOP %d. ",i+1);
        sprintf(b,"%d",temp);
        outtextxy(200,i*40+200,a);
        outtextxy(280,i*40+200,b);
    }
    fin.close();
}