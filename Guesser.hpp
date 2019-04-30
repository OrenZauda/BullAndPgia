#pragma once
#include <string>
#include <iostream>
using namespace std;

namespace bullpgia
{
class Guesser
{
private:
    string _guess;

public:
    uint length;

    Guesser() {
    _guess="0011";
     length = 4;
    }

    Guesser(const string &guess)
    {
        _guess = guess;
        length = guess.length();
    }

    void startNewGame(uint length)
    {
        length--;
    }

    virtual string guess()
    {
        return _guess;
    }

    void learn(string reply)
    {
        return;
    }
};
}; // namespace bullpgia
