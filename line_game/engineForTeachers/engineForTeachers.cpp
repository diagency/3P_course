#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>  
#include <vector>
#include <string>
#define MAXIMAL_AREA_SIZE 12
#define MAXIMAL_STANDING_TIME 4

using namespace std;

int x, y, n, m, step = 0, winnerNumber = -1, lastGamer = -1, tour = 1, Area[100][100], order;
string gamer1Name = "Computer_1", gamer2Name = "Computer_2";
vector <string> steps;
string (*gamer1Step)(int ) = NULL, (*gamer2Step)(int ) = NULL;
ofstream fout;


bool stepIsValid(int row, int column){
    if (row == 0 && column == 0)
        return false;
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

string unlucky_player(int tour_number){
    vector<string> possibleSteps;
    if (stepIsValid(x - 1, y))
        possibleSteps.push_back("north");
    if (stepIsValid(x + 1, y))
        possibleSteps.push_back("south");
    if (stepIsValid(x, y - 1))
        possibleSteps.push_back("west");
    if (stepIsValid(x, y + 1))
        possibleSteps.push_back("east");
    if (possibleSteps.size() > 0){
        return possibleSteps[rand() % possibleSteps.size()];
    } 
    return "north";
}

string tour1step(){
    if (x < y)
        return "south";
    return "east";
}

string tour2step(){
    if (step == 0){
        if (n < m)
            return "east";
        return "south";
    } 
    return tour1step();
}

string tour3step(){
    if (stepIsValid(x - 1, y) && x % 2 == 1 && y % 2 == 0)
        return "north";
    if (stepIsValid(x + 1, y) && x % 2 == 1 && y % 2 == 0)
        return "south";
    if (stepIsValid(x, y - 1) && x % 2 == 0 && y % 2 == 1)
        return "west";
    if (stepIsValid(x, y + 1) && x % 2 == 0 && y % 2 == 1)
        return "east";
    return "north";
}

string computer1(int tour_number){
    if (tour == 1 || tour == 3)
        return unlucky_player(tour_number);
    return tour2step();
}

string computer2(int tour_number){
    if (tour == 1)
        return tour1step();
    if (tour == 2)
        return unlucky_player(tour_number);
    if (tour == 3)
        return tour3step();
}

void applySettings(){
    gamer1Name = "Clever_computer_1";
    gamer2Name = "Clever_computer_2";
    gamer1Step = &computer1;
    gamer2Step = &computer2;
    tour = 3;
    order = 5;
}

void generateTour(int tour_number){
    x = 0;
    y = 0;
    if (tour_number == 1){
        n = rand() % (MAXIMAL_AREA_SIZE - 6) + 6;
        m = n;
    }
    if (tour_number == 2){
        n = rand() % (MAXIMAL_AREA_SIZE - 6) + 6;
        m = n + 1;
    }
    if (tour_number == 3){
        n = 2 * (rand() % (MAXIMAL_AREA_SIZE / 2 - 2) + 2) + 1;
        m = 2 * (rand() % (MAXIMAL_AREA_SIZE / 2 - 2) + 2) + 1;
    }
    for (int i = 0; i < MAXIMAL_AREA_SIZE; i++){
        for (int j = 0; j < MAXIMAL_AREA_SIZE; j++){
            Area[i][j] = 0;
        }
    }
    Area[x][y] = 2;
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

bool isPossibleToContinue(){
    return stepIsValid(x, y + 1) || stepIsValid(x + 1, y) || stepIsValid(x, y - 1) || stepIsValid(x - 1, y);
}

void printAreaInFile(){
    fout << "Area[" << order << "][" << step << "] = [";
    for (int i = 0; i < n; i++){
        fout << "[";
        for (int j = 0; j < m; j++){
            fout << Area[i][j];
            if (j < m - 1)
                fout << ", ";
        }
        fout << "]";
        if (i < n - 1)
            fout << ", ";
    }
    fout << "]" << endl;
}

void printGeneralInfoInFile(){
    fout.open( "histories/" + to_string(order) + ".txt");
    fout << "n[" << order << "] = " << n << endl;
    fout << "m[" << order << "] = " << m << endl;
    fout << "level[" << order << "] = " << tour << endl;
    fout << "gamer_name_1[" << order << "] = \"" << gamer1Name << "\"" << endl;
    fout << "gamer_name_2[" << order << "] = \"" << gamer2Name << "\"" << endl;
    fout << "Area[" << order << "] = " << "[]" << endl; 
}

void printArea(){
    cout << "-----------" << endl;
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

void printResultsInFile(){
    fout << "winner[" << order << "] = " << winnerNumber << endl;
    fout << "steps[" << order << "] = [";
    for (int i = 0; i < steps.size() - 1; i++){
        fout << "\"" << steps[i] << "\", ";
    }
    fout << "\"" << steps[steps.size() - 1] << "\"" << "]" << endl;  
}

int main(){
    applySettings();
    srand(time(NULL));
    generateTour(tour);
    
    printGeneralInfoInFile();
    printAreaInFile();

    string currentStepResult;
    int standingTime = 0;
    
    while (isPossibleToContinue() && standingTime < MAXIMAL_STANDING_TIME){
        currentStepResult = gamerStepResult(1 + step % 2);
        if (currentStepResult != "still"){
            lastGamer = 1 + step % 2;
            standingTime = 0;
        } else {
            standingTime++;
        }
        steps.push_back(currentStepResult);
        step++;
        printAreaInFile();
    }
    
    winnerNumber = lastGamer;
    printResultsInFile();
    return 0;
}
