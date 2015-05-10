#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int data;
	struct node *left;
	struct node *right;
} Node;

void insert(Node **node, int data) {
	if(*node == NULL) {
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->data = data;
		newNode->left = newNode->right = NULL;
		*node = newNode;
	} else {
		if(data <= (*node)->data) {
			insert(&(*node)->left, data);
		} else {
			insert(&(*node)->right, data);
		}
	}
}

void printInorder(Node **node) {
	if(*node == NULL) return;
	printInorder(&(*node)->left);
	printf("%d ", (*node)->data);
	printInorder(&(*node)->right);
}

void printPreorder(Node **node) {
	if(*node == NULL) return;
	printf("%d ", (*node)->data);
	printPreorder(&(*node)->left);
	printPreorder(&(*node)->right);
}

void printPostorder(Node **node) {
	if(*node == NULL) return;
	printPostorder(&(*node)->left);
	printPostorder(&(*node)->right);
	printf("%d ", (*node)->data);
}

int maxDepth(Node **node) {
	if(*node == NULL) {
		return 0;
	} else {
		int lDepth = maxDepth(&(*node)->left);
		int rDepth = maxDepth(&(*node)->right);
		
		if(lDepth > rDepth) {
			return lDepth + 1;
		} else {
			return rDepth + 1;
		}
	}
}

int minValue(Node **node) {
	// TODO
}

int main(void) {
    Node *root = NULL;
	
	insert(&root, 4);
	insert(&root, 2);
	insert(&root, 5);
	insert(&root, 1);
	insert(&root, 3);
	
	printf("     %d\n"
		   "    / \\\n"
		   "   %d   %d\n"
		   "  / \\\n"
		   " %d   %d", root->data, root->left->data, root->right->data, root->left->left->data, root->left->right->data);
		   
	
	printf("\n\nDepth: %d\n ", maxDepth(&root));
	
	printf("\nInorder: "); printInorder(&root);
	printf("\nPostorder: "); printPostorder(&root);
	printf("\nPreorder: "); printPreorder(&root);

    return 0;
}
