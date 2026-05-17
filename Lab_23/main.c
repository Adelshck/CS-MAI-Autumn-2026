#include <stdio.h>
#include <stdlib.h>

typedef enum {
    VAL_0 = 0,
    VAL_1,
    VAL_2,
    VAL_3,
    VAL_4,
    VAL_5,
    VAL_10 = 10,
    VAL_50 = 50,
    VAL_100 = 100
} NodeType;

typedef struct Node {
    NodeType data;       
    struct Node *son;
    struct Node *brother;
} Node;

// Создание нового узла
Node* createNode(NodeType value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->son = NULL;
    newNode->brother = NULL;
    return newNode;
}

// Поиск узла по значению перечисления
Node* findNode(Node* root, NodeType value) {
    if (root == NULL) return NULL;
    if (root->data == value) return root;

    Node* res = findNode(root->son, value);
    if (res) return res;

    return findNode(root->brother, value);
}

// Добавление дочернего узла
void addSon(Node* parent, NodeType value) {
    if (!parent) return;
    Node* newNode = createNode(value);
    if (parent->son == NULL) {
        parent->son = newNode;
    } else {
        Node* temp = parent->son;
        while (temp->brother != NULL) {
            temp = temp->brother;
        }
        temp->brother = newNode;
    }
}

// Визуализация структуры дерева
void printTree(Node* root, int depth) {
    if (root == NULL) return;

    for (int i = 0; i < depth; i++) printf("  ");
    printf("%d\n", (int)root->data); // Выводим числовое значение enum
    printTree(root->son, depth + 1);
    printTree(root->brother, depth);
}

// Поиск максимума и его глубины
void findMaxDepth(Node* root, int currentDepth, NodeType* maxVal, int* depthOfMax) {
    if (root == NULL) return;

    if (root->data > *maxVal) {
        *maxVal = root->data;
        *depthOfMax = currentDepth;
    }

    findMaxDepth(root->son, currentDepth + 1, maxVal, depthOfMax);
    findMaxDepth(root->brother, currentDepth, maxVal, depthOfMax);
}

// Рекурсивное удаление поддерева
void clearSubtree(Node* target) {
    if (target == NULL) return;
    clearSubtree(target->son); 
    free(target);
}

// Удаление узла и его ветки
Node* deleteNode(Node* root, NodeType value) {
    if (root == NULL) return NULL;

    if (root->data == value) {
        Node* nextRoot = root->brother;
        clearSubtree(root->son);
        free(root);
        return nextRoot;
    }

    if (root->son && root->son->data == value) {
        Node* toDelete = root->son;
        root->son = toDelete->brother; 
        clearSubtree(toDelete->son);   
        free(toDelete);                
        return root;
    }

    Node* curr = root->son;
    while (curr && curr->brother) {
        if (curr->brother->data == value) {
            Node* toDelete = curr->brother;
            curr->brother = toDelete->brother; 
            clearSubtree(toDelete->son);
            free(toDelete);
            return root;
        }
        curr = curr->brother;
    }

    deleteNode(root->son, value);
    deleteNode(root->brother, value);
    return root;
}

int main() {
    Node* root = NULL;
    int choice;
    int inputVal, parentVal;

    while (1) {
        printf("\n--- GENERAL TREE (ENUM DATA) - VAR 20 ---\n");
        printf("1. Add Node\n");
        printf("2. Print Tree\n");
        printf("3. Find Max & Depth (Task 20)\n");
        printf("4. Delete Node & Subtree\n");
        printf("5. Exit\n");
        printf("Select action: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Enter a number.\n");
            while(getchar() != '\n'); 
            continue;
        }

        if (choice == 1) {
            if (root == NULL) {
                printf("Enter root value (as integer): ");
                scanf("%d", &inputVal);
                root = createNode((NodeType)inputVal);
                printf("Root created.\n");
            } else {
                printf("Enter PARENT and NEW node values: ");
                if (scanf("%d %d", &parentVal, &inputVal) == 2) {
                    Node* parent = findNode(root, (NodeType)parentVal);
                    if (parent) {
                        addSon(parent, (NodeType)inputVal);
                        printf("Node added.\n");
                    } else {
                        printf("Parent not found!\n");
                    }
                }
            }
        } else if (choice == 2) {
            if (!root) printf("Tree is empty.\n");
            else printTree(root, 0);
        } else if (choice == 3) {
            if (!root) printf("Tree is empty.\n");
            else {
                NodeType mVal = root->data;
                int dMax = 0;
                findMaxDepth(root, 0, &mVal, &dMax);
                printf("Max value: %d at Depth: %d\n", (int)mVal, dMax);
            }
        } else if (choice == 4) {
            if (!root) printf("Tree is empty.\n");
            else {
                printf("Enter value to delete: ");
                scanf("%d", &inputVal);
                root = deleteNode(root, (NodeType)inputVal);
                printf("Deleted (if existed).\n");
            }
        } else if (choice == 5) {
            if (root) {
                clearSubtree(root->son);
                free(root);
            }
            printf("Exit. Memory cleared.\n");
            break;
        }
    }
    return 0;
}