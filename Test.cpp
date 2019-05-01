/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#define COMMA ,

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS - DO NOT CHANGE
		ConstantChooser c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g1234{"1234"}, g12345{"12345"}, g9999{"9999"};

		testcase.setname("Calculate bull and pgia")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		;

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		.CHECK_EQUAL(play(c12345, g12345, 4, 100), 1)
		.CHECK_EQUAL(play(c9999, g12345, 4, 100), 0)
		.CHECK_EQUAL(play(c9999, g12345, 4, 100), 0)
		.CHECK_EQUAL(play(c9999, g12345, 4, 100), 0)
		.CHECK_EQUAL(play(c9999, g12345, 4, 100), 0)
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)
		.CHECK_EQUAL(play(c9999, g1234, 4, 100), 101)
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1000"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1111"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1984"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","29843"), "0,2")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1984"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("9999","1984"), "1,0")
		;

		testcase.setname("Play with smart guesser");
		RandomChooser randy;
		SmartGuesser smarty;
		for (uint i=0; i<100; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 100)<=100, true);  // smarty should always win in at most 10 turns!
		}

    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
	cout << "Your grade is: "  << grade << endl;
	return 0;
}
