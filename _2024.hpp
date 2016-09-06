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
        _2024Board(): Tokens{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8}
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

        void MoveDown()
        {
             //------------//
            // 0  1  2  3 //
            // 4  5  6  7 //
            // 8  9 10 11 //
            //12 13 14 15 //
            //------------//

            //summUp Token
            for(std::size_t i = 12; i < 16; ++i)
            {
                for(std::size_t j = i; j > i-7; j-=4)
                {
                    std::cout << "i: " << i << '\n' ;
                    while(this->Tokens[j] == empty && j > 4)
                    {
                        j-=4;
                    }

                    unsigned j2 = j-4;
                    /*if(j > 4)
                    {
                        j2 = j-4;
                    }*/

                    while(this->Tokens[j2] == empty && j2 > 4)
                    {
                        j2-=4;
                    }
                    std::cout << "j:   " << j << '\n';
                    std::cout << "j2:  " << j2 << '\n';
                    if(this->Tokens[j] == this->Tokens[j2])
                    {
                        this->Tokens[j] *= 2;
                        this->Tokens[j2] = empty;
                        if(j > 4)
                        {
                            j-=4;
                        }
                    }
                }

                for(std::size_t j = i; j > i-12; j-=4)
                {
                    unsigned counter = j;
                    while(this->Tokens[j] == empty && counter > i-12)
                    {
                        this->Tokens[j] = this->Tokens[counter-4];
                        this->Tokens[counter-4] = empty;
                        counter-=4;
                    }
                }
            }
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
                for(std::size_t j = i; j < i+8; j+=4)
                {
                    while(this->Tokens[j] == empty && j < 12)
                    {
                        j+=4;
                    }

                    unsigned j2 = j+4;
                    while(this->Tokens[j2] == empty && j2 < 12)
                    {
                        j2+=4;
                    }

                    if(this->Tokens[j] == this->Tokens[j2])
                    {
                        this->Tokens[j] *= 2;
                        this->Tokens[j2] = empty;
                        if(j < 12)
                        {
                            j+=4;
                        }
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

        void MoveRight()
        {
            //------------//
            // 0  1  2  3 //
            // 4  5  6  7 //
            // 8  9 10 11 //
            //12 13 14 15 //
            //------------//

            //clear empty Token
            for(std::size_t i = 3; i < 15; i+=4)
            {
                for(std::size_t j = i; j > i-3; --j)
                {
                    while(this->Tokens[j] == empty && j > i-3)
                    {
                        --j;
                    }

                    unsigned j2 = j-1;
                    while(this->Tokens[j2] == empty && j2 > i-3)
                    {
                        --j2;
                    }

                    if(this->Tokens[j] == this->Tokens[j2])
                    {
                        this->Tokens[j] *= 2;
                        this->Tokens[j2] = empty;
                        if(j > i-4)
                        {
                            --j;
                        }
                    }
                }

                for(std::size_t j = i; j > i-3; --j)
                {
                    unsigned counter = j;
                    while(this->Tokens[j] == empty && counter > i-3)
                    {
                        this->Tokens[j] = this->Tokens[counter-1];
                        this->Tokens[counter-1] = empty;
                        --counter;
                    }
                }
            }
        }
};

