#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

struct treeNode {
	struct treeNode* leftPtr;
	char data;
	struct treeNode* rightPtr;
};

typedef struct treeNode TREENODE;
typedef  TREENODE* TREENODEPTR;

int height(TREENODEPTR treePtr, int max);
void insertNode(TREENODEPTR*, int);
void inOrder(TREENODEPTR);				/*По возрастанию*/
void preOrder(TREENODEPTR);
void postOrder(TREENODEPTR);
void delete(TREENODEPTR* root, int key);
TREENODEPTR minim(TREENODEPTR root);
TREENODEPTR prevSearch(TREENODEPTR root, int key);
TREENODEPTR search(TREENODEPTR root, int key);

int main()
{
	int i, item;
	TREENODEPTR  rootPtr = NULL;
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	printf("The numbers being placed in the tree are: \n");

	for (i = 1; i <= 10; i++) {
		item = rand() % 20;
		printf("%d  ", item);				  /*Рандомим 10 числе и заталкиваем их в ввод иерархией дерева*/
		insertNode(&rootPtr, item);
	}

	printf("\n\nThe preOrder traversal is: \n");
	preOrder(rootPtr);

	printf("\n\nThe inOrder traversal is: \n");
	inOrder(rootPtr);

	printf("\n\nThe postOrder traversal is: \n");
	postOrder(rootPtr);

	printf("\n\nThe height is %d", height(rootPtr, 0));
	int number;

	printf("\n\nEnter the element which you want to delete: ");
	scanf_s("%d", &number);
	delete(&rootPtr, number);
	inOrder(rootPtr);

	printf("\n\nDeleting  clones....\n\n");
	doubleDelete(&rootPtr);
	printf("\n\nThe inOrder traversal is: \n");
	inOrder(rootPtr);

	printf("\n\n");
	system("pause");

	return 0;
}

void insertNode(TREENODEPTR* treePtr, int value)
{
	if (*treePtr == NULL) {
		*treePtr = malloc(sizeof(TREENODE));			/*Остановка рекурсии*/
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL; /*Ставим число в нужное место, и две ветви отводим от этой ячейки и зануляем их*/
			(*treePtr)->rightPtr = NULL;
		}
		else
			printf("%d not inserted. No memore available.\n", value); /*Защита от утечки памяти*/
	}
	else if (value <= (*treePtr)->data)
			insertNode(&((*treePtr)->leftPtr), value);		/*Обход влево и снова пытаемся найти нужное место*/
	else if (value > (*treePtr)->data)
				insertNode(&((*treePtr)->rightPtr), value);   /*Обход вправа и снова пытаемся найти нужное место*/

			//else
			//	printf("dup  ");									/*На случай повторения элементов*/

}

void inOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		inOrder(treePtr->leftPtr);				/*заходим в наше дерево, печатаем самый левый(минимальный элемент по заполнению), дальше печатаем самый левый символ не считая этот и так далее*/
		printf("%d  ", treePtr->data);
		inOrder(treePtr->rightPtr);
	}
}

void preOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		printf("%d  ", treePtr->data);
		preOrder(treePtr->leftPtr);			/*Печатаем первый, печатаем первый левый, печатаем второй левой, и тд как только эти "левые" закончились печатаем один правый и также идем по принципу печатаем "левый"*/
		preOrder(treePtr->rightPtr);
	}
}

void postOrder(TREENODEPTR treePtr)
{
	if (treePtr != NULL) {
		postOrder(treePtr->leftPtr);
		postOrder(treePtr->rightPtr);			/*Печатаем самый левый, возвращаемся к узлу, от узла идём вправо, там ищем самый левый, и тд через рекурсию*/
		printf("%d  ", treePtr->data);
	}
}

int height(TREENODEPTR treePtr, int max)
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

// Минимальный элемент дерева
TREENODEPTR minim(TREENODEPTR root)
{
	TREENODEPTR l = root;
	while (l->leftPtr != NULL)
		l = l->leftPtr;
	return l;
}

//поиск предка (эл-та перед нужным)
TREENODEPTR prevSearch(TREENODEPTR root, int key)
{
	// если дерево пусто или ключ корня равен искомому ключу, то возвращается указатель на корень

	if ((root == NULL))
	{
		return root; //ситуация, когда искомого эл-та нет
	}

	//находим элемент, у которого потом нам подходит
	if (root->leftPtr != NULL && root->leftPtr->data == key)
	return root;

	if (root->rightPtr != NULL && root->rightPtr->data == key)
	return root;


	// Поиск нужного узла
	if (key < root->data) prevSearch(root->leftPtr, key);
	else prevSearch(root->rightPtr, key);
}

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


//удаление
void delete(TREENODEPTR* root, int key)
{

	//проверка на пустоту дерева
	if (*root == NULL)
	{
		printf("\nДерево уже пустое, удалять нечего!\n");
		return;
	}

	else
	{
		TREENODEPTR current = NULL, temp = NULL, m = NULL;

		//если удаляемый нами эл-т - корень
		if ((*root)->data == key)
		{
			//если дерево только из корня
			if ((*root)->leftPtr == NULL && (*root)->rightPtr == NULL)
			{
				*root = NULL;
				printf("\nДерево теперь пустое!\n");
				return;
			}

			//если у корня есть листья по обе стороны
			else if ((*root)->leftPtr != NULL && (*root)->rightPtr != NULL)
			{
				current = minim((*root)->rightPtr); //то к минимальному из правой ветки прикрепляем левую ветку корня
				current->leftPtr = (*root)->leftPtr;

				temp = (*root);
				(*root) = (*root)->rightPtr; //и смещаем корень вправо
				free(temp);
				return;
			}

			//если всё дерево уходит вправо
			else if ((*root)->leftPtr == NULL)
			{
				temp = (*root);
				(*root) = (*root)->rightPtr; //то прикреплять нечего, просто смещаем корень вправо
				free(temp);
				return;
			}

			//если всё дерево уходит влево
			else if ((*root)->rightPtr == NULL)
			{
				temp = (*root);
				(*root) = (*root)->leftPtr; //то прикреплять нечего, просто смещаем корень влево
				free(temp);
				return;
			}

			return;
		}


		// если удаляемый элемент - лист
		TREENODEPTR l = NULL; //m-предок l-удаляемый элемент
		int flag; //будет 1, если l - это левый потомок и 0, если l- это правый потомок, нужно для 3 случая

		m = prevSearch(*root, key); //находим предка удаляемого эл-та

		if (!m)
		{
			printf("\nЗапрашиваемое на удаление число не найдено в дереве!\n");
			return;
		}


		if (m->leftPtr!=NULL && m->leftPtr->data == key)//нашли удаляемый элемент, поставили флаг
		{
			l = m->leftPtr;
			flag = 1;
		}

		if (m->rightPtr != NULL && m->rightPtr->data == key)//нашли удаляемый элемент, поставили флаг
		{
			l = m->rightPtr;
			flag = 0;
		}

		// 1 случай - лист без потомков
		if ((l->leftPtr == NULL) && (l->rightPtr == NULL))
		{
			if (flag == 1) m->leftPtr = NULL; //если флаг 1, т.е. лист слева от предка, то зануляем левую связь предка
			else m->rightPtr = NULL; // иначе правую
			free(l);
		}

		// 2 случай, 1 вариант - поддерево справа
		else if ((l->leftPtr == NULL) && (l->rightPtr != NULL))
		{
			if (flag) m->leftPtr = l->rightPtr;
			else m->rightPtr = l->rightPtr;
			free(l);
		}

		// 2 случай, 2 вариант - поддерево слева
		else if ((l->leftPtr != NULL) && (l->rightPtr == NULL))
		{
			if (flag) m->leftPtr = l->leftPtr;
			else m->rightPtr = l->leftPtr;
			free(l);
		}

		// 3 случай - два потомка: и слева, и справа
		else if ((l->leftPtr != NULL) && (l->rightPtr != NULL))
		{
			current = minim(l->rightPtr);
			current->leftPtr = l->leftPtr;

			if (flag) m->leftPtr = l->rightPtr;
			else m->rightPtr = l->rightPtr;

			free(l);
		}
	}
	return;
}

void level_elems(TREENODEPTR treePtr, int level, int current) { //six func (input -- floor -- element) 
	if (treePtr != NULL) {
		current++;
		if (current == level) {
			printf("Elem value: %d\n", treePtr->data);
			return;
		}
		else if (current < level) {
			level_elems(treePtr->rightPtr, level, current);
			level_elems(treePtr->leftPtr, level, current);
		}
	}
}

void doubleDelete(TREENODEPTR* current)
{
	TREENODEPTR temp = NULL;

	while ((*current)->leftPtr != NULL && (*current)->data == (*current)->leftPtr->data) //если значение в обрабатываемом равно значению в левом потомке
	{
		temp = (*current)->leftPtr; //сохраняем потомка для чистки
		(*current)->leftPtr = (*current)->leftPtr->leftPtr; //смещаем связь
		free(temp); //чистим 
	}

	if ((*current)->leftPtr != NULL)
	{
		doubleDelete(&((*current)->leftPtr));
	}

	if ((*current)->rightPtr != NULL)
	{
		doubleDelete(&((*current)->rightPtr));
	}
}
