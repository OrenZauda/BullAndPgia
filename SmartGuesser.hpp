
#include <string>
#include "Guesser.hpp"
#include "calculate.hpp"

using namespace std;
using std::string;
namespace bullpgia{
    class SmartGuesser:public Guesser{
        public:
       string _choose;
       SmartGuesser();
      
       SmartGuesser(const string& choose);
    };
};