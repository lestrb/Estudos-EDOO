// a. Version using incorrect logic:
// void swap(float *p1, float *p2)
// {
// float *temp; // Temporary variable
// temp = p1;
// p1 = p2;
// p2 = temp;
// }

// Answer: when swap(&x, &y) is called, the pointers p1 and p2 are local copies of &x and &y.
// Swapping p1 and p2 only swaps these local copies, not the values pointed to x and y in the caller.
// (From now on they are pointing to the changed values, but x and y didn't change).
// To swap the actual values pointed to by x and y, you should dereference the pointers or use references (I chose references),
// because references allow the function to modify the original variables passed as arguments

// b. Using references:
#include <iostream>
using namespace std;

void swap(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}

// Testing 
int main() {
    float x = 15.89, y = 2.5;
    cout << "Before swap: x = " << x << ", y = " << y << endl;
    swap(x, y);
    cout << "After swap: x = " << x << ", y = " << y << endl;
    return 0;
}

