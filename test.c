#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <string.h>

// Estrutura basica
struct Node {
    char nome[50];
    float preco;
    char categoria[20];
    int quantidadeEstoque;
    struct Node* left;
    struct Node* right;
};

// Criar node na árvore binaria
struct Node* createNode(char nome[50], float preco, char categoria[20], int quantstoque) {
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

// Função recursiva para percorrer a arvore binária em ordem
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
            // Achou
            if (current->left == NULL && current->right == NULL) {
                // Case 1: Node não tem filho
                if (parent == NULL) {
                    *root = NULL; // A raiz é o unico node
                } else if (parent->left == current) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
                free(current);
            } else if (current->left == NULL || current->right == NULL) {
                // Case 2: Node tem um filho
                struct Node* child = (current->left != NULL) ? current->left : current->right;
                if (parent == NULL) {
                    *root = child; // Node atual é a raiz
                } else if (parent->left == current) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
                free(current);
            } else {
                // Caso 3: Node tem dois filhos
                struct Node* successor = findMin(current->right);
                successor->left = current->left;
                
                if (parent->left == current) {
                    parent->left = current->right;
                } else {
                    parent->right = current->right;
                }
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
    char nome[50] = "";
    char cat[20] = "";
    strcpy(nome, current->nome);
    strcpy(cat, current->categoria);
    
    while(menu != 0){
        puts("Por favor digite o que deseja alterar:");
        puts("0: SAIR");
        puts("1: PRECO");
        puts("2: CATEGORIA");
        puts("3: QUANTIDADE DE ESTOQUE");
        puts("4: NOME");
        puts("5: APLICAR");
        scanf("%d", &menu);
        fflush(stdin);

        switch(menu){
            case 0: return;
            case 1: puts("DIGITE O NOVO PRECO"); scanf("%f", &preco); fflush(stdin);break;
            case 2: puts("DIGITE A NOVA CATEGORIA"); fgets(cat, 20, stdin); strtok(cat, "\n");  fflush(stdin);break;
            case 3: puts("DIGITE A NOVA QUANTIDADE DE ESTOQUE"); scanf("%d", &quantidadestoq); fflush(stdin);break;
            case 4: puts("DIGITE O NOVO NOME"); fgets(nome, 50, stdin); strtok(nome, "\n"); fflush(stdin);break;
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

        // Deleta o node antigo
        deleteNode(&root, targetNome);
        // Insere outro com os mesmos dados;
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
    char prodName[50] = "";
    char cat[20] = "";
    float preco = 0;
    int qtdestoque;
    char confirm[10] = "";
    puts("================= REGISTRO ==============");
    puts("Por favor digite o nome do produto: ");
    fgets(prodName, 50, stdin);
    strtok(prodName, "\n");
    fflush(stdin);
    puts("Por favor digite o preco do produto: ");
    scanf("%f", &preco);
    fflush(stdin);
    puts("Por favor digite a categoria do produto: ");
    fgets(cat, 20, stdin);
    strtok(cat, "\n");
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
    char nome[50];
    inOrderTraversal(root);
    puts("Que produto deseja alterar?");
    fgets(nome, 50, stdin);
    strtok(nome, "\n");
    fflush(stdin);
    updateNode(root, nome);

}

void deleteScreen(struct Node** root){
    char nome[50];
    inOrderTraversal(*root);
    puts("Que produto deseja deletar?");
    fgets(nome, 50, stdin);
    strtok(nome, "\n");
    fflush(stdin);
    system("pause");
    deleteNode(root, nome);

}

void filterPrincer(struct Node* root){
    float preco;
    puts("Digite o preco maximo: ");
    scanf("%f", &preco);
    printIfLowerThan(root, preco);
    system("pause");
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
            puts("5: Ver por preco");
            scanf("%d", &selector);
            fflush(stdin);
            switch(selector){
                case 1: root = registerScreen(root); break;
                case 2: inOrderTraversal(root); system("pause");break;
                case 3: alterScreen(root); break;
                case 4: deleteScreen(&root); break;
                case 5: filterPrincer(root); break;
            }

    }

    return 0;
}
