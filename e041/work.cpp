#include <iostream>

using namespace std;

bool isaprime(int tal);

int main()
{
    char ca[]="7654321";
    int tal;

    while(1)
    {
        prev_permutation(ca,ca+strlen(ca));
        tal=atoi(ca);
        if(isaprime(tal))        
            break;
    }
    
    cout << tal << endl;
    
    system("pause");
}
