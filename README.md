### Authors: 
Oren Zauda, [Avichay Nega](https://github.com/avichaynega), [Omer Hadida](https://github.com/2MarShmello2), 

# BullAndPgia

In this task we will learn about a design model called "strategy," which is one of the main uses of the inheritance mechanism.
our task is to write automatic agents for a game Bull's Eye.

## Bulls and Cows rules

the game it's for two players , "the guesser" and "the chooser" ,
the chooser write a 4-digit secret number. 
Then, the geusser try to guess chooser's number who gives the number of matches. 
If the matching digits are in their right positions, they are "bulls", 
if in different positions, they are "cows". 

For Example:

Secret number: 4271
the guesser try: 1234
Answer: 1 bull and 2 cows. (The bull is "2", the cows are "4" and "1").

## Run example in bash :

   for demostration run :
          
      make deme && ./demo
      
   for test run :
    
      make test && ./test 
      
### Our mentor: 

[Erel Segal-Halevi](https://github.com/erelsgl/ariel-cpp-5779)

### Read more about game:

[Bulls and Cows](https://en.wikipedia.org/wiki/Bulls_and_Cows)
