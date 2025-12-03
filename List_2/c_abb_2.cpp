#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ArvoreBinariaLegal {
private:
    string travessiaPreOrdem;
    int indiceAtual;

    int calcularProfundidade() {
        // Le ate o fim da string
        if (indiceAtual >= travessiaPreOrdem.length()) {
            return 0;
        }

        // Obtem o caractere e incrementa indice
        char item = travessiaPreOrdem[indiceAtual++];

        if (item == 'l') {
            return 0;  // Se eh folha, retorna 0 
        } else {
            // Se no, calcula recursivamente os filhos. Pre-ordem calcula logo os da esquerda
            int profundidadeEsquerda = calcularProfundidade();

            // A segunda chamada resolve toda a subarvore direita
            int profundidadeDireita = calcularProfundidade();

            // A profundidade do no eh 1 + a maior profundidade entre seus filhos
            return (1 + max(profundidadeEsquerda, profundidadeDireita));
        }
    }

public:
    // Inicializa a arvore com a string de travessia do input
    ArvoreBinariaLegal(string s) {
        travessiaPreOrdem = s;
        indiceAtual = 0;
    }

    // Reseta o indice e inicia o calculo
    int obterProfundidade() {
        indiceAtual = 0;         
        return calcularProfundidade();
    }
};

int main() {
    int casosTeste;
    cin >> casosTeste;

    while (casosTeste--) {
        string entrada;
        cin >> entrada;

        // Instancia objeto
        ArvoreBinariaLegal arvore(entrada);

        // Printa profundidade
        cout << arvore.obterProfundidade() << endl;
    }
    return 0;
}