#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>  
#include <vector>
#define MAXIMAL_AREA_SIZE 6
#define MAXIMAL_STANDING_TIME 4

using namespace std;

int x, y, n, m, step = 0, winnerNumber = -1, lastGamer = -1, tour = 1, Area[100][100];
string (*gamer1Step)(int ) = NULL, (*gamer2Step)(int ) = NULL;
vector <string> steps;

string computer1(int tour_number){
    return "east";
}

string computer2(int tour_number){
    return "south";
}

void applySettings(){
    gamer1Step = &computer1;
    gamer2Step = &computer2;
    tour = 1;
}

void generateTour(int tour_number){
    x = 0;
    y = 0;
    if (tour_number == 1){
        n = 5;
        m = 5;
    }
    if (tour_number == 2){
        n = 5;
        m = 6;
    }
    if (tour_number == 3){
        n = 5;
        m = 7;
    }
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            Area[i][j] = 0;
        }
    }
    Area[x][y] = 2;
}

bool stepIsValid(int row, int column){
    if (row < 0 || column < 0 || row >= n || column >= m)
        return false;
    if (row > 0 && Area[row - 1][column] == 1)
        return false;
    if (row < n - 1 && Area[row + 1][column] == 1)
        return false;
    if (column > 0 && Area[row][column - 1] == 1)
        return false;
    if (column < m - 1 && Area[row][column + 1] == 1)
        return false;
    return true;
}

string stepResult(string direction){
    string result = "still";
    if (direction == "west" && stepIsValid(x, y - 1)){
        Area[x][y] = 1;
        y -= 1;
        result = direction;
    }
    if (direction == "east" && stepIsValid(x, y + 1)){
        Area[x][y] = 1;
        y += 1;
        result = direction;
    }
    if (direction == "north" && stepIsValid(x - 1, y)){
        Area[x][y] = 1;
        x -= 1;
        result = direction;
    }
    if (direction == "south" && stepIsValid(x + 1, y)){
        Area[x][y] = 1;
        x += 1;
        result = direction;
    }
    Area[x][y] = 2;
    return result;
}

string gamerStepResult(int gamerNumber){
    if (gamerNumber == 1)
        return stepResult((*gamer1Step)(tour));
    else
        return stepResult((*gamer2Step)(tour));
}

bool isImpossibleToContinue(){
    return stepIsValid(x, y + 1) || stepIsValid(x + 1, y) || stepIsValid(x, y - 1) || stepIsValid(x - 1, y);
}

void printArea(){
    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){
            cout << Area[i][j];
        }
        cout << endl;
    }
    cout << "-----------" << endl;
}

void printResults(){
    cout << "Winner = " << winnerNumber << endl;
}

int main(){
    applySettings();
    srand(time(NULL));
    generateTour(tour);
    
    printArea();

    string currentStepResult;
    int standingTime = 0;
    
    while (isImpossibleToContinue() && standingTime < MAXIMAL_STANDING_TIME){
        currentStepResult = gamerStepResult(1 + step % 2);
        if (currentStepResult != "still"){
            lastGamer = 1 + step % 2;
            standingTime = 0;
        } else {
            standingTime++;
        }
        steps.push_back(currentStepResult);
        step++;
        printArea();
        char key = cin.get();
    }
    
    winnerNumber = lastGamer;
    printResults();
    return 0;
}
