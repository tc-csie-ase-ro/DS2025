#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

#define LINESIZE 128
#define COUNT 10

typedef struct FileProperties FP;
typedef struct TreeNode TreeNode;

struct FileProperties {
	int id;
	char* filename;
};

struct TreeNode {
	FP fp;
	TreeNode* left;
	TreeNode* right;
};

int treeHeight(TreeNode* tree) {
	if (tree) {
		int hLeft = treeHeight(tree->left);
		int hRight = treeHeight(tree->right);

		return 1 + (hLeft > hRight ? hLeft : hRight);
	}
	else {
		return 0;
	}
}

int balanceFactor(TreeNode* tree) {
	if (tree) {
		int hLeft = treeHeight(tree->left);
		int hRight = treeHeight(tree->right);

		return hRight - hLeft;
	}
	else {
		return 0;
	}
}

void rotateRight(TreeNode** root) {
	TreeNode* aux = (*root)->left;
	(*root)->left = aux->right; // (*root)->left->right
	aux->right = *root;
	*root = aux;
}

void rotateLeft(TreeNode** root) {
	TreeNode* aux = (*root)->right;
	(*root)->right = aux->left; // (*root)->right->left
	aux->left = *root;
	*root = aux;
}

void insertTree(TreeNode** root, FP fp) {
	if (*root) {
		if (fp.id < (*root)->fp.id) {
			insertTree(&(*root)->left, fp);
		}
		else {
			insertTree(&(*root)->right, fp);
		}

		int balanceFactorValue = balanceFactor(*root);

		if (balanceFactorValue == 2) {
			if (balanceFactor((*root)->right) == 1) {
				rotateLeft(root);
			}
			else {
				rotateRight(&(*root)->right);
				rotateLeft(root);
			}
		}

		if (balanceFactorValue == -2) {
			if (balanceFactor((*root)->left) == -1) {
				rotateRight(root);
			}
			else {
				rotateLeft(&(*root)->left);
				rotateRight(root);
			}
		}
	}
	else {
		TreeNode* newNode = malloc(sizeof(TreeNode));
		newNode->fp = fp;
		newNode->left = NULL;
		newNode->right = NULL;
		*root = newNode;
	}
}

void printTree(TreeNode* tree, int space) {
	if (tree) {

		space += COUNT;

		printTree(tree->right, space);

		printf("\n");
		for (int i = COUNT; i < space; i++) {
			printf(" ");
		}
		printf("%d", tree->fp.id);

		printTree(tree->left, space);

	}
}

FP readDataFromFile(FILE* f) {

	FP fp;

	char buffer[LINESIZE];
	fgets(buffer, LINESIZE, f);

	char* token = strtok(buffer, ",");
	fp.id = atoi(token);

	token = strtok(NULL, ",");
	fp.filename = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(fp.filename, token);

	return fp;
}

void readAllFromFile(TreeNode** tree, const char* filename) {
	FILE* f;
	f = fopen(filename, "r");

	while (!feof(f)) {
		insertTree(tree, readDataFromFile(f));
	}
}

int main() {
	TreeNode* tree = NULL;
	readAllFromFile(&tree, "files.txt");
	printTree(tree, 20);
	return 0;
}


/*
8,aaa.txt
9,bbb.txt
10,ccc.txt
7,ddd.txt
6,eee.txt
12,fff.txt
11,ggg.txt
4,hhh.txt
5,iii.txt
3,jjj.txt
*/
