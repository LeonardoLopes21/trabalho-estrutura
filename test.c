#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

// Define the structure for a binary tree node
struct Node {
    char nome[20];
    float preco;
    char categoria[20];
    int quantidadeEstoque;
    struct Node* left;
    struct Node* right;
};

// Function to create a new binary tree node
struct Node* createNode(char nome[20], float preco, char categoria[20], int quantstoque) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->nome, nome); 
    newNode->preco = preco;
    strcpy(newNode->categoria, categoria);
    newNode->quantidadeEstoque = quantstoque;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


struct Node* insert(struct Node* root, char *data, float preco, char *cat, int quantstoq) {
    if (root == NULL) {
        return createNode(data, preco, cat, quantstoq);
    }

    if (0 > strcmp(data, root->nome)) {
        root->left = insert(root->left, data, preco, cat, quantstoq);
    } else if (0 < strcmp(data, root->nome)) {
        root->right = insert(root->right, data, preco, cat, quantstoq);
    }

    return root;
}

// Function to perform an in-order traversal of the binary tree
void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("==================\n");
        printf("%s \n", root->nome);
        printf("%s \n", root->categoria);
        printf("%.2f \n", root->preco);
        printf("%d \n", root->quantidadeEstoque);
        inOrderTraversal(root->right);
    }
}

void delete(struct Node* root){

}

void finder(struct Node* root, char *targetNome) {
    if (root == NULL || strcmp(root->nome, targetNome) == 0) {
        printf("==================\n");
        printf("%s \n", root->nome);
        printf("%s \n", root->categoria);
        printf("%.2f \n", root->preco);
        printf("%d \n", root->quantidadeEstoque);
        printf("==================\n");
        return;
    }

    if (strcmp(targetNome, root->nome) < 0) {
        return finder(root->left, targetNome);
    } else {
        return finder(root->right, targetNome);
    }
}



int main() {
    struct Node* root = NULL;

    // Insert some nodes into the binary tree
    root = insert(root, "Omo", 2.99, "Higiene", 20);
    insert(root, "Dove", 7.99, "Higiene", 20);
    insert(root, "Frango", 10.99, "Comida", 10);
    insert(root, "Asa", 4.99, "Comida", 50);
    insert(root, "Boi", 100.00, "Comida", 10);

 
    // insert(root, 40);
    // insert(root, 70);
    // insert(root, 60);
    // insert(root, 80);
    // insert(root, 45);

    // Perform an in-order traversal to print the elements in sorted order
    // printf("In-order traversal: ");
    // inOrderTraversal(root);
    // printf("\n");
    finder(root, "Frango");

    return 0;
}
