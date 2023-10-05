#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
//#include <windows.h> // for windows
#include <unistd.h>  // for linux

#include "pilhaEncadeada.cpp"

using namespace std;

pilhaEncadeada positionStack = pilhaEncadeada();


void printMatrix(const vector<string>& inputMatrix) {
    for (const string& line : inputMatrix) {
        for(char c: line){
            if(c == 'X'){
                cout << " ";
            }
            else{
                cout << c;
            }
            cout << " ";
        }
        printf("\n");
    }
}

bool move(vector<string>& inputMatrix, int row, int column){
    bool end = false;
    if(inputMatrix[row][column+1] == '@'){
        cout << "Direita fim" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row][column+1] = 'P';
        end = true;
        printMatrix(inputMatrix);
        sleep(1);
        cout << endl;
    }
    else if(inputMatrix[row+1][column] == '@'){
        cout << "Baixo fim" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row+1][column] = 'P';
        end = true;
        printMatrix(inputMatrix);
        sleep(1);
        cout << endl;
    }
    else if(inputMatrix[row-1][column] == '@'){
        cout << "Cima fim" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row-1][column] = 'P';
        end = true;
        printMatrix(inputMatrix);
        sleep(1);
        cout << endl;
    }
    else if(inputMatrix[row][column-1] == '@'){
        cout << "Esquerda fim" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row][column-1] = 'P';
        end = true;
        printMatrix(inputMatrix);
        sleep(1);
        cout << endl;
    }
    else{
        if(inputMatrix[row][column+1] == ' '){
            cout << "Direita" << endl;
            positionStack.push(row,column+1);
            inputMatrix[row][column] = '.';
            inputMatrix[row][column+1] = 'P';
            printMatrix(inputMatrix);
            sleep(1);
            move(inputMatrix, row, column+1);
        }
        else if(inputMatrix[row+1][column] == ' '){
            cout << "Baixo" << endl;
            positionStack.push(row+1,column);
            inputMatrix[row][column] = '.';
            inputMatrix[row+1][column] = 'P';
            printMatrix(inputMatrix);
            sleep(1);
            move(inputMatrix, row+1, column);
        }
        else if(inputMatrix[row-1][column] == ' '){
            cout << "Cima" << endl;
            positionStack.push(row-1,column);
            inputMatrix[row][column] = '.';
            inputMatrix[row-1][column] = 'P';
            printMatrix(inputMatrix);
            sleep(1);
            move(inputMatrix, row-1, column);
        }
        else if(inputMatrix[row][column-1] == ' '){
            cout << "Esquerda" << endl;
            positionStack.push(row,column-1);
            inputMatrix[row][column] = '.';
            inputMatrix[row][column-1] = 'P';
            printMatrix(inputMatrix);
            sleep(1);
            move(inputMatrix, row, column-1);
        }
        else{
            cout << "Retorne" << endl;
        }
    }
    return end;
}

vector<string> readFile(const string& inputFile) {
    vector<string> outputMatrix;

    string readedLine;
    int mazeSize;

    ifstream readedFile(inputFile);

    getline(readedFile, readedLine);
    mazeSize = stoi(readedLine);

    vector<int> firstPosition;
    bool lastPositionFound = false;

    for (int row = 0; row < mazeSize; row++) {
        getline(readedFile, readedLine);
        string outputLine;
        for (char c : readedLine) {
            if (c == '0') {
                outputLine += ' ';
            } 
            else if (c == '1') {
                outputLine += '#';
            } 
            else if (c == '2') {
                outputLine += 'P';
                positionStack.push(row, (outputLine.size()-1));
            } 
            else if (c == '3') {
                outputLine += '@';
                lastPositionFound = true;
            }
        }
        outputMatrix.push_back(outputLine);
    }
    readedFile.close();

    if(!lastPositionFound){
        cout << "Last position not found" << endl;
        exit(1);
    }

    return outputMatrix;
}

void printTrack(){
    pilhaEncadeada positionStackCopy = pilhaEncadeada();
    int* position;
    while(!positionStack.isEmpty()){
        position = positionStack.pop();
        positionStackCopy.push(*position, *(position+1));
    }
    printf("Caminho correto: ");
    while(!positionStackCopy.isEmpty()){
        position = positionStackCopy.pop();
        printf("(%d, %d) ", *position, *(position+1));
    }
    printf("\n");
}

// para testar o labinto.txt
int main(){
    vector<string> readedFile = readFile("labirinto.txt");
    
    while(true){
        printMatrix(readedFile);
        sleep(1);
        cout << endl;
        printMatrix(readedFile);
        cout << endl;
        break;
    }

    move(readedFile, 1, 1);

    return 0;
}

/* Para poder testar diversos labirintos
int main(int argc , char ** argv) {
    for(int i = 1; i < argc; i++){
        vector<string> readedFile = readFile(argv[i]);

        while(true){
            printMatrix(readedFile);
            sleep(1);
            cout << endl;
            printMatrix(readedFile);
            cout << endl;
            break;
        }
    }

    return 0;
}
*/