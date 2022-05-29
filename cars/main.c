#include "my_file.h"

/*
В типизированной файле, хранящем инфу о легковых автомобилях: марка, номер, литраж и масса. 
Реализовать добавление в файл нового легкового автомобиля, 
сортировка по каждому из полей и удаление автомобилей литражем меньше 10 литров, 
добавление после каждой машины марки "Жигули" условной машины "Рино"
*/

// Ключи для сортировки по полям:
// b - марка
// n - номер
// d - литраж
// w - масса

int main(int argc, char **argv)
{

	if (argc == 3 && strcmp(argv[1], "ab") == 0)
	{
		FILE *f;
		cars car;

		f = fopen(argv[2], "ab");
		if (car_scan(&car))
			return EXIT_FAILURE;

		fwrite(&car, sizeof(cars), 1, f);

		fclose(f);

	}
	else if (strcmp(argv[1], "sb") == 0)
	{
		FILE *f;

		f = fopen(argv[2], "rb+");

		if (file_sort_by_field(f, argv[3]))
			return EXIT_FAILURE;

		file_delete_car(f);

		fclose(f);

	}
	else if (strcmp(argv[1], "pb") == 0)
	{
		FILE *f;
		cars car;
		f = fopen(argv[2], "rb");
		int size;

		file_size(f, &size);

		for (int i = 0; i < size; i++)
		{
			get_car_by_pos(f, &car, i);
			printf("%s\n%d\n%d\n%lf\n", car.brand, car.number, car.displacement, car.weight);
		}

		fclose(f);

	}
	else if (strcmp(argv[1], "db") == 0)
	{
		FILE *f;

		f = fopen(argv[2], "rb+");

		file_delete_car(f);

		fclose(f);

	}

	return EXIT_SUCCESS;
}
