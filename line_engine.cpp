#include <iostream>
#include <stdlib.h>
#include <time.h>  
#define TOUR 1

using namespace std;

int x, y, n, m, step, winner;
int A[100][100];

string computer1(int tour_number){
    return "east";
}

string computer2(int tour_number){
    return "north";
}

void generateTour(int tour_number){
    x = 0;
    y = 0;
    if (tour_number == 1){
        n = rand() % 100;
        m = n;
    }
    if (tour_number == 2){
        n = 4 * (rand() % 25);
        m = n + 1;
    }
    if (tour_number == 3){
        n = 2 * (rand() % 50) + 1;
        m = 2 * (rand() % 50) + 1;
    }
}

bool stepIsValid(int row, int column){
    //TODO: implement
    return true;
}

void makeStep(string direction){
    A[x][y] = 1;
    if (direction == "west" && y > 0 && stepIsValid(x, y - 1))
        y -= 1;
    //TODO: implement
    A[x][y] = 2;
}

bool isImpossibleToContinue(){
    //TODO: implement
    return true;
}

int main(){
    step = 0;
    srand (time(NULL));
    generateTour(TOUR);
    while (isImpossibleToContinue()){
        if (step % 2 == 0)
            makeStep(computer1(step));
        else
            makeStep(computer2(step));
        step++;
    }
    winner = 2 - step;
    return 0;
}
