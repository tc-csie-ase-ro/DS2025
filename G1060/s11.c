#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#define LINESIZE 128
#define COUNT 10

typedef struct FileProperties FileProperties;
typedef struct TreeNode TreeNode;

struct FileProperties {
	int id;
	char* filename;
};

struct TreeNode {
	FileProperties fp;
	TreeNode* left;
	TreeNode* right;
};

void insertTreeNode(TreeNode** root, FileProperties fp) {
	if (*root) {
		if (fp.id < (*root)->fp.id) {
			insertTreeNode(&(*root)->left, fp);
		}
		else {
			insertTreeNode(&(*root)->right, fp);
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

FileProperties readOneFromFile(FILE* f) {

	char buffer[LINESIZE];

	fgets(buffer, LINESIZE, f);

	FileProperties fp;
	char* token = strtok(buffer, ",");
	
	fp.id = atoi(token);

	token = strtok(NULL, ",");
	fp.filename = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(fp.filename, token);
	
	return fp;

}

void readDataFromFile(TreeNode** tree, const char* fileName) {

	FILE* f;
	f = fopen(fileName, "r");

	while (!feof(f)) {
		insertTreeNode(tree, readOneFromFile(f));
	}
}

int main() {

	TreeNode* tree = NULL;

	readDataFromFile(&tree, "files.txt");
	printTree(tree, 20);

	return 0;
}
