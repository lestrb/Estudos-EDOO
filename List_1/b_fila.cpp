#include <iostream>
using namespace std;

// Classe abstrata para lista
template <typename E> // Cria um molde, dentro dos <> sao os parametros 
                      // o E significa que eh um tipo generico (pode ser int, float, string, ou uma classe)
class Lista{
    private: 
        // Evita copia acidental
        void operator=(const Lista&) {} // Operador de atribuicao
        Lista(const Lista&) {}          // Construtor de copia

    public:
        Lista() {} // Construtor padrao
        virtual ~Lista() {} // Destrutor virtual padrao

        // Metodos virtuais puros
        virtual void limpar() = 0; // Limpa a lista

        virtual void inserirFim(const E& item) = 0; // Insere um elemento no final da lista

        virtual E remover(const E& item) = 0; // Remove um elemento da lista e retorna o elemento removido

        virtual void proximo() = 0; // Navegacao do cursor para o proximo elemento

        virtual int tamanho() const = 0;

        virtual const E& pegarValor() const = 0; // Retorna valor atual do cursor
};

template <typename E> // Implementacao lista ligada, herdando da classe Lista
class ListaLigada : public Lista<E> {
    private:
        // Define o no -> struct pq todos os elementos sao publicos para a classe ListaLigada, mas sao encapsulados para o mundo externo
        struct No{
            E elemento;  // Dado armazenado no no
            No* proximo; // Ponteiro para o proximo no

            No(const E& elem, No* prox = nullptr) : elemento(elem), proximo(prox) {} // Construtor do no
        };
        
        No* cabeca; // Ponteiro para o primeiro no da lista
        No* cauda;  // Ponteiro para o ultimo no da lista
        No* atual;  // Ponteiro para o no atual (cursor)
        int tamanhoLista; // Tamanho da lista

        // Metodo pra inicializar a lista
        void init() {
            cabeca = new No(E(), nullptr); // Cria o no sentinela/dummy
            cauda = cabeca = atual;  // No inicio, cabeca, cauda e cursor sao o mesmo
            tamanhoLista = 0;
        }

        // Metodo auxiliar para deletar tudo (menos a cabeca)
        void removerTodos() {
            while(cabeca->proximo != nullptr) {
                atual = cabeca->proximo;          // Pega o primeiro 
                cabeca->proximo = atual->proximo; // Pula ele
                delete atual;                     // Deleta
            }
            atual = cauda = cabeca; // Reseta ponteiros
            tamanhoLista = 0;
        }

        public:
        ListaLigada() { // Construtor
            init();
        }

        ~ListaLigada() { // Destrutor
            limpar();
            delete cabeca;
        }

        // Implementacao dos metodos virtuais puros da classe base
        void limpar() override {
            removerTodos();
        }

        void inserirFim(const E& item) override {
            cauda->proximo = new No(item, nullptr); // No apontando para NULL
            cauda = cauda->proximo; // Atualiza o ponteiro de cauda para ser esse novo no

            if (tamanhoLista == 0) {
                atual = cauda; // Se for o primeiro elemento, atual aponta pra ele
            }   
            tamanhoLista++;
        }

        E remover(const E& item) override {
            No* temp = cabeca; // Ponteiro temporario recebe a cabeca
            
            while (temp->proximo != nullptr) {
                if (temp->proximo->elemento == item) {
                    No* paraDeletar = temp->proximo; // Elemento a remover e temp->proximo
                    E valorRetorno = paraDeletar->elemento;

                    temp->proximo = paraDeletar->proximo; // Pula o no que sera deletado

                    if (paraDeletar == cauda) { // Se for o ultimo, atualiza a cauda
                        cauda = temp;
                    }
                    
                    if (atual == paraDeletar) { // Se for o atual, move o atual para o no anterior
                        atual = cabeca; 
                    }

                    delete paraDeletar;
                    tamanhoLista--;
                    return valorRetorno;
                }
                temp = temp->proximo;
            }
            return E(); // Retorna valor padrao se nao encontrar
        }

        void proximo() override {
            if (tamanhoLista == 0) return;   // Se a lista tiver vazia, nao faz nada
            if (atual->proximo != nullptr) { // Se nao tiver no final, move cursor
                atual = atual->proximo;
            } else { // Se tiver no final, volta pro primiero elemento real
                atual = cabeca->proximo;
            }
        }

        int tamanho() const override {
            return tamanhoLista;
        }

        const E& pegarValor() const override {
            if (tamanhoLista == 0) {
                 return cabeca->elemento; // Retorna valor padrao se a lista tiver vazia
            }
            if (atual == cabeca) { // Se a lista tem itens mas o cursor esta no dummy, retorna o 1º real
                return cabeca->proximo->elemento;
            }
            return atual->elemento;
        };
};

int main(){
    int quantidade_pessoas;
    int tempo_pessoas;

    // Ponteiros do tipo Lista (pai), instanciando a classe ListaLigada
    Lista<int>* fila_original = new ListaLigada<int>();
    Lista<int>* fila_ordenada = new ListaLigada<int>();

    cin >> quantidade_pessoas; // Recebe a quantidade de pessoas na fila

    for (int i = 0; i < quantidade_pessoas; i++){ // Recebe tempo de cada pessoa e coloca na lista ligada
        cin >> tempo_pessoas;
        fila_original->inserirFim(tempo_pessoas);
    };

    // Fila em ordem crescente (pra ter o minimo de pessoas desapontadas)
    while (fila_original->tamanho() > 0){
        int menor_tempo = fila_original->pegarValor();
        fila_original->proximo();

        for (int i = 0; i < fila_original->tamanho(); i++){
            if (fila_original->pegarValor() < menor_tempo){
                menor_tempo = fila_original->pegarValor();
            };
            fila_original->proximo();
        };

        fila_ordenada->inserirFim(menor_tempo);
        fila_original->remover(menor_tempo);
    };

    // Calcula quantas pessoas nao ficaram desapontadas 
    long long soma_tempos = fila_ordenada->pegarValor();
    int nao_desapontados = 1;
    for (int i = 1; i < quantidade_pessoas; i++){
        fila_ordenada->proximo();
        if (soma_tempos <= fila_ordenada->pegarValor()){
            nao_desapontados++;
        };
        soma_tempos += fila_ordenada->pegarValor();
    };

    cout << nao_desapontados << endl;

    delete fila_original;
    delete fila_ordenada;
    return 0;
};