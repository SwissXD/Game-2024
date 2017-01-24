//--------------------------------------//
// creat date 16.01.2016
// autor: tkel
//--------------------------------------//
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <array>
#include <cassert>
#include <random>

enum class Colour
{
    Grew,
    bYellow,
    Yellow,
    dYellow,
    Orange,
    dOrange,
    Red,
    dRed

};

enum class Cardinals
{
	Top,
	Right,
	Bottom,
	Left
};


struct Field
{
    std::size_t mValue;
    std::size_t x;
    std::size_t y;
    Colour mColour;

    Field(std::size_t value): mValue(value), mColour(Colour::Grew), x(0),y(0)
    {}
    Field(): mValue(0), mColour(Colour::Grew), x(0),y(0)
    {}


    Field(std::size_t xPos, std::size_t yPos,std::size_t value): mValue(value), mColour(Colour::Grew), x(xPos),y(yPos)
    {}

};

class Game
{
    enum
    {
        mWidht = 4,
        mHeight = 4,
    };
    std::array<Field, 16> mPuzzle;

    std::minstd_rand mEngine{ std::random_device{}() };
	std::uniform_int_distribution<std::size_t> mValueDist{ 0, 4 };
	std::uniform_int_distribution<std::size_t> mPosDist  { 0, mWidht*mHeight };

    void addNumber()
    {
        for(;;)
        {
            std::size_t Pos = mPosDist(mEngine);
            if(mPuzzle[Pos].mValue == 0)
            {
                switch(mValueDist(mEngine))
                {
                case 0:
                    mPuzzle[Pos].mValue = 2;
                    break;
                case 1:
                    mPuzzle[Pos].mValue = 4;
                    break;
                case 2:
                    mPuzzle[Pos].mValue = 8;
                    break;
                case 3:
                    mPuzzle[Pos].mValue = 16;
                    break;
                default:
                    assert(false);
                }
            }
            break;
        }
    }

    void tiltBoard(Cardinals Direction)
    {
        switch(Direction)
	    {
        case Cardinals::Top:
            break;
        case Cardinals::Right:
            break;
        case Cardinals::Bottom:
            break;
        case Cardinals::Left:
            break;
        default:
            assert(false);
	    }
    }

    void TiltUp()
    {
        for(std::size_t row = 0; row < mWidht; ++row)
            for(std::size_t i = row; row < mWidht*mHeight; i+=4)
            {
                if(mPuzzle[i].mValue == 0)
                {
                    //for
                }
            }
    }

public:
    Game()
    {
        for(std::size_t x = 0; x < mWidht; ++x)
            for(std::size_t y = 0; y < mHeight; ++y)
            {
                mPuzzle[(x*mWidht)+y].x = x;
                mPuzzle[(x*mWidht)+y].y = y;
            }

        this->addNumber();
        this->addNumber();
    }

    friend std::ostream& operator<<(std::ostream& Stream, Game const& Obj)
    {
        for(std::size_t x = 0; x < mWidht; ++x)
        {
            for(std::size_t y = 0; y < mHeight; ++y)
            {
                Stream << '[' << Obj.mPuzzle[(x*mWidht)+y].mValue << ']' << " ";
            }
            Stream << '\n';
        }
        return Stream;
    }
};
