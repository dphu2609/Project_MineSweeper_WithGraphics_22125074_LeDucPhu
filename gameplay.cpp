#include "function.h"

#define MouseLeft() GetAsyncKeyState(VK_LBUTTON)
#define MouseRight() GetAsyncKeyState(VK_RBUTTON)

void PlayGame(const int height,const int width,const int bombs) {
    createDisplay(height,width,bombs);
    createAnswer(height,width,bombs);
    play(height,width,bombs);
}

void createDisplay(const int height, const int width, const int bombs) {
    closegraph();
    initwindow(width*SquareSize+240, height*SquareSize+240, "MineSweeper",(getmaxwidth()-(width*SquareSize+240))/2, (getmaxheight()-(height*SquareSize+240))/2);
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
            checkOpenedCell[i][j]=false;
            checkRandomBombs[i][j]=false;
            display[i][j]='*';
            answer[i][j]='.';
        }
    }
    int count = 1;
    while (count <= bombs) {
        int i=rand()%height;
        int j=rand()%width;
        if (checkRandomBombs[i][j]) continue;
        checkRandomBombs[i][j]=true;
        count++;
        answer[i][j]='B';
        bombsPos.push_back(make_pair(i,j));
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
    checkOpenedCell[x][y]=true;
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
    int x, y;
    queue<pair<int, int>> q;
    q.push({i,j});
    while (!q.empty()) {
        x = q.front().first;
        y = q.front().second;
        q.pop();
        if (x < 0 || x > height-1 || y < 0 || y > width-1) continue;
        if (checkOpenedCell[x][y]) continue;
        if (answer[x][y] == '.') {
            checkOpenedCell[x][y] = true;
            display[x][y] = answer[x][y];
            readimagefile("images\\num0.jpg", y*SquareSize+120, x*SquareSize+120,
                y*SquareSize+120+SquareSize, x*SquareSize+120+SquareSize);
            for (int m = x - 1; m <= x + 1; m++) {
                for (int n = y - 1; n <= y + 1; n++) {
                    if (m == x && n == y) continue;
                    q.push({m, n});
                }
            }
        }
        else openNumCell(x,y);
    }
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

clock_t Timer(clock_t time_since_epoch, clock_t now) {
    return (int)(now-time_since_epoch)/1000;
}

void play(const int height, const int width, const int bombs) {
    delay(500);
    isPlaying=true;
    playAgain=false;
    int x,y,t;
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

void loseGame(int x, int y, const int height, const int width,const int bombs) {
    readimagefile("images\\bomb.jpg",y*SquareSize+120,x*SquareSize+120,y*SquareSize+120+SquareSize,x*SquareSize+120+SquareSize);
    fout.open("data\\statistic.txt");
    fout << 0;
    fout.close();
    checkLose=true;
    Time=0;
    delay(500);
    for (int i=0;i<bombs;i++) readimagefile("images\\bomb.jpg",bombsPos[i].second*SquareSize+120,bombsPos[i].first*SquareSize+120,bombsPos[i].second*SquareSize+120+SquareSize,bombsPos[i].first*SquareSize+120+SquareSize);
    char a[20]="YOU LOSE";
    settextstyle(3,HORIZ_DIR,5);
    outtextxy((width*SquareSize+240)/2-130,height*SquareSize+240-90,a);
    delay(2500);
    PlayAgain(height, width, bombs);
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
                else if (display[i][j]=='*') readimagefile("images\\unopened.gif",j*SquareSize+120,i*SquareSize+120,j*SquareSize+120+SquareSize,i*SquareSize+120+SquareSize);
                else openNumCell(i,j);
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