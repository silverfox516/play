#include <stdio.h>
#include <search.h>
#include <string.h>

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

	return 0;
}
