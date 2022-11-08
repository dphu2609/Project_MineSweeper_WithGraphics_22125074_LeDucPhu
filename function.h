bool checkRandomBombs[50][50];
bool checkBlankCell[50][50];
char display[50][50];
char answer[50][50];
int SquareSize=30;
int countMark;
int countMarkMatchBombs;
clock_t Time;
bool checkLose=false;

const int MAX_HEIGHT=16;
const int MAX_WIDTH=30;

#define MouseLeft() GetAsyncKeyState(VK_LBUTTON)
#define MouseRight() GetAsyncKeyState(VK_RBUTTON)

void menu();
void newGame();
void loadGame();
void play(int height, int width, int bombs);
void createDisplay(int height, int width, int bombs);
void createAnswer(int height, int width, int bombs);
void openBlankCell(int i, int j, int height, int width);
void openNumCell(int x, int y);
void loseGame(int x, int y,int height, int width, int bombs);
bool checkWin(int height, int width, int bombs);
void clickOpenedNumCell(int x, int y, int height, int width,int bombs);
void highScoreSave(int data, int height, int width, int bombs);
void highScoreDisplay();
void PlayAgain(int height, int width, int bombs);