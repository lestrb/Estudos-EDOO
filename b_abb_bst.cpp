#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Definicao do No
struct No {
    char dado;       // Letra
    No *esquerda;    // Ponteiro pro filho esquerdo
    No *direita;     // Ponteiro pro filho direito

    // Construtor
    No(char valor) : dado(valor), esquerda(nullptr), direita(nullptr) {}
};

// Classe abstrata pra ABB
class ArvoreBinariaBusca {
public:
    virtual void inserir(char valor) = 0;
    virtual void mostrarPreOrdem() = 0;
    virtual void limpar() = 0;

    virtual ~ArvoreBinariaBusca() {}
};

class Arvore : public ArvoreBinariaBusca {
private:
    No* raiz;

    // Retorna o no atualizado para fazer a ligacao recursiva
    No* inserir(No* noAtual, char valor) {
        // Se no nulo, cria novo
        if (noAtual == nullptr) {
            return new No(valor);
        }

        // Se valor menor que o no atual, vai pra esquerda. Se maior, direita
        if (valor < noAtual->dado) {
            // No pai aponta pro retorno do filho
            noAtual->esquerda = inserir(noAtual->esquerda, valor);
        } 
        else {
            noAtual->direita = inserir(noAtual->direita, valor);
        }

        // Retorna no atual
        return noAtual;
    }

    void preOrdem(No* noAtual) {
        if (noAtual != nullptr) {
            cout << noAtual->dado;       // Visita raiz em questao e printa
            preOrdem(noAtual->esquerda); // Visita Esquerda
            preOrdem(noAtual->direita);  // Visita Direita
        }
    }

    // Funcao auxiliar para liberar memoria (pos-ordem pra deletar)
    void limpar(No* noAtual) {
        if (noAtual != nullptr) {
            limpar(noAtual->esquerda);
            limpar(noAtual->direita);
            delete noAtual;
        }
    }

public:
    Arvore() : raiz(nullptr) {}

    void inserir(char valor) override {
        raiz = inserir(raiz, valor);
    }

    void mostrarPreOrdem() override {
        preOrdem(raiz);
        cout << endl; // Quebra de linha apos terminar a arvore
    }

    void limpar() override {
        limpar(raiz);
        raiz = nullptr;
    }

    ~Arvore() {
        limpar();
    }
};

int main() {
    // Instancia a classe concreta baseada na abstracao
    ArvoreBinariaBusca* arvore = new Arvore();

    vector<string> bufferLinhas; // Lista dinamica de textos
    string linha;

    // Leitura continua da entrada
    while (cin >> linha) {
        // Verifica se bloco acabou ou input foi finalizado
        if (linha == "*" || linha == "$") {
            // Se tem dados no buffer, processa o bloco
            if (!bufferLinhas.empty()) {
                // Le input de tras pra frente (ultima linha tem raiz, penultima filhos da raiz...)
                for (int i = bufferLinhas.size() - 1; i >= 0; i--) {
                    string strAtual = bufferLinhas[i];
                    // Insere cada caractere da linha
                    for (char c : strAtual) {
                        arvore->inserir(c);
                    }
                }

                // Printa sequencia varrendo pre ordem
                arvore->mostrarPreOrdem();
                
                // Limpa pro prox bloco
                arvore->limpar();
                bufferLinhas.clear();
            }

            if (linha == "$") break;
        } 
        else {
            // Se for linha de letras, guarda no buffer
            bufferLinhas.push_back(linha);
        }
    }

    delete arvore;
    return 0;
}