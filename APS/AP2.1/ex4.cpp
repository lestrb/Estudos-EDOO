#include <iostream>
#include <cstdlib> // rand(), srand()
#include <ctime>
using namespace std;

int main(){
    time_t seconds;
    time(&seconds);           // obtém o tempo atual em segundos desde 01/01/1970
    srand(unsigned(seconds)); // inicializa o gerador de números aleatórios, usando o tempo atual como semente
    rand();                   // gera o primeiro número, para que seja usado somente o segundo
    char play_again = '1';

    while(play_again == '1'){
        int number = rand() % 15 + 1;
        int guess;
        bool got_it_right = false;
        int counter = 0;

        while (!got_it_right && counter <= 3){    // !got_it_right ~ got_it_right == false
            if (counter == 3){
                cout << "You are out of tries. The number was " << number << "." << endl;
            }
            else {
                cout << "Guess a number (1-15): ";
                cin >> guess;
                while (guess < 1 || guess > 15){
                    cout << "Ooops! Guess out of range... Try again.\nGuess a number (1-15): ";
                    cin >> guess;
                }

                if (guess == number){
                    got_it_right = true;
                    cout << "Congrats! The number really was " << number << "." << endl;
                } 
                else if (guess < number and counter < 3){
                    if (counter == 2){
                        cout << "Too low! :(" << endl;
                    } else{
                        cout << "Too low! Try again" << endl;
                    }
                }
                else if (guess > number and counter < 3){
                    if (counter == 2){
                        cout << "Too high! :(" << endl;
                    } else{
                        cout << "Too high! Try again" << endl;
                    }
                }
            }
            ++counter;          // ~ counter = counter + 1 ~ counter += 1
        }
        cin.clear();            // limpa possíveis flags de erros de entrada
        cin.ignore(100, '\n');  // descarta caracteres que sobraram no buffer, até 100 ou até '\n'

        cout << "Do you want to play again?\nPress <1> for yes and <2> for no!" << endl;
        cin >> play_again;
    }
    cout << "Bye bye" << endl;
    return 0;
}