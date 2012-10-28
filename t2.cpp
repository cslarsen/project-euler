#include <stdio.h>

unsigned int length_of_sequence(unsigned long long);

int main(int argc, char* argv[]){
  unsigned int start_num = 999999,largest = 0,last = 0,current;
  
  do{
    current = length_of_sequence((unsigned long long)start_num);
    if(current > last){
      largest = start_num;
      last = current;
    }
    start_num-=2;
  }while(start_num > 500001);
  
  printf("%u :: %u\n",largest,current);
  
  return 0;
}

unsigned int length_of_sequence(unsigned long long num){
  unsigned int length = 1;
  
  while(num != 1){
    if(!(num & 1)){
      num/=2;
    }else{
      num = num * 3 + 1;
    }
    length++;
  }
  return length;
}
