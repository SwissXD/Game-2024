//--------------------------------------//
// creat date 16.01.2016
// autor: tkel
//--------------------------------------//
#include <iostream>
#include "Puzzel2048.hxx"
int main()
{
    Game test;
    std::cout << test;
    test.tiltBoard(Cardinals::Bottom);
    std::cout << test;
}
