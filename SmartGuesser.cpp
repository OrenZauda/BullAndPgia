#include "SmartGuesser.hpp"
#include <iostream>
#include <string>

#define MINIMAX_TURNOFF 5000
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
    }

    if (start)
    {
        start = false;
        return _guess;
    }

    int r = responsePegs;
   
    if (r == p * 10)
    {
        return "";
    }

   
    long newTeste;
    // if (countActive(active, pow(m,p)) < MINIMAX_TURNOFF)
    // {
    //     // Apply the minimax rule to select next code to test
    //     //   printf("    Applying minimax...\n");
    //     newTeste = minimax(b, pow(m,p), active, p);
    // }
    // else
    // {
        // Turn off minimax for big numbers to increase speed,
        // but will need more steps
        newTeste = firstActive(b, pow(m,p), active, p);
    // }

    if (newTeste == teste)
    {
        //   printf("\n[E] Opps, got into an infinite loop, please report to "
        //          "author\nExiting immediately\n");
        return "8";
    }
    
    teste = newTeste;
    _guess = to_string(teste);
    complete(_guess);
    return _guess;
    //   }
}
void SmartGuesser::complete(string guess)
{
    for(int i=guess.length();i<p;i++){
        _guess="0"+guess;
    }

}
void SmartGuesser::startNewGame(uint length)
{
    start = true;
    _length = length;
    p = length;

    long len = pow(m, p); // 6^4 possibilities

    // Initialization of possibilities
     active = new bool[len]; // array of booleans to exclude in next search
    b = new long[len];
    initArrayFromZero(b, len, m);
    for (int i = 0; i < len; i++)
    {
        active[i] = 1;
    }
   
}

void SmartGuesser::learn(string reply)
{

    int responsePegs = ((int)reply[0] - 48) * 10;
    responsePegs += (int)reply[2] - 48;
    excludeNumbersWithSameCode(stol(_guess), responsePegs, b, pow(m, p), active, p);
}

// other functions

long SmartGuesser::min(long a, long b) { return a < b ? a : b; }

// int SmartGuesser::inputCP(int def)
// {
//     /// Handle input of number from 2 to 10
//     // TODO: deal with scanf() overflow
//     int n = 0, s = 0;
//     while (1)
//     {
//         s = scanf("%i", &n);
//         if (n > 0 && n < 11)
//         {
//             return n;
//         }
//         else if (s)
//         {
//             //   printf("[!] Please enter number from 2 to 10\n");
//         }
//         else
//         {
//             //   printf("[!] Your input may have caused overflow. Using default number "
//             //          "(%i)\n",
//             //          def);
//             break;
//         }
//     }
//     return def;
// }

bool SmartGuesser::handleInput(long input, int m, int p)
{
    /// Return true if proper number is being input (base m, length p)
    for (int i = 0; i < p; ++i)
    {
        long num = input / pow(10, p - i - 1);
        if (num >= m || num < 0)
            return 0;
        input -= num * pow(10, p - i - 1);
    }
    return 1;
}

int SmartGuesser::testCode(long guess, long code, int p)
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

long SmartGuesser::countActive(bool  *active, long length)
{
    long count = 0;
    for (long i = 0; i < length; ++i)
    {
        if (active[i])
            count++;
    }
    return count;
    // return active.size();
}

void SmartGuesser::initArrayFromZero(long *a, long length, int m)
{
    /// Recursively initialize array [{0..m},{1..m},{2..m} ... {n..m}]
    for (long i = 0; i < length; i++)
    {
        a[i] = composeNum(i, m);
    }
}

long SmartGuesser::testNumber(long testingNumber, long *b, long length, bool *active, int p)
{
    /// Find maximum score of number to test:
    /// https://programmingpraxis.com/2009/11/20/master-mind-part-2/
    long maximum = 0;
    for (long i = 0; i < p * 10; i++)
    {
        long counter = 0;
        bool f = (composeNum(i, 5) / 10 + composeNum(i, 5)) < 5;
        for (long j = 0; j < length; j++)
        {
            if (active[j] && f)
            {
                if (testCode(testingNumber, b[j], p) == composeNum(i, 5))
                {
                    counter++;
                }
            }
        }
        if (counter > maximum)
        {
            maximum = counter;
        }
    }

    return maximum;
}

// void setNumbersWithSameCodeActive(long number, long code, long *b, long length,
//                                   bool *active, int p) {
//   /// For each number with the same # of blacks and whites set "active"
//   for (long i = 0; i < length; ++i) {
//     if (testCode(b[i], number, p) == code) {
//       active[i] = 1;
//     } else {
//       active[i] = 0;
//     }
//   }
// }

void SmartGuesser::excludeNumbersWithSameCode(long number, long code, long *b, long length,
                                              bool *active, int p)
{
    /// For each number with not the same # of blacks and whites set "not active"
    for (long i = 0; i < length; ++i)
    {
        if (active[i] && (testCode(b[i], number, p) != code))
        {
            active[i] = 0;
        }
    }
}

long SmartGuesser::firstActive(long *b, long length, bool *active, int p)
{
    /// This does what you think it does
    long minimum = -1;
    long minimumNumber = -1;
    for (long i = 0; i < length; ++i)
    {
        if (active[i])
        {
            //minimum = testNumber(b[i], b, pow(m,p), active, p);
            minimumNumber = b[i];
            return minimumNumber;
        }
    }
    return minimumNumber;
}

long SmartGuesser::minimax(long *b, long length, bool *active, int p)
{
    /// Minimax explanation:
    /// https://programmingpraxis.com/2009/11/20/master-mind-part-2/

    // Set initial minimum
        cout<<"delay1"<<endl;

    long minimumNumber = firstActive(b, pow(m,p), active, p);
        cout<<"delay2"<<endl;

    long minimum = testNumber(minimumNumber, b, pow(m,p), active, p);
        cout<<"delay3"<<endl;

    // Apply minimax
    for (long j = 0; j < length; j++)
    {
        if (!active[j])
        {
            continue;
        }
        else
        {
            long localMaximum = testNumber(b[j], b, pow(m,p), active, p);
                cout<<"delay4"<<endl;

            if (localMaximum < minimum)
            {
                minimum = localMaximum;
                minimumNumber = b[j];
            }
            //   printf("\r    [%li] minimum: %li minimax: %li", j, minimum, minimumNumber);
        }
    }

    //   printf("\n");
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
// void printResult(long result) {
//   /// This does what you think it does
//   printf("\nYour number is %li.\nGGWP\n\n", result);
// }

}; // namespace bullpgia
