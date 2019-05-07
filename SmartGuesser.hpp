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
    long combinations;
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
   
   
   
    // functions
    long min(long a, long b);
    int testCode(long guess, long code);
    long composeNum(long j, int m);
    void initArrayFromZero();
   void excludeNumbersWithSameCode(long number, long code);
    long firstActive();
    long pow(int a, int b);
    void complete(string guess);
    
};
}; // namespace bullpgia
