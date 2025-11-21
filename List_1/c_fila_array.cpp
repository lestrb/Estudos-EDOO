#include <iostream>
using namespace std;

// Classe abstrata para Fila
template <typename E>
class Fila{
    private: 
        // Evita copia acidental
        void operator=(const Fila&) {} // Operador de atribuicao
        Fila(const Fila&) {}           // Construtor de copia

    public:
        Fila() {} // Construtor padrao
        virtual ~Fila() {} // Destrutor virtual padrao

        // Metodos virtuais puros
        virtual void limpar() = 0; // Limpa a fila
        virtual void enfileirar(const E& item) = 0; // Insere um elemento (final da fila) - enqueue
        virtual E desenfileirar() = 0; // Remove o primeiro elemento da fila - dequeue
        virtual const E& valorAtual() const = 0; // Retorna cabeça da fila
        virtual int tamanho() const = 0;
};

template <typename E> // Implementacao array circular, herdando da classe Fila
class Fila_Array : public Fila<E> {
    private:
        int tamMax;     // Tamanho maximo do array
        int frente;     // Indice do primeiro elemento (front)
        int tras;       // Indice do ultimo elemento (rear)
        E *fArray;      // Array para armazenar os elementos

    public:
        Fila_Array(int tamanho = 10){ // Construtor
            tamMax = tamanho + 1;     // Deixa uma posição vazia pra checagem de tamanho do array circular
            tras = 0;
            frente = 1;
            fArray = new E[tamMax];
        }

        ~Fila_Array() { // Destrutor
            delete[] fArray; 
        }

        void limpar() override { // Reinicializa os índices
            tras = 0;
            frente = 1;
        }

        void enfileirar(const E& item) override {       // Insere no fim
            if (((tras + 2) % tamMax) == frente) {      // Verifica se tá cheia
                throw runtime_error("A fila esta cheia");
            }
            // Incremento circular
            tras = (tras + 1) % tamMax; 
            fArray[tras] = item;
        }

        E desenfileirar() override {      // Tira do começo
            if (tamanho() == 0) {
                throw runtime_error("A fila esta vazia");
            }
            
            E item = fArray[frente];
            frente = (frente + 1) % tamMax; // Incremento circular
            return item;
        }

        const E& valorAtual() const override {  // Retorna valor da cabeca/frente
            if (tamanho() == 0) {
                throw runtime_error("A fila esta vazia");
            }
            return listArray[frente];
        }

        int tamanho() const override {
            return ((tras + tamMax) - frente + 1) % tamMax; // Calculo pro array circular
        }
};

int main(){
    int qtd_testes, tamanho_balsa, qtd_carros;

    for (int i = 0; i < qtd_testes; i++){
        



    }



}