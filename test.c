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


struct Node* insert(struct Node* root, char *nome, float preco, char *cat, int quantstoq) {
    if (root == NULL) {
        return createNode(nome, preco, cat, quantstoq);
    }

    if (0 > strcmp(nome, root->nome)) {
        root->left = insert(root->left, nome, preco, cat, quantstoq);
    } else if (0 < strcmp(nome, root->nome)) {
        root->right = insert(root->right, nome, preco, cat, quantstoq);
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

void printIfLowerThan(struct Node* root, int lower){

     if (root != NULL) {
        printIfLowerThan(root->left, lower);
        if(root->preco < lower){
            printf("==================\n");
            printf("%s \n", root->nome);
            printf("%s \n", root->categoria);
            printf("%.2f \n", root->preco);
            printf("%d \n", root->quantidadeEstoque);
        }
        
        printIfLowerThan(root->right, lower);
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



struct Node* registerScreen(struct Node* root){
    puts(root);
    char prodName[50] = "";
    char cat[20] = "";
    float preco = 0;
    int qtdestoque;
    char confirm[10] = "";
    puts("================= REGISTRO ==============");
    puts("Por favor digite o nome do produto: ");
    scanf("%s", prodName);
    fflush(stdin);
    puts("Por favor digite o preco do produto: ");
    scanf("%f", &preco);
    fflush(stdin);
    puts("Por favor digite a categoria do produto: ");
    scanf("%s", cat);
    fflush(stdin);
    fflush(stdin);
    puts("Por favor digite a quantidade no estoque do produto: ");
    scanf("%d", &qtdestoque);
    puts("=======================================");
    puts("Deseja adicionar este produto? y/n");
    puts(prodName);
    puts(cat);
    printf("%.2f \n", preco);
    printf("%d\n", qtdestoque);
    scanf("%s", confirm);
    if(!strcmp(confirm, "y")){ 
        if(root != NULL){
            insert(root, prodName, preco, cat, qtdestoque); 
            return root;
        } else {
            root = insert(root, prodName, preco, cat, qtdestoque); 
            return root;
           
        }
    } else {
        return root;
    }

}

void alterScreen(struct Node* root){
    char nome[20];
    inOrderTraversal(root);
    puts("Que produto deseja alterar?");
    scanf("%s", nome);
    fflush(stdin);
    updateNode(root, nome);

}

void deleteScreen(struct Node* root){
    char nome[20];
    inOrderTraversal(root);
    puts("Que produto deseja alterar?");
    fgets(nome, 20, stdin);
    puts(nome);
    system("pause");
    deleteNode(&root, nome);

}


int main() {

    struct Node* root = NULL;

    while(1){

        system("cls");

            int selector = 0;
            puts("=============== BEM VINDO! ====================");
            puts("1: Registrar produto");
            puts("2: Ver Produtos");
            puts("3: Alterar Produtos");
            puts("4: Deletar Produtos");
            scanf("%d", &selector);
            fflush(stdin);
            switch(selector){
                case 1: root = registerScreen(root); break;
                case 2: inOrderTraversal(root); system("pause");break;
                case 3: alterScreen(root); break;
                case 4: deleteScreen(root); break;
            }

    }

    return 0;
}
