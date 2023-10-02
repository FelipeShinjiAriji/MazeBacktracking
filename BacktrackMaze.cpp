#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
//#include <windows.h> // for windows
#include <unistd.h>  // for linux

using namespace std;

void printMatrix(const vector<string>& inputMatrix) {
    for (const string& line : inputMatrix) {
        cout << line << endl;
    }
}

vector<string> readFile(const string& inputFile) {
    vector<string> outputMatrix;

    string readedLine;
    int mazeSize;

    ifstream readedFile(inputFile);

    getline(readedFile, readedLine);
    mazeSize = stoi(readedLine);

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
            } 
            else if (c == '3') {
                outputLine += "@ ";
            }
        }
        outputMatrix.push_back(outputLine);
    }
    readedFile.close();

    return outputMatrix;
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