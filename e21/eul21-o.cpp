#include <stdio.h>

int isprime(int n);
int d(int n);
int pow(int a, int b);

int primes[10000];
int psize;

int main() {
  int i;
  int a,b,sum;
  
  for (i = 2; i < 10000; i++) {
    if (isprime(i)) primes[psize++] = i;
  }
  
  sum = 0;
  for (a = 2; a < 10000; a++) {
    b = d(a);
    if (a!=b && a==d(b)) {
      sum += a;
    }
  }
  printf("%d\n",sum);
  
  return 0;
}

int isprime(int n) {
  int i;
  
  if (n<=1) return 0;
  if (n%2==0) return n==2;
  for (i = 3; i*i <= n; i+=2) {
    if (n%i==0) return 0;
  }
  return 1;
}

int d(int n) {
  int i,cnt,m=n;
  int sum;
  
  if (n==1) return 0;
  
  i = 0;
  sum = 1;
  while (n>1) {
    cnt = 0;
    while (i < psize && n%primes[i]==0) {
      n/=primes[i];
      cnt++;
    }
    if (i >= psize) break;
    
    /*printf("there are %d %d's\n",cnt,primes[i]);*/
    
    if (cnt>0) sum *= (pow(primes[i],cnt+1)-1)/(primes[i]-1);
    i++;
  }
  
  return sum-m;
}

int pow(int a, int b) { return b==0?1:a*pow(a,b-1); }
