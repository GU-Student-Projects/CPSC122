#include <iostream>
#include <vector>

using namespace  std;

void myRecursiveFunction(int num){
    if (num != 0)
        myRecursiveFunction(num--);
    cout << "Blast off!" << endl;
    return;
}

int main(){

   myRecursiveFunction(10);
    return 0;
}
