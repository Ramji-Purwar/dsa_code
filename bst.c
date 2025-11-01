#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define REP(i, a, b) for(int i = a; i < b; i++)

typedef struct Node{
    int val;
    struct Node* l;
    struct Node* r;
} node;

node* cnode(int x) {
    node* new = malloc(sizeof(node));
    new->val = x;
    new->l = new->r = NULL;
    return new;
}

node* add(node* root, int x){
    if(root == NULL) 
        return cnode(x);
    
    if(root->val > x){
        root->l = add(root->l, x);
    } 
    else if(x > root->val) {
        root->r = add(root->r, x);
    }    
    return root;
}

node* findMin(node* root) {
    if (root == NULL)
        return NULL;

    while(root->l != NULL)
        root = root->l;
    return root;
}

node* findMax(node* root) {
    if (root == NULL)
        return NULL;
    
    while(root->r != NULL)
        root = root->r;
    return root;
}

node* search(node* root, int x) {
    while (root != NULL) {
        if (root->val == x)
            return root;
        else if (x < root->val)
            root = root->l;
        else
            root = root->r;
    }
    return NULL;
}

int height(node* root) {
    if (root == NULL) {
        return -1;
    }
    
    int lHeight = height(root->l);
    int rHeight = height(root->r);
    
    return (lHeight > rHeight ? lHeight : rHeight) + 1;
}

void getHeights(node* root, int* lHeight, int* rHeight) {
    if (root->l != NULL) {
        int ll = height(root->l->l);
        int lr = height(root->l->r);
        *lHeight = (ll > lr ? ll : lr) + 1;
    } else {
        *lHeight = -1;
    }
    
    if (root->r != NULL) {
        int rl = height(root->r->l);
        int rr = height(root->r->r);
        *rHeight = (rl > rr ? rl : rr) + 1;
    } else {
        *rHeight = -1;
    }
}

node* unlink_node(node* n) {
    node* replacement = NULL;
    
    if (n->l == NULL) {
        replacement = n->r;
    } else if (n->r == NULL) {
        replacement = n->l;
    }
    
    return replacement;
}

node* delete(node* root, int x) {
    if (root == NULL) {
        return NULL;
    }
    
    if (x < root->val) {
        root->l = delete(root->l, x);
        return root;
    } 
    else if (x > root->val) {
        root->r = delete(root->r, x);
        return root;
    }
    
    if (root->l == NULL || root->r == NULL) {
        node* temp = unlink_node(root);
        free(root);
        return temp;
    }
    
    int lHeight, rHeight;
    getHeights(root, &lHeight, &rHeight);
    
    if (lHeight > rHeight) {
        node* predecessor = findMax(root->l);
        root->val = predecessor->val;
        root->l = delete(root->l, predecessor->val);
    } else {
        node* successor = findMin(root->r);
        root->val = successor->val;
        root->r = delete(root->r, successor->val);
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

int countnodes(node* root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countnodes(root->l) + countnodes(root->r);
}

node* inorderSuccessor(node* root, int val) {
    node* current = search(root, val);
    
    if (current == NULL) {
        return NULL;
    }
    
    if (current->r != NULL) {
        return findMin(current->r);
    }
    
    node* successor = NULL;
    node* ancestor = root;
    
    while (ancestor != current) {
        if (current->val < ancestor->val) {
            successor = ancestor;
            ancestor = ancestor->l;
        } else {
            ancestor = ancestor->r;
        }
    }
    
    return successor;
}

node* inorderPredecessor(node* root, int val) {
    node* current = search(root, val);
    
    if (current == NULL) {
        return NULL;
    }
    
    if (current->l != NULL) {
        return findMax(current->l);
    }
    
    node* predecessor = NULL;
    node* ancestor = root;
    
    while (ancestor != current) {
        if (current->val > ancestor->val) {
            predecessor = ancestor;
            ancestor = ancestor->r;
        } else {
            ancestor = ancestor->l;
        }
    }
    
    return predecessor;
}

void freeTree(node* root) {
    if (root != NULL) {
        freeTree(root->l);
        freeTree(root->r);
        free(root);
    }
}

int main() {
    node* root = NULL;

    int n = 9;
    int arr[] = {5, 2, 6, 3, 8, 9, 1, 7, 4};
    
    for(int i = 0; i < n; i++) {
        root = add(root, arr[i]);
    }

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    printf("Postorder: ");
    postorder(root);
    printf("\n");

    printf("Height: %d\n", height(root));
    printf("Node count: %d\n", countnodes(root));

    int val = 6;
    node* found = search(root, val);
    printf("Search %d: %s\n", val, found ? "Found" : "Not Found");

    node* minNode = findMin(root);
    node* maxNode = findMax(root);
    printf("Min: %d\n", minNode ? minNode->val : -1);
    printf("Max: %d\n", maxNode ? maxNode->val : -1);

    node* succ = inorderSuccessor(root, 6);
    node* pred = inorderPredecessor(root, 6);
    printf("Successor of 6: %d\n", succ ? succ->val : -1);
    printf("Predecessor of 6: %d\n", pred ? pred->val : -1);

    root = delete(root, 6);
    printf("After deleting 6, inorder: ");
    inorder(root);
    printf("\n");

    freeTree(root);    
    return 0;
}