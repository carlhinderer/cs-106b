/* 
 * File: vectorutils.cpp 
 * ------------------ 
 * Implements the following vector utilities:
 *   - A function RemoveZeroElements that removes any zero-valued
 *       elements from a vector of ints.
 *
 *   - A function ReadVector that reads lines from the data file specified 
 *       by infile, each of which consists of afloating-point number, and 
 *       adds them to the vector vec.  The end of the vector isindicated by 
 *       a blank line or the end of the file.  The function should return true 
 *       if itsuccessfully reads the vector of numbers; if it encounters the 
 *       end of the data filebefore it reads any values, the function should 
 *       return false.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void RemoveZeroElements(vector<int> & vec);
void PrintIntVector(vector<int> & vec);
void PrintDoubleVector(vector<double> & vec);
bool ReadVector(ifstream & infile, vector<double> & vec);
void TestRemoveZeroElements();
void TestReadVector();

int main() {
    TestRemoveZeroElements();
    TestReadVector();
    return 0;
}

void RemoveZeroElements(vector<int> & vec) {
    int size = vec.size();
    int pos = 0;
    while(pos < size) {
        if (vec[pos] == 0) {
            vec.erase(vec.begin() + pos);
            size--;
        } else {
            pos++;
        }
    }
}

bool ReadVector(ifstream & infile, vector<double> & vec) {
    double num;
    string line;
    bool endOfFile = true;
    vec.clear();
    while (getline(infile, line)) {
        endOfFile = false;
        if (line == "") break;
        istringstream(line) >> num;
        vec.push_back(num);
    }
    return !endOfFile;
}

void PrintIntVector(vector<int> & vec) {
    for (int i=0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void PrintDoubleVector(vector<double> & vec) {
    for (int i=0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
}

void TestRemoveZeroElements() {
    cout << "Testing RemoveZeroElements..." << endl;
    int arr[] = {1, 2, 3, 0, 4, 0, 5, 0, 6};
    vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
    cout << "Original Vector: ";
    PrintIntVector(vec);
    RemoveZeroElements(vec);
    cout << "After Removing Zeros: ";
    PrintIntVector(vec);
    cout << endl;
}

void TestReadVector() {
    cout << "Test ReadVector..." << endl;
    vector<double> vec;
    ifstream infile;
    infile.open("SquareCubeRoots.txt");
    while (ReadVector(infile, vec)) {
        cout << "Current value of vector: ";
        PrintDoubleVector(vec);
    }
    cout << endl;
}