#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_TABLE	10
#define SIZE_ITEM	20

int compare(const void *cmp1, const void *cmp2)
{
	return strcmp((char *)cmp1, (char *)cmp2);
}

int main(void)
{
	char table[SIZE_TABLE][SIZE_ITEM] = { "3com", "2embedded", "1falinux", "3forum", "4jwmx", "5linux" };
	char *ptr;

	ptr = (char *)bsearch("3forum", table, SIZE_TABLE, SIZE_ITEM, compare);
	printf("str = %s\n", ptr);

	ptr = (char *)bsearch("1embedded", table, SIZE_TABLE, SIZE_ITEM, compare);
	printf("str = %s\n", ptr);

	ptr = (char *)bsearch("jwjw", table, SIZE_TABLE, SIZE_ITEM, compare);
	printf("str = %s\n", ptr);

	return 0;
}
