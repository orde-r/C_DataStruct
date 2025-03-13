#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left, *right;
} node;

// Fungsi untuk membuat node baru
node *createNewNode(int value) {
    node *newNode = (node *)malloc(sizeof(node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->value = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert tanpa rekursi
node *insert(node *root, int value) {
    node *newNode = createNewNode(value);
    if (!root) return newNode;

    node *parent = NULL, *current = root;
    while (current) {
        parent = current;
        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else {
            free(newNode);  // Jika duplikat, tidak ditambahkan
            return root;
        }
    }

    if (value < parent->value)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root;
}

// Search tanpa rekursi
node *search(node *root, int value) {
    while (root && root->value != value) {
        if (value < root->value)
            root = root->left;
        else
            root = root->right;
    }
    return root; // NULL jika tidak ditemukan
}

// Mencari nilai minimum
node *findMin(node *root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Delete tanpa rekursi
node *delete(node *root, int value) {
    node *parent = NULL, *current = root;

    // Mencari node yang akan dihapus
    while (current && current->value != value) {
        parent = current;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    if (!current) return root; // Tidak ditemukan

    // Kasus 1: Node tanpa anak
    if (!current->left && !current->right) {
        if (!parent) root = NULL;
        else if (parent->left == current) parent->left = NULL;
        else parent->right = NULL;
        free(current);
    }

    // Kasus 2: Node dengan satu anak
    else if (!current->left || !current->right) {
        node *child = (current->left) ? current->left : current->right;
        if (!parent) root = child;
        else if (parent->left == current) parent->left = child;
        else parent->right = child;
        free(current);
    }

    // Kasus 3: Node dengan dua anak
    else {
        node *successor = findMin(current->right);
        int tempValue = successor->value;
        root = delete(root, successor->value); // Hapus successor
        current->value = tempValue;
    }

    return root;
}

// Fungsi untuk traversal (tetap rekursif)
void inorder(node *root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->value);
        inorder(root->right);
    }
}

int main() {
    node *root = NULL;

    // Insert tanpa rekursi
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Search
    int searchValue = 40;
    if (search(root, searchValue))
        printf("Value %d found in BST\n", searchValue);
    else
        printf("Value %d not found in BST\n", searchValue);

    // Delete
    int deleteValue = 30;
    root = delete(root, deleteValue);
    printf("Inorder after deleting %d: ", deleteValue);
    inorder(root);
    printf("\n");

    return 0;
}
