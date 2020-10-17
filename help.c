#include "help.h"

int show_h1()
{
    car_t cars[MAX_COUNT];
    int count = 0;
    FILE *f;
    f = fopen("test.txt", "r");
    read_file(cars, &count, f);
    char brand[] = "BMW";
    int min_cost = 0, max_cost = 1000;
    key_t keys[MAX_COUNT];
    int key_count = 0;
    make_key_table(cars, keys, count, &key_count, brand, min_cost, max_cost);
    key_quick_sort(keys, 0, key_count - 1);
    printf("Таблица остортирована по марке BMW в ценовом диапазоне от 0 до 1000.\n");
    printf("Отсортированная таблица ключей:\n");
    printf("┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓\n");
    printf("┃    № в исх. ┃   № в таб.  ┃     Ключ    ┃\n"
           "┃   таблице   ┃   ключей    ┃             ┃\n");
    for (int i = 0; i < key_count; i++)
    {
        printf("┣━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
        printf("┃%13d┃%13d┃%13d┃\n", keys[i].index  + 1, i, keys[i].field + 1);
    }
    printf("┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┛\n");
    printf("Исходная таблица:\n");
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━┳"
		"━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━┓\n");
	printf("┃       Марка      ┃       Страна       ┃     Цена    ┃      Цвет      ┃  Состояние  ┃ Гарантия ┃"
		" Год выпуска ┃    Пробег    ┃  Ремонты   ┃ Собственники ┃   №  ┃\n");
	for (int i = 0; i < count; i++)
	{
		printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━╋"
			"━━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━┫\n");
		printf("┃%-18s┃%-20s┃%-13d┃%-16s┃", cars[i].brand, cars[i].country, cars[i].cost, cars[i].color);
		if (!cars[i].new)
		{
			printf("%s┃%-10d┃", "Новая        ", cars[i].condition.warranty);
			printf("     ---     ┃      ---     ┃    ---     ┃     ---      ┃");
		}
		else
		{
			printf("%s┃%s┃", "Не новая     ", "    ---   ");
			printf("%-13d┃%-14d┃%-12d┃%-14d┃", cars[i].condition.used.year, cars[i].condition.used.mileage,
				cars[i].condition.used.repairs, cars[i].condition.used.owners);
		}
		printf("%6d┃\n", i + 1);
	}
	printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━┻"
		"━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━┛\n");
    fclose(f);
    return EXIT_SUCCESS;
}

int show_h2()
{
    car_t cars[MAX_COUNT];
    car_t sorted[MAX_COUNT];
    int s_count = 0;
    int count = 0;
    FILE *f;
    f = fopen("test.txt", "r");
    read_file(cars, &count, f);
    char brand[] = "BMW";
    int min_cost = 0, max_cost = 1000;
    make_table(cars, sorted, count, &s_count, brand, min_cost, max_cost);
    quick_sort(sorted, 0, s_count - 1);
    match(cars, sorted, count, s_count, brand, min_cost, max_cost);
    printf("Таблица остортирована по марке BMW в ценовом диапазоне от 0 до 1000.\n");
    printf("Исходная таблица:\n");
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━┳"
		"━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━┓\n");
	printf("┃       Марка      ┃       Страна       ┃     Цена    ┃      Цвет      ┃  Состояние  ┃ Гарантия ┃"
		" Год выпуска ┃    Пробег    ┃  Ремонты   ┃ Собственники ┃   №  ┃\n");
	for (int i = 0; i < count; i++)
	{
		printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━╋"
			"━━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━┫\n");
		printf("┃%-18s┃%-20s┃%-13d┃%-16s┃", cars[i].brand, cars[i].country, cars[i].cost, cars[i].color);
		if (!cars[i].new)
		{
			printf("%s┃%-10d┃", "Новая        ", cars[i].condition.warranty);
			printf("     ---     ┃      ---     ┃    ---     ┃     ---      ┃");
		}
		else
		{
			printf("%s┃%s┃", "Не новая     ", "    ---   ");
			printf("%-13d┃%-14d┃%-12d┃%-14d┃", cars[i].condition.used.year, cars[i].condition.used.mileage,
				cars[i].condition.used.repairs, cars[i].condition.used.owners);
		}
		printf("%6d┃\n", i + 1);
	}
	printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━┻"
		"━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━┛\n");
    fclose(f);
    return EXIT_SUCCESS;
}

int show_h3()
{
    car_t cars[MAX_COUNT];
    int count = 0;
    FILE *f;
    f = fopen("test.txt", "r");
    read_file(cars, &count, f);
    char brand[] = "BMW";
    int min_cost = 0, max_cost = 1000;
    key_t keys[MAX_COUNT];
    int key_count = 0;
	make_key_table(cars, keys, count, &key_count, brand, min_cost, max_cost);
    key_quick_sort(keys, 0, key_count - 1);
    match_key(keys, key_count, cars, count);
    printf("\nОтсортированная исходная таблица с использованием таблицы ключей:\n");
    printf("Таблица остортирована по марке BMW в ценовом диапазоне от 0 до 1000.\n");
    printf("Исходная таблица:\n");
    printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━┳"
		"━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━┓\n");
	printf("┃       Марка      ┃       Страна       ┃     Цена    ┃      Цвет      ┃  Состояние  ┃ Гарантия ┃"
		" Год выпуска ┃    Пробег    ┃  Ремонты   ┃ Собственники ┃   №  ┃\n");
	for (int i = 0; i < count; i++)
	{
		printf("┣━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━╋"
			"━━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━━━━━━━╋━━━━━━━━━━━━━━╋━━━━━━┫\n");
		printf("┃%-18s┃%-20s┃%-13d┃%-16s┃", cars[i].brand, cars[i].country, cars[i].cost, cars[i].color);
		if (!cars[i].new)
		{
			printf("%s┃%-10d┃", "Новая        ", cars[i].condition.warranty);
			printf("     ---     ┃      ---     ┃    ---     ┃     ---      ┃");
		}
		else
		{
			printf("%s┃%s┃", "Не новая     ", "    ---   ");
			printf("%-13d┃%-14d┃%-12d┃%-14d┃", cars[i].condition.used.year, cars[i].condition.used.mileage,
				cars[i].condition.used.repairs, cars[i].condition.used.owners);
		}
		printf("%6d┃\n", i + 1);
	}
	printf("┗━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━┻"
		"━━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━━━━━━━┻━━━━━━━━━━━━━━┻━━━━━━┛\n");
    return EXIT_SUCCESS;
}

void shuffle(car_t cars[], int count);

int show_h4(void)
{
    FILE *f;
    f = fopen("sort8000.txt", "r");
    car_t cars[MAX_COUNT];
    int count = 0;
    key_t key[MAX_COUNT];
    int key_count = 0;
    read_file(cars, &count, f);
    struct timeval ta, te;
    int64_t time_k = 0;
    //char *brand = "BMW";
    int min_cost = 0;
    int max_cost = 5000;
    for (int i = 0; i < 100; i++)
    {
        shuffle(cars, count);
        gettimeofday(&ta, NULL);
        slow_sort(cars, count);
        gettimeofday(&te, NULL);
        time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("Медленная сортировка исходной таблицы: %lld микросекунд\n", time_k / 100);
    time_k = 0;
    make_key_table(cars, key, count, &key_count, "BMW", min_cost, max_cost);
    for (int i = 0; i < 100; i++)
    {
        shuffle(cars, count);
        gettimeofday(&ta, NULL);
        make_key_table(cars, key, count, &key_count, "BMW", min_cost, max_cost);
        key_slow_sort(key, key_count);
        //match_key(key, key_count, cars, count);
        gettimeofday(&te, NULL);
        time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("Медленная сортировка с использованием таблицы ключей: %lld микросекунд\n", time_k / 100);
    time_k = 0;
    for (int i = 0; i < 1000; i++)
    {
        shuffle(cars, count);
        //make_table(copy, sorted, count, &s_count, brand, min_cost, max_cost);
        gettimeofday(&ta, NULL);
        quick_sort(cars, 0, count - 1);
        gettimeofday(&te, NULL);
        // match(copy, sorted, count, s_count, brand, min_cost, max_cost);
        time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("Быстрая сортировка исходной таблицы: %lld микросекунд\n", time_k / 1000);
    time_k = 0;
    for (int i = 0; i < 1000; i++)
    {
        shuffle(cars, count);
        gettimeofday(&ta, NULL);
        make_key_table(cars, key, count, &key_count, "BMW", min_cost, max_cost);
        key_quick_sort(key, 0, key_count - 1);
       // match_key(key, key_count, cars, count);
        gettimeofday(&te, NULL);
        time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("Быстрая сортировка с использованием таблицы ключей: %lld микросекунд\n", time_k / 1000);
    return EXIT_SUCCESS;
}

void shuffle(car_t cars[], int count)
{
    car_t buf;
    for (int i = 0; i < count - 4; i += 4)
    {
        buf = cars[i];
        cars[i] = cars[i + 2];
        cars[i + 2] = buf;
        buf = cars[i + 3];
        cars[i + 3] = cars[i + 1];
        cars[i + 1] = buf;
    }
}