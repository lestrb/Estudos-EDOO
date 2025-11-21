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
    bool preencheu;

    cin >> qtd_testes;
    for (int i = 0; i < qtd_testes; i++){    // Laço pras quantidades de casos
        cin >> tamanho_balsa >> qtd_carros;
        tamanho_balsa = tamanho_balsa * 100; // Transforma em centimetros

        Fila<int>* carros = new Fila_Array<int>(qtd_carros);          // Fila para armazenar os tamanhos dos carros
        Fila<string>* direcoes = new Fila_Array<string>(qtd_carros);  // Fila para armazenar as direcoes dos carros

        for (int j = 0; j < qtd_carros; j++){
            cin >> tamanho_carro >> direcao_carro;
            carros->enfileirar(tamanho_carro);
            direcoes->enfileirar(direcao_carro);
        }

        preenchimento_balsa = 0;
        lado_balsa = "left"; // Balsa sempre começa na esquerda
        qtd_atravessadas = 0;
        while (carros->tamanho() > 0){
            if (lado_balsa == "left"){
                if (direcoes->valorAtual() == "right" && preenchimento_balsa == 0){  // Se o primeiro carro da fila tiver na direita e a balsa vazia, vai pro outro lado
                    qtd_atravessadas++;
                    lado_balsa = "right";
                }
                else if (direcoes->valorAtual() == "right" && preenchimento_balsa > 0){  // Se o primeiro carro da fila tiver na direita e a balsa ja com algum carro, a balsa vai pro outro lado
                    preenchimento_balsa = 0;  // Balsa foi "descarregada" ao ir pro outro lado
                    qtd_atravessadas++;
                    lado_balsa = "right";
                }
                else if (direcoes->valorAtual() == "left" && (carros->valorAtual() + preenchimento_balsa) <= tamanho_balsa){ // Se o carro couber, ele entra na balsa e é removido da fila
                    preenchimento_balsa += carros->valorAtual();                        
                    carros->desenfileirar();
                    direcoes->desenfileirar();

                    if (carros->tamanho() == 0){ // Se não tiver mais carros, a balsa atravessa
                        qtd_atravessadas++;
                    }
                }
                else if (direcoes->valorAtual() == "left" && (carros->valorAtual() + preenchimento_balsa) > tamanho_balsa){ // Se o carro não couber, a balsa preencheu e atravessa
                    preenchimento_balsa = 0;  // Balsa foi "descarregada" ao ir pro outro lado
                    qtd_atravessadas++;
                    lado_balsa = "right";
                }
            } else if (lado_balsa == "right"){
                if (direcoes->valorAtual() == "left" && preenchimento_balsa == 0){  // Se o primeiro carro da fila tiver na direita e a balsa vazia, vai pro outro lado
                    qtd_atravessadas++;
                    lado_balsa = "left";
                }
                else if (direcoes->valorAtual() == "left" && preenchimento_balsa > 0){  // Se o primeiro carro da fila tiver na direita e a balsa ja com algum carro, a balsa vai pro outro lado
                    preenchimento_balsa = 0;  // Balsa foi "descarregada" ao ir pro outro lado
                    qtd_atravessadas++;
                    lado_balsa = "left";
                }
                else if (direcoes->valorAtual() == "right" && (carros->valorAtual() + preenchimento_balsa) <= tamanho_balsa){ // Se o carro couber, ele entra na balsa e é removido da fila
                    preenchimento_balsa += carros->valorAtual();                        
                    carros->desenfileirar();
                    direcoes->desenfileirar();

                    if (carros->tamanho() == 0){ // Se não tiver mais carros, a balsa atravessa
                        qtd_atravessadas++;
                    }
                }
                else if (direcoes->valorAtual() == "right" && (carros->valorAtual() + preenchimento_balsa) > tamanho_balsa){ // Se o carro não couber, a balsa preencheu e atravessa
                    preenchimento_balsa = 0;  // Balsa foi "descarregada" ao ir pro outro lado
                    qtd_atravessadas++;
                    lado_balsa = "left";
                }
            } 
        }
        cout << qtd_atravessadas << endl; // Printa quantidade desse caso
    }
}