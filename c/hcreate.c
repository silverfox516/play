#include <stdio.h>
#include <search.h>

int main(void)
{
	ENTRY item;
	ENTRY *result;

	// man 설명에서는 검색 테이블의 요소 개수를 5000개로 했지만 
	// 여기 샘플에서는 테스트를 위해 2개로 지정했습니다.
	// 실제 코드에서는 넉넉한 크기로 지정해 주십시오.

	hcreate(2);

	item.key = "1st";
	item.data = "forum.falinux.com";
	hsearch(item, ENTER);


	item.key = "2nd";
	item.data = "www.falinux.com";
	hsearch(item, ENTER);

	item.key = "3rd";
	item.data = "jwmx.tistory.com";
	hsearch(item, ENTER);


	item.key = "4th";
	item.data = "Embedded Linux Programming";
	hsearch(item, ENTER);

	item.key = "5th";
	item.data = "GCC Compiler";
	hsearch(item, ENTER);

	// 여기서부터는 자료 찾기

	item.key = "1st";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	item.key = "2nd";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	item.key = "3rd";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	item.key = "4th";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	item.key = "5th";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	item.key = "6th";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	item.key = "7th";
	if (NULL != (result = hsearch(item, FIND)))
		printf( "%s key data is %s\n", result->key, (char *)result->data);

	hdestroy();
	return 0;
}
