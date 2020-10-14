#include "readf.h"

int read_file(car_t *cars, int *count, FILE *f)
{
    car_t car;
    if (!f)
    {
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
        if (strlen(file) == 0)
        {
            printf("Ошибка: пустое имя файла.");
            return VALUE_ERR;
        }
        if (!f)
        {
            printf("Ошибка во время открытия файла. Возможно, файла с таким названием не существует.");
            return READ_ERR;
        }
    }
    int rc = EXIT_SUCCESS;
    char str[MAX_STR_LEN], ch;
    int temp;
    while (!rc)
    {
        if ((rc = readf_str(car.brand, f)))
        {
            if (rc == -1 && feof(f))
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
	return EXIT_SUCCESS;
}

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

void print(car_t cars[], int count, FILE *f)
{
	int rc;
	if (!(rc = read_file(cars, &count, f)))
    {
        printf("\n--------------------------------------------------------------------");
        printf("\n|Maшина №|       Марка      |       Страна-производитель     |   Цена   |  Цвет  | Состояние|Гарантия|Год выпуска|Пробег|Кол-во "
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
}