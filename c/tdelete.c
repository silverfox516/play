#include <stdio.h>
#include <search.h>
#include <string.h>

void print_tree(const void *node, VISIT order, int level)
{
	char *str;

	str = *(char **)node;

	if ((postorder == order) ||
			(leaf == order))
		printf("%d %s\n", level, str);
}

int compare(const void *cmp1, const void *cmp2)
{
	return strcmp((char *)cmp1, (char *)cmp2);
}

int main(void)
{
	void *btree = NULL;
	void **ptr;
	char *str;

	tsearch("forum", &btree, compare);
	tsearch("falinux", &btree, compare);
	tsearch("com", &btree, compare);

	twalk(btree, print_tree);

	printf("----------------------------\n");

	ptr = tfind("forum", &btree, compare);
	if (ptr) {
		str = *(char **)ptr;
		printf("%s\n", str);
	}

	ptr = tfind("jwmx", &btree, compare);
	if (ptr) {
		str = *(char **)ptr;
		printf("%s\n", str);
	}

	twalk(btree, print_tree);

	printf("----------------------------\n");

	ptr = tdelete("forum", &btree, compare);
	if (ptr) {
		str = *(char **)ptr;
		printf("%s\n", str);
	}

	ptr = tdelete("jwmx", &btree, compare);
	if (ptr) {
		str = *(char **)ptr;
		printf("%s\n", str);
	}

	twalk(btree, print_tree);

	printf("----------------------------\n");


	return 0;
}
