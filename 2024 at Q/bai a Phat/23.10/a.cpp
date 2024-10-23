#include <string>
#include <iostream>
using namespace std;

int main() {
    string s = "Hello, World!";
    cout << s << endl;

    // Accessing characters in a string
    cout << "Character at index 0: " << s[0] << endl;

    // Changing characters in a string
    s[0] = 'H';
    cout << "Modified string: " << s << endl;

    // Concatenation of strings
    string s1 = "Hello";
    string s2 = " World";
    string s3 = s1 + " " + s2;
    cout << "Concatenated string: " << s3 << endl;

    // Finding the length of a string
    int length = s.length();
    cout << "Length of the string: " << length << endl;

    // Checking if a string is empty
    if (s.empty()) {
        cout << "String is empty" << endl;