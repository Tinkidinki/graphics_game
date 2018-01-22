#include <iostream> 
#include "test1.h"
using namespace std;

int main(){
    Lala* obj2 = new Lala();
    cout<< obj2->var1 <<endl;

    delete obj2;
    cout<< obj2->var1 <<endl;

}