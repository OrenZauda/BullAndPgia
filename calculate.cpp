

#include <string>
using std::string;
#include "calculate.hpp"


namespace bullpgia{
string calculateBullAndPgia(string choice, string guess){
     int bull = 0, pgia = 0;
    for (int i = 0; i < choice.length(); i++)
    {
        if (choice[i] == guess[i])
        {
            bull++;
            choice[i] = 't';
            guess[i] = 's';
        }
    }
    for (int i = 0; i < guess.length(); i++)
    {
        if (choice.find(guess[i]) != string::npos)
            pgia++;
    }
    string bullAndPgia = to_string(bull) + "," + to_string(pgia);
    return bullAndPgia;
}
};
