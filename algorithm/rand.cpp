#include<iostream>
#include<time.h>

const unsigned long maxshort = 65536L;
const unsigned long multiplier = 1194211693L;
const unsigned long adder  = 12345L;

class Rand{
    private:
    unsigned long randSeed;
    public:
    Rand(unsigned long seed=0);        //constructor
    unsigned short generateRand(unsigned long n);       //get the number from 0 to n-1
    double generateRand_1();                          //get the number from 0 to 1
};
Rand::Rand(unsigned long seed){
    if(seed == 0)
        this->randSeed = time(0);
    else
        this->randSeed = seed;
}
unsigned short Rand::generateRand(unsigned long n){
  this->randSeed = multiplier * this->randSeed + adder;
  return (unsigned short)((this->randSeed>>16)%n);
}

double Rand::generateRand_1(){
  return this->generateRand(maxshort) / (double)maxshort;
}

int main(){
  Rand rand;
  int a = rand.generateRand(5);
  int arr[100]{0};
  for(int i=0;i<=99;i++){
    arr[i]=rand.generateRand(5);
  }
  return 0;
}