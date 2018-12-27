#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *cmp1, const void *cmp2)
{
	return strcmp((char *)cmp1, (char *)cmp2);
}

#define  SIZE_TABLE     10
#define  SIZE_ITEM      100

int main(void)
{
	char table[SIZE_TABLE][SIZE_ITEM] = {
		"forum",
		"falinux",
		"com",
		"jwmx",
		"Linux",
		"GCC",
		"Programming"
	};

	int ndx;

	for (ndx  = 0; ndx < SIZE_TABLE; ndx++)
		printf("%s\n", table[ndx]);   

	printf("소트 후\n");

	qsort(table, SIZE_TABLE, SIZE_ITEM, compare);

	for (ndx  = 0; ndx < SIZE_TABLE; ndx++)
		printf( "%s\n", table[ndx]);   

	return 0;
}
