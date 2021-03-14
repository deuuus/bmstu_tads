#include "io.h"

/*
Функция считывает данные о машинах из файла и записывает их в динамический массив.
\params [in] cars - массив элементов типа car_t
\params [in] count - указатель на количество введенных машин
\params [in] f - файловая переменная, с помощью которой производится чтение
\params [out] - код ошибки
*/
int read_file(car_t *cars, int *count, FILE *f)
{
    car_t car;
	int rc = EXIT_SUCCESS;
    if (f == NULL)
    {
        printf("\nВведите имя файла, содержащее сведения о машинах: ");
        char file[MAX_STR_LEN];
        if ((rc = read_str(file)))
			return rc;
        f = fopen(file, "r");
        if (!f)
        {
            printf("\nОшибка во время открытия файла. Возможно, файла с таким именем не существует.\n\n");
            return READ_ERR;
        }
        *count = 0;
    }
    char str[MAX_STR_LEN], ch;
    int temp;
	rc = EXIT_SUCCESS;
    while (!rc)
    {
        if ((rc = readf_str(car.brand, f)))
        {
            if (rc == -1 && (f))
                return EXIT_SUCCESS;
            return rc;
        }
        if ((rc = readf_str(car.country, f)))
            return rc;
        if ((rc = readf_uint(&car.cost, f)))
            return rc;
        if ((rc = readf_str(car.color, f)))
            return rc;
        if ((rc = readf_uint(&temp, f)))
            return rc;
        car.new = 0;
        rc = readf_str(str, f);
        if (strlen(str) != 0)
        {
            if (rc)
                return rc;
            car.new = 1;
            car.condition.used.year = temp;
            if (sscanf(str, "%d%c", &car.condition.used.mileage, &ch) != 1 || car.condition.used.mileage <= 0)
                return VALUE_ERR;
            if ((rc = readf_uint(&car.condition.used.repairs, f)))
                return rc;
            if ((rc = readf_uint(&car.condition.used.owners, f)))
                return rc;
            rc = readf_str(str, f);
        }
        else
            car.condition.warranty = temp;
        if (strlen(str) != 0)
            return VALUE_ERR;
        cars[(*count)++] = car;
        rc = EXIT_SUCCESS;
    }
    if (*count == 0)
    {
        printf("\nОшибка: пустой файл.\n\n");
        return EMPTY_FILE_ERR;
    }
	fclose(f);
	return EXIT_SUCCESS;
}

/*
Функция реализует печать данных на экран. Для этого во время работы запрашивается имя файла с данными.
\params [out] - код ошибки
*/
int print()
{
	int rc;
	car_t cars[MAX_COUNT];
	int count = 0;
	FILE *f;
	f = NULL;
	if ((rc = read_file(cars, &count, f)))
    	return rc;
	printf("┏━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┳━━━━━━━━━━┳"
		"━━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━━━━━━━┳━━━━━━━━━━━━━━┳━━━━━━┓\n");
	printf("┃       Марка      ┃       Страна       ┃   Цена, ₽   ┃      Цвет      ┃  Состояние  ┃Гарантия,г┃"
		" Год выпуска ┃   Пробег,км  ┃  Ремонты   ┃ Собственники ┃   №  ┃\n");
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

/*
Функция считывает строку и определяет ее корректность(она не должна превышать максимальную длину или быть пустой).
\params [in] str - массив символов
\params [out] - код ошибки
*/
int read_str(char str[])
{
	if (!fgets(str, MAX_STR_LEN, stdin))
	{
        printf("\nОшибка чтения марки автомобиля. Следуйте справке.\n\n");
		return READ_ERR;
	}
	if (str[strlen(str) - 1] != '\n')
	{
        printf("\nОшибка: превышена максимальная длина строки.\n\n");
		return VALUE_ERR;
	}
	else
		str[strlen(str) - 1] = '\0';
	if (strlen(str) == 0)
	{
        printf("\nОшибка: пустая строка.\n\n");
		return VALUE_ERR;
	}
	return EXIT_SUCCESS;
}

/*
Функция считывает число и определяет ее корректность(оно должно быть целым и неотрицательным).
\params [in] num - указатель на число для записи данных
\params [out] - код ошибки
*/
int read_uint(int *num)
{
	int rc;
	char str[MAX_STR_LEN], ch;
	if ((rc = read_str(str)))
		return rc;
	if (sscanf(str, "%d%c", num, &ch) != 1 || *num < 0 || ch != '\0')
	{
        printf("Ошибка: должно быть введено целое неотрицатальное число.\n");
		return VALUE_ERR;
	}
	return EXIT_SUCCESS;
}

/*
Функция считывает строку из файла и определяет ее корректность(она не должна превышать максимальную длину или быть пустой).
\params [in] str - массив символов
\params [in] f - файловая переменная, с помощью которой производится чтение
\params [out] - код ошибки
*/
int readf_str(char str[], FILE *f)
{
    if (!fgets(str, MAX_STR_LEN, f))
		return READ_ERR;
    if (str[strlen(str) - 1] != '\n')
          return READ_ERR;
    else
        str[strlen(str) - 1] = '\0';
    if (strlen(str) == 0)
	    return VALUE_ERR;
    return EXIT_SUCCESS;
}

/*
Функция считывает число и определяет ее корректность(оно должно быть целым и неотрицательным).
\params [in] num - указатель на число для записи данных
\params [in] f - файловая переменная, с помощью которой производится чтение
\params [out] - код ошибки
*/
int readf_uint(int *num, FILE *f)
{
    int rc;
    char str[MAX_STR_LEN], ch;
    if ((rc = readf_str(str, f)))
        return rc;
    if (sscanf(str, "%d%c", num, &ch) != 1 || *num < 0)
        return VALUE_ERR;
    return EXIT_SUCCESS;
}