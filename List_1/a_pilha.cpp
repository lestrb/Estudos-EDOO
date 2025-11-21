#include <iostream>
#include <string>
#include <cassert> // Pra usar o assert()
using namespace std;

template <typename E> class Pilha{
private:
    // Evita copia acidental
    void operator=(const Pilha&) {}
    Pilha(const Pilha&) {}         

public:
    Pilha() {} // Construtor
    virtual ~Pilha() {} // Destrutor virtual

    // Reinicializa a pilha
    virtual void limpar() = 0; 

    // Insere um elemento no topo (Push)
    virtual void push(const E& it) = 0; 

    // Remove e retorna o elemento do topo (Pop)
    virtual E pop() = 0; 

    // Retorna uma copia do elemento do topo sem remover (Peek/Top)
    virtual const E& verTopo() const = 0; 

    // Retorna o numero de elementos na pilha
    virtual int tamanho() const = 0; 
};

template <typename E> class PilhaArray : public Pilha<E>{
private:
    int tamMax;  // Tamanho maximo do array
    int topo;    // Idx pro proximo espaco livre 
    E *Array;    // Array dinamico de elementos

public:
    PilhaArray(int tam = 1000){  // Construtor
        tamMax = tam;
        topo = 0;
        Array = new E[tamMax];
    }

    ~PilhaArray(){  // Destrutor
        delete[] Array;
    }

    // Reinicializa a pilha
    void limpar() { 
        topo = 0; 
    }

    // Inserir
    void push(const E& it) {
        assert(topo != tamMax);  // Verifica se a pilha encheu
        Array[topo++] = it;      // Coloca o elemento e so depois incrementa topo
    }

    // Remover
    E pop() {
        assert(topo != 0);       // Verifica se a pilha ta vazia
        return Array[--topo];    // Decrementa topo e so depois retorna o elemento
    }

    const E& verTopo() const {
        assert(topo != 0);      // Verifica se a pilha ta vazia
        return Array[topo-1];   // Retorna o elemento do topo
    }

    int tamanho() const {       // Retorna o tamanho da pilha  
        return topo; 
    }
};

int main(){
    int qtd;
    cin >> qtd;

    for (int i = 0; i < qtd; i++){
        string sequencia;
        cin >> sequencia;

        PilhaArray<char>* pilha = new PilhaArray<char>();
        string seq_balanceada = "YES";
        for (char c : sequencia){
            if (c == '{' || c == '(' || c == '['){  // Push se for abrindo
                pilha->push(c);
            } else if (c == '}'){   // Se for fechando, checa se nao tem nada na pilha ou se o topo eh diferente
                if (pilha->tamanho() == 0 || pilha->verTopo() != '{'){
                    seq_balanceada = "NO";
                    break;
                } else {            // Se o topo for igual, pop nele
                    pilha->pop();
                }
            } else if (c == ')'){
                if (pilha->tamanho() == 0 || pilha->verTopo() != '('){
                    seq_balanceada = "NO";
                    break;
                } else {
                    pilha->pop();
                }
            } else if (c == ']'){
                if (pilha->tamanho() == 0 || pilha->verTopo() != '['){
                    seq_balanceada = "NO";
                    break;
                } else {
                    pilha->pop();
                }
            }
        }
        // Pos loop, checa se algo nao foi fechado (nao ta balanceada)
        if (pilha->tamanho() > 0){
            seq_balanceada = "NO";
        }

        cout << seq_balanceada << endl;
        delete pilha;
    }
    return 0;
}