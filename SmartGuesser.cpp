#include "SmartGuesser.hpp"
#include <iostream>
#include <string>
using namespace std;
using std::string;


namespace bullpgia
{
SmartGuesser::SmartGuesser(const string &guess)
{
    _guess = guess;
    _length = _guess.length();
}
SmartGuesser::SmartGuesser()
{
    _guess = "";
    _length = _guess.length();
}

// basic finction
string SmartGuesser::guess()
{
    
    long teste = -1;
    
    if (start)
    {
        _guess = "";
        for (int i = 0; i < p; i++)
        {
            if (i < p / 2)
                _guess = '0' + _guess;
            else
                _guess = _guess + '1';
        }
        start = false;
        return _guess;
    }

    
    long newTeste;
  
     newTeste = firstActive();
    
     
    _guess = to_string(newTeste);
    complete(_guess);
    return _guess;
   
}
void SmartGuesser::complete(string guess)
{
    string zero = "";
    for(int i=guess.length();i<p;i++){
        zero="0"+zero;
    }
    _guess = zero + _guess;

}
void SmartGuesser::startNewGame(uint length)
{
   
    start = true;
    _length = length;
    p = length;
    

    combinations = pow(m, p);
    
    // Initialization of possibilities
     active = new bool[combinations]; // array of booleans to exclude in next search
    b = new long[combinations];
    
    initArrayFromZero();
    
    for (int i = 0; i < combinations; i++)
    {
        active[i] = 1;
    }
    
   
}

void SmartGuesser::learn(string reply)
{

    int responsePegs = ((int)reply[0] - 48) * 10;
    responsePegs += (int)reply[2] - 48;
    excludeNumbersWithSameCode(stol(_guess), responsePegs);
}

// other functions

long SmartGuesser::min(long a, long b) { return a < b ? a : b; }

int SmartGuesser::testCode(long guess, long code)
{
    /// Test code for # of black and white pegs
    /// Returns # of black and white pegs
    int g[p];
    int c[p];
    // Decompose a number to p numbers by their places
    for (int i = 0; i < p; ++i)
    {
        g[i] = guess / pow(10, p - i - 1);
        guess -= g[i] * pow(10, p - i - 1);
        c[i] = code / pow(10, p - i - 1);
        code -= c[i] * pow(10, p - i - 1);
    }
    // Create array of occurring numbers
    // 0 - no occurrence,
    // 1 - only color
    // 2 - color and place
    int occurring[11] = {0};
    for (int i = 0; i < p; ++i)
    {
        occurring[g[i]]++;
    }
    int occurringC[11] = {0};
    for (int i = 0; i < p; ++i)
    {
        occurringC[c[i]]++;
    }
    for (int i = 0; i < 11; ++i)
    {
        occurring[i] = min(occurring[i], occurringC[i]);
    }

    int blacks = 0;
    for (int i = 0; i < p; ++i)
    {
        if (g[i] == c[i])
        {
            blacks++;
            occurring[g[i]]--;
        }
    }
    int whites = 0;
    for (int i = 0; i < 11; ++i)
    {
        if (occurring[i] != 0)
            whites += occurring[i];
    }
    
    return blacks * 10 + whites;
}

long SmartGuesser::composeNum(long j, int m)
{
    
    /// Translate number j from decimal into a numeral system with base m
    long r = j % m;
    long b = j / m;
    int d = 1;
    while (b != 0)
    {
        r += (b % m) * pow(10, d);
        b = b / m;
        d++;
    }
    return r;
}


void SmartGuesser::initArrayFromZero()
{
    
    /// Recursively initialize array [{0..m},{1..m},{2..m} ... {n..m}]
    for (long i = 0; i < combinations; i++)
    {
        b[i] = composeNum(i, m);
    }
}



void SmartGuesser::excludeNumbersWithSameCode(long number, long code)
{
    
    /// For each number with not the same # of blacks and whites set "not active"
    for (long i = 0; i < combinations; ++i)
    {
        if (active[i] && (testCode(b[i], number) != code))
        {
            active[i] = 0;
        }
    }
}

long SmartGuesser::firstActive()
{
    long minimumNumber = -1;
    for (long i = 0; i < combinations ; ++i)
    {
        if (active[i])
        {
            minimumNumber = b[i];
            return minimumNumber;
        }
    }
    
    return minimumNumber;
}


long SmartGuesser::pow(int a, int b) {
  /// Power for integers
  if (b == 0) {
    return 1;
  } else if (b == 1) {
    return a;
  } else {
    long r = a;
    for (int i = 1; i < b; i++)
      r = r * a;
    return r;
  };
}


}; // namespace bullpgia
