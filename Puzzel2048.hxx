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
    dGrew   =  2,
    Grew    =  4,
    bGrew   =  8,
    bYellow =  16,
    Yellow  =  32,
    dYellow =  64,
    Orange  = 128,
    dOrange = 256,
    Red     = 512,
    dRed    =1024,
    Pink    =2048,
    dPink   =4096,
    bBlue   =8192
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

    void Double()
    {
        mValue += mValue;
        //mColour = mValue;
    }

    void Reset()
    {
        this->mValue = 0;
        this->mColour = Colour::Grew;
    }

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

    unsigned long long mScore;

    std::minstd_rand mEngine{ std::random_device{}() };
	std::uniform_int_distribution<std::size_t> mValueDist{ 0, 4 };
	std::uniform_int_distribution<std::size_t> mPosDist  { 0, mWidht*mHeight };

    void scored(std::size_t currField, std::size_t nextField)
    {
        this->mScore += mPuzzle[currField].mValue;
        mPuzzle[currField].Double();
        mPuzzle[nextField].Reset();
    }


    void addNumber()
    {
        for(;;)
        {
            if(!BoardFilled())
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
            }
            break;
        }
    }

    bool BoardFilled()
    {
        for(auto it : mPuzzle)
        {
            if(it.mValue == 0)
                return false;
        }
        return true;
    }

    void TiltLeft()
    {
        for(std::size_t row = 0; row < mWidht*mHeight; row+=mWidht)
        {
            bool ColumnDone = false;
            std::size_t currField = row;
            //std::cout << "F0::row: " << row << "\n";
            while(!ColumnDone)
            {
                //std::cout << "W0::currField: " << currField << "\n";
                std::size_t nextField = currField + 1;
                while(mPuzzle[currField].mValue == 0 && nextField <= row+(mHeight-1))
                {
                    //std::cout << "W1::nextField: " << nextField << "\n";
                    if(mPuzzle[nextField].mValue != 0)
                    {
                        mPuzzle[currField] = mPuzzle[nextField];
                        mPuzzle[nextField].Reset();
                        nextField = mWidht*mHeight; //leave loop
                    }
                    else if(mPuzzle[nextField].mValue == 0)
                    {
                        ++nextField;
                    }
                }

                nextField = currField + 1;
                while(mPuzzle[currField].mValue != 0 && nextField <= row+(mHeight-1))
                {
                    //std::cout << "W2::nextField: " << nextField << "\n";
                    if(mPuzzle[nextField].mValue == 0)
                    {
                        ++nextField;
                    }
                    else if(mPuzzle[currField].mValue == mPuzzle[nextField].mValue)
                    {
                        this->scored(currField,nextField);
                        nextField = mWidht*mHeight;//leave loop
                    }
                    else if(mPuzzle[currField].mValue != mPuzzle[nextField].mValue)
                    {
                        nextField = mWidht*mHeight;//leave loop
                    }
                }
                ++currField;
                if(currField >= row+(mHeight-1))
                {
                    ColumnDone = true;
                }
            }
        }
    }


    void TiltRight()
    {
        for(int row = (mWidht-1); row < mWidht*mHeight; row+=mWidht)
        {
            bool ColumnDone = false;
            int currField = row;
            //std::cout << "F0::row: " << row << "\n";
            while(!ColumnDone)
            {
                //std::cout << "W0::currField: " << currField << "\n";
                int nextField = currField - 1;
                while(mPuzzle[currField].mValue == 0 && nextField >= row-(mHeight-1))
                {
                    //std::cout << "W1::nextField: " << nextField << "\n";
                    if(mPuzzle[nextField].mValue != 0)
                    {
                        mPuzzle[currField] = mPuzzle[nextField];
                        mPuzzle[nextField].Reset();
                        nextField = - 1; //leave loop
                    }
                    else if(mPuzzle[nextField].mValue == 0)
                    {
                        --nextField;
                    }
                }

                nextField = currField - 1;
                while(mPuzzle[currField].mValue != 0 && nextField >= row-(mHeight-1))
                {
                    //std::cout << "W2::nextField: " << nextField << "\n";
                    if(mPuzzle[nextField].mValue == 0)
                    {
                        --nextField;
                    }
                    else if(mPuzzle[currField].mValue == mPuzzle[nextField].mValue)
                    {
                        this->scored(currField,nextField);
                        nextField = -1;//leave loop
                    }
                    else if(mPuzzle[currField].mValue != mPuzzle[nextField].mValue)
                    {
                        nextField = -1;//leave loop
                    }
                }
                --currField;
                if(currField <= row-(mHeight-1))
                {
                    ColumnDone = true;
                }
            }
        }
    }

    void TiltUp()
    {
        for(std::size_t column = 0; column < mWidht; ++column)
        {
            bool ColumnDone = false;
            std::size_t currField = column;
            while(!ColumnDone)
            {

                std::size_t nextField = currField + mHeight;
                while(mPuzzle[currField].mValue == 0 && nextField < mWidht*mHeight)
                {

                    if(mPuzzle[nextField].mValue != 0)
                    {
                        mPuzzle[currField] = mPuzzle[nextField];
                        mPuzzle[nextField].Reset();
                        nextField = mWidht*mHeight;
                    }
                    else if(mPuzzle[nextField].mValue == 0)
                    {
                        nextField += mHeight;
                    }
                }

                nextField = currField + mHeight;
                while(mPuzzle[currField].mValue != 0 && nextField < mWidht*mHeight)
                {

                    if(mPuzzle[nextField].mValue == 0)
                    {
                        nextField += mHeight;
                    }
                    else if(mPuzzle[currField].mValue == mPuzzle[nextField].mValue)
                    {
                        this->scored(currField,nextField);
                        nextField = mWidht*mHeight;
                    }
                    else if(mPuzzle[currField].mValue != mPuzzle[nextField].mValue)
                    {
                        nextField = mWidht*mHeight;
                    }
                }
                currField += mHeight;
                if(currField > mWidht*mHeight)
                {
                    ColumnDone = true;
                }
            }
        }
    }

    void TiltDown()
    {
        for(std::size_t column = mWidht*(mHeight-1); column < mWidht*mHeight; ++column)
        {
            bool ColumnDone = false;
            int currField = column;
            while(!ColumnDone)
            {
                int nextField = currField - mHeight;
                while(mPuzzle[currField].mValue == 0 && nextField >= 0)
                {
                    if(mPuzzle[nextField].mValue != 0)
                    {
                        mPuzzle[currField] = mPuzzle[nextField];
                        mPuzzle[nextField].Reset();
                        nextField = -1;
                    }
                    else if(mPuzzle[nextField].mValue == 0)
                    {
                        nextField -= mHeight;
                    }
                }

                nextField = currField - mHeight;
                while(mPuzzle[currField].mValue != 0 && nextField >= 0)
                {
                    if(mPuzzle[nextField].mValue == 0)
                    {
                        nextField -= mHeight;
                    }
                    else if(mPuzzle[currField].mValue == mPuzzle[nextField].mValue)
                    {
                        this->scored(currField,nextField);
                        nextField = -1;
                    }
                    else if(mPuzzle[currField].mValue != mPuzzle[nextField].mValue)
                    {
                        nextField = -1;
                    }
                }
                currField -= mHeight;
                //std::cout << "currField" << currField << "\n";
                if(currField < 0)
                {
                    ColumnDone = true;
                }
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
        mScore = 0;

       // this->addNumber();
        //this->addNumber();
       mPuzzle[0].mValue  = 8;
       mPuzzle[4].mValue  = 16;
       mPuzzle[8].mValue  = 16;
       mPuzzle[12].mValue = 16;

       mPuzzle[1].mValue  = 2;
       mPuzzle[5].mValue  = 2;
       mPuzzle[9].mValue  = 2;
       mPuzzle[13].mValue = 2;

       mPuzzle[2].mValue  = 8;
       mPuzzle[6].mValue  = 2;
       mPuzzle[10].mValue = 2;
       mPuzzle[14].mValue = 16;

       mPuzzle[3].mValue  = 2;
       mPuzzle[7].mValue  = 0;
       mPuzzle[11].mValue = 8;
       mPuzzle[15].mValue = 2;

    }

    void tiltBoard(Cardinals Direction)
    {
        switch(Direction)
	    {
        case Cardinals::Top:
            this->TiltUp();
            break;
        case Cardinals::Right:
            this->TiltRight();
            break;
        case Cardinals::Bottom:
            this->TiltDown();
            break;
        case Cardinals::Left:
            this->TiltLeft();
            break;
        default:
            assert(false);
	    }
	    this->addNumber();
    }

    friend std::ostream& operator<<(std::ostream& Stream, Game const& Obj)
    {
        Stream << "===================\n";
        for(std::size_t x = 0; x < mWidht; ++x)
        {
            for(std::size_t y = 0; y < mHeight; ++y)
            {
                if( Obj.mPuzzle[(x*mWidht)+y].mValue < 10)
                    Stream << '[' << '0' << Obj.mPuzzle[(x*mWidht)+y].mValue << ']' << " ";
                else
                    Stream << '[' << Obj.mPuzzle[(x*mWidht)+y].mValue << ']' << " ";
            }
            Stream << '\n';
        }
        Stream << "=== Score: " << Obj.mScore << " ===\n";
        return Stream;
    }
};
