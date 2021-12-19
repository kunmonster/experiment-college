#include<iostream>
#include<time.h>

class Rand{
    private:
    unsigned long randSeed;
    public:
    Rand(unsigned long);        //constructor
    unsigned short generateRand(unsigned long seed=0);       //get the number from 0 to n-1
    double generateRand_1();                          //get the number from 0 to 1
};
Rand::Rand(unsigned long seed){
    if(seed == 0)
        this->randSeed = time(0);
    else
        this->randSeed = seed;
}