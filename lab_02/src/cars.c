#include "cars.h"   

/*
Функция считывает данные о машиных из файла и фильтрует полученный массив соответвии с критериями, введенными пользователем.
\params [in] cars - массив элементов типа car_t
\params [in] count - количество введенных машин
\params [in] f - файловая переменная, с помощью которой производится чтение
\params [out] - код ошибки
*/
int sort(car_t cars[], int count, FILE *f)
{
	int rc;
    f = NULL;
    if ((rc = read_file(cars, &count, f)))
    {
        printf("\nОшибка во время чтения файла.\n\n");
        return rc;
    }
    car_t cars_to_sort[count];
    for (int i = 0; i < count; i++)
    {   
        cars_to_sort[i] = cars[i];
    }
	printf("\nВведите марку автомобиля, по которой будет производиться сортировка.\n\nМарка: ");
	char brand[MAX_STR_LEN];
	if ((rc = read_str(brand)))
		return rc;
	printf("\nВведите ценовой диапазон, по которому будет производиться сортировка.\n\nМинимальная цена в ₽: ");
	int min_cost, max_cost;
	if ((rc = read_uint(&min_cost)))
		return rc;
	printf("\nМаксимальная цена в ₽: ");
	if ((rc = read_uint(&max_cost)))
		return rc;
	if (min_cost >= max_cost)
	{
		printf("\nОшибка: недопустимый ценовой диапазон.\n\n");
		return VALUE_ERR;
	}
	printf("\nДанные для поиска успешно введены. Происходит сортировка...\n\n");
	key_t key[count];
	int key_count = 0;
	make_key_table(cars_to_sort, key, count, &key_count, brand, min_cost, max_cost);
	if (key_count == 0)
	{
		printf("\nНе найдено ни одной машины с заданными параметрами.\n\n");
		return VALUE_ERR;
	}
    key_quick_sort(key, 0, key_count - 1);
    print_request(key, key_count, brand, min_cost, max_cost);
    match_key(key, key_count, cars_to_sort, count);
	return EXIT_SUCCESS;
}

/*
Функция считает разность двух чисел и возвращает ее.
\params [in] i - указатель на первое число
\params [in] j - указатель на второе число
\params [out] - разность первого и второго чисел
*/
int cmp(const int *i, const int *j)
{
    return *i - *j;
}

/*
Функция восстанавливает исходную таблицу по отсортированной таблице ключей.
\params [in] keys - массив элементов типа key_t
\params [in] key_n - количество элементов массива key
\params [in] cars - массив элементов типа car_t
\params [in] cars_n - количество элементов массива cars
*/
void match_key(key_t keys[], int key_n, car_t cars[], int cars_n)
{
    car_t buf[key_n];
    for (int i = 0; i < key_n; i++)
        buf[i] = cars[keys[i].index];
    int a[key_n];
    for (int i = 0; i < key_n; i++)
        a[i] = keys[i].index;
    qsort(a, key_n, sizeof(int), (int(*) (const void *, const void *)) cmp);
    for (int i = 0; i < key_n; i++)
        cars[a[i]] = buf[i];
}

/*
Функция восстанавливает исходную таблицу по копии исходной отсортированной таблицы.
\params [in] cars - массив элементов типа car_t
\params [in] count - количество элементов в массиве cars
\params [in] sorted - остортированный массив элементов типа car_t
\params [in] s_count - количество элементов в массиве sorted
\params [in] brand - строка, содержащая марку машины для поиска
\params [in] min_cost - нижняя граница диапазона цен для поиска
\params [in] max_cost - верхняя граница диапазона цен для поиска
*/
void match(car_t cars[], car_t sorted[], int count, int s_count, char brand[], int min_cost, int max_cost)
{
    s_count = 0;
    for (int i = 0; i < count; i++)
        if (suit(cars[i], brand, min_cost, max_cost) == 0)
            cars[i] = sorted[s_count++];
}

/*
Функция реализует медленную сортировку массива типа car_t.
\params [in] a - массив элементов типа car_t
\params [in] n - количество элементов в массиве a
*/
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

/*
Функция восстанавливает исходную таблицу по копии исходной отсортированной таблицы.
\params [in] cars - массив элементов типа car_t
\params [in] count - количество элементов в массиве cars
\params [in] sorted - остортированный массив элементов типа car_t
\params [in] s_count - количество элементов в массиве sorted
\params [in] brand - строка, содержащая марку машины для поиска
\params [in] min_cost - нижняя граница диапазона цен для поиска
\params [in] max_cost - верхняя граница диапазона цен для поиска
*/
void make_key_table(car_t cars[], key_t key[], int count, int *key_count, const char *brand, int min_cost, int max_cost)
{
    int k = 0;
	for (int i = 0; i < count; i++)
    {
		if (!strcmp(cars[i].brand, brand) && cars[i].cost >= min_cost && cars[i].cost <= max_cost
		    && cars[i].new && !cars[i].condition.used.repairs && cars[i].condition.used.owners == 2)
		{
			key[k].field = cars[i].cost;
			key[k].index = i;
			k += 1;
		}
    }
    *key_count = k;
}

void make_table(car_t cars[], car_t sorted[], int count, int *s_count, char brand[], int min_cost, int max_cost)
{
    for (int i = 0; i < count; i++)
		if (suit(cars[i], brand, min_cost, max_cost) == 0)
		{
			sorted[(*s_count)++] = cars[i];
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

int suit(car_t car, char brand[], int min_cost, int max_cost)
{
    if (!strcmp(car.brand, brand) && car.cost >= min_cost && car.cost <= max_cost
		&& car.new && !car.condition.used.repairs && car.condition.used.owners == 2)
            return EXIT_SUCCESS;
    else
        return EXIT_FAILURE; 
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
		"отсутствием ремонта в диапазоне цен от %d₽ до %d₽:\n", brand, min_cost, max_cost);
	for (int i = 0; i < n; i++)
		printf("%d) %d\n", i + 1, a[i].field);
}

int del(car_t cars[], int *count, FILE *f)
{
    int rc;
    f = NULL;
    *count = 0;
    printf("\nВведите имя файла, содержащее сведения о машинах: ");
	char file[MAX_STR_LEN];
	if ((rc = read_str(file)))
        return rc;
    f = fopen(file, "r");
    if ((rc = read_file(cars, count, f)))
    {
        printf("\nОшибка чтения файла.\n\n");
        return rc;
    }
    if (*count == 0)
    {
        printf("\nОшибка: невозможно произвести удаление - файл пустой.\n\n");
        return DEL_ERR;
    }
    int ans, res;
    char str[MAX_STR_LEN];
    printf("\nВведите поле для удаления:\n1) Марка\n2) Страна-производитель\n3) Цена\n4) Цвет"
        "\n5) Новизна\n6) Гарантия\n7) Год выпуска\n"
        "8) Пробег\n9) Кол-во ремонтов\n10) Кол-во собственников\n\nВаш ответ: ");
    if (scanf("%d", &ans) != 1 || (ans < 1 && ans > 10) || getchar() != (int)'\n')
    {
        printf("\nОшибка ввода: необходимо ввести номер одного из предложенных вариантов.\n\n");
		return READ_ERR;
    }
    if (ans == 1)
    {
        printf("Введите марку: ");
        if ((rc = read_str(str)))
            return rc;
        f = fopen(file, "w");
        del_brand(cars, count, str);
    }
    if (ans == 2)
    {
        printf("Введите страну-производитель: ");
        if ((rc = read_str(str)))
            return rc;
        f = fopen(file, "w");
        del_country(cars, count, str);
    }
    if (ans == 3)
    {
        printf("Введите цену: ");
        if ((rc = read_uint(&res)))
            return rc;
        f = fopen(file, "w");
        del_cost(cars, count, res);
    }
    if (ans == 4)
    {
        printf("Введите цвет: ");
        if ((rc = read_str(str)))
            return rc;
        f = fopen(file, "w");
        del_color(cars, count, str);
    }
    if (ans == 5)
    {
        printf("Какие машины нужно удалить?\n1) Новые\n2) Не новые\n\nОтвет: ");
        if (scanf("%d", &res) != 1 || (res != 1 && res != 2) || getchar() != (int)'\n')
        {
            printf("\nОшибка ввода: необходимо ввести номер одного из предложенных вариантов.\n\n");
            return VALUE_ERR;
        }
        res--;
        f = fopen(file, "w");
        del_new(cars, count, res);
    }
    if (ans == 6)
    {
        printf("Введите гарантию в годах: ");
        if ((rc = read_uint(&res)))
            return rc;
        f = fopen(file, "w");
        del_warranty(cars, count, res);
    }
    if (ans == 7)
    {
        printf("Введите год выпуска: ");
        if ((rc = read_uint(&res)))
            return rc;
        f = fopen(file, "w");
        del_year(cars, count, res);
    }
    if (ans == 8)
    {
        printf("Введите пробег: ");
        if ((rc = read_uint(&res)))
            return rc;
        f = fopen(file, "w");
        del_mileage(cars, count, res);
    }
    if (ans == 9)
    {
        printf("Введите кол-во ремонтов: ");
        if ((rc = read_uint(&res)))
            return rc;
        f = fopen(file, "w");
        del_repairs(cars, count, res);
    }
    if (ans == 10)
    {
        printf("Введите кол-во собственников: ");
        if ((rc = read_uint(&res)))
            return rc;
        f = fopen(file, "w");
        del_owners(cars, count, res);
    }
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
    fclose(f);
    printf("\nДанные удалены.\n\n");
    return EXIT_SUCCESS;
}

int add(car_t cars[], int *count, FILE *f)
{
    int rc;
    *count = 0;
    printf("\nВведите имя файла, содержащее сведения о машинах: ");
	char file[MAX_STR_LEN];
	if ((rc = read_str(file)))
        return rc;
    f = fopen(file, "r");
    if (!f)
    {
        printf("\nОшибка во время открытия файла.\n\n");
        return READ_ERR;
    }
    if ((rc = read_file(cars, count, f)))
        return rc;
    car_t car;
    if (*count == MAX_COUNT)
    {
        printf("\nНевозможно добавить запись - достигнут максимальный размер файла.\n\n");
        return EXIT_SUCCESS;
    }
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
    printf("Эта машина новая?\n1)Да\n2)Нет\n\nОтвет: ");
    if (scanf("%d", &car.new) != 1 || (car.new != 1 && car.new != 2) || getchar() != (int)'\n')
    {
        printf("\nОшибка ввода: необходимо ввести номер одного из предложенных вариантов.\n\n");
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
        printf("Введите год выпуска автомобиля(в годах): ");
        if ((rc = read_uint(&car.condition.used.year)))
            return rc;
        printf("Введите пробег автомобиля(в км): ");
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
    fclose(f);
    f = fopen(file, "a+");
    fprintf(f, "%s\n%s\n%d\n%s\n", car.brand, car.country, car.cost, car.color);
    if (car.new == 0)
        fprintf(f, "%d\n\n", car.condition.warranty);
    else
    {
        fprintf(f, "%d\n%d\n%d\n%d\n\n", car.condition.used.year, car.condition.used.mileage,
            car.condition.used.repairs, car.condition.used.owners);
    }
    printf("\nИнформация о машине успешно добавлена.\n\n");
    fclose(f);
    return EXIT_SUCCESS;
}

void del_brand(car_t cars[], int *count, char brand[])
{
    car_t res[MAX_COUNT];
    int n = 0;
    for (int i = 0; i < *count; i++)
        if (strcmp(cars[i].brand, brand))
            res[n++] = cars[i];
    for (int i = 0; i < n; i++)
        cars[i] = res[i];
    *count = n;
}

void del_country(car_t cars[], int *count, char country[])
{
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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
    car_t res[MAX_COUNT];
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