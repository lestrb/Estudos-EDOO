#include <iostream>
#include <string>
using namespace std;

// Classe abstrata de Tabela Hash
template <typename E>
class TabelaHash {
    protected: // Classe filha (HashFechado) acessa o array diretamente
        static const int TAMANHO_TABELA = 101;
        string tabela[TAMANHO_TABELA];

    public:
        TabelaHash(){ // Construtor padrao 
            for (int i = 0; i < TAMANHO_TABELA; i++) {
                tabela[i] = "LIVRE"; //Estado inicial
            }
        }
        virtual ~TabelaHash() {} // Destrutor virtual padrao

        virtual void inserir_chave(const string& chave) = 0;
        virtual void deletar_chave(const string& chave) = 0;
        virtual int achar_indice(const string& chave) = 0;
        
        // Impressao do output
        void imprimir_tabela() {
            int contador_elementos = 0;

            // Valido se a string nao for "LIVRE"
            for (int i = 0; i < TAMANHO_TABELA; i++) {
                if (tabela[i] != "LIVRE") {
                    contador_elementos++;
                }
            }
            cout << contador_elementos << endl;

            // Como o loop vai de 0 a 100, elementos ja saem ordenados
            for (int i = 0; i < TAMANHO_TABELA; i++) {
                if (tabela[i] != "LIVRE") {
                    cout << i << ":" << tabela[i] << endl;
                }
            }
        }
};

// Classe filha pra hashing fechado (enderecamento aberto)
template <typename E>
class HashFechado : public TabelaHash<E> {
    public:
        // h(key) = 19 * (ASCII(a1)*1 + ... + ASCII(an)*n)
        int calcular_hash(const string& chave) {
            long long soma = 0;
            for (size_t i = 0; i < chave.length(); i++) {
                soma += (int)chave[i] * (i + 1); // // (i + 1) pq a formula conta posicoes a partir de 1
            }
            long long hash_chave = 19 * soma;
            return hash_chave % 101; // Retorna o modulo
        }

        // Retorna o indice (0-100) se achar, ou -1 se nao achar
        int achar_indice(const string& chave) override {
            int valor_hash = calcular_hash(chave);

            // Tenta ate 20 vezes (j=0 eh primeira tentativa, j=1..19 sao colisoes)
            for (int j = 0; j < 20; j++) {
                int posicao_atual;
                
                if (j == 0) {
                    posicao_atual = valor_hash;
                } else {
                    // Colisao: (Hash(key) + j^2 + 23*j) mod 101
                    posicao_atual = (valor_hash + (j * j) + (23 * j)) % 101;
                }

                // Se "LIVRE", a chave nao ta na tabela
                if (this->tabela[posicao_atual] == "LIVRE") {
                    return -1;
                }
                else if (this->tabela[posicao_atual] == chave) { // Encontrou
                    return posicao_atual;
                }
                
                // Se for outra chave (colisao), continua o loop enquanto nao der 20 vezes
            }
            return -1; // Caso nao encontre apos 20 tentativas
        }

        void inserir_chave(const string& chave) override {
            // Ignora se a chave ja existe na tabela
            if (achar_indice(chave) != -1) return;

            int valor_hash = calcular_hash(chave);

            for (int j = 0; j < 20; j++) {
                int posicao_atual;
                if (j == 0) {
                    posicao_atual = valor_hash; // Primeira tentativa
                } else {
                    posicao_atual = (valor_hash + (j * j) + (23 * j)) % 101; // Colisoes
                }

                // Pode inserir se for "LIVRE"
                if (this->tabela[posicao_atual] == "LIVRE") {
                    this->tabela[posicao_atual] = chave; 
                    return;
                }
            }
            // Se passar de 20 tentativas, desiste
        }

        void deletar_chave(const string& chave) override {
            int indice = achar_indice(chave);
            
            // Se encontrou a chave
            if (indice != -1) {
                // Reseta a posição para "LIVRE"
                this->tabela[indice] = "LIVRE";
            }
        }
};

int main() {
    int qtd_casos_teste;
    
    if (!(cin >> qtd_casos_teste)) return 0; // Lê número de casos de teste. Se falhar a leitura, encerra.

    while (qtd_casos_teste--) {
        int num_operacoes;
        cin >> num_operacoes;

        // Cria uma nova tabela para este caso de teste
        HashFechado<string> hash_problema;

        for (int i = 0; i < num_operacoes; i++) {
            string linha_entrada;
            cin >> linha_entrada;

            // Divide a string "ADD:valor" ou "DEL:valor"
            string comando = linha_entrada.substr(0, 3); // Pega os 3 primeiros chars
            string chave = linha_entrada.substr(4);      // Pega do 4º char até o fim

            if (comando == "ADD") {
                hash_problema.inserir_chave(chave);
            } else if (comando == "DEL") {
                hash_problema.deletar_chave(chave);
            }
        }
        hash_problema.imprimir_tabela();
    }
    return 0;
}