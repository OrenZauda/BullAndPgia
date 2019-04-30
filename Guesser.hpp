#pragma once
#include <string>
using namespace std;

namespace bullpgia
{
class Guesser
{
private:
    string _guess;

public:
    uint length;

    Guesser() {}

    Guesser(const string &guess)
    {
        cout<< "*****"<< endl;
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
