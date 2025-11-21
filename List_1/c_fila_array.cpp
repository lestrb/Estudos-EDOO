#include <iostream>
#include <string>
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
            return fArray[frente];
        }

        int tamanho() const override {
            return ((tras + tamMax) - frente + 1) % tamMax; // Calculo pro array circular
        }
};

int main(){
    int qtd_testes, tamanho_balsa, qtd_carros, tamanho_carro, qtd_atravessadas, preenchimento_balsa;
    string direcao_carro, lado_balsa;
    bool tem_carro;

    cin >> qtd_testes;
    for (int i = 0; i < qtd_testes; i++){    // Laço pras quantidades de casos
        cin >> tamanho_balsa >> qtd_carros;
        tamanho_balsa = tamanho_balsa * 100; // Transforma em centimetros

        Fila<int>* esquerda = new Fila_Array<int>(qtd_carros);         
        Fila<int>* direita = new Fila_Array<int>(qtd_carros); 

        for (int j = 0; j < qtd_carros; j++){
            cin >> tamanho_carro >> direcao_carro;
            if (direcao_carro == "left") {
                esquerda->enfileirar(tamanho_carro);
            } else {
                direita->enfileirar(tamanho_carro);
            }
        }

        preenchimento_balsa = 0;
        lado_balsa = "left"; // Balsa sempre começa na esquerda
        qtd_atravessadas = 0;
        while (esquerda->tamanho() > 0 || direita->tamanho() > 0){ // Enquanto houver carros em qualquer fila
            tem_carro = false;
            if (lado_balsa == "left"){ // Se tiver do lado esquerdo
                while (esquerda->tamanho() > 0 && (preenchimento_balsa + esquerda->valorAtual() <= tamanho_balsa)){ // Se ainda tiver carro e couber na balsa
                    preenchimento_balsa += esquerda->valorAtual();
                    esquerda->desenfileirar();
                    tem_carro = true;
                }
                if (tem_carro == true || direita->tamanho() > 0) { // Se tem algum carro pra atravessar ou se tiver carro do outro lado
                    qtd_atravessadas++;
                    lado_balsa = "right";
                    preenchimento_balsa = 0; // Descarrega tudo ao chegar no outro lado
                }
            } else { // Se tiver do lado direito
                while (direita->tamanho() > 0 && (preenchimento_balsa + direita->valorAtual() <= tamanho_balsa)){ // Se ainda tiver carro e couber na balsa
                    preenchimento_balsa += direita->valorAtual();
                    direita->desenfileirar();
                    tem_carro = true;
                }
                if (tem_carro == true || esquerda->tamanho() > 0) { // Se tem algum carro pra atravessar ou se tiver carro do outro lado
                    qtd_atravessadas++;
                    lado_balsa = "left";
                    preenchimento_balsa = 0; // Descarrega tudo ao chegar no outro lado
                }
            }
        }
        cout << qtd_atravessadas << endl; // Printa quantidade desse caso
        delete esquerda;
        delete direita;
    }
    return 0;
}