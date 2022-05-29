#include "my_file.h"

/*
В типизированной файле, хранящем инфу о легковых автомобилях: марка, номер, литраж и масса. 
Реализовать добавление в файл нового легкового автомобиля, 
сортировка по каждому из полей и удаление автомобилей литражем меньше 10 литров, 
добавление после каждой машины марки "Жигули" условной машины "Рино"
*/

int get_car_by_pos(FILE *f, cars *car, int pos)
{
	if (fseek(f, sizeof(cars) * pos, SEEK_SET) == 0)
		if (fread(car, sizeof(cars), 1, f) == 1)
			return EXIT_SUCCESS;
	return EXIT_FAILURE;
}

int put_car_by_pos(FILE *f, cars *car, int pos)
{
	if (fseek(f, sizeof(cars) * pos, SEEK_SET) == 0)
		if (fwrite(car, sizeof(cars), 1, f) == 1)
			return EXIT_SUCCESS;
	return EXIT_FAILURE;
}

int file_size(FILE *f, int *size)
{
	if (fseek(f, 0, SEEK_END) != 0)
        return EXIT_FAILURE;

    long rc = ftell(f);

    if (rc <= 0 || rc % (long) sizeof(int) != 0)
		return EXIT_FAILURE;

    *size = rc / sizeof(cars);

    return fseek(f, 0, SEEK_SET);

}

int delete_car(FILE *f, int pos, int size)
{
	cars car1, car2;
	for (int i = pos; i < size - 1; i++)
	{
		if (get_car_by_pos(f, &car1, i) || get_car_by_pos(f, &car2, i + 1))
			return EXIT_FAILURE;
		if (put_car_by_pos(f, &car1, i + 1) || put_car_by_pos(f, &car2, i))
			return EXIT_FAILURE;
	}
	ftruncate(fileno(f), (size - 1) * sizeof(cars));
	return EXIT_SUCCESS;
}

int file_delete_car(FILE *f)
{
	cars car;
	int size;

	if (file_size(f, &size))
		return EXIT_FAILURE;

	for (int i = 0; i < size; i++)
	{
		if (get_car_by_pos(f, &car, i))
			return EXIT_FAILURE;

		if (car.displacement < 10)
		{
			if (delete_car(f, i, size))
				return EXIT_FAILURE;
			--size;
		}
	}

	if (get_car_by_pos(f, &car, 0))
		return EXIT_FAILURE;

	if (car.displacement < 10)
	{
		if (delete_car(f, 0, size))
			return EXIT_FAILURE;
		--size;
	}

	return EXIT_SUCCESS;
}

int file_sort_by_field(FILE *f, char field[])
{
	cars car1, car2;
	int size;

	if (file_size(f, &size))
		return EXIT_FAILURE;

	if (strcmp(field, "b") == 0)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
			{
				if (get_car_by_pos(f, &car1, j) || get_car_by_pos(f, &car2, i))
					return EXIT_FAILURE;

				if (strcmp(car1.brand, car2.brand) < 0)
					if (put_car_by_pos(f, &car1, i) || put_car_by_pos(f, &car2, j))
						return EXIT_FAILURE;
			}
	}
	else if (strcmp(field, "n") == 0)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
			{
				if (get_car_by_pos(f, &car1, j) || get_car_by_pos(f, &car2, i))
					return EXIT_FAILURE;

				if (car1.number > car2.number)
					if (put_car_by_pos(f, &car1, i) || put_car_by_pos(f, &car2, j))
						return EXIT_FAILURE;
			}
	}
	else if (strcmp(field, "d") == 0)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
			{
				if (get_car_by_pos(f, &car1, j) || get_car_by_pos(f, &car2, i))
					return EXIT_FAILURE;

				if (car1.displacement > car2.displacement)
					if (put_car_by_pos(f, &car1, i) || put_car_by_pos(f, &car2, j))
						return EXIT_FAILURE;
			}
	}
	else if (strcmp(field, "w") == 0)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = i + 1; j < size; j++)
			{
				if (get_car_by_pos(f, &car1, j) || get_car_by_pos(f, &car2, i))
					return EXIT_FAILURE;

				if (car1.weight > car2.weight)
					if (put_car_by_pos(f, &car1, i) || put_car_by_pos(f, &car2, j))
						return EXIT_FAILURE;
			}
	}

	return EXIT_SUCCESS;
}



int str_scan(char brand[], int n)
{
	if (B_L >= MAX_B_L)
		return EXIT_FAILURE;

	char tmp[MAX_B_L];

	if (fgets(tmp, n + 1, stdin) == NULL)
		return EXIT_FAILURE;

	int len = strlen(tmp);

	if (tmp[len - 1] == '\n' || tmp[len - 1] == '\r' )
		tmp[--len] = '\0';

	if (len == 0)
		return EXIT_FAILURE;
	if (len >= n)
		return EXIT_FAILURE;

	strncpy(brand, tmp, n);

	return EXIT_SUCCESS;
}


int car_scan(cars *car)
{
	if (str_scan(car->brand, B_L))
		return SCAN_ERROR;
	if (!scanf("%d", &car->number))
		return SCAN_ERROR;
	if (!scanf("%d", &car->displacement))
		return SCAN_ERROR;
	if (!scanf("%lf", &car->weight))
		return SCAN_ERROR;

	return EXIT_SUCCESS;
}
