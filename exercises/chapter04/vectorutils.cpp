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
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void RemoveZeroElements(vector<int> & vec);
void PrintVector(vector<int> & vec);
void TestRemoveZeroElements();

int main() {
    TestRemoveZeroElements();
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

void PrintVector(vector<int> & vec) {
    string vecStr = "";
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
    PrintVector(vec);
    RemoveZeroElements(vec);
    cout << "After Removing Zeros: ";
    PrintVector(vec);
}