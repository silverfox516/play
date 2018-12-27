#include <stdio.h>
#include <search.h>
#include <string.h>

#define SIZE_TABLE	5
#define SIZE_ITEM	100

int compare(const void *cmp1, const void *cmp2)
{
	return strcmp((char *)cmp1, (char *)cmp2);
}

int main(void)
{
	char table[SIZE_TABLE][SIZE_ITEM] = { "forum", "falinux", "com" };
	char *ptr;
	size_t count;
	int ndx;

	printf("------------------ 1\n");

	count = 3;
	ptr = (char *)lfind("forum", table, &count, SIZE_ITEM, compare);

	printf("str : %s\n", ptr);
	printf("cnt : %ld\n", count);
	for (ndx = 0; ndx < SIZE_TABLE; ndx++)
		printf("%d=%s\n", ndx, table[ndx]);

	printf("------------------ 2\n");

	count = 3;
	ptr = (char *)lfind("falinux", table, &count, SIZE_ITEM, compare);

	printf("str : %s\n", ptr);
	printf("cnt : %ld\n", count);
	for (ndx = 0; ndx < SIZE_TABLE; ndx++)
		printf("%d=%s\n", ndx, table[ndx]);

	return 0;
}
