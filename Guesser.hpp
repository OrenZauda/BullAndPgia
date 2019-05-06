#pragma once
#include <string>
using namespace std;

namespace bullpgia
{
class Guesser
{
private:
    string _guess;
    string _learn;

public:
    uint length;

    Guesser() {}

    Guesser(const string &guess)
    {
        _guess = guess;
        length = guess.length();
    }

    virtual void startNewGame(uint length)
    {
        return;
    }

    virtual string guess()
    {
        
        return " ";
    }

    virtual void learn(string reply)
    {
        return;
        
    }
};
}; // namespace bullpgia
