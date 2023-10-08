#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

// Define the structure for a binary tree node
struct Node {
    char nome[20];
    float preco;
    char categoria[20];
    
    struct Node* left;
    struct Node* right;
};

// Function to create a new binary tree node
struct Node* createNode(char nome[20], float preco, char categoria[20]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->nome, nome); 
    newNode->preco = preco;
    strcpy(newNode->categoria, categoria);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}


struct Node* insert(struct Node* root, char *data, float preco, char *cat) {
    if (root == NULL) {
        return createNode(data, preco, cat);
    }

    if (0 > strcmp(data, root->nome)) {
        root->left = insert(root->left, data, preco, cat);
    } else if (0 < strcmp(data, root->nome)) {
        root->right = insert(root->right, data, preco, cat);
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
        inOrderTraversal(root->right);
    }
}

void finder() {
    // // printf("%s", root->nome);
    // if(root != NULL){
    //     // int compare_val = strcmp(root->nome, busca);

    //     if (strcmp(root->nome, busca) < 0){

    //         finder(root->left, busca);

    //     } else if( strcmp(root->nome, busca) > 0){
    //         finder(root->right, busca);
    //     } else {

    //         printf("%s \n", root->nome);
    //         printf("%s \n", root->categoria);
    //         printf("%.2f \n", root->preco);

    //     }
    // };

    


}

void finder2(struct Node* root, char *busca){

    if (root != NULL) {
        finder2(root->left,busca);
        printf("==================\n");
        if(strcmp(busca, root->nome) == 0){
            printf("%s \n", root->nome);
            printf("%s \n", root->categoria);
            printf("%.2f \n", root->preco);
            return;
        }
        
        finder2(root->right,busca);
    }



}

int main() {
    struct Node* root = NULL;

    // Insert some nodes into the binary tree
    root = insert(root, "Omo", 2.99, "Sabao");
    insert(root, "Sabao", 7.99, "Sabao");
    insert(root, "Frango", 10.99, "Comida");
    insert(root, "Asa", 4.99, "Parte");
    insert(root, "Boi", 100.00, "Comida");

 
    // insert(root, 40);
    // insert(root, 70);
    // insert(root, 60);
    // insert(root, 80);
    // insert(root, 45);

    // Perform an in-order traversal to print the elements in sorted order
    // printf("In-order traversal: ");
    // inOrderTraversal(root);
    // printf("\n");
    finder();

    return 0;
}
