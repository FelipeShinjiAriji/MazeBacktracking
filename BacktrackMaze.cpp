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

void move(vector<string>& inputMatrix, int row, int column){
    if(inputMatrix[row][column+1] == '@'){
        cout << "Direita" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row][column+1] = 'P';
        printMatrix(inputMatrix);
        sleep(1);
        cout << "FIM" << endl;
    }
    else if(inputMatrix[row+1][column] == '@'){
        cout << "Baixo" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row+1][column] = 'P';
        printMatrix(inputMatrix);
        sleep(1);
        cout << "FIM" << endl;
    }
    else if(inputMatrix[row-1][column] == '@'){
        cout << "Cima" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row-1][column] = 'P';
        printMatrix(inputMatrix);
        sleep(1);
        cout << "FIM" << endl;
    }
    else if(inputMatrix[row][column-1] == '@'){
        cout << "Esquerda" << endl;
        inputMatrix[row][column] = '.';
        inputMatrix[row][column-1] = 'P';
        printMatrix(inputMatrix);
        sleep(1);
        cout << "FIM" << endl;
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
            int* position = positionStack.pop();
            inputMatrix[row][column] = 'X';
            inputMatrix[*position][*(position+1)] = 'P';
            printMatrix(inputMatrix);
            sleep(1);
            move(inputMatrix, *position, *(position+1));
        }
    }
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

int main(){
    vector<string> readedFile = readFile("labirinto.txt");
    
    cout << "Labirinto inicial: " << endl;
    printMatrix(readedFile);
    sleep(1);
    
    int* position = positionStack.pop();
    positionStack.push(*position, *(position+1));

    move(readedFile, *position, *(position+1));
    printTrack();
    return 0;
}