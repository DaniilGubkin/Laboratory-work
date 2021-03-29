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

void freeTree(TREENODEPTR* treePtr); //функция №2

void inOrder(TREENODEPTR);	//функция №3	/*По возрастанию*/
void preOrder(TREENODEPTR);
void postOrder(TREENODEPTR);

void doubleDelete(TREENODEPTR* current); //функция №4

void delete(TREENODEPTR* root, int key); //функция №5
TREENODEPTR search(TREENODEPTR root, int key);
TREENODEPTR prevSearch(TREENODEPTR root, int key);
TREENODEPTR minim(TREENODEPTR root);

void level_elems(TREENODEPTR treePtr, int level, int current);//функция №6

void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr); //функция №7

int height(TREENODEPTR treePtr, int max); //функция №8

void insertNode(TREENODEPTR*, int);
void instructions();


int main() {
	TREENODEPTR rootPtr = NULL;
	setlocale(LC_ALL, "Rus");
	int choice, answer, n, i, item;
	printf("Добро пожаловать в программу по работе с деревьями!\n"
		"Предлагаем Вам создать свое дерево, но для начала выберете желаемый способ:\n"
		"1. Ввод с клавиатуры\n"
		"2. Случайный ввод\n");
	printf("? ");
	scanf_s("%d", &choice);
	printf("\n Принято! Сколько элементов желаете?\n");
	printf("? ");
	scanf_s("%d", &n);
	switch (choice)
	{
	case 1:
		printf("\nВаше дерево:\n");
		for (i = 0; i < n; i++)
		{
			scanf_s("%d", &item);
			insertNode(&rootPtr, item);
		}
		break;
	case 2:
		srand((unsigned int)time(NULL));
		int a, b;
		printf("\nЗадайте верхнюю границу рандома:");
		scanf_s("%d", &b);
		printf("Задайте нижнюю границу рандома:");
		scanf_s("%d", &a);
		printf("\nВаше дерево:\n");
		for (i = 0; i < n; i++)
		{
			item = a + rand() % (b - a + 1);
			printf("%3d", item);
			insertNode(&rootPtr, item);
		}
		break;
	default:
		printf("\nОшибка ввода!\n");
		break;
	}

	instructions();
	printf("? ");
	scanf_s("%d", &answer);
	while (answer != 7) {
		switch (answer)
		{
		case 0:
			instructions();
			break;
		case 1:
			printf("\n\nПрямой обход:\n");
			preOrder(rootPtr);
			printf("\n\nОбратный обход:\n");
			inOrder(rootPtr);
			printf("\n\nКонцевой обход:\n");
			postOrder(rootPtr);
			break;
		case 2:
			for (int level = 1; level <= height(rootPtr, 0); level++)
			{
				printf("%d этаж: ", level);
				level_elems(rootPtr, level, 0);
				printf("\n");
			}
			break;
		case 3:
			//копирование
			break;
		case 4:
			printf("Высота дерева равна : %d\n\n", height(rootPtr, 0));
			break;
		case 5:
			//удаление элементов
			break;
		case 6:
			if (rootPtr != NULL)
			{
				freeTree(&rootPtr);
				printf("Дерево удалено!");
			}
			else
				printf("Дерево пусто!");
			break;
		default:
			printf("\nОшибка ввода!");
			instructions();
			break;
		}
		printf("\n\n? ");
		scanf_s("%d", &answer);
	}
	printf("\nЗавершение работы...\n");
	return 0;

}


void freeTree(TREENODEPTR* treePtr)
{
	if ((*treePtr)->leftPtr)   freeTree(&((*treePtr)->leftPtr));
	if ((*treePtr)->rightPtr)  freeTree(&((*treePtr)->rightPtr));
	free(*treePtr);
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


		if (m->leftPtr != NULL && m->leftPtr->data == key)//нашли удаляемый элемент, поставили флаг
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

// Минимальный элемент дерева
TREENODEPTR minim(TREENODEPTR root)
{
	TREENODEPTR l = root;
	while (l->leftPtr != NULL)
		l = l->leftPtr;
	return l;
}


void level_elems(TREENODEPTR treePtr, int level, int current)
{ //six func (input -- floor -- element) 

	if (treePtr != NULL) {
		current++;
		if (current == level) {
			printf("%d ", treePtr->data);
			return;
		}
		else if (current < level) {
			level_elems(treePtr->rightPtr, level, current);
			level_elems(treePtr->leftPtr, level, current);
		}
	}
}


void copyBinaryTree(TREENODEPTR* root, TREENODEPTR* treePtr)
{
	if (*root == NULL) {
		*root = malloc(sizeof(TREENODE));			/*Остановка рекурсии*/
		if (*root != NULL) {
			(*root)->leftPtr = NULL; /*Ставим число в нужное место, и две ветви отводим от этой ячейки и зануляем их*/
			(*root)->rightPtr = NULL;
		}
		else
			printf("No memore available.\n"); /*Защита от утечки памяти*/
	}
	(*root)->data = (*treePtr)->data;
	if ((*treePtr)->leftPtr != NULL)
		copyBinaryTree(&((*root)->leftPtr), &((*treePtr)->leftPtr));
	if ((*treePtr)->rightPtr != NULL)
		copyBinaryTree(&((*root)->rightPtr), &((*treePtr)->rightPtr));

}


int height(TREENODEPTR treePtr, int max)
{
	max++;
	int max1;
	int max2;
	if (treePtr->leftPtr != NULL)
		max1 = height(treePtr->leftPtr, max);
	else
		max1 = max;
	if (treePtr->rightPtr != NULL)
		max2 = height(treePtr->rightPtr, max);
	else
		max2 = max;
	if (max1 > max2)
		max = max1;
	else
		max = max2;
	return max;
}


void insertNode(TREENODEPTR* treePtr, int value)
{
	static int counter = 0;

	if (*treePtr == NULL) {
		*treePtr = malloc(sizeof(TREENODE));			/*Остановка рекурсии*/
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL; /*Ставим число в нужное место, и две ветви отводим от этой ячейки и зануляем их*/
			(*treePtr)->rightPtr = NULL;
		}
		else
			printf("%d not inserted. No memore available.\n", value); /*Защита от утечки памяти*/
		counter = 0;
	}
	else if (counter == 0 && value == (*treePtr)->data) //если первый раз, то хотим добавить верхушку
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //создаём новый элемент
		newPtr->data = value; //присваиваем значение
		newPtr->leftPtr = *treePtr; //прицепляем к нему 
		newPtr->rightPtr = (*treePtr)->rightPtr; //всю праввую ветку верхушки перецепляем
		(*treePtr)->rightPtr = NULL;
		*treePtr = newPtr; //теперь верхушка - новый элемент
	}
	else if ((*treePtr)->leftPtr && (*treePtr)->leftPtr->data == value) //если такой же элемент нашёлся у левого потомка обрабатываемого элемента
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //создаём новый элемент
		newPtr->data = value; //присваиваем значение
		newPtr->rightPtr = (*treePtr)->leftPtr->rightPtr; //перекинули правую ветку от потомка к новому эл-ту
		(*treePtr)->leftPtr->rightPtr = NULL;
		newPtr->leftPtr = (*treePtr)->leftPtr; //присоединили левого потомка обрабатываемого к новому элементу
		(*treePtr)->leftPtr = newPtr; //прицепили новый элемент к обрабатываемому 

	}
	else if ((*treePtr)->rightPtr && (*treePtr)->rightPtr->data == value) //если такой же элемент нашёлся у правого потомка обрабатываемого элемента
	{
		TREENODEPTR newPtr = malloc(sizeof(TREENODE)); //создаём новый элемент
		newPtr->data = value; //присваиваем значение
		newPtr->rightPtr = (*treePtr)->rightPtr->rightPtr; //прицепляем правую ветку дубля (он же правый потомок обрабатываемого эл-та) к новому
		(*treePtr)->rightPtr->rightPtr = NULL;
		newPtr->leftPtr = (*treePtr)->rightPtr; //присоединяем дубль слева от нового
		(*treePtr)->rightPtr = newPtr; //прицепляем новый к обрабатываемому эл-ту
	}
	else if (value < (*treePtr)->data)
	{
		counter++;
		insertNode(&((*treePtr)->leftPtr), value);		/*Обход влево и снова пытаемся найти нужное место*/
	}
	else if (value > (*treePtr)->data)
	{
		counter++;
		insertNode(&((*treePtr)->rightPtr), value);/*Обход вправа и снова пытаемся найти нужное место*/
	}
}

void instructions() {
	printf("\n\nЧто желаете сделать?\n"
		"0. ВНИМАНИЕ! Нажав 0 можно всегда вызвать инструкцию!\n"
		"1. Обход дерева:прямой, обратный, концевой\n"
		"2. Поэтажный обход дерева\n"
		"3. Копирование дерева\n"
		"4. Опредление высоты дерева\n"
		"5. Удаление определенных элементов\n"
		"6. Удалить дерево\n"
		"7. Завершение работы\n");
}

