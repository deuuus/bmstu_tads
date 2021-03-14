#include "analys.h"

void shuffle_key(key_t keys[], int key_count);
void shuffle(car_t cars[], int count);
void cycle(car_t cars[], int count, key_t keys[], int key_count, int repeats, int size);

int sorted_key_unsorted_table()
{
    car_t cars[MAX_COUNT];
    int count = 0;
    FILE *f;
    f = fopen("data.txt", "r");
    read_file(cars, &count, f);
    char *brand = NULL;
    strcpy(brand, cars[0].brand);
    int min_cost = 0, max_cost = 1000;
    key_t keys[MAX_COUNT];
    int key_count = 0;
    make_key_table(cars, keys, count, &key_count, brand, min_cost, max_cost);
    key_quick_sort(keys, 0, key_count - 1);
    printf("\nТаблица остортирована по марке %s в ценовом диапазоне от 0 до 1000.\n", brand);
    printf("\nОтсортированная таблица ключей:\n");
    printf("┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓\n");
    printf("┃    № в исх. ┃   № в таб.  ┃     Ключ    ┃\n"
           "┃   таблице   ┃   ключей    ┃             ┃\n");
    for (int i = 0; i < key_count; i++)
    {
        printf("┣━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
        printf("┃%13d┃%13d┃%13d┃\n", keys[i].index  + 1, i + 1, keys[i].field);
    }
    printf("┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┛\n");
    printf("\nИсходная таблица:\n");
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

int sorted_table()
{
    car_t cars[MAX_COUNT];
    car_t sorted[MAX_COUNT];
    int s_count = 0;
    int count = 0;
    FILE *f;
    f = fopen("data.txt", "r");
    read_file(cars, &count, f);
    char brand[] = "BMW";
    int min_cost = 0, max_cost = 1000;
    make_table(cars, sorted, count, &s_count, brand, min_cost, max_cost);
    quick_sort(sorted, 0, s_count - 1);
    match(cars, sorted, count, s_count, brand, min_cost, max_cost);
    printf("\nТаблица остортирована по марке BMW в ценовом диапазоне от 0 до 1000.\n");
    printf("\nИсходная таблица:\n");
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

int sorted_key_sorted_table()
{
    car_t cars[MAX_COUNT];
    int count = 0;
    FILE *f;
    f = fopen("data.txt", "r");
    read_file(cars, &count, f);
    char brand[] = "BMW";
    int min_cost = 0, max_cost = 1000;
    key_t keys[MAX_COUNT];
    int key_count = 0;
	make_key_table(cars, keys, count, &key_count, brand, min_cost, max_cost);
    key_quick_sort(keys, 0, key_count - 1);
    match_key(keys, key_count, cars, count);
    printf("\nТаблица остортирована по марке BMW в ценовом диапазоне от 0 до 1000.\n");
    printf("\nОтсортированная таблица ключей:\n");
    printf("┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓\n");
    printf("┃    № в исх. ┃   № в таб.  ┃     Ключ    ┃\n"
           "┃   таблице   ┃   ключей    ┃             ┃\n");
    for (int i = 0; i < key_count; i++)
    {
        printf("┣━━━━━━━━━━━━━╋━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫\n");
        printf("┃%13d┃%13d┃%13d┃\n", keys[i].index  + 1, i + 1, keys[i].field);
    }
    printf("┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┛\n");
    printf("\nИсходная таблица:\n");
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

void cycle(car_t cars[], int count, key_t keys[], int key_count, int repeats, int size)
{
    struct timeval ta, te;
    size_t time_k1 = 0, time_k2 = 0, time_k3 = 0, time_k4 = 0;
    for (int i = 0; i < repeats; i++)
    {
        shuffle(cars, count);
        gettimeofday(&ta, NULL);
        slow_sort(cars, count);
        gettimeofday(&te, NULL);
        time_k1 += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("┃%16d┃%15lld┃%15lld", size, time_k1 / repeats, sizeof(cars[0]) * size);
    time_k1 = 0;
    for (int i = 0; i < repeats; i++)
    {
        shuffle_key(keys, key_count);
        gettimeofday(&ta, NULL);
        key_slow_sort(keys, key_count);
        gettimeofday(&te, NULL);
        time_k2 += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("┃%15lld┃%15lld", time_k2 / repeats, (sizeof(cars[0]) + sizeof(keys[0])) * size);
    time_k2 = 0;
    for (int i = 0; i < repeats; i++)
    {
        shuffle(cars, count);
        gettimeofday(&ta, NULL);
        quick_sort(cars, 0, count - 1);
        gettimeofday(&te, NULL);
        time_k3 += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("┃%15lld┃%15lld", time_k3/repeats, sizeof(cars[0]) * size);
    time_k4 = 0;
    for (int i = 0; i < repeats; i++)
    {
        shuffle_key(keys, key_count);
        gettimeofday(&ta, NULL);
        key_quick_sort(keys, 0, key_count - 1);
        gettimeofday(&te, NULL);
        time_k4 += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
    }
    printf("┃%15lld┃%15lld┃\n", time_k4/repeats, (sizeof(cars[0]) + sizeof(keys[0])) * size);
}

void measures(void)
{
    FILE *f;
    printf("┏━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("┃                ┃      Медленная сортировка     ┃      Медленная сортировка     ┃      Быстрая сортировка       ┃       Быстрая сортировка      ┃\n");
    printf("┃   Количество   ┃    исходной таблицы (O(n^2))  ┃   с таблицей ключей (O(n^2))  ┃  исходной таблицы (O(n*long)) ┃  с таблицей ключей(O(n*logn)) ┃\n");
    printf("┃    записей     ┣━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┫\n");
    printf("┃                ┃    Время, ms  ┃   Память, b   ┃    Время, ms  ┃   Память, b   ┃    Время, ms  ┃   Память, b   ┃    Время, ms  ┃   Память, b   ┃\n");
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort100.txt", "r");
    car_t cars[MAX_COUNT];
    int count = 0;
    key_t key[MAX_COUNT];
    int key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 100);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort250.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 250);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort500.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 500);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort1000.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 1000);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort2000.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 2000);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort5000.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 5000);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort7500.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 7500);
    printf("┣━━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━╋━━━━━━━━━━━━━━━┫\n");
    f = fopen("shared/sort10000.txt", "r");
    count = 0;
    key_count = 0;
    read_file(cars, &count, f);
    fclose(f);
    make_key_table(cars, key, count, &key_count, "BMW", 100, 200);
    cycle(cars, count, key, key_count, 1000, 10000);
    printf("┗━━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┻━━━━━━━━━━━━━━━┛\n");
}

void shuffle(car_t cars[], int count)
{
    car_t buf;
    for (int i = 0; i < count - 4; i++)
    {
        buf = cars[i];
        cars[i] = cars[i + 2];
        cars[i + 2] = buf;
        buf = cars[i + 3];
        cars[i + 3] = cars[i + 1];
        cars[i + 1] = buf;
    }
}

void shuffle_key(key_t keys[], int key_count)
{
    key_t buf;
    for (int i = 0; i < key_count - 4; i += 4)
    {
        buf = keys[i];
        keys[i] = keys[i + 2];
        keys[i + 2] = buf;
        buf = keys[i + 3];
        keys[i + 3] = keys[i + 1];
        keys[i + 1] = buf;
    }
}