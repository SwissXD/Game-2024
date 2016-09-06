//main.cpp
//--------------------------
// GameProjekt: 2048
// Tkel
// Data 30.08.2016
//--------------------------

#include "_2024.hpp"

int main()
{
    std::cout << "\nInit------------------------------------\n";
    _2024Board t1;
    std::cout << t1;

    std::cout << "\nStartGame()-----------------------------\n";
    t1.StartGame();
    std::cout << t1;

    std::cout << "\nMoveDown()------------------------------\n";
    t1.MoveDown();
    std::cout << t1;

    std::cout << "\nMoveUp()-------------------------------\n";
    t1.MoveUp();
    std::cout << t1;
}
