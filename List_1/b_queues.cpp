#include <iostream>
#include <string>
using namespace std;

// Classe abstrata para lista
template <typename E> // Cria um molde, dentro dos <> são os parâmetros 
                      // o E sifnifica que é um tipo genérico (pode ser int, float, string, ou uma classe)
class Lista{
    private: 
        // Evita cópia acidental
        void operator=(const Lista&) {} // Operador de atribuição
        Lista(const Lista&) {}          // Construtor de cópia

    public:
        Lista() {} // Construtor virtual padrão
        virtual ~Lista() {} // Destrutor virtual padrão

        // Metodos virtuais puros
        virtual void limpar() = 0; // Limpa a lista

        //virtual void inserirComeco(const E& item) = 0; // Insere um elemento no começo da lista

        virtual void inserirFim(const E& item) = 0; // Insere um elemento no final da lista

        virtual E remover(const E& item) = 0; // Remove um elemento da lista e retorna o elemento removido

        // Navegação do cursor
        virtual void proximo() = 0;

        // Informações sobre a lista
        virtual int tamanho() const = 0;
        virtual const E& pegarValor() const = 0;
};

// Implementação lista ligada, herdando da classe Lista
template <typename E>
class ListaLigada : public Lista<E> {
    private:
        // Define o nó - struct pq todos os elementos são públicos para a classe ListaLigada, mas são encapsulados para o mundo externo
        struct No{
            E elemento;  // Dado armazenado no nó
            No* proximo; // Ponteiro para o próximo nó

            // Construtor do nó
            No(const E& elem, No* prox = nullptr) : elemento(elem), proximo(prox) {}
        };
        
        // Atributos de controle da lista
        No* cabeca; // Ponteiro para o primeiro nó da lista
        No* cauda;  // Ponteiro para o último nó da lista
        No* atual;  // Ponteiro para o nó atual (cursor)
        int tamanhoLista; // Tamanho da lista

        // Método pra inicializar a lista
        void init() {
            cabeca = new No(E(), nullptr); // Cria o nó sentinela/dummy
            cauda = cabeca;  // No início, cabeça e cauda são o mesmo
            atual = cabeca; // Cursor também
            tamanhoLista = 0;
        }

        // Método auxiliar para deletar tudo (sem deletar a cabeça)
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
        // Construtor
        ListaLigada() {
            init();
        }

        // Destrutor
        ~ListaLigada() {
            limpar();
            delete cabeca;
        }

        // Implementação dos métodos virtuais puros da classe base
        void limpar() override {
            removerTodos();
        }

        // void inserirComeco(const E& item) override {
        //     cabeca->proximo = new No(item, cabeca->proximo); // Aponta pro primeiro nó sem ser o dummy

        //     if (cauda == cabeca) {
        //         cauda = cabeca->proximo;
        //         atual = cabeca->proximo; // Se for o primeiro elemento, atual aponta pra ele
        //     }
        //     tamanhoLista++;
        // }

        void inserirFim(const E& item) override {
            cauda->proximo = new No(item, nullptr); // Nó apontando para NULL
            cauda = cauda->proximo; // Atualiza o ponteiro de cauda para ser esse novo nó

            if (tamanhoLista == 0) {
                atual = cauda; // Se for o primeiro elemento, atual aponta pra ele
            }   
            tamanhoLista++;
        }

        E remover(const E& item) override {
            No* temp = cabeca; // Ponteiro temporário recebe a cabeça
            
            while (temp->proximo != nullptr) {
                if (temp->proximo->elemento == item) {
                    No* paraDeletar = temp->proximo; // Elemento a remover é temp->proximo
                    E valorRetorno = paraDeletar->elemento;

                    temp->proximo = paraDeletar->proximo; // Pula o nó que será deletado

                    if (paraDeletar == cauda) { // Se for o último, atualiza a cauda
                        cauda = temp;
                    }
                    
                    if (atual == paraDeletar) { // Se for o atual, move o atual para o nó anterior
                        atual = cabeca; 
                    }

                    delete paraDeletar;
                    tamanhoLista--;
                    return valorRetorno;
                }
                temp = temp->proximo;
            }
            return E(); // Retorna valor padrão se não encontrar
        }

        void proximo() override {
            if (tamanhoLista == 0) return;   // Se a lista estiver vazia, não faz nada
            if (atual->proximo != nullptr) { // Se não estiver no final, move cursor
                atual = atual->proximo;
            } else { // Se estiver no final, volta pro primieor elemento real
                atual = cabeca->proximo;
            }
        }

        int tamanho() const override {
            return tamanhoLista;
        }

        const E& pegarValor() const override {
            if (tamanhoLista == 0) {
                 return cabeca->elemento; // Retorna valor padrão se a lista estiver vazia
            }
            if (atual == cabeca) { // Se a lista tem itens mas o cursor está no dummy, retorna o 1º real
                return cabeca->proximo->elemento;
            }
            return atual->elemento;
        };
};

// RESOLUÇÃO DA QUESTÃO
int main(){
    int quantidade_pessoas;
    int tempo_pessoas;
    ListaLigada<int> fila_original;
    ListaLigada<int> fila_ordenada;

    cin >> quantidade_pessoas; // Recebe a quantidade de pessoas na fila

    for (int i = 0; i < quantidade_pessoas; i++){ // Recebe tempo de cada pessoa e coloca na lista ligada
        cin >> tempo_pessoas;
        fila_original.inserirFim(tempo_pessoas);
    };

    // Ordena fila pra ter o mínimo de pessoas desapontadas
    while (fila_original.tamanho() > 0){
        int menor_tempo = fila_original.pegarValor();
        fila_original.proximo();

        for (int i = 0; i < fila_original.tamanho(); i++){
            if (fila_original.pegarValor() < menor_tempo){
                menor_tempo = fila_original.pegarValor();
            };
            fila_original.proximo();
        };

        fila_ordenada.inserirFim(menor_tempo);
        fila_original.remover(menor_tempo);
    };

    // Calcula quantas pessoas não ficaram desapontadas 
    int soma_tempos = fila_ordenada.pegarValor();
    int nao_desapontados = 1;
    for (int i = 1; i < quantidade_pessoas; i++){
        fila_ordenada.proximo();
        if (soma_tempos <= fila_ordenada.pegarValor()){
            nao_desapontados++;
        };
        soma_tempos += fila_ordenada.pegarValor();
    };

    cout << nao_desapontados << endl;
};