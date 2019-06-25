# Authors: 
Avichay Avtai Nega, [Omer Hadida](https://github.com/2MarShmello2), [Oren Zauda](https://github.com/OrenZauda)

# BullAndPgia

In this task we will learn about a design model called "strategy," which is one of the main uses of the inheritance mechanism.
our task is to write automatic agents for a game Bull's Eye.

## Bulls and Cows rules

Its a game for two players. The game is based on guessing and cracking. 
At the beginning of the game each player chooses a number of digits, and the purpose of the game of the game is to crack the opponent's code.

### The progress of the game

At the beginning of the game, each player chooses a number of several digits. When a four-digit number is used, 
numbers are not allowed to be repeated and the number will not start at 0. For example, 1234 is a valid number, 1123 and 0123 are invalid.

**What is Bulls and Cows**
   - Bulls
     - A situation in which one of the digits in the numeral number is the same as the number in the original number,
     and is positioned correctly.
   - Cows
      - A situation in which one of the digits in the numeral number is the same as the number in the original number,
      but is located in a different position.

## Run example in bash :

   for demostration run :
          
      make deme && ./demo
      
   for test run :
    
      make test && ./test 
      
### Our mentor: 

[Erel Segal-Halevi](https://github.com/erelsgl/ariel-cpp-5779)

### Source:

[Bulls and Cows](https://en.wikipedia.org/wiki/Bulls_and_Cows)
