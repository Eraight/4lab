#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
	if (r != NULL && r->data == data)
		return r;
	if (r == NULL) {
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("Ошибка выделения памяти");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l) {

	if (r == NULL) {
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++) {
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}

int search_tree(struct Node* r, int itemSearch, int consta) {
	int status = consta;
	if (r->data == itemSearch)
		return 1;
	if (r->right != NULL && itemSearch < r->data)
		status = search_tree(r->right, itemSearch, status);
	if (r->left != NULL && itemSearch > r->data)
		status = search_tree(r->left, itemSearch, status);
	return status;
}

int main() {
	setlocale(LC_ALL, "");
	int D, start = 1;

	struct Node* root = NULL;
	printf("<-1 - окончание построения дерева\n");
	while (start) {
		printf("Введите число: ");
		scanf_s("%d", &D);
		if (D <= -1) {
			printf("Построение дерева окончено\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);

	}

	print_tree(root, 0);

	while (1) {
		printf("\nИскать элемент? (0/1) ");
		switch (_getch()) {
		case '1':
			printf("Поиск элемента...\nВведите искомое число: ");
			(void)scanf("%d", &start);
			printf("%s", !search_tree(root, start, 0) ? "Отсутствует искомый элемент или дерево" : "Элемент найден");
			break;
		case '0':
			return 0;
		}
	}
}