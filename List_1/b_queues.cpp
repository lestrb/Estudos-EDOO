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

        virtual void inserirComeco(const E& item) = 0; // Insere um elemento no começo da lista

        virtual void inserirFim(const E& item) = 0; // Insere um elemento no final da lista

        virtual E remover(const E& item) = 0; // Remove um elemento da lista e retorna o elemento removido

        // Navegação do cursor
        // virtual void moverComeco() = 0;
        // virtual void moverFim() = 0;
        virtual void anterior() = 0;
        virtual void proximo() = 0;

        // Informações sobre a lista
        virtual int tamanho() const = 0;
        // virtual int posAtual() const = 0;
        // virtual void moverParaPos(int pos) = 0;
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

        // Método pra inicializar a lista (usado no construtor e no limpar)
        void init() {
            cabeca = new No(E(), nullptr); // Cria o nó sentinela (dummy). Ele não guarda dado útil.
            cauda = cabeca;  // No início, cabeça e cauda são o mesmo
            atual = cabeca; // Cursor também
            tamanhoLista = 0;
        }

        // Método auxiliar para deletar tudo (sem deletar a cabeça, usado no limpar)
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


    
};