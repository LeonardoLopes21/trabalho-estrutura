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

struct Node* findMin(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

void deleteNode(struct Node** root, char *targetNome) {
    struct Node* current = *root;
    struct Node* parent = NULL;

    while (current != NULL) {
        int cmp = strcmp(targetNome, current->nome);

        if (cmp == 0) {
            // Node found
            if (current->left == NULL && current->right == NULL) {
                // Case 1: Node has no children
                if (parent == NULL) {
                    *root = NULL; // The root itself is the only node in the tree
                } else if (parent->left == current) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
                free(current);
            } else if (current->left == NULL || current->right == NULL) {
                // Case 2: Node has one child
                struct Node* child = (current->left != NULL) ? current->left : current->right;
                if (parent == NULL) {
                    *root = child; // Current node is the root
                } else if (parent->left == current) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                free(current);
            } else {
                // Case 3: Node has two children
                struct Node* successor = findMin(current->right);
                successor->left = current->left;
                parent->left = current->right;
                free(current);
            }
        } else if (cmp < 0) {
            parent = current;
            current = current->left;
        } else {
            parent = current;
            current = current->right;
        }
    }
}

void updateNode(struct Node* root, char *targetNome) {
    puts(root);
    struct Node* current = root;
    
    while (current != NULL) {
        int cmp = strcmp(targetNome, current->nome);
        if (cmp == 0) {
            break;
        } else if (cmp < 0) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if(current == NULL){
        puts("NAO ENCONTRADO");
        return;
    }

    int menu = 1;
    float preco = current->preco;
    int quantidadestoq = current->quantidadeEstoque;
    char nome[20] = "";
    char cat[20] = "";
    strcpy(nome, current->nome);
    strcpy(cat, current->categoria);
    
    while(menu != 0){
        puts("Por favor digite o que deseja alterar: \n");
        puts("0: SAIR");
        puts("1: PRECO \n");
        puts("2: CATEGORIA \n");
        puts("3: QUANTIDADE DE ESTOQUE\n");
        puts("4: NOME\n");
        puts("5: APLICAR\n");
        scanf("%d", &menu);
        fflush(stdin);

        switch(menu){
            case 0: return;
            case 1: puts("DIGITE O NOVO PRECO"); scanf("%f", &preco); fflush(stdin);break;
            case 2: puts("DIGITE A NOVA CATEGORIA"); scanf("%s", cat); fflush(stdin);break;
            case 3: puts("DIGITE A NOVA QUANTIDADE DE ESTOQUE"); scanf("%d", &quantidadestoq); fflush(stdin);break;
            case 4: puts("DIGITE O NOVO NOME"); scanf("%s", nome); fflush(stdin);break;
            case 5: menu = 0; break;
        }

        

    }

    puts(root);
    
    if(preco != current->preco && preco > 0){
        current->preco = preco;
    }

    if(strcmp(cat, current->categoria) != 0){
        strcpy(current->categoria, cat);
    }

    if(quantidadestoq != current->quantidadeEstoque){
        current->quantidadeEstoque = quantidadestoq;
    }

    if(strcmp(nome, current->nome) != 0){

        // Delete the old node
        deleteNode(&root, targetNome);
        // Node found, insert a new node with the updated name
        insert(root, nome, preco, cat, quantidadestoq);
         
    }

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
    root = insert(root, "Queijo", 2.99, "Comida", 20);
    insert(root, "Humus", 100.00, "Comida", 10);
    insert(root, "Omo", 21.99, "Comida", 23);
    insert(root, "Faca", 21.99, "Comida", 23);
    insert(root, "Navio", 21.99, "Comida", 23);
    insert(root, "Mingau", 21.99, "Comida", 23);
    insert(root, "Pato", 21.99, "Comida", 23);
    insert(root, "Asa", 100.00, "Comida", 10);

 
    // insert(root, 40);
    // insert(root, 70);
    // insert(root, 60);
    // insert(root, 80);
    // insert(root, 45);

    // Perform an in-order traversal to print the elements in sorted order
    // printf("In-order traversal: ");
    // inOrderTraversal(root);
    // printf("\n");
    inOrderTraversal(root);
    updateNode(root, "Humus");
    inOrderTraversal(root);

    return 0;
}
