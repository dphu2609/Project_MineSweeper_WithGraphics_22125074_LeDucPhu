bool checkRandomBombs[16][30];
bool checkBlankCell[16][30];
char display[16][30];
char answer[16][30];
POINT mouse;
int SquareSize;
int countMark;
int countMarkMatchBombs;
clock_t Time;

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
void loseGame(int x, int y,int height, int width);
bool checkWin(int height, int width, int bombs);
void clickOpenedNumCell(int x, int y, int height, int width);