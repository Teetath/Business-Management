#include <iostream>
#include<cstdlib>
using namespace std;
#include"NODE.h"
#include"cat_dog.h"
#include"LL.h"
int menu(){
  int i;
  cout << "Type 1 for cat." << endl;
  cout << "Type 2 for dog." << endl;
  cout << "Type 3 for ens this program." << endl;
  cin >> i;
  return i;
} // Finish your menu to choose cat or dog.
int main(int argc, char *argv[])
{  LL A;
   int i=0,size;
   float height;
   NODE *t;

 while((i=menu())!=3){
 /* modified main to either add cat or dog*/

  if(i==1){
    cout << "What size of your cat?" << endl;
    cin >> size;
    t=new cat(i,size);
  } 
  else {
    cout << "What height of your dog?" << endl;
    cin >> height;
    t=new dog(i,height);
  }
    // t=new NODE(atoi(argv[i]));
      A.add_node(t);
}
  
  A.show_all();
  
}
