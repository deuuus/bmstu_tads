#include "codes.h"
#include "menu.h"
#include "io.h"
#include "matrix.h"
#include "analys.h"

int main(void)
{
    //eff();
    int act = EXIT_SUCCESS, rc;
    matrix_t matrix;
    vector_t vector, res;
    init_matrix(&matrix);
    init_vector(&vector);
    init_vector(&res);
    FILE *f = NULL;
    while (act != EXIT)
    {
        if ((rc = choose_action(&act)))
            return rc;
        if (act == INPUT)
        { 
            int ans;
            printf("Какой способ ввода Вам подходит?\n\n1) Вручную\n2) В форме трех объектов"
                "\n3) Чтение из файла\n\nВаш ответ: ");
            if (scanf("%d", &ans) != 1 || (ans != 1 && ans != 2 && ans != 3))
            {
                printf("Ошибка ввода команды: команда должна соответствовать одному из пунктов меню.\n");
                return ERR_MENU;
            }
            if (ans == 1)
            {
                printf("Какой способ ввода вручную Вам подходит?\n\n1) Поэлементно\n2) Построчно\n\nВаш ответ: ");
                if (scanf("%d", &ans) != 1 || (ans != 1 && ans != 2))
                {
                    printf("Ошибка ввода команды: команда должна соответствовать одному из пунктов меню.\n");
                    return ERR_MENU;
                }
                init_matrix(&matrix);
                init_vector(&vector);
                if (ans == 1 && (rc = index_usual_input(&matrix, &vector)))
                    return rc;
                if (ans == 2 && (rc = usual_input(&matrix, &vector)))
                    return rc;
            }
            else if (ans == 2 && (rc = input_objects(&matrix, &vector)))
                return rc;
            else if (ans == 3 && (rc = read_file(&matrix, &vector, &f)))
                return rc;
            printf("\nИнформация успешно введена.\n\n");
        }
        if (act == PRINT)
        {
            if (!matrix.a)
                printf("\nЧтобы вывести информацию, сначала нужно загрузить информацию.\n"
                    "Воспользуйтесь командой 1 из меню.\n\n");
            else
            {
                output_matrix(matrix);
                output_vector(vector);
            }
        }
        if (act == PROD)
        {
            init_vector(&res);
            if (!matrix.a)
                printf("\nЧтобы произвести расчет, необходимо ввести данные в систему.\n"
                    "Воспользуйтесь командой 1 из меню.\n\n");
            else if ((rc = prod(matrix, vector, &res)))
                return rc;
            else
            {
                printf("\nРезультат:");
                output_vector(res);
            }
        }
        if (act == INFO)
            show_info();
        if (act == ANALYS)
            analys();
        if (act == EXIT)
            printf("Завершение работы.");
    }
    return EXIT_SUCCESS;
}