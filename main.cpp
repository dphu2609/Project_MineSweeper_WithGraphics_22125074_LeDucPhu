#include "function.cpp"
using namespace std;
int main() {
    while(1) {
        if (isPlaying==false) {
            checkLose=false;
            countMark=0;
            countMarkMatchBombs=0;
            if (playAgain) {
                createDisplay(againHeight,againWidth,againBombs);
                createAnswer(againHeight,againWidth,againBombs);
                play(againHeight,againWidth,againBombs);
            }
            else menu();
        }   
    }
    return 0;
}