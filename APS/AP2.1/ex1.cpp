#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int number1 = 4, square_root1;    // uso de diferentes tipos para entendimento, já que as raízes são conhecidas
    float number2 = 12.25, square_root2;  
    float number3 = 0.0121, square_root3;
    double number_keyboard, square_root_keyboard;

    square_root1 = sqrt(number1);
    square_root2 = sqrt(number2);
    square_root3 = sqrt(number3);

    cout << "\nNumber\tSquare Root\n" << endl;
    cout << number1 << "\t" << square_root1 << endl;
    cout << number2 << "\t" << square_root2 << endl;
    cout << number3 << "\t" << square_root3 << endl << endl;

    cin >> number_keyboard;
    square_root_keyboard = sqrt(number_keyboard);
    cout << "The square root of " << number_keyboard << " is " << square_root_keyboard << endl;

    return 0;
}