#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char data[16];          
    struct Node *left;      
    struct Node *right;     
} Node;

Node* createNode(const char* value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;

    strncpy(newNode->data, value, 15);
    
    newNode->data[15] = '\0';

    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

typedef struct StackNode {
    Node* treeNode;           
    struct StackNode* next;   
} StackNode;

void push(StackNode** top, Node* tNode) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode) {
        return;
    }
    newNode->treeNode = tNode;
    newNode->next = *top; 
    *top = newNode;       
}

Node* pop(StackNode** top) {
    if (*top == NULL) {
        return NULL; 
    }
    StackNode* temp = *top;
    Node* tNode = temp->treeNode;
    *top = (*top)->next; 
    free(temp);          
    return tNode;
}

int isEmpty(StackNode* top) {
    return top == NULL;
}

int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '(':
        case ')':
            return 0; 
        default:
            return -1; 
    }
}

void buildSubTree(StackNode** nodes, char op) {
    char strOp[2] = {op, '\0'};
    Node* root = createNode(strOp); 
    
    root->right = pop(nodes);
    root->left = pop(nodes);
    
    push(nodes, root); 
}

Node* parseExpression(const char* expr) {
    StackNode* nodes = NULL;      
    char ops[100]; 
    int opsTop = -1;

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == ' ') continue; 

        // число или буква
        if (isalnum(expr[i]) || expr[i] == '.') {
            char buffer[16] = {0};
            int k = 0;
            while (isalnum(expr[i]) || expr[i] == '.') {
                buffer[k++] = expr[i++];
            }
            i--; 
            push(&nodes, createNode(buffer));
        }
        // открывающая скобка
        else if (expr[i] == '(') {
            ops[++opsTop] = '(';
        }
        // закрывающая скобка
        else if (expr[i] == ')') {
            while (opsTop >= 0 && ops[opsTop] != '(') {
                buildSubTree(&nodes, ops[opsTop--]);
            }
            opsTop--; 
        }
        // оператор
        else {
            while (opsTop >= 0 && ops[opsTop] != '(' && 
                   getPriority(ops[opsTop]) >= getPriority(expr[i])) {
                buildSubTree(&nodes, ops[opsTop--]);
            }
            ops[++opsTop] = expr[i];
        }
    }

    while (opsTop >= 0) {
        buildSubTree(&nodes, ops[opsTop--]);
    }

    return pop(&nodes);
}


void printInfix(Node* root) {
    if (root == NULL) return;

    if (root->left != NULL || root->right != NULL) {
        printf("(");
    }

    printInfix(root->left);

    printf(" %s ", root->data);

    printInfix(root->right);

    if (root->left != NULL || root->right != NULL) {
        printf(")");
    }
}


void transform(Node* root) {
    if (root == NULL) return;

    transform(root->left);
    transform(root->right);

    if (strcmp(root->data, "/") == 0) {
        
        //(a / b) / c  = a / (b * c)
        if (root->left != NULL && strcmp(root->left->data, "/") == 0) {
            Node* A = root->left->left;
            Node* B = root->left->right;
            Node* C = root->right;
            Node* leftSlash = root->left;


            root->left = A; 
            
            strcpy(leftSlash->data, "*");
            leftSlash->left = B;
            leftSlash->right = C;
            
            root->right = leftSlash;
            
            transform(root);
        }
        
        // a / (b / c)  = (a / b) * c
        else if (root->right != NULL && strcmp(root->right->data, "/") == 0) {
            Node* A = root->left;
            Node* B = root->right->left;
            Node* C = root->right->right;
            Node* rightSlash = root->right;

            strcpy(root->data, "*");
            
            strcpy(rightSlash->data, "/");
            rightSlash->left = A;
            rightSlash->right = B;
            
            root->left = rightSlash;
            root->right = C;

            transform(root);
        }
    }
}

void printTree(Node* root, int level) {
    if (root == NULL) return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) printf("    ");
    printf("%s\n", root->data);

    printTree(root->left, level + 1);
}

int main() {
    char input[100];
    printf("Input: ");
    fgets(input, 100, stdin);

    Node* root = parseExpression(input);

    printf("Start: ");
    printInfix(root);
    printf("\n");

    transform(root);

    printf("End: ");
    printInfix(root);
    printf("\n");
    printTree(root, 0);

    freeTree(root);
    return 0;
}