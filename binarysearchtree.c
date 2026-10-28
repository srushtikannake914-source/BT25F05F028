
#include <stdio.h>
#include <stdlib.h>

/* Structure for BST and AVL Tree */
struct Node {
    int data;
    struct Node *left, *right;
    int height;
};

/* Create a new node */
struct Node* createNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

/* BST Insertion */
struct Node* bstInsert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = bstInsert(root->left, data);
    else if (data > root->data)
        root->right = bstInsert(root->right, data);

    return root;
}

/* AVL Tree Functions */
int height(struct Node* n) {
    return n == NULL ? 0 : n->height;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int balanceFactor(struct Node* n) {
    return n == NULL ? 0 : height(n->left) - height(n->right);
}

/* Right Rotation */
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

/* Left Rotation */
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/* AVL Insertion */
struct Node* avlInsert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = avlInsert(root->left, data);
    else if (data > root->data)
        root->right = avlInsert(root->right, data);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = balanceFactor(root);

    /* LL Case */
    if (balance > 1 && data < root->left->data)
        return rightRotate(root);

    /* RR Case */
    if (balance < -1 && data > root->right->data)
        return leftRotate(root);

    /* LR Case */
    if (balance > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    /* RL Case */
    if (balance < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* Inorder Traversal */
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

/* Preorder Traversal */
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

/* Postorder Traversal */
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

/* Main Function */
int main() {
    struct Node *bst = NULL, *avl = NULL;
    int n, i, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter node values:\n");

    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        bst = bstInsert(bst, value);
        avl = avlInsert(avl, value);
    }

    printf("\n--- Binary Search Tree ---\n");
    printf("Inorder: ");
    inorder(bst);
    printf("\nPreorder: ");
    preorder(bst);
    printf("\nPostorder: ");
    postorder(bst);

    printf("\n\n--- AVL Tree ---\n");
    printf("Inorder: ");
    inorder(avl);
    printf("\nPreorder: ");
    preorder(avl);
    printf("\nPostorder: ");
    postorder(avl);

    printf("\n");
    return 0;
}
