//_2024.hpp

//--------------------------
// GameProjekt: 2024
// Tkel
// Data 30.08.2016
//--------------------------
#include <cstdlib>
#include <iostream>
#include <ctime>

class GameToken
{
    private:
        unsigned Counter;

    public:
        unsigned Position;

        GameToken(unsigned counter, unsigned pos): Counter(counter), Position(pos)
        {
        }

        GameToken(unsigned counter): Counter(counter), Position(0)
        {

        }
        GameToken(): Counter(0), Position(0)
        {

        }

        unsigned getCounter()
        {
            return this->Counter;
        }

        GameToken& operator+=(GameToken const& val)
        {
            this->Counter += val.Counter;
            return *this;
        }

        bool operator== (GameToken const& val) const
        {
            return this->Counter == Counter;
        }

        friend std::ostream& operator<< (std::ostream& Stream, GameToken const& Object)
        {
            Stream << Object.Counter;
            return Stream;
        }
};


class _2024Board
{
    private:
        GameToken Tokens[16] = { 0 };

    public:
        _2024Board()
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
};

