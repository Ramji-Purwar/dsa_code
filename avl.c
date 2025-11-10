#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)

typedef struct Node {
    int val;
    struct Node* l;
    struct Node* r;
    int h;
} node;

int height(node* root) {
    if (root == NULL)
        return 0;
    return root->h;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

node* cnode(int x) {
    node* new = malloc(sizeof(node));
    new->val = x;
    new->l = new->r = NULL;
    new->h = 1;
    return new;
}

int getBalance(node* root) {
    if (root == NULL)
        return 0;
    return height(root->l) - height(root->r);
}

node* rightRotate(node* y) {
    node* x = y->l;
    node* T2 = x->r;

    x->r = y;
    y->l = T2;

    y->h = max(height(y-> l), height(y-> r)) + 1;
    x->h = max(height(x-> l), height(x-> r)) + 1;

    return x;
}

node* leftRotate(node* x) {
    node* y = x->r;
    node* T2 = y->l;

    y->l = x;
    x->r = T2;

    x->h = max(height(x->l), height(x->r)) + 1;
    y->h = max(height(y->l), height(y->r)) + 1;

    return y;
}

node* add(node* root, int x) {
    if(root == NULL)
        return cnode(x);

    if(x < root->val) 
        root->l = add(root->l, x);
    else if(x > root->val) 
        root->r = add(root->r, x);
    else 
        return root; // Duplicate values not allowed

    root->h = 1 + max(height(root->l), height(root->r));

    int balance = getBalance(root);
    
    if (balance > 1 && x < root->l->val)
        return rightRotate(root);

    if (balance < -1 && x > root->r->val)
        return leftRotate(root);

    if (balance > 1 && x > root->l->val) {
        root->l = leftRotate(root->l);
        return rightRotate(root);
    }

    if (balance < -1 && x < root->r->val) {
        root->r = rightRotate(root->r);
        return leftRotate(root);
    }

    return root;
}

node* findMin(node* root) {
    node* cur = root;
    while (cur->l != NULL)
        cur = cur->l;
    return cur;
}

node* findMax(node* root) {
    node* cur = root;
    while(cur->r != NULL)
        cur = cur->r;
    return cur;
}

node* delete(node* root, int x) {
    if (root == NULL)
        return root;

    if (x < root->val)
        root->l = delete(root->l, x);
    else if (x > root->val)
        root->r = delete(root->r, x);
    else {
        if ((root->l == NULL) || (root->r == NULL)) {
            node* temp = root->l ? root->l : root->r;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            node* temp = findMin(root->r);
            root->val = temp->val;
            root->r = delete(root->r, temp->val);
        }
    }

    if (root == NULL)
        return root;

    root->h = 1 + max(height(root->l), height(root->r));

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->l) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->l) < 0) {
        root->l = leftRotate(root->l);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->r) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->r) > 0) {
        root->r = rightRotate(root->r);
        return leftRotate(root);
    }

    return root;
}

void inorder(node* root) {
    if (root != NULL) {
        inorder(root->l);
        printf("%d ", root->val);
        inorder(root->r);
    }
}

void preorder(node* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorder(root->l);
        preorder(root->r);
    }
}

void postorder(node* root) {
    if (root != NULL) {
        postorder(root->l);
        postorder(root->r);
        printf("%d ", root->val);
    }
}

bool search(node* root, int x) {
    if (root == NULL)
        return false;
    if (root->val == x)
        return true;
    if (x < root->val)
        return search(root->l, x);
    return search(root->r, x);
}

node* LCA(node* root, int a, int b){
    if (root == NULL) return NULL;
    if (a < root->val && b < root->val) return LCA(root->l, a, b);
    if (a > root->val && b > root->val) return LCA(root->r, a, b);
    return root;
}

void freeTree(node* root) {
    if (root != NULL) {
        freeTree(root->l);
        freeTree(root->r);
        free(root);
    }
}

int main(){
    int n;
    scanf("%d", &n);

    int* v = (int*)malloc(n * sizeof(int));
    REP(i, 0, n) scanf("%d", &v[i]);

    node* root = NULL;
    REP(i, 0, n){
        root = add(root, v[i]);
    }

    // Print traversals
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");



    printf("Tree height: %d\n", height(root));

    freeTree(root);
    return 0;
}