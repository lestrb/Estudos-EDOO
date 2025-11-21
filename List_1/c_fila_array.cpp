#include <iostream>
using namespace std;

// Classe abstrata para Fila
template <typename E>
class Fila{
    private: 
        // Evita copia acidental
        void operator=(const Fila&) {} // Operador de atribuicao
        Lista(const Fila&) {}          // Construtor de copia

    public:
        Fila() {} // Construtor padrao
        virtual ~Fila() {} // Destrutor virtual padrao

        // Metodos virtuais puros
        virtual void limpar() = 0; // Limpa a lista
        virtual void inserirFim(const E& item) = 0; // Insere um elemento no final da lista
        virtual E remover(const E& item) = 0; // Remove um elemento da lista e retorna o elemento removido
        virtual void proximo() = 0; // Navegacao do cursor para o proximo elemento
        virtual int tamanho() const = 0;
        virtual const E& pegarValor() const = 0; // Retorna valor atual do cursor
};

template <typename E> // Implementacao array, herdando da classe Lista
class Fila_Array : public Lista<E> {
    private:
        

    public:
};