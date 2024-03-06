#include <iostream>
using namespace std;

// Definição da estrutura para um nó da árvore
struct Node {
    int value;
    Node* left;
    Node* right;
};

// Função para criar um novo nó com um valor específico
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Função para inserir um novo valor na árvore de busca binária
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        // Se a árvore está vazia, o novo nó se torna a raiz
        return createNode(value);
    }

    if (value < root->value) {
        // Insere no lado esquerdo se o valor for menor que o valor da raiz
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        // Insere no lado direito se o valor for maior que o valor da raiz
        root->right = insert(root->right, value);
    }

    return root;
}

// Função para realizar a travessia in-order da árvore e imprimir seus valores
void inOrder(Node* root) {
    if (root != nullptr) {
        inOrder(root->left);   // Visita a subárvore esquerda
        cout << root->value << " ";  // Imprime o valor do nó
        inOrder(root->right);  // Visita a subárvore direita
    }
}

// Função para deletar (liberar) todos os nós da árvore, evitando vazamentos de memória
void deleteTree(Node* root) {
    if (root != nullptr) {
        deleteTree(root->left);   // Deleta a subárvore esquerda
        deleteTree(root->right);  // Deleta a subárvore direita
        delete root;              // Deleta o nó atual
    }
}

int main() {
    Node* root = nullptr;  // Cria uma árvore vazia

    // Insere valores na árvore de busca binária
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    // Realiza a travessia in-order e imprime a árvore
    cout << "A travessia in-order da árvore de busca binária é: ";
    inOrder(root);
    cout << endl;

    // Limpa a memória alocada para a árvore antes de terminar o programa
    deleteTree(root);

    return 0;
}
