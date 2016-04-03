#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N	5

typedef struct t {
	struct t *child[N];
	int	value;
} T;

void make_child(T *node, int level) {
	if (level < 1)
		return;
	for (int i = 0; i != N; ++i) {
		node->child[i] = (T *)malloc(sizeof(T));
		bzero(node->child[i], sizeof(T));
		node->child[i]->value = i+1;
		make_child(node->child[i], level - 1);
	}
}

void make_tree(T **node, int level) {
	if (level < 0)
		return;

	*node = (T *)malloc(sizeof(T));
	bzero(*node, sizeof(T));

	for (int i = 0; i != N; ++i) {
		make_tree(&((*node)->child[i]), level-1);
		if (level > 0)
			(*node)->child[i]->value = i+1;
	}
}

void display_tree(T *node) {
	if (!node)
		return;

	printf("%d", node->value);
	if(node->child[0]) {
		printf("(");
		for (int i = 0; i != N; ++i) {
			display_tree(node->child[i]);
			if (i+1 != N && node->child[i+1])
				printf(",");
		}
		printf(")");
	}
}

void destroy_tree(T *node) {
	if (!node)
		return;

	for (int i = 0; i != N; ++i) {
		destroy_tree(node->child[i]);
		node->child[i] = NULL;
	}
	free(node);
	node = NULL;
}	

static int g_cnt = 0;
void traverse(T *node, int total) {
	if (!node)
		return;

	total += node->value;
	if (total == N) {
		++g_cnt;
	}
	for (int i=0; i != N; ++i)
		traverse(node->child[i], total);
}	

int main() {
	T	*head;

	//make_tree(&head, N);
	head = (T *)malloc(sizeof(T));
	bzero(head, sizeof(T));
	make_child(head, N);
	display_tree(head);
	putchar('\n');
	traverse(head, 0);
	printf("%d\n", g_cnt);
	destroy_tree(head);
}
