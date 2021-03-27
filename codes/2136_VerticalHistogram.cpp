#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

using namespace std;

int main()
{
  int i,j;
  char a[4][72];

  for(i=0;i<4;i++){
    gets(a[i]);
  }

  int b[26];
  for(i=0;i<26;i++) {
    b[i]=0;
  }
  for(i=0;i<4;i++) {
    for(j=0;j<strlen(a[i]);j++) {
        b[int(a[i][j])-65]++;
    }
  }


  int m=0;
  for(i=0;i<26;i++) {
    if(m<b[i]) {
        m=b[i];
    }
  }


  for(i=m;i>0;i--)
  {
    for(j=0;j<25;j++)
    {
      if(b[j]>=i)
        cout<<'*'<<" ";
      else
        cout<<"  ";
    }


    if(b[25]>=i)
      cout<<'*';
    else
      cout<<" ";

    cout<<endl;
  }


  for(i=65;i<90;i++)
    cout<<char(i)<<" ";

  cout<<'Z'<<endl;

  return 0;
}
