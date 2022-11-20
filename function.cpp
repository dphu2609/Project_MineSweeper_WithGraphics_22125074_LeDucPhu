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
int page;
vector<int> highscore;

void menu() {
    initwindow(600,600,"MineSweeper");
    char a[20]="MineSweeper";
    char b[20]="NEW GAME";
    char c[20]="CONTINUE PLAYING";
    char d[20]="HIGH SCORE";
    char e[20]="EXIT";
    settextstyle(10,HORIZ_DIR,7);
    outtextxy(90,170,a);
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
            else if (mousex()>180 && mousex()<440 && mousey()>330 && mousey()<360) {
                loadGame();
                break;
            }
            else if (mousex()>215 && mousex()<385 && mousey()>360 && mousey()<400) {
                highScoreDisplay();
                break;
            }
            else if (mousex()>255 && mousex()<345 && mousey()>400 && mousey()<440) exit(0);
        }
        delay(100);
    }
}

void newGame() {
    cleardevice();
    delay(200);
    char a[20]="CHOOSE DIFFICULTY";
    char b[20]="BEGINNER";
    char c[20]="INTERMIDIATE";
    char d[20]="EXPERT";
    char e[20]="CUSTOM";
    settextstyle(3,HORIZ_DIR,5);
    outtextxy(55,190,a);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(245,290,b);
    outtextxy(225,330,c);
    outtextxy(255,370,d);
    outtextxy(250,410,e);   
    while (1) {
        if (MouseLeft()) {
            if (mousex()>220 && mousex()<380 && mousey()>290 && mousey()<330) {
                PlayGame(9,9,10);
                break;
            }
            else if (mousex()>180 && mousex()<440 && mousey()>330 && mousey()<360) {
                PlayGame(16,16,40);
                break;
            }
            else if (mousex()>215 && mousex()<385 && mousey()>360 && mousey()<400) {
                PlayGame(16,30,99);
                break;
            }
            else if (mousex()>255 && mousex()<345 && mousey()>400 && mousey()<440) {
                custom();
                break;
            }
        }
        delay(100);
    }
}

void createDisplay(const int height, const int width, const int bombs) {
    closegraph();
    initwindow(width*SquareSize+240, height*SquareSize+240, "MineSweeper");
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            readimagefile("images\\unopened.gif",j*SquareSize+120,i*SquareSize+120,j*SquareSize+120+SquareSize,i*SquareSize+120+SquareSize);
        }
    }
}

void createAnswer(const int height, const int width, const int bombs) {
    srand(time(0));
    bombsPos.clear();
    for (int i=0;i<50;i++) {
        for (int j=0;j<50;j++) {
            checkBlankCell[i][j]=false;
            checkRandomBombs[i][j]=false;
            display[i][j]='.';
            answer[i][j]='.';
        }
    }
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            display[i][j]='*';
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
            bombsPos.push_back(make_pair(i,j));
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
            if (count==0) answer[i][j]='.';
            else answer[i][j]=count+48;
        }
    }
    fout.open("data\\answer.txt");
    for (int i=0;i<height;i++) {
        for (int j=0;j<width;j++) {
            fout << answer[i][j] << endl;
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

void openBlankCell(int i, int j, const int height, const int width) {
    if (checkBlankCell[i][j]) return;
    if (i<0 || i>height-1 || j<0 || j>width-1) return;
    else if ((answer[i][j]=='.') && (checkBlankCell[i][j]==false)) {
        checkBlankCell[i][j]=true;
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

bool checkWin(const int height, const int width, const int bombs) {
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

void clickOpenedNumCell(int x, int y, const int height, const int width,const int bombs) {
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
                if (answer[i][j]=='.') openBlankCell(i,j,height,width);
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

void play(const int height, const int width, const int bombs) {
    delay(500);
    isPlaying=true;
    int x,y,t;
    playAgain=false;
    char a[20];
    clock_t time_since_epoch=clock();
    while(1) {
        delay(50);
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
        if (MouseLeft()) {
            delay(50);
            if (mousex()-120 < 0) continue;
            if (mousey()-120 < 0) continue;
            x=(mousey()-120)/SquareSize;
            y=(mousex()-120)/SquareSize;
            if (display[x][y]=='P') continue;
            else if (display[x][y]!='*') clickOpenedNumCell(x,y,height,width,bombs);
            else if (answer[x][y]=='.') openBlankCell(x,y,height,width);
            else if (answer[x][y]=='B') {
                loseGame(x,y,height,width,bombs);
                break;
            }
            else openNumCell(x,y);
        }
        else if (MouseRight()) {
            delay(50);
            if (mousex()-120 < 0) continue;
            if (mousey()-120 < 0) continue;
            x=(mousey()-120)/SquareSize;
            y=(mousex()-120)/SquareSize;
            if (display[x][y]!='*' && display[x][y]!='P') continue;
            else if (display[x][y]=='P') {
                display[x][y]='*';
                readimagefile("images\\unopened.gif",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
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
                fout << display[i][j] << endl;
            }
        }
        fout.close();
        if (countMark==bombs && countMarkMatchBombs==bombs) {
            if (checkWin(height,width,bombs)) {
                char a[20]="YOU WIN";
                settextstyle(3,HORIZ_DIR,5);
                outtextxy((width*SquareSize+240)/2-100,height*SquareSize+240-90,a);
                fout.open("data\\statistic.txt");
                fout << 0;
                fout.close();
                highScoreSave(t,height,width,bombs);
                delay(2500);
                PlayAgain(height,width,bombs);
                break;
            }
        }
    }
}

void PlayAgain(const int height, const int width, const int bombs) {
    char b[40]="DO YOU WANT TO PLAY AGAIN?";
    char c[4]="YES";
    char d[3]="NO";
    setfillstyle(SOLID_FILL,BLACK);
    rectangle((width*SquareSize+240)/2-140,(height*SquareSize+240)/2-70,(width*SquareSize+240)/2+140,(height*SquareSize+240)/2+70);
    floodfill((width*SquareSize+240)/2-140,(height*SquareSize+240)/2-70,BLACK);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy((width*SquareSize+240)/2-150,(height*SquareSize+240)/2-60,b);
    outtextxy((width*SquareSize+240)/2-20,(height*SquareSize+240)/2,c);
    outtextxy((width*SquareSize+240)/2-15,(height*SquareSize+240)/2+40,d);
    while (isPlaying) {
        if (MouseLeft()) {
            if ((mousex()>(width*SquareSize+240)/2-40) && (mousex()<(width*SquareSize+240)/2+40) && (mousey()>(height*SquareSize+240)/2) && (mousey()<(height*SquareSize+240)/2+30)) {
                playAgain=true;
                isPlaying=false;
                againHeight=height;
                againWidth=width;
                againBombs=bombs;
            }
            else if ((mousex()>(width*SquareSize+240)/2-30) && (mousex()<(width*SquareSize+240)/2+30) && (mousey()>(height*SquareSize+240)/2+30) && (mousey()<(height*SquareSize+240)/2+60)) {
                playAgain=false;
                isPlaying=false;
                againHeight=height;
                againWidth=width;
                againBombs=bombs;
            }
        }
    }
}

void loseGame(int x, int y, const int height, const int width,const int bombs) {
    readimagefile("images\\bomb.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    fout.open("data\\statistic.txt");
    fout << 0;
    fout.close();
    checkLose=true;
    delay(500);
    for (int i=0;i<bombs;i++) readimagefile("images\\bomb.jpg",bombsPos[i].second*SquareSize+120,bombsPos[i].first*SquareSize+120,bombsPos[i].second*SquareSize+120+SquareSize,bombsPos[i].first*SquareSize+120+SquareSize);
    char a[20]="YOU LOSE";
    settextstyle(3,HORIZ_DIR,5);
    outtextxy((width*SquareSize+240)/2-130,height*SquareSize+240-90,a);
    delay(2500);
    PlayAgain(height, width, bombs);
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
        bombsPos.clear();
        for (int i=0;i<height;i++) {
            for (int j=0;j<width;j++) {
                if (answer[i][j]=='B') bombsPos.push_back(make_pair(i,j));
            }
        }
        play(height,width,bombs);
    }
}

void highScoreSave(int data, const int height, const int width, const int bombs) {
    if (height==9 && width==9 && bombs==10) fin.open("data\\highscore\\beginner.txt");
    else if (height==16 && width==16 && bombs==40) fin.open("data\\highscore\\intermidiate.txt");
    else if (height==9 && width==9 && bombs==10) fin.open("data\\highscore\\beginner.txt");
    int i=0, index;
    while(!fin.eof()) {
        int temp;
        fin >> temp;
        highscore.push_back(temp);
    }
    if (highscore[0]==0) highscore[0]=999999999;
    fin.close();
    if (data>highscore[4]) return;
    highscore.push_back(data);
    sort(highscore.begin(),highscore.end());
    if (height==9 && width==9 && bombs==10) fout.open("data\\highscore\\beginner.txt");
    else if (height==16 && width==16 && bombs==40) fout.open("data\\highscore\\intermidiate.txt");
    else if (height==9 && width==9 && bombs==10) fout.open("data\\highscore\\beginner.txt");
    for (int i=0;i<5;i++) {
        fout << highscore[i] << endl;
    }
    highscore.clear();
    fout.close();
}

void highScoreDisplay() {
    delay(200);
    char a[20]="HIGHSCORE BOARD";
    char b[20]="BEGINNER";
    char c[20]="INTERMIDIATE";
    char d[20]="EXPERT";
    char e[20]="RETURN";
    while (1) {
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        settextstyle(3,HORIZ_DIR,5);
        outtextxy(55,190,a);
        settextstyle(3,HORIZ_DIR,3);
        outtextxy(245,290,b);
        outtextxy(225,330,c);
        outtextxy(255,370,d);
        outtextxy(250,450,e);  
        if (MouseLeft()) {
            if (mousex()>220 && mousex()<380 && mousey()>290 && mousey()<330) {
                delay(200);
                while(1) {
                    setactivepage(page);
                    setvisualpage(1-page);
                    cleardevice();
                    int temp;
                    char f[20];
                    char g[20];
                    fin.open("data\\highscore\\beginner.txt");
                    for (int i=0;i<5;i++) {
                        fin >> temp;
                        sprintf(f,"TOP %d. ",i+1);
                        sprintf(g,"%d",temp);
                        outtextxy(200,i*40+200,f);
                        outtextxy(280,i*40+200,g);
                    }
                    fin.close();
                    outtextxy(250,450,e);   
                    if (MouseLeft()) {
                        if (mousex()>170 && mousex()<370 && mousey()>440 && mousey()<480) {
                            delay(100);
                            break;
                        }
                    }
                    page=1-page;
                }
            }
            else if (mousex()>180 && mousex()<440 && mousey()>330 && mousey()<360) {
                delay(200);
                while(1) {
                    setactivepage(page);
                    setvisualpage(1-page);
                    cleardevice();
                    int temp;
                    char f[20];
                    char g[20];
                    fin.open("data\\highscore\\intermidiate.txt");
                    for (int i=0;i<5;i++) {
                        fin >> temp;
                        sprintf(f,"TOP %d. ",i+1);
                        sprintf(g,"%d",temp);
                        outtextxy(200,i*40+200,f);
                        outtextxy(280,i*40+200,g);
                    }
                    fin.close();
                    outtextxy(250,450,e);   
                    if (MouseLeft()) {
                        if (mousex()>170 && mousex()<370 && mousey()>440 && mousey()<480) {
                            delay(100);
                            break;
                        }
                    }
                    page=1-page;
                }
            }
            else if (mousex()>215 && mousex()<385 && mousey()>360 && mousey()<400) {
                delay(200);
                while(1) {
                    setactivepage(page);
                    setvisualpage(1-page);
                    cleardevice();
                    int temp;
                    char f[20];
                    char g[20];
                    fin.open("data\\highscore\\expert.txt");
                    for (int i=0;i<5;i++) {
                        fin >> temp;
                        sprintf(f,"TOP %d. ",i+1);
                        sprintf(g,"%d",temp);
                        outtextxy(200,i*40+200,f);
                        outtextxy(280,i*40+200,g);
                    }
                    fin.close();
                    outtextxy(250,450,e);   
                    if (MouseLeft()) {
                        if (mousex()>170 && mousex()<370 && mousey()>440 && mousey()<480) {
                            delay(100);
                            break;
                        }
                    }
                    page=1-page;
                }
            }
            else if (mousex()>170 && mousex()<370 && mousey()>440 && mousey()<480) {
                playAgain=false;
                break;
            }
        }
        page=1-page;
        delay(50);
    }
} 

void PlayGame(const int height,const int width,const int bombs) {
    createDisplay(height,width,bombs);
    createAnswer(height,width,bombs);
    play(height,width,bombs);
}

void custom() {
    cleardevice();
    char a[20]="SIZE: ";
    char b[20]="BOMBS: ";
    char c[20];
    char d[20]; 
    char e[20];
    char f[20]="CONFIRM";
    settextstyle(3,HORIZ_DIR,4);
    outtextxy(150,200,a);
    outtextxy(150,350,b);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(270,500,f);
    readimagefile("images\\arrow_up.jpg",300,170,320,190);
    readimagefile("images\\arrow_up.jpg",355,170,375,190);
    readimagefile("images\\arrow_down.jpg",300,240,320,260);
    readimagefile("images\\arrow_down.jpg",355,240,375,260);
    readimagefile("images\\arrow_up.jpg",345,320,365,340);
    readimagefile("images\\arrow_down.jpg",345,390,365,410);
    int height=2,width=2,bombs=1;
    settextstyle(3,HORIZ_DIR,4);
    while (1) {
        delay(100);
        if (height<2) height=16;
        if (width<2) width=30;
        if (height>16) height=2;
        if (width>30) width=2;
        if (bombs>height*width) bombs=1;
        if (bombs<1) bombs=height*width;
        if (height<10) sprintf(c,"  %d x",height);
        else sprintf(c,"%d x",height);
        if (width<10) sprintf(d,"%d  ",width);
        else sprintf(d,"%d",width);
        sprintf(e,"  %d    ",bombs);
        if (height<10) outtextxy(283,200,c);
        else outtextxy(280,200,c);
        outtextxy(355,200,d);
        if (bombs<10) outtextxy(325,350,e);
        else if (bombs<100) outtextxy(315,350,e);
        else if (bombs<1000) outtextxy(305,350,e);
        if (MouseLeft()) {
            if (mousex()>300 && mousex()<320 && mousey()>170&& mousey()<190) height++;
            else if (mousex()>355 && mousex()<375 && mousey()>170 && mousey()<190) width++;
            else if (mousex()>300 && mousex()<320 && mousey()>240&& mousey()<260) height--;
            else if (mousex()>355 && mousex()<375 && mousey()>240 && mousey()<260) width--;
            else if (mousex()>345 && mousex()<365 && mousey()>320 && mousey()<340) bombs++;
            else if (mousex()>345 && mousex()<365 && mousey()>390 && mousey()<410) bombs--;
            else if (mousex()>260 && mousex()<340 && mousey()>500 && mousey()<530) {
                playAgain=true;
                againHeight=height;
                againWidth=width;
                againBombs=bombs;
                break;
            }
        }
    }
}