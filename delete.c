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

//поиск нужного эл-та
TREENODEPTR search(TREENODEPTR root, int key)
{
	// Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень
	if ((root == NULL) || (root->data = key))
		return root;
	// Поиск нужного узла
	if (key < root->data)
		return search(root->leftPtr, key);
	else return search(root->rightPtr, key);
}

//поиск эл-та перед нужным
TREENODEPTR prevSearch(TREENODEPTR root, int key)
{
	// Если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень

	if ((root == NULL))
	{
		return root; //ситуация, когда искомого эл-та нет
	}

	//находим элемент, у которого потом нам подходит
	if ( root->leftPtr->data==key || root->rightPtr->data == key)
		return root;

	// Поиск нужного узла
	if (key < root->data)
		 search(root->leftPtr, key);
	else search(root->rightPtr, key);
}

// Минимальный элемент дерева
 TREENODEPTR minim (TREENODEPTR root)
{
	TREENODEPTR l = root;
	while (l->leftPtr != NULL)
		l = l->leftPtr;
	return l;
}

 // Максимальный элемент дерева
 TREENODEPTR maxim(TREENODEPTR root)
 {
	 TREENODEPTR r = root;
	 while (r->rightPtr != NULL)
		 r = r->rightPtr;
	 return r;
 }

 void delete(TREENODEPTR* root, int key)
 {
	 // Поиск удаляемого узла по ключу
	 TREENODEPTR current = NULL, l = NULL, m = NULL; //m-предок l-удаляемый элемент

	 int flag; //будет 1, если l - это левый потомок и 0, если l- это правый потомок, нужно для 3 случая

	 m = prevSearch(*root, key);

	 if (!m)
	 {
		 printf("\nЗапрашиваемое на удаление число не найдено в дереве!\n");
		 return;
	 }

	 if (m->leftPtr->data = key)//нашли удаляемый элемент
	 {
		 l = m->leftPtr;
		 flag = 1;
	 }
		 
	 else
	 {
		 l = m->rightPtr;
		 flag = 0;
	 }

	 // 1 случай
	 if ((l->leftPtr == NULL) && (l->rightPtr == NULL))
	 {
		 if (l == m->rightPtr) m->rightPtr = NULL;
		 else m->leftPtr = NULL;
		 free(l);
	 }
	 // 2 случай, 1 вариант - поддерево справа
	 if ((l->leftPtr == NULL) && (l->rightPtr != NULL))
	 {
		 if (l == m->rightPtr) m->rightPtr = l->rightPtr;
		 else m->leftPtr = l->rightPtr;
		 free(l);
	 }
	 // 2 случай, 2 вариант - поддерево слева
	 if ((l->leftPtr != NULL) && (l->rightPtr == NULL))
	 {
		 if (l == m->rightPtr) m->rightPtr = l->leftPtr;
		 else m->leftPtr = l->leftPtr;
		 free(l);
	 }
	 // 3 случай
	 if ((l->leftPtr != NULL) && (l->rightPtr != NULL))
	 {
		 current = minim(l->rightPtr);
		 current->leftPtr = l->leftPtr;

		 if (flag) m->leftPtr = l->rightPtr;
		 else m->rightPtr = l->rightPtr;

		 free(l);
	 }
 }

 //удаление дерева
 void FreeTree(TREENODEPTR rootPtr)
 {
	 if (!rootPtr) return;
	 FreeTree(rootPtr->leftPtr);
	 FreeTree(rootPtr->rightPtr);
	 free(rootPtr);
	 return;
 }

int main()
{
	setlocale(LC_ALL, "ru");
	int item;
	TREENODEPTR rootPtr = NULL;

	srand(time(NULL));

	printf("Числа, которые будут помещены в дерево: ");

	for (int i = 0; i < 10; i++)
	{
		do {
			item = rand() % 15;
			printf("%d  ", item);
		} while (insertNode(&rootPtr, item));
	}

	//delete(&rootPtr, 2);

	printf("\n\nОбход порядковой выборкой: ");
	inOrder(rootPtr);

	printf("\n\nОбход предварительной выборкой: ");
	preOrder(rootPtr);

	printf("\n\nОбход отложенной выборкой: ");
	postOrder(rootPtr);
	printf("\n");

	freeTree(rootPtr);
}
