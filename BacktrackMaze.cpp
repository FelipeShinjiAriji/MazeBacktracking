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
        }
        printf("\n");
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

    for (int i = 0; i < mazeSize; i++) {
        getline(readedFile, readedLine);
        string outputLine;
        for (char c : readedLine) {
            if (c == '0') {
                outputLine += "  ";
            } 
            else if (c == '1') {
                outputLine += "# ";
            } 
            else if (c == '2') {
                outputLine += "° ";
                positionStack.push(i, ((outputLine.size()-3)/2));
            } 
            else if (c == '3') {
                outputLine += "@ ";
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

void printTrack(pilhaEncadeada positionStack){
    pilhaEncadeada positionStackCopy = pilhaEncadeada();
    while(!positionStack.isEmpty()){
        int* position = positionStack.pop();
        positionStackCopy.push(*position, *(position+1));
    }
    printf("Caminho correto: ");
    int* position;
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

    printTrack(positionStack);

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