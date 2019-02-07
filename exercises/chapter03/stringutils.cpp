/* 
 * File: stringutils.cpp 
 * ------------------ 
 * Implements the following string utilities:
 *   - A function EqualIgnoringCase(str1, str2) that returns true if the two string
 *       parameters contain the same sequence of characters ignoring case distinctions
 *
 *   - A function Capitalize(str) that returns a string in which the initialcharacter is 
 *       capitalized (if it is a letter) and all other letters are converted so that they
 *       appear in lowercase form
 *
 *   - A function IsPalindrome(str) that returns true if the string str is a palindrome
 *
 */


#include <iostream>
using namespace std;

bool EqualIgnoringCase(string str1, string str2);
string Lowercase(string str);
string Capitalize(string str);
bool IsPalindrome(string str);
void TestEqualIgnoringCase();
void TestCapitalize();
void TestIsPalindrome();

int main() {
    TestEqualIgnoringCase();
    TestCapitalize();
    TestIsPalindrome();
    return 0;
}

bool EqualIgnoringCase(string str1, string str2) {
    return Lowercase(str1) == Lowercase(str2);
}

string Lowercase(string str) {
    string lower = "";
    for (int i=0; i < str.length(); i++){
        lower += tolower(str[i]);
    }
    return lower;
}

string Capitalize(string str) {
    if (str.length() == 0) return str;
    string capitalized = "";
    capitalized += toupper(str[0]);
    for (int i=1; i < str.length(); i++) {
        capitalized += tolower(str[i]);
    }
    return capitalized;
}

bool IsPalindrome(string str) {
    if (str.length() <= 1) return true;
    return str[0] == str[str.length()-1] && 
           IsPalindrome(str.substr(1, str.length()-2));
}

void TestEqualIgnoringCase() {
    cout << "Testing EqualIgnoringCase..." << endl
         << "ABCD == abcd: " << EqualIgnoringCase("ABCD", "abcd") << endl
         << "ABCD == abc: " << EqualIgnoringCase("ABCD", "abc") << endl
         << "\"\" == \"\":" << EqualIgnoringCase("", "") << endl
         << endl;
}

void TestCapitalize() {
    cout << "Testing Capitalize..." << endl
         << "Capitalizing 'aBcDe': " << Capitalize("aBcDe") << endl
         << "Capitalizing '': " << Capitalize("") << endl
         << endl;
}

void TestIsPalindrome() {
    cout << "Test IsPalindrome..." << endl
         << "Palindrome 'abcdcba': " << IsPalindrome("abcdcba") << endl
         << "Palindrome 'abcdcb': " << IsPalindrome("abcdcb") << endl
         << "Palindrome '': " << IsPalindrome("") << endl
         << "Palindrome 'a': " << IsPalindrome("a") << endl
         << "Palindrome 'bb': " << IsPalindrome("bb") << endl
         << endl;
}