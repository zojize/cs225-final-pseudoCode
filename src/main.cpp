/**
 * @file main.cpp
 * A simple C++ program to reverse entropy
 */

#include <iostream>

using namespace std;

int main() {
    int entropy;
    
    cout << "Please insert an entropy value: " << std::endl;

    cin >> entropy;

    cout << "The reverse entropy is: " << (entropy * -1) << std::endl;
}
