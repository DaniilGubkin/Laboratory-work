#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

struct treeNode {
	struct treeNode *leftPtr;
	char data;
	struct treeNode *rightPtr;
};

typedef struct treeNode TREENODE;
typedef  TREENODE * TREENODEPTR1;

void insertNode(TREENODEPTR1 *, int);
void inOrder(TREENODEPTR1);				/*По возрастанию*/
void preOrder(TREENODEPTR1);
void postOrder(TREENODEPTR1);
int height(TREENODEPTR1 treePtr, int max);

int main()
{
	int i, item;
	TREENODEPTR1  rootPtr = NULL;
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	printf("The numbers being placed in the tree are: \n");
	for (i = 1; i <= 10; i++) {
		item = rand() % 20;
		printf("%3d", item);				  /*Рандомим 10 числе и заталкиваем их в ввод иерархией дерева*/
insertNode(&rootPtr, item);
	}
	printf("\n\n The preOrder traversal is: \n");
	preOrder(rootPtr);

	printf("\n\n The inOrder traversal is: \n");
	inOrder(rootPtr);

	printf("\n\n The postOrder traversal is: \n");
	postOrder(rootPtr);

	printf("\n Высота равна %d", height(rootPtr, 0));
	getch();
		return 0;
}

void insertNode(TREENODEPTR1 *treePtr, int value)
{
	if (*treePtr == NULL) {
		*treePtr = malloc(sizeof(TREENODE));			/*Остановка рекурсии*/
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL; /*Ставим число в нужное место, и две ветви отводим от этой ячейки и зануляем их*/
			(*treePtr)->rightPtr = NULL;
		}
		else
			printf("%d not inserted. No memore available.\n"); /*Защита от утечки памяти*/
	}
	else
		if (value < (*treePtr)->data)
			insertNode(&((*treePtr)->leftPtr), value);		/*Обход влево и снова пытаемся найти нужное место*/
		else
			if (value > (*treePtr)->data)
				insertNode(&((*treePtr)->rightPtr), value);   /*Обход вправа и снова пытаемся найти нужное место*/

			else
				printf("dup");									/*На случай повторения элементов*/

}

void inOrder(TREENODEPTR1 treePtr)
{
	if (treePtr != NULL) {
		inOrder(treePtr->leftPtr);				/*заходим в наше дерево, печатаем самый левый(минимальный элемент по заполнению), дальше печатаем самый левый символ не считая этот и так далее*/
		printf("%3d", treePtr->data);
		inOrder(treePtr->rightPtr);
	}
}

void preOrder(TREENODEPTR1 treePtr)
{
	if (treePtr != NULL) {
		printf("%3d", treePtr->data);
		preOrder(treePtr->leftPtr);			/*Печатаем первый, печатаем первый левый, печатаем второй левой, и тд как только эти "левые" закончились печатаем один правый и также идем по принципу печатаем "левый"*/
		preOrder(treePtr->rightPtr);
	}
}

void postOrder(TREENODEPTR1 treePtr)
{
	if (treePtr != NULL) {
		postOrder(treePtr->leftPtr);
		postOrder(treePtr->rightPtr);			/*Печатаем самый левый, возвращаемся к узлу, от узла идём вправо, там ищем самый левый, и тд через рекурсию*/
		printf("%3d", treePtr->data);
	}
}

int height(TREENODEPTR1 treePtr, int max)
{
	max++;
	int max1;
	int max2;
	if (treePtr->leftPtr != 0)
		max1 = height(treePtr->leftPtr, max);
	else
		max1 = max;
	if (treePtr->rightPtr != 0)
		max2 = height(treePtr->rightPtr, max);
	else
		max2 = max;
	if (max1 > max2)
		max = max1;
	else
		max = max2;
	return max;
}
