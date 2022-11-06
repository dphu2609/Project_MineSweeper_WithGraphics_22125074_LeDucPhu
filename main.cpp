#include "function.cpp"
using namespace std;
int main() {
    while(1) {
        if (!isPlaying) {
            if (playAgain) {
                createDisplay(againHeight,againWidth,againBombs);
                createAnswer(againHeight,againWidth,againBombs);
                checkLose=false;
                play(againHeight,againWidth,againBombs);
            }
            else menu();
        }   
    }
    return 0;
}