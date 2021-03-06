#include <stdio.h>
#include <stdlib.h>
#include <search.h>

char *data[] = { "alpha", "bravo", "charlie", "delta",
	"echo", "foxtrot", "golf", "hotel", "india", "juliet",
	"kilo", "lima", "mike", "november", "oscar", "papa",
	"quebec", "remeo", "sierra", "tango", "uniform",
	"victor", "whisky", "x-ray", "yankee", "zulu"
};

int main(void)
{
	ENTRY e, *ep;
	int i;

	hcreate(30);

	for (i = 0; i < 24; i++) {
		e.key = data[i];
		e.data = (void *)i;

		ep = hsearch(e, ENTER);
		if (NULL == ep) {
			fprintf(stderr, "entry failed\n");
			exit(EXIT_FAILURE);
		}
	}

	for (i = 22; i < 26; i++) {
		e.key = data[i];

		ep = hsearch(e, FIND);
		printf("%9.9s -> %9.9s:%d\n", e.key, ep ? ep->key : "NULL", ep ? (int)(ep->data) : 0);
	}

	hdestroy();
	exit(EXIT_SUCCESS);
}
