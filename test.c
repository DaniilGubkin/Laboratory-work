#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct treeNode
{
	struct treeNode* leftPtr;
	int data;
	struct treeNode* rightPtr;
};

typedef struct treeNode TREENODE;
typedef TREENODE* TREENODEPTR;


int main()
{
	setlocale(LC_ALL, "ru");
	TREENODEPTR rootPtr = NULL;
	
	freeTree(rootPtr);
}
