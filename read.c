#include "read.h"

int read_str(char str[])
{
	if (!fgets(str, MAX_STR_LEN, stdin))
	{
        printf("Ошибка чтения марки автомобиля. Следуйте справке.");
		return READ_ERR;
	}
	if (str[strlen(str) - 1] != '\n')
	{
        printf("Ошибка: превышена максимальная длина строки.");
		return VALUE_ERR;
	}
	else
		str[strlen(str) - 1] = '\0';
	if (strlen(str) == 0)
	{
        printf("Ошибка: пустая строка.");
		return VALUE_ERR;
	}
	return EXIT_SUCCESS;
}

int read_uint(int *num)
{
	int rc;
	char str[MAX_STR_LEN], ch;
	if ((rc = read_str(str)))
		return rc;
	if (sscanf(str, "%d%c", num, &ch) != 1 || *num < 0 || ch != '\0')
	{
        printf("Ошибка: должно быть введено целое неотрицатальное число.");
		return VALUE_ERR;
	}
	return EXIT_SUCCESS;
}

int read(car_t *cars, int *count)
{
	int lim, rc;
	car_t car;
	printf("Введите количество машин, о которых вы хотите ввести информацию:\n");
	if (scanf("%d", &lim) != 1 || lim <= 0 || getchar() != (int)'\n')
	{
		printf("Ошибка ввода: количество должно быть целым неотрицательным числом.");
		return VALUE_ERR;
	}
	while (*count < lim)
	{
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
            printf("Введите пробег автомобиля в км: ");
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
	}
	if (*count != lim)
		return READ_ERR;
	printf("Данные успешно введены.\n"
			"--------------------------------------------------\n");
	return EXIT_SUCCESS;
}