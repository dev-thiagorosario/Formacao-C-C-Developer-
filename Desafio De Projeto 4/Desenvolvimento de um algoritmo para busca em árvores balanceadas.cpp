#include <iostream>
#include <algorithm>
using namespace std;

class No {
public:
    int chave;
    No* esquerda;
    No* direita;
    int altura;

    No(int chave) : chave(chave), esquerda(nullptr), direita(nullptr), altura(1) {}
};

class AVL {
private:
    No* raiz;

    int altura(No* no) {
        if (no == nullptr) {
            return 0;
        }
        return no->altura;
    }

    int fatorDeBalanceamento(No* no) {
        if (no == nullptr) {
            return 0;
        }
        return altura(no->esquerda) - altura(no->direita);
    }

    No* rotacaoDireita(No* y) {
        No* x = y->esquerda;
        No* T2 = x->direita;

        x->direita = y;
        y->esquerda = T2;

        y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

        return x;
    }

    No* rotacaoEsquerda(No* x) {
        No* y = x->direita;
        No* T2 = y->esquerda;

        y->esquerda = x;
        x->direita = T2;

        x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

        return y;
    }

    No* balancear(No* no) {
        if (no == nullptr) {
            return nullptr;
        }

        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));

        int fator = fatorDeBalanceamento(no);

        if (fator > 1 && fatorDeBalanceamento(no->esquerda) >= 0) {
            return rotacaoDireita(no);
        }

        if (fator > 1 && fatorDeBalanceamento(no->esquerda) < 0) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }

        if (fator < -1 && fatorDeBalanceamento(no->direita) <= 0) {
            return rotacaoEsquerda(no);
        }

        if (fator < -1 && fatorDeBalanceamento(no->direita) > 0) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }

        return no;
    }

    No* inserir(No* no, int chave) {
        if (no == nullptr) {
            return new No(chave);
        }

        if (chave < no->chave) {
            no->esquerda = inserir(no->esquerda, chave);
        } else if (chave > no->chave) {
            no->direita = inserir(no->direita, chave);
        } else {
            return no;
        }

        return balancear(no);
    }

    No* noValorMinimo(No* no) {
        No* atual = no;

        while (atual->esquerda != nullptr) {
            atual = atual->esquerda;
        }

        return atual;
    }

    No* deletarNo(No* no, int chave) {
        if (no == nullptr) {
            return no;
        }

        if (chave < no->chave) {
            no->esquerda = deletarNo(no->esquerda, chave);
        } else if (chave > no->chave) {
            no->direita = deletarNo(no->direita, chave);
        } else {
            if (no->esquerda == nullptr || no->direita == nullptr) {
                No* temp = no->esquerda ? no->esquerda : no->direita;

                if (temp == nullptr) {
                    temp = no;
                    no = nullptr;
                } else {
                    *no = *temp;
                }
                delete temp;
            } else {
                No* temp = noValorMinimo(no->direita);

                no->chave = temp->chave;

                no->direita = deletarNo(no->direita, temp->chave);
            }
        }

        if (no == nullptr) {
            return no;
        }

        return balancear(no);
    }

    void percorrerInOrdem(No* raiz) {
        if (raiz != nullptr) {
            percorrerInOrdem(raiz->esquerda);
            cout << raiz->chave << " ";
            percorrerInOrdem(raiz->direita);
        }
    }

public:
    AVL() : raiz(nullptr) {}

    void inserir(int chave) {
        raiz = inserir(raiz, chave);
    }

    void deletar(int chave) {
        raiz = deletarNo(raiz, chave);
    }

    void percorrerInOrdem() {
        percorrerInOrdem(raiz);
        cout << endl;
    }
};

int main() {
    AVL arvore;

    arvore.inserir(10);
    arvore.inserir(20);
    arvore.inserir(30);
    arvore.inserir(40);
    arvore.inserir(50);
    arvore.inserir(25);

    cout << "Percorrendo a árvore em ordem (após inserções): ";
    arvore.percorrerInOrdem();

    arvore.deletar(20);

    cout << "Percorrendo a árvore em ordem (após a deleção): ";
    arvore.percorrerInOrdem();

    return 0;
}
