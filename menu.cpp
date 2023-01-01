#include "function.h"

#define MouseLeft() GetAsyncKeyState(VK_LBUTTON)
#define MouseRight() GetAsyncKeyState(VK_RBUTTON)

void menu() {
    closegraph();
    delay(100);
    initwindow(600,600,"MineSweeper",(getmaxwidth()-600)/2, (getmaxheight()-600)/2);
    char a[20]="MineSweeper";
    char b[20]="NEW GAME";
    char c[20]="CONTINUE PLAYING";
    char d[20]="HIGH SCORE";
    char e[20]="EXIT";
    char f[40]="designed by Phus";
    settextstyle(10,HORIZ_DIR,7);
    outtextxy(90,170,a);
    settextstyle(3,HORIZ_DIR,3);
    outtextxy(245,290,b);
    outtextxy(205,330,c);
    outtextxy(240,370,d);
    outtextxy(280,410,e);   
    settextstyle(5,HORIZ_DIR,4);
    outtextxy(170,550,f);  
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
    delay(150);
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
    settextstyle(5,HORIZ_DIR,4);
    char f[40]="designed by Phus";
    outtextxy(170,550,f);  
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


void highScoreSave(int data, const int height, const int width, const int bombs) {
    if (height==9 && width==9 && bombs==10) fin.open("data\\highscore\\beginner.txt");
    else if (height==16 && width==16 && bombs==40) fin.open("data\\highscore\\intermidiate.txt");
    else if (height==9 && width==9 && bombs==10) fin.open("data\\highscore\\beginner.txt");
    else return;
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
    char f[40]="designed by Phus";
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
        settextstyle(5,HORIZ_DIR,4);
        outtextxy(170,550,f);  
        settextstyle(3,HORIZ_DIR,3);
        if (MouseLeft()) {
            if (mousex()>220 && mousex()<380 && mousey()>290 && mousey()<330) {
                delay(100);
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
                        outtextxy(235,i*40+200,f);
                        outtextxy(315,i*40+200,g);
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
                delay(100);
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
                        outtextxy(235,i*40+200,f);
                        outtextxy(315,i*40+200,g);
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
                delay(100);
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
                        outtextxy(235,i*40+200,f);
                        outtextxy(315,i*40+200,g);
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
    readimagefile("images\\arrow_up.jpg",342,320,362,340);
    readimagefile("images\\arrow_down.jpg",342,390,362,410);
    int height=2,width=2,bombs=1;
    settextstyle(3,HORIZ_DIR,4);
    while (1) {
        delay(150);
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