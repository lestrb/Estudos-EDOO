#include <iostream> // cin, cout and endl
#include <cmath>    // sqrt
#include <iomanip>  // setprecision and fixed
#include <fstream>  // ifstream and ofstream
using namespace std;

bool quadEquation(double a, double b, double c, double *p1, double *p2){
    double delta;
    delta = b*b - 4*a*c;

    if (delta < 0) return false;                     // if there's no real solution or the function isn't quadratic 
    if (a == 0) return false;                        // not a quadratic equation
    
    if (delta == 0){                                 // if there's only 1 real solution
        *p1 = *p2 = -b / (2*a);
    } 
    else{                                            // if there's 2 real solutions
        *p1 = (-b + sqrt(delta)) / (2*a);
        *p2 = (-b - sqrt(delta)) / (2*a);
    }
    return true;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin || !fout) {
        cerr << "Error opening file." << endl;      // error message if file can't be opened or created/written (cerr is like cout but for error messages)
        return 1;                                   // return a non-zero value to indicate error (usually 1)
    }

    // if I wanted to use cin and cout with files (instead of fin and fout):
    // cin.rdbuf(fin.rdbuf());
    // cout.rdbuf(fout.rdbuf());

    double a, b, c;
    int qt_inputs;
    fin >> qt_inputs;

    fout << fixed << setprecision(1);                // set output format to 1 decimal place always
    for (int i = 0; i < qt_inputs; ++i) {            // read 3 numbers from input
        fin >> a >> b >> c;                          // presuming a, b and c are valid real numbers and are all written in the right format

        double x1, x2;
        double *pointer1 = &x1, *pointer2 = &x2;     // both created pointing to objects

        if (!quadEquation(a, b, c, pointer1, pointer2)) {
            fout << "none" << endl;                  // no real solution available
        } else{
            fout << *pointer1 << " " << *pointer2 << endl;     // prints real solutions
        }
    }

    fin.close();
    fout.close();
    return 0;
}