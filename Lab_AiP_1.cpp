#include <cctype>
#include <stdlib.h>
#include<iostream>
#include <algorithm>
#include <array>
#include <cmath>
 
using namespace std;
 
bool is_number(const string s)
{
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !isdigit(c) && c != ','; }) == s.end();
}
 
int main() {
    int xmin = 0, xmax = 20, dx = 2, counter = 1;
    float lox = 1488.228;
    string a;
    cout << "x\t|y\t|a" << endl;
    cout << "___________________";
    cin >> a;
    bool sosi = false;
    if(!is_number(a))
    {
        sosi = true;
    }
    else
        lox = stof(a);
    for(xmin; xmin <= xmax; xmin += dx){
        if(sosi)
            cout << xmin <<"\t|" << "Idi Nahuy" << "\t|" << a << endl;
        else
            cout << xmin <<"\t|" << (2 / (lox + xmin)) * (pow(xmin,2)) + ((3*xmin) / (lox + cos(2*xmin))) << "\t|" << lox << endl;
 
 
    }
}