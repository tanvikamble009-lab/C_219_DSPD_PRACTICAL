#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left, *right;
};

struct node* create(int data) {
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->data = data;
    p->left = p->right = NULL;
    return p;
}

struct node* build() {
    int data;
    printf("Enter value (-1 for NULL): ");
    scanf("%d", &data);

    if (data == -1)
        return NULL;

    struct node* root = create(data);

    printf("Left child of %d:\n", data);
    root->left = build();

    printf("Right child of %d:\n", data);
    root->right = build();

    return root;
}

void inorder(struct node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

int search(struct node* root, int key) {
    if (root == NULL) return 0;
    if (root->data == key) return 1;
    return search(root->left, key) || search(root->right, key);
}

int main() {
    struct node* root;
    int key;

    printf("Enter root and children:\n");
    root = build();

    printf("\nInorder  : ");
    inorder(root);
    printf("\nPreorder : ");
    preorder(root);
    printf("\nPostorder: ");
    postorder(root);

    printf("\n\nEnter element to search: ");
    scanf("%d", &key);

    if (search(root, key))
        printf("Found\n");
    else
        printf("Not Found\n");

    return 0;
}

