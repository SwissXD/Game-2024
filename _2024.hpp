//_2024.hpp

//--------------------------
// GameProjekt: 2024
// Tkel
// Data 30.08.2016
//--------------------------
#include <cstdlib>
#include <iostream>
#include <ctime>

#define empty 0


class _2024Board
{
    private:
        unsigned Tokens[16];


    void setFreePos(unsigned NumbOfPos)
    {
        for(std::size_t j = 0; j < NumbOfPos; ++j)
        {
            unsigned FreePos = 0;
            for(std::size_t i = 0; i < 16; ++i)
            {
                if(Tokens[i]==0)
                {
                    ++FreePos;
                }
            }

            std::srand(std::time(0));
            unsigned RandNumb = std::rand()%FreePos;

            FreePos = 0;
            for(std::size_t i = 0; i < 16; ++i)
            {
                if(Tokens[i]==0)
                {
                    ++FreePos;
                }

                if(RandNumb == FreePos)
                {
                    unsigned temp = std::rand()%2;
                    if(temp)
                    {
                        Tokens[i] = 2;
                    }
                    else
                    {
                        Tokens[i] = 4;
                    }
                }
            }
        }
    }

    public:                 //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
        _2024Board(): Tokens{ 2, 0, 0, 0, 2, 0, 0, 0, 4, 0, 0, 0, 4, 0, 0, 0}
        {

        }

    friend std::ostream& operator<<(std::ostream& Stream, _2024Board const& Obj)
    {
        for(std::size_t i = 0; i < 16; ++i)
        {
            Stream << Obj.Tokens[i] << "\t";
            if((i+1)%4 == 0)
            {
                Stream << '\n';
            }
        }
        return Stream;
    }

    void StartGame()
    {
        this->setFreePos(2);
    }

    void MoveUp()
    {
        // 0  1  2  3
        // 4  5  6  7
        // 8  9 10 11
        //12 13 14 15

        for(std::size_t i = 0; i < 4; ++i)
        {
            for(std::size_t j = 4; j< 16; j+=4)
            {
                if(this->Tokens[i] == this->Tokens[i+j])
                {
                    this->Tokens[i] += this->Tokens[i+j];
                    this->Tokens[i+j] = empty;
                    j+=4;
                }
            }
        }
    }
};

