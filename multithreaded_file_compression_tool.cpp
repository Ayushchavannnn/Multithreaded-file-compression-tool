#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool compressFile(const string& inputFile, const string& outputFile) {
    ifstream input(inputFile, ios::binary);
    if (!input) {
        cerr << "Could not open input file!" << endl;
        return false;
    }

    ofstream output(outputFile, ios::binary);
    if (!output) {
        cerr << "Could not create output file!" << endl;
        return false;
    }

    char currentChar, prevChar;
    int count = 1;

    input.get(prevChar); 

    while (input.get(currentChar)) {
        if (currentChar == prevChar) {
            count++;
        } else {
            output.put(prevChar);
            output.write(reinterpret_cast<char*>(&count), sizeof(count));
            count = 1;
        }
        prevChar = currentChar;
    }

    output.put(prevChar);
    output.write(reinterpret_cast<char*>(&count), sizeof(count));

    return true;
}

bool decompressFile(const string& inputFile, const string& outputFile) {
    ifstream input(inputFile, ios::binary);
    if (!input) {
        cerr << "Could not open input file for decompression!" << endl;
        return false;
    }

    ofstream output(outputFile, ios::binary);
    if (!output) {
        cerr << "Could not create output file for decompression!" << endl;
        return false;
    }

    char currentChar;
    int count;

    while (input.get(currentChar)) {
        input.read(reinterpret_cast<char*>(&count), sizeof(count));
        for (int i = 0; i < count; i++) {
            output.put(currentChar);
        }
    }

    return true;
}

int main() {
    string inputFile = "input.txt";
    string compressedFile = "output.rle";
    string decompressedFile = "decompressed.txt";

    cout << "Starting compression of: " << inputFile << endl;
    if (compressFile(inputFile, compressedFile)) {
        cout << "Compression successful!" << endl;
    } else {
        cerr << "Compression failed!" << endl;
    }

    cout << "Starting decompression of: " << compressedFile << endl;
    if (decompressFile(compressedFile, decompressedFile)) {
        cout << "Decompression successful!" << endl;
    } else {
        cerr << "Decompression failed!" << endl;
    }

    return 0;
}







