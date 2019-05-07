#include <string>
#include "Guesser.hpp"
#include "calculate.hpp"
#include <list>
using namespace std;
using std::string;
namespace bullpgia
{
class SmartGuesser : public bullpgia::Guesser
{
public:
   
    //  basic
    string _guess;
    uint _length;
    bool start=true;
    
    // others
    int p;
    int m = 10; 
    int responsePegs ;
   bool *active; 
    long *b;

    // constuctors
    SmartGuesser();
    SmartGuesser(const string &choose);

   
    // basic function
    string guess() override;
    void startNewGame(uint length) override;
    void learn(string reply) override;
    string correctstring (int x,uint len);
   
   
   
    // functions
    long min(long a, long b);
    int inputCP(int def);
    bool handleInput(long input, int m, int p);
    int testCode(long guess, long code, int p);
    long composeNum(long j, int m);
    long countActive(bool *active, long length);
    void initArrayFromZero(long *a, long length, int m);
    long testNumber(long testingNumber, long *b, long length, bool *active, int p);
    void setNumbersWithSameCodeActive(long number, long code, long *b, long length,
                                  bool *active, int p);
   void excludeNumbersWithSameCode(long number, long code, long *b, long length,
                                bool *active, int p);
    long firstActive(long *b, long length, bool *active, int p);
    long minimax(long *b, long length, bool *active, int p);
    long pow(int a, int b);
    void complete(string guess);
    // void printResult(long result);
};
}; // namespace bullpgia
