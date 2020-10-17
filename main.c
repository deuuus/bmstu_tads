#include "read.h"
#include "sort.h"
#include "info.h"
#include "help.h"

int main()
{
	show_info();
	int act = 0, rc, count = 0;
	car_t cars[MAX_COUNT];
	FILE *f = NULL;
	while (act != EXIT)
	{
		if ((rc = choose_action(&act)))
			return rc;
		if (act == PRINT)
			print();
		if (act == SORT)
			sort(cars, count, f);
		if (act == ADD)
			add(cars, &count, f);
		if (act == HELP)
			choose_help(&act);
		if (act == DEL)
			del(cars, &count, f);
		if (act == H1)
			show_h1();
		if (act == H2)
			show_h2();
		if (act == H3)
			show_h3();
		if (act == H4)
			show_h4();
		if (act == EXIT)
			printf("Завершение работы.");
	}
 	return EXIT_SUCCESS;
}
