#include "io.h"
#include "cars.h"
#include "menu.h"
#include "analys.h"

/*
Функция main запускает меню с командами интерфейса, описанными в модуле menu, 
и работает до тех пор, пока пользователь не введет команду "Выход".
\param [out] - код ошибки
\author Сироткина Полина ИУ7-36Б
\ndate 15.10.2020
*/
int main()
{
	int act = 0, rc, count = 0;
	car_t cars[MAX_COUNT];
	FILE *f = NULL;
	while (act != EXIT)
	{
		if ((rc = choose_action(&act)))
			return rc;
		if (act == INFO)
			show_info();
		if (act == PRINT)
			print();
		if (act == SORT)
			sort(cars, count, f);
		if (act == ADD)
			add(cars, &count, f);
		if (act == ANALYS && (rc = choose_analys(&act)))
			return rc;
		if (act == DEL)
			del(cars, &count, f);
		if (act == S_KEY_US_TABLE)
			sorted_key_unsorted_table();
		if (act == S_TABLE)
			sorted_table();
		if (act == S_KEY_S_TABLE)
			sorted_key_sorted_table();
		if (act == MEASURES)
			measures();
	}
 	return EXIT_SUCCESS;
}
