#include "function.cpp"
#include "gameplay.cpp"

using namespace std;

int main() {
    while(1) {
        if (isPlaying==false) {
            checkLose=false;
            countMark=0;
            countMarkMatchBombs=0;
            if (playAgain) PlayGame(againHeight,againWidth,againBombs);
            else menu();
        }   
    }
    return 0;
}  