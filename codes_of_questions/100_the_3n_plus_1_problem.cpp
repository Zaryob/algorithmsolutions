#include <iostream>
using namespace std;

long long int lenght_of_algorithm(int a){
    long long int length=0;
    
    loop_jump:
    length++;
    
    if(a==1)
    {
        return length;
    }
    
    else 
    {
        if (a % 2 == 1)
        {
            a = 3 * a + 1;
        }
         
        else
        {
            a /= 2;
        }
    }
    goto loop_jump;
    
}

int main(){
    long long int a[2];
    
    while(cin>>a[0]>>a[1])
    {
        bool flipped;

        if (a[0]> a[1]){
            flipped=true;
            long long int temp=a[0];
            a[0]=a[1];
            a[1]=temp;
        }

        long long int lenght = 0;
        for(int i=a[0];i<=a[1];i++){
            long long int tlenght=lenght_of_algorithm(i);
            if(tlenght> lenght){
                lenght=tlenght;
            }
        }

        if(flipped){
            cout<< a[1] << " " << a[0] << " "<< lenght << endl;
        }
        else 
        {
            cout<< a[0] << " " << a[1] << " "<< lenght << endl;

        }

    }
    
    return 0;
} 

