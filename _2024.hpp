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
            unsigned FreePos = 0;
            for(std::size_t i = 0; i < 16; ++i)
            {
                if(Tokens[i] == empty)
                {
                    ++FreePos;
                }
            }
            //if(FreePos == 0)
            //{
                //throw shitshit
            //}
            for(std::size_t j = 0; j < NumbOfPos; ++j)
            {
               // std::cout << "j: " << j << '\n';
                std::srand(std::time(0));
                unsigned RandNumb = (std::rand()%FreePos)+1;

                unsigned countPos = 0;
                for(std::size_t i = 0; i < 16; ++i)
                {
                    if(Tokens[i] == empty)
                    {
                        ++countPos;
                    }

                    if(RandNumb == countPos)
                    {
                        //std::cout << "RandNumb: " << RandNumb << '\n';
                       // std::cout << "i: " << i << '\n';
                        unsigned temp = std::rand()%2;
                        if(temp)
                        {
                            Tokens[i] = 2;
                        }
                        else
                        {
                            Tokens[i] = 4;
                        }
                        i=16;
                    }
                }
                --FreePos;
            }
        }

    public:                 //0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15
        _2024Board(): Tokens{ 2, 0, 0, 0, 2, 4, 0, 0, 4, 0, 0, 0, 8, 4, 0, 0}
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
            //------------//
            // 0  1  2  3 //
            // 4  5  6  7 //
            // 8  9 10 11 //
            //12 13 14 15 //
            //------------//

            //clear empty Token
            for(std::size_t i = 0; i < 4; ++i)
            {
                for(std::size_t j = i; j < i+12; j+=4)
                {
                    while(this->Tokens[j] == empty)
                    {
                        j+=4;
                    }

                    unsigned j2 = j+4;
                    while(this->Tokens[j2] == empty)
                    {
                        j2+=4;
                    }

                    if(this->Tokens[j] == this->Tokens[j2])
                    {
                        this->Tokens[j] *= 2;
                        this->Tokens[j2] = empty;
                        j+=4;
                    }
                }

                for(std::size_t j = i; j < i+12; j+=4)
                {
                    unsigned counter = j;
                    while(this->Tokens[j] == empty && counter < i+12)
                    {
                        this->Tokens[j] = this->Tokens[counter+4];
                        this->Tokens[counter+4] = empty;
                        counter+=4;
                    }
                }
            }
        }
};

