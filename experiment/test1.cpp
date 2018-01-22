#include <iostream> 
#include <vector>
#include "test1.h"
using namespace std;

int main(){
    vector<Lala> list(10);
    Lala* obj2 = new Lala();
    cout<< obj2->var1 <<endl;

    delete obj2;
    cout<< obj2->var1 <<endl;

    for(int i=0;i<10;i++){
        cout << list[i].var1 <<endl;
    }

}

