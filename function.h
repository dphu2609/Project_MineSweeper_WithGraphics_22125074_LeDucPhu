bool checkRandomBombs[16][30];
char answer[16][30];
POINT mouse;
int SquareSize;


#define MouseLeft() GetAsyncKeyState(VK_LBUTTON)
#define MouseRight() GetAsyncKeyState(VK_RBUTTON)

void menu();
void newGame();
void play(int height, int width, int bombs);
void createDisplay(int height, int width);
void createAnswer(int height, int width, int bombs);