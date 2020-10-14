#include "sort.h"
#include <sys/time.h>
#include <inttypes.h>

int show_h4(void)
{
    int rc;
    int count = 0;
    car_t cars[MAX_COUNT];
    FILE *f;
    printf("\nВведите имя файла, содержащее сведения о машинах: ");
	char file[MAX_STR_LEN];
	if (!fgets(file, sizeof(file), stdin))
	{
        printf("Ошибка чтения имени файла.");
    	return READ_ERR;
    }
	if (file[strlen(file) - 1] != '\n')
	{
		printf("Ошибка ввода: превышена максимальная длина строки.");
		return VALUE_ERR;
	}
	else
		file[strlen(file) - 1] = '\0';
    f = fopen(file, "r");
    if ((rc = read_file(cars, &count, f)))
    {
        printf("Ошибка чтения файла.\n");
        return rc;
    }
    car_t origin[count];
    for (int i = 0; i < count; i++)
    {
        origin[i] = cars[i];
    }
    {
        struct timeval ta, te;
        int64_t time_k = 0;
        int mem = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < count; j++)
                cars[j] = origin[j];
            char brand[] = "BMW";
            int min_cost = 0;
            int max_cost = 1000;
            key_t key[count];
            int key_count = 0;
            gettimeofday(&ta, NULL);
            make_table(cars, key, count, &key_count, brand, min_cost, max_cost);
            slow_sort(cars, count);
            gettimeofday(&te, NULL);
            mem += sizeof(cars);
            time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
        }
        printf("Затрачиваемая память: %d байт\n", mem / 1000);
        printf("\nМедленная сортировка исходной таблицы: %lf миллисекунд\n\n", time_k / 1000.0);
    }
    {
        struct timeval ta, te;
        int64_t time_k = 0;
        int mem = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < count; j++)
                cars[j] = origin[j];
            char brand[] = "BMW";
            int min_cost = 0;
            int max_cost = 1000;
            key_t key[count];
            int key_count = 0;
            gettimeofday(&ta, NULL);
            make_table(cars, key, count, &key_count, brand, min_cost, max_cost);
            quick_sort(cars, 0, count - 1);
            gettimeofday(&te, NULL);
            mem += sizeof(cars);
            time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
        }
        printf("Затрачиваемая память: %d\n байт", mem / 1000);
        printf("\nБыстрая сортировка исходной таблицы: %lf миллисекунд\n\n", time_k / 1000.0);
    }
    {
        struct timeval ta, te;
        int64_t time_k = 0;
        int mem = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < count; j++)
                cars[j] = origin[j];
            char brand[] = "BMW";
            int min_cost = 0;
            int max_cost = 1000;
            key_t key[count];
            int key_count = 0;
            gettimeofday(&ta, NULL);
            make_table(cars, key, count, &key_count, brand, min_cost, max_cost);
            key_slow_sort(key, key_count);
            match(key, key_count, cars, count);
            gettimeofday(&te, NULL);
            mem += sizeof(key);
            time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
        }
        printf("Затрачиваемая память: %d байт\n", mem / 1000);
        printf("\nМедленная сортировка с использованием таблицы ключей: %lf миллисекунд\n\n", time_k / 1000.0);
    }
    {
        struct timeval ta, te;
        int64_t time_k = 0;
        int mem = 0;
        for (int i = 0; i < 1000; i++)
        {
            for (int j = 0; j < count; j++)
                cars[j] = origin[j];
            char brand[] = "BMW";
            int min_cost = 0;
            int max_cost = 1000;
            key_t key[count];
            int key_count = 0;
            gettimeofday(&ta, NULL);
            make_table(cars, key, count, &key_count, brand, min_cost, max_cost);
            key_quick_sort(key, 0, key_count - 1);
            match(key, key_count, cars, count);
            gettimeofday(&te, NULL);
            mem += sizeof(key);
            time_k += (te.tv_sec - ta.tv_sec) * 1000000LL + (te.tv_usec - ta.tv_usec);
        }
        printf("Затрачиваемая память: %d байт\n", mem / 1000);
        printf("\nБыстрая сортировка с использованием таблицы ключей: %lf миллисекунд\n\n", time_k / 1000.0);
    }
    return EXIT_SUCCESS;
}

int show_h1(car_t cars[], int *count, FILE *f)
{
    int rc;
    if ((rc = read_file(cars, count, f)))
    {
        printf("Ошибка во время чтения файла.\n");
    }
    int n = *count;
    car_t cars_to_sort[n];
    for (int i = 0; i < n; i++)
    {   
        cars_to_sort[i] = cars[i];
    }
    printf("Введите марку автомобиля, по которой будет производиться сортировка.\nМарка: ");
	char brand[MAX_STR_LEN];
	if ((rc = read_str(brand)))
		return rc;
	printf("Введите ценовой диапазон, по которому будет производиться сортировка.\nМинимальная цена: ");
	int min_cost, max_cost;
	if ((rc = read_uint(&min_cost)))
		return rc;
	printf("Максимальная цена: ");
	if ((rc = read_uint(&max_cost)))
		return rc;
	if (min_cost >= max_cost)
	{
		printf("Ошибка: недопустимый ценовой диапазон.");
		return VALUE_ERR;
	}
	printf("Данные для поиска успешно введены. Происходит сортировка...\n");
	key_t key[n];
	int key_count = 0;
	make_table(cars_to_sort, key, n, &key_count, brand, min_cost, max_cost);
	if (key_count == 0)
	{
		printf("Не найдено ни одной машины с заданными параметрами.");
		return VALUE_ERR;
	}
    key_quick_sort(key, 0, key_count - 1);
    printf("\nОтсортированная таблица ключей:\n");
    for (int i = 0; i < key_count; i++)
        printf("Ключ: %d\nИндекс в исходной таблице: %d\n", key[i].field, key[i].index);
    return EXIT_SUCCESS;
}

int show_h2(car_t cars[], int *count, FILE *f)
{
    int rc;
    if ((rc = read_file(cars, count, f)))
    {
        printf("Ошибка во время чтения файла.\n");
    }
    int n = *count;
    car_t cars_to_sort[n];
    for (int i = 0; i < n; i++)
    {   
        cars_to_sort[i] = cars[i];
    }
    printf("Введите марку автомобиля, по которой будет производиться сортировка.\nМарка: ");
	char brand[MAX_STR_LEN];
	if ((rc = read_str(brand)))
		return rc;
	printf("Введите ценовой диапазон, по которому будет производиться сортировка.\nМинимальная цена: ");
	int min_cost, max_cost;
	if ((rc = read_uint(&min_cost)))
		return rc;
	printf("Максимальная цена: ");
	if ((rc = read_uint(&max_cost)))
		return rc;
	if (min_cost >= max_cost)
	{
		printf("Ошибка: недопустимый ценовой диапазон.");
		return VALUE_ERR;
	}
	printf("Данные для поиска успешно введены. Происходит сортировка...\n");
    printf("\nКоличество машин = %d\n", n);
	key_t key[n];
	int key_count = 0;
	make_table(cars_to_sort, key, n, &key_count, brand, min_cost, max_cost);
	if (key_count == 0)
	{
		printf("Не найдено ни одной машины с заданными параметрами.");
		return VALUE_ERR;
	}
    quick_sort(cars_to_sort, 0, n - 1);
    printf("\nОтсортированная исходная таблица:\n");
    prt(cars_to_sort, n);
    return EXIT_SUCCESS;
}

void prt(car_t cars[], int count)
{
    printf("\n--------------------------------------------------------------------");
    printf("\n|Maшина №|Марка|Страна-производитель|Цена|Цвет|Состояние|Гарантия|Год выпуска|Пробег|Кол-во "
        "ремонтов|Кол-во собственников|\n");
        for (int i = 0; i < count; i++)
        {
            printf("\nМашина №%d:\n", i + 1);
            printf("Марка: %s\n", cars[i].brand);
            printf("Страна-производитель: %s\n", cars[i].country);
            printf("Цена: %d\n", cars[i].cost);
            printf("Цвет: %s\n", cars[i].color);
            printf("Состояние: ");
            if (cars[i].new == 0)
            {
                printf("Новая\n");
                printf("Гарантия(в годах): %d\n\n", cars[i].condition.warranty);
            }
            else
            {
                printf("Не новая\n");
                printf("Год выпуска: %d\n", cars[i].condition.used.year);
                printf("Пробег: %d\n", cars[i].condition.used.mileage);
                printf("Кол-во ремонтов: %d\n", cars[i].condition.used.repairs);
                printf("Кол-во собственников: %d\n", cars[i].condition.used.owners);
            }
        }
        printf("--------------------------------------------------------------------\n");
}

int show_h3(car_t cars[], int *count, FILE *f)
{
    int rc;
    if ((rc = read_file(cars, count, f)))
    {
        printf("Ошибка во время чтения файла.\n");
    }
    int n = *count;
    car_t cars_to_sort[n];
    for (int i = 0; i < n; i++)
    {   
        cars_to_sort[i] = cars[i];
    }
    printf("Введите марку автомобиля, по которой будет производиться сортировка.\nМарка: ");
	char brand[MAX_STR_LEN];
	if ((rc = read_str(brand)))
		return rc;
	printf("Введите ценовой диапазон, по которому будет производиться сортировка.\nМинимальная цена: ");
	int min_cost, max_cost;
	if ((rc = read_uint(&min_cost)))
		return rc;
	printf("Максимальная цена: ");
	if ((rc = read_uint(&max_cost)))
		return rc;
	if (min_cost >= max_cost)
	{
		printf("Ошибка: недопустимый ценовой диапазон.");
		return VALUE_ERR;
	}
	printf("Данные для поиска успешно введены. Происходит сортировка...\n");
	key_t key[n];
	int key_count = 0;
	make_table(cars_to_sort, key, n, &key_count, brand, min_cost, max_cost);
	if (key_count == 0)
	{
		printf("Не найдено ни одной машины с заданными параметрами.");
		return VALUE_ERR;
	}
    key_quick_sort(key, 0, key_count - 1);
    match(key, key_count, cars_to_sort, n);
    printf("\nОтсортированная исходная таблица с использованием таблицы ключей:\n");
    prt(cars_to_sort, n);
    return EXIT_SUCCESS;
}

int del(car_t cars[], int *count, FILE *f)
{
    int rc;
    printf("\nВведите имя файла, содержащее сведения о машинах: ");
	char file[MAX_STR_LEN];
	if (!fgets(file, sizeof(file), stdin))
	{
        printf("Ошибка чтения имени файла.");
    	return READ_ERR;
    }
	if (file[strlen(file) - 1] != '\n')
	{
		printf("Ошибка ввода: превышена максимальная длина строки.");
		return VALUE_ERR;
	}
	else
		file[strlen(file) - 1] = '\0';
    f = fopen(file, "r");
    if ((rc = read_file(cars, count, f)))
    {
        printf("Ошибка чтения файла.\n");
        return rc;
    }
    fclose(f);
    f = fopen(file, "w");
    int ans, res;
    char str[MAX_STR_LEN];
    printf("Введите поле для удаления:\n1) Марка\n2) Страна-производитель\n3) Цена\n4) Цвет"
        "\n5) Новизна\nДополнительные параметры в случае новизны:\n6) Гарантия\nИначе\n7) Год выпуска\n"
        "8) Пробег\n9) Кол-во ремонтов\n10) Кол-во собственников\n\nВаш ответ: ");
    if (scanf("%d", &ans) != 1 || (ans < 1 && ans > 10) || getchar() != (int)'\n')
    {
        printf("Ошибка ввода: необходимо ввести номер одного из предложенных вариантов.\n");
		return READ_ERR;
    }
    if (ans == 1)
    {
        printf("Введите марку: ");
        if ((rc = read_str(str)))
            return rc;
        del_brand(cars, count, str);
    }
    if (ans == 2)
    {
        printf("Введите страну-производитель: ");
        if ((rc = read_str(str)))
            return rc;
        del_country(cars, count, str);
    }
    if (ans == 3)
    {
        printf("Введите цену: ");
        if ((rc = read_uint(&res)))
            return rc;
        del_cost(cars, count, res);
    }
    if (ans == 4)
    {
        printf("Введите цвет: ");
        if ((rc = read_str(str)))
            return rc;
        del_color(cars, count, str);
    }
    if (ans == 5)
    {
        printf("Машина новая?\n1)Да\n2)Нет\n\nОтвет: ");
        if (scanf("%d", &res) != 1 || (res != 1 && res != 2) || getchar() != (int)'\n')
        {
            printf("Ошибка ввода: необходимо ввести номер одного из предложенных вариантов.");
            return VALUE_ERR;
        }
        res--;
        del_new(cars, count, res);
    }
    if (ans == 6)
    {
        printf("Введите гарантию в годах: ");
        if ((rc = read_uint(&res)))
            return rc;
        del_warranty(cars, count, res);
    }
    if (ans == 7)
    {
        printf("Введите год выпуска: ");
        if ((rc = read_uint(&res)))
            return rc;
        del_year(cars, count, res);
    }
    if (ans == 8)
    {
        printf("Введите пробег: ");
        if ((rc = read_uint(&res)))
            return rc;
        del_mileage(cars, count, res);
    }
    if (ans == 9)
    {
        printf("Введите кол-во ремонтов: ");
        if ((rc = read_uint(&res)))
            return rc;
        del_repairs(cars, count, res);
    }
    if (ans == 10)
    {
        printf("Введите кол-во собственников: ");
        if ((rc = read_uint(&res)))
            return rc;
        del_owners(cars, count, res);
    }
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < *count; i++)
    {
        fprintf(f, "%s\n%s\n%d\n%s\n", cars[i].brand, cars[i].country, cars[i].cost, cars[i].color);
        if (cars[i].new == 0)
            fprintf(f, "%d\n\n", cars[i].condition.warranty);
        else
        {
            fprintf(f, "%d\n%d\n%d\n%d\n\n", cars[i].condition.used.year, cars[i].condition.used.mileage,
                cars[i].condition.used.repairs, cars[i].condition.used.owners);
        }
    }
    printf("Данные удалены. Чтобы сохранить изменения, выйдите из программы.\n");
    return EXIT_SUCCESS;
}

int add(car_t cars[], int *count, FILE *f)
{
    int rc;
    car_t car;
    if (*count == MAX_COUNT)
    {
        printf("Невозможно добавить запись - достигнут максимальный размер файла.\n");
        return EXIT_SUCCESS;
    }
    printf("\nВведите имя файла, содержащее сведения о машинах: ");
	char file[MAX_STR_LEN];
	if (!fgets(file, sizeof(file), stdin))
	{
        printf("Ошибка чтения имени файла.");
    	return READ_ERR;
    }
	if (file[strlen(file) - 1] != '\n')
	{
		printf("Ошибка ввода: превышена максимальная длина строки.");
		return VALUE_ERR;
	}
	else
		file[strlen(file) - 1] = '\0';
    f = fopen(file, "a+");
    printf("\nВвод информации о машине №%d\n\n", *count + 1);
    printf("Введите марку автомобиля: ");
    if ((rc = read_str(car.brand)))
        return rc;
    printf("Введите страну-производителя автомобиля: ");
    if ((rc = read_str(car.country)))
        return rc;
    printf("Введите цену автомобиля в рублях: ");
    if ((rc = read_uint(&car.cost)))
        return rc;
    printf("Введите цвет автомобиля: ");
	    if ((rc = read_str(car.color)))
		    return rc;
    printf("Ваша машина новая?\n1)Да\n2)Нет\n\nОтвет: ");
    if (scanf("%d", &car.new) != 1 || (car.new != 1 && car.new != 2) || getchar() != (int)'\n')
    {
        printf("Ошибка ввода: необходимо ввести номер одного из предложенных вариантов.");
        return VALUE_ERR;
    }
    car.new--;
    if (!car.new)
    {
        printf("Введите гарантию автомобиля(в годах): ");
        if ((rc = read_uint(&car.condition.warranty)))
            return rc;
    }
    else
    {
        printf("Введите год выпуска автомобиля: ");
        if ((rc = read_uint(&car.condition.used.year)))
            return rc;
        printf("Введите пробег автомобиля: ");
        if ((rc = read_uint(&car.condition.used.mileage)))
            return rc;
        printf("Введите количество ремонтов автомобиля: ");
        if ((rc = read_uint(&car.condition.used.repairs)))
            return rc;
        printf("Введите количество собственников: ");
        if ((rc = read_uint(&car.condition.used.owners)))
            return rc;
    }
    cars[(*count)++] = car;
    fprintf(f, "%s\n%s\n%d\n%s\n", car.brand, car.country, car.cost, car.color);
    if (car.new == 0)
        fprintf(f, "%d\n\n", car.condition.warranty);
    else
    {
        fprintf(f, "%d\n%d\n%d\n%d\n\n", car.condition.used.year, car.condition.used.mileage,
            car.condition.used.repairs, car.condition.used.owners);
    }
    printf("Информация о машине успешно добавлена.\n");
    return EXIT_SUCCESS;
}

int sort(car_t cars[], int count, FILE *f)
{
	int rc;
    f = NULL;
    if ((rc = read_file(cars, &count, f)))
    {
        printf("Ошибка во время чтения файла.\n");
        return rc;
    }
    car_t cars_to_sort[count];
    for (int i = 0; i < count; i++)
    {   
        cars_to_sort[i] = cars[i];
    }
	printf("Введите марку автомобиля, по которой будет производиться сортировка.\nМарка: ");
	char brand[MAX_STR_LEN];
	if ((rc = read_str(brand)))
		return rc;
	printf("Введите ценовой диапазон, по которому будет производиться сортировка.\nМинимальная цена: ");
	int min_cost, max_cost;
	if ((rc = read_uint(&min_cost)))
		return rc;
	printf("Максимальная цена: ");
	if ((rc = read_uint(&max_cost)))
		return rc;
	if (min_cost >= max_cost)
	{
		printf("Ошибка: недопустимый ценовой диапазон.");
		return VALUE_ERR;
	}
	printf("Данные для поиска успешно введены. Происходит сортировка...\n");
	key_t key[count];
	int key_count = 0;
	make_table(cars_to_sort, key, count, &key_count, brand, min_cost, max_cost);
	if (key_count == 0)
	{
		printf("Не найдено ни одной машины с заданными параметрами.");
		return VALUE_ERR;
	}
    key_quick_sort(key, 0, key_count - 1);
    print_request(key, key_count, brand, min_cost, max_cost);
    match(key, key_count, cars_to_sort, count);
	return EXIT_SUCCESS;
}

void match(key_t key[], int key_n, car_t cars[], int cars_n)
{
    car_t buf[key_n];
    for (int i = 0; i < key_n; i++)
        buf[i] = cars[key[i].index];
    for (int i = 0; i < key_n - 1; i++)
		for (int j = 0; j < key_n - i - 1; j++)
			if (key[j].index > key[j + 1].index)
            {
                key_t buf = key[j];
                key[j] = key[j + 1];
                key[j + 1] = buf;
            }
    for (int i = 0; i < key_n; i++)
        cars[key[i].index] = buf[i];
}

void slow_sort(car_t a[], int n)
{
    for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (a[j].cost > a[j + 1].cost)
            {
                car_t buf = a[j];
                a[j] = a[j + 1];
                a[j + 1] = buf;
            }
}

void make_table(car_t cars[], key_t key[], int count, int *key_count, char brand[], int min_cost, int max_cost)
{
	for (int i = 0; i < count; i++)
		if (!strcmp(cars[i].brand, brand) && cars[i].cost >= min_cost && cars[i].cost <= max_cost
			&& cars[i].new && !cars[i].condition.used.repairs && cars[i].condition.used.owners == 2)
		{
			key[*key_count].field = cars[i].cost;
			key[*key_count].index = i;
			*key_count += 1;
		}
}

void key_quick_sort(key_t a[], int b, int e)
{
    int l = b, r = e;
    key_t mid = a[(l + r) / 2];
    while (l <= r)
    {
        while (a[l].field < mid.field)
            l++;
        while (a[r].field > mid.field)
            r--;
        if (l <= r)
        {
            key_t buf = a[l];
            a[l] = a[r];
            a[r] = buf;
            l++;
            r--;
        }
    }
    if (b < r)
        key_quick_sort(a, b, r);
    if (e > l)
        key_quick_sort(a, l, e);
}

void quick_sort(car_t a[], int b, int e)
{
    int l = b, r = e;
    car_t mid = a[(l + r) / 2];
    while (l <= r)
    {
        while (a[l].cost < mid.cost)
            l++;
        while (a[r].cost > mid.cost)
            r--;
        if (l <= r)
        {
            car_t buf = a[l];
            a[l] = a[r];
            a[r] = buf;
            l++;
            r--;
        }
    }
    if (b < r)
        quick_sort(a, b, r);
    if (e > l)
        quick_sort(a, l, e);
}

void key_slow_sort(key_t a[], int n)
{
	for (int i = 0; i < n - 1; i++)
		for (int j = 0; j < n - i - 1; j++)
			if (a[j].field > a[j + 1].field)
			{
				key_t buf = a[j];
                a[j] = a[j + 1];
                a[j + 1] = buf;
			}
}

void print_request(key_t a[], int n, const char brand[], int min_cost, int max_cost)
{
	printf("\nЦены не новых машин марки %s с одним предыдущим собственником, "
		"отсутствием ремонта в диапазоне цен от %d до %d:\n", brand, min_cost, max_cost);
	for (int i = 0; i < n; i++)
		printf("%d) %d\n", i + 1, a[i].field);
}

void del_brand(car_t cars[], int *count, char brand[])
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(cars[i].brand, brand))
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_country(car_t cars[], int *count, char country[])
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(cars[i].country, country))
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_color(car_t cars[], int *count, char color[])
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (strcmp(cars[i].color, color))
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_cost(car_t cars[], int *count, int cost)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].cost != cost)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_new(car_t cars[], int *count, int new)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].new != new)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_warranty(car_t cars[], int *count, int war)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].new == 0 && cars[i].condition.warranty != war)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_year(car_t cars[], int *count, int year)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].new == 1 && cars[i].condition.used.year != year)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_mileage(car_t cars[], int *count, int mileage)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].new == 1 && cars[i].condition.used.mileage != mileage)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_repairs(car_t cars[], int *count, int repairs)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].new == 1 && cars[i].condition.used.repairs != repairs)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_owners(car_t cars[], int *count, int owners)
{
    car_t res[*count];
    int n = 0;
    for (int i = 0; i < *count; i++)
    {
        if (cars[i].new == 1 && cars[i].condition.used.owners != owners)
            res[n++] = cars[i];
    }
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}