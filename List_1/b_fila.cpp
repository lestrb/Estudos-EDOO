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
        virtual void ordenar() = 0;  // Merge sort
};

template <typename E> // Implementacao lista ligada, herdando da classe Lista
class ListaLigada : public Lista<E> {
    private:
        struct No{       // Define o no -> struct pq todos os elementos sao publicos para a classe ListaLigada, mas sao encapsulados para o mundo externo
            E elemento;  // Dado armazenado no no
            No* proximo; // Ponteiro para o proximo no

            No(const E& elem, No* prox = nullptr) : elemento(elem), proximo(prox) {} // Construtor do no
        };
        
        No* cabeca; // Ponteiro para o primeiro no da lista
        No* cauda;  // Ponteiro para o ultimo no da lista
        No* atual;  // Ponteiro para o no atual (cursor)
        int tamanhoLista; // Tamanho da lista

        void init() {        // Metodo pra inicializar a lista
            cabeca = new No(E(), nullptr); // Cria o no sentinela/dummy
            cauda = cabeca;  // No inicio, cabeca, cauda e cursor sao o mesmo
            atual = cabeca;
            tamanhoLista = 0;
        }

        void removerTodos() { // Metodo auxiliar para deletar tudo (menos a cabeca)
            while(cabeca->proximo != nullptr) {
                atual = cabeca->proximo;          // Pega o primeiro 
                cabeca->proximo = atual->proximo; // Pula ele
                delete atual;                     // Deleta
            }
            atual = cauda = cabeca; // Reseta ponteiros
            tamanhoLista = 0;
        }

        // Metodos pro Merge sort
        No* obterMeio(No* inicio) { // Encontra o meio da lista para dividir
            if (inicio == nullptr) return inicio;
            No* devagar = inicio;
            No* rapido = inicio->proximo;

            while (rapido != nullptr && rapido->proximo != nullptr) {
                devagar = devagar->proximo;
                rapido = rapido->proximo->proximo;
            }
            return devagar;
        }

        No* merge(No* lista1, No* lista2) { // Junta duas listas ordenadas mexendo nos ponteiros
            if (lista1 == nullptr) return lista2;
            if (lista2 == nullptr) return lista1;
            
            No* juncao = nullptr;
            
            // Ordena do menor pro maior
            if (lista1->elemento <= lista2->elemento) {
                juncao = lista1;
                juncao->proximo = merge(lista1->proximo, lista2);
            } else {
                juncao = lista2;
                juncao->proximo = merge(lista1, lista2->proximo);
            }
            return juncao;
        }

        No* mergeSort(No* inicio) {
            // Caso base: Lista vazia ou com 1 elemento já está ordenada
            if (inicio == nullptr || inicio->proximo == nullptr) {
                return inicio;
            }

            // Corta a lista ao meio
            No* meio = obterMeio(inicio);
            No* proxMeio = meio->proximo;
            meio->proximo = nullptr; 

            // Faz a recursão para as duas metades
            No* esquerda = mergeSort(inicio);
            No* direita = mergeSort(proxMeio);

            // Combina as metades ordenadas
            return merge(esquerda, direita);
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

                    if (paraDeletar == cauda) cauda = temp; // Se for o ultimo, atualiza a cauda
                    if (atual == paraDeletar) atual = cabeca; // Se for o atual, move o atual para o no anterior

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
            if (tamanhoLista == 0) return cabeca->elemento; // Retorna valor padrao se a lista tiver vazia
            if (atual == cabeca) return cabeca->proximo->elemento; // Se a lista tem itens mas o cursor esta no dummy, retorna o 1º real
            return atual->elemento;
        }

        void ordenar() override {
            if (tamanhoLista <= 1) return; // Se 0 ou 1 elemento, faz nada

            No* primeiroReal = cabeca->proximo; // Pega o primeiro nó real
            cabeca->proximo = mergeSort(primeiroReal); // Chama o Merge Sort e reconecta no dummy

            No* temp = cabeca; // Atualiza a cauda
            while(temp->proximo != nullptr) {
                temp = temp->proximo;
            }
            cauda = temp;

            atual = cabeca->proximo; // Reseta o cursor para o começo
        }
};

int main(){
    ios_base::sync_with_stdio(false); // Faz com que o C++ use seus proprios buffers de I/O, sem sincronizar com o C
    cin.tie(NULL); // Desativa o laço entre cin e cout (não limpa buffer de cout a cada entrada de cin)

    int quantidade_pessoas;
    int tempo_pessoas;

    // Ponteiro do tipo Lista (pai), instanciando a classe ListaLigada
    Lista<int>* fila = new ListaLigada<int>();

    cin >> quantidade_pessoas; // Recebe a quantidade de pessoas na fila

    for (int i = 0; i < quantidade_pessoas; i++){ // Recebe tempo de cada pessoa e coloca na lista ligada
        cin >> tempo_pessoas;
        fila->inserirFim(tempo_pessoas);
    };

    fila->ordenar(); // Ordena a fila pelo tempo de atendimento

    // Calcula quantas pessoas nao ficaram desapontadas 
    long long soma_tempos = fila->pegarValor();
    int nao_desapontados = 1;
    for (int i = 1; i < quantidade_pessoas; i++){
        fila->proximo();
        if (soma_tempos <= fila->pegarValor()){
            nao_desapontados++;
            soma_tempos += fila->pegarValor();  // Só soma o tempo se a pessoa nao ficou desapontada
        };    
    };

    cout << nao_desapontados << endl;

    delete fila;
    return 0;
};