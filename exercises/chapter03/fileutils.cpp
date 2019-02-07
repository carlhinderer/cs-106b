/* 
 * File: fileutils.cpp 
 * ------------------ 
 *  This program reads a file, and prints the number of lines, words, and
 *    characters in the file.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
using namespace std;

void GetFile(ifstream & infile);
string GetFileName();
void PrintCounts(ifstream & infile);
int NumWords(string str);
void PrintCounts(int lineCount, int charCount, int wordCount);

int main() {
    ifstream file;
    GetFile(file);
    PrintCounts(file);
    return 0;
}

void GetFile(ifstream & infile) {
    string filename = GetFileName();
    cout << "File: " << filename << endl;
    infile.open(filename.c_str());
}

string GetFileName() {
    string filename = "";
    cout << "Enter the name of the file: ";
    cin >> filename;
    return filename;
}

void PrintCounts(ifstream & infile) {
    int lineCount = 0;
    int wordCount = 0;
    int charCount = 0;
    string line;
    while (getline(infile, line)) {
        lineCount++;
        charCount += line.length();
        wordCount += NumWords(line);
    }
    infile.close();
    PrintCounts(lineCount, charCount, wordCount);
}

int NumWords(string str) {
    int numWords = 0;
    string intermediate;
    stringstream tokenizer(str);
    while(getline(tokenizer, intermediate, ' ')) {
        numWords++;
    }
    return numWords;
}

void PrintCounts(int lineCount, int charCount, int wordCount) {
    cout << "Number of lines: " << lineCount << endl;
    cout << "Number of characters: " << charCount << endl;
    cout << "Number of words: " << wordCount << endl;    
}