#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>  
#include <vector>
#define MAXIMAL_AREA_SIZE 100

using namespace std;

int x, y, n, m, step, tour, Area[100][100];
string (*gamer1Step)(int ) = NULL, (*gamer2Step)(int ) = NULL;

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
        n = rand() % (MAXIMAL_AREA_SIZE - 4) + 4;
        m = n;
    }
    if (tour_number == 2){
        // TODO: implement (сгенерировать параметры поля для второго тура)
    }
    if (tour_number == 3){
        n = 2 * rand() % (MAXIMAL_AREA_SIZE / 2) + 1;
        m = 2 * rand() % (MAXIMAL_AREA_SIZE / 2) + 1;
    }
    // TODO: implement (заполнить массив Area начальными значениями) 
}

bool stepIsValid(int row, int column){
    // TODO: implement (вернуть true, если можно сделать шаг в строчку row столбец column)
    return true;
}

string stepResult(string direction){
    string result = "still";
    if (direction == "west" && stepIsValid(x, y - 1)){
        Area[x][y] = 1;
        y -= 1;
        result = direction;
    }
    // TODO: implement
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
   // TODO: implement (вернуть true, если игра не может быть продолжена)
}

void printArea(){
    // TODO: implement (вывести на экран поле)
}

void printResults(){
    // TODO: implement (вывести на номер победителя)
}

int main(){
    srand(time(NULL));
    applySettings();
    generateTour(tour);
    
    for (step = 0; isImpossibleToContinue(); step++){
        string currentStep = gamerStepResult(1 + step % 2);
        printArea();
    }
    return 0;
}
