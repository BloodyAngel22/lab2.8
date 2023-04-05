#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/*Массив представлен дескриптором. Количество строк
определяется полем дескриптора. Количество элементов строки
определяется терминальным символом.*/

struct RaggedArray {
	int** data = NULL;
	int rows = 0;
};

void array_allocate_1(RaggedArray &mas) {
	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
	if (mas.data == NULL) {
		printf("Память не была выделена для массива\n");
		exit(1);
	}
}

//int* array_allocate_2(RaggedArray mas) {
//	mas.cols = (int*)malloc(sizeof(int) * mas.rows);
//	if (mas.cols == NULL) {
//		printf("Память не была выделена для массива\n");
//		exit(1);
//	}
//	return mas.cols;
//}

//int* array_allocate_3(RaggedArray mas) {
//	mas.tmp = (int*)malloc(sizeof(int) * mas.rows);
//	if (mas.tmp == NULL) {
//		printf("Память не была выделена для массива\n");
//		exit(1);
//	}
//	return mas.tmp;
//}

void memory_release(RaggedArray mas) {
	for (int i = 0; i < mas.rows; i++)
		free(mas.data[i]);
	free(mas.data);
}

void print_array(RaggedArray mas) {
	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; mas.data[i][j] != '\0'; j++) {
			printf("%d ", mas.data[i][j]);
		}
		printf("\n");
	}
}

void task(RaggedArray mas, int limiter) {
	for (int i = 0; i < mas.rows; i++) {
		mas.data[i] = (int*)malloc(sizeof(int) * limiter);
		printf("Введите элементы массива\n");
		for (int j = 0; j <= limiter; j++) {
			scanf_s("%d", &mas.data[i][j]);
			if (mas.data[i][j] == '\0') {
				mas.data[i][j] = '\0';
				break;
			}
		}
	}
}

void save_in_txt_file(RaggedArray mas, const char* storage_for_txt, int limiter) {
	FILE* save_in_txt;
	if (fopen_s(&save_in_txt, storage_for_txt, "w+") != 0) {
		printf("Не удалось открыть файл");
		exit(1);
	}

	fprintf(save_in_txt, "%d \n", mas.rows);
	int* cols = (int*)malloc(sizeof(int) * limiter);
	for (int i = 0; i < mas.rows; i++) {
		int counter = 0;
		for (int j = 0; mas.data[i][j] != '\0'; j++) {
			counter++;
		}
		cols[i] = counter;
	}

	for (int i = 0; i < mas.rows; i++)
		fprintf(save_in_txt, "%d ", cols[i]);

	fprintf(save_in_txt, "\n");

	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; mas.data[i][j] != '\0'; j++) {
			fprintf(save_in_txt, "%d ", mas.data[i][j]);
		}
		fprintf(save_in_txt, "\n");
	}

	fclose(save_in_txt);
}

void save_in_bin_file(RaggedArray mas, const char* storage_for_bin, int limiter) {
	FILE* save_in_binary = NULL;
	if (fopen_s(&save_in_binary, storage_for_bin, "wb") != NULL) {
		printf("Не удалось открыть файл");
		exit(1);
	}

	fwrite(&mas.rows, sizeof(int), 1, save_in_binary);
	int* cols = (int*)malloc(sizeof(int) * limiter);
	for (int i = 0; i < mas.rows; i++) {
		int counter = 0;
		for (int j = 0; mas.data[i][j] != '\0'; j++) {
			counter++;
		}
		cols[i] = counter;
	}

	for (int i = 0; i < mas.rows; i++)
		fwrite(&cols[i], sizeof(int), 1, save_in_binary);

	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; j < mas.data[i][j] != '\0'; j++) {
			fwrite(&mas.data[i][j], sizeof(int), 1, save_in_binary);
		}
	}

	fclose(save_in_binary);
}

void print_txt_file(RaggedArray mas, const char* storage_for_txt, int limiter) {
	FILE* print_txt;
	if (fopen_s(&print_txt, storage_for_txt, "rt") != 0) {
		printf("Не удалось открыть файл");
		exit(1);
	}


	int* cols = (int*)malloc(sizeof(int) * limiter);
	fscanf_s(print_txt, "%d", &mas.rows);
	array_allocate_1(mas);
	for (int i = 0; i < mas.rows; i++) {
		fscanf_s(print_txt, "%d", &cols[i]);
		mas.data[i] = (int*)malloc(sizeof(int) * cols[i]);
	}

	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; j < cols[i]; j++) {
			fscanf_s(print_txt, "%d", &mas.data[i][j]);
		}
	}

	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; j < cols[i]; j++) {
			printf("%d ", mas.data[i][j]);
		}
		printf("\n");
	}

	memory_release(mas);

	fclose(print_txt);
}

void print_bin_file(RaggedArray mas, const char* storage_for_bin, int limiter) {
	FILE* print_bin = NULL;
	if (fopen_s(&print_bin, storage_for_bin, "rb") != 0) {
		printf("Не удалось открыть файл");
		exit(1);
	}


	fread(&mas.rows, sizeof(int), 1, print_bin);
	array_allocate_1(mas);
	int* cols = (int*)malloc(sizeof(int) * limiter);
	for (int i = 0; i < mas.rows; i++) {
		fread(&cols[i], sizeof(int), 1, print_bin);
		mas.data[i] = (int*)malloc(sizeof(int) * cols[i]);
	}

	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; j < cols[i]; j++) {
			fread(&mas.data[i][j], sizeof(int), 1, print_bin);
		}
	}

	for (int i = 0; i < mas.rows; i++) {
		for (int j = 0; j < cols[i]; j++) {
			printf("%d ", mas.data[i][j]);
		}
		printf("\n");
	}

	memory_release(mas);

	fclose(print_bin);
}

int main() {
	system("chcp 1251");
	const char storage_for_txt[50] = "storage.txt";
	const char storage_for_bin[50] = "binary_storage.bin";
	RaggedArray mas;
	int limiter = 99999;

	int flag_1;
	do {
		printf("Хотите задать или считать массив?\n1 - задать массив\n2 - считать из текстового файла\n3 - считать из бинарного файла\n"); scanf_s("%d", &flag_1);
	} while (flag_1 > 3 or flag_1 < 1);
	if (flag_1 == 1) {
		do {
			printf("rows = "); scanf_s("%d", &mas.rows);
		} while (mas.rows < 1);
		array_allocate_1(mas);


		task(mas, limiter);
	}

	if (flag_1 == 2) {
		print_txt_file(mas, storage_for_txt, limiter);
		exit(1);
	}
	if (flag_1 == 3) {
		print_bin_file(mas, storage_for_bin, limiter);
		exit(1);
	}

	int flag = 0;
	do {
		printf("Хотите сохранить массив в файл?\n0 - нет\n1 - да\n"); scanf_s("%d", &flag);
	} while(flag > 1 or flag < 0);
	if (flag == 1) {
		int switcher;
		do {
			printf("Куда сохраняем массив?\n1 - текстовый файл\n2 - бинарный файл\n"); scanf_s("%d", &switcher);
		} while (switcher > 2 or switcher < 1);
		switch (switcher) {
		case 1:
			save_in_txt_file(mas, storage_for_txt, limiter);
			break;
		case 2:
			save_in_bin_file(mas, storage_for_bin, limiter);
			break;
		}
	}

	printf("\n\n"); printf("Вывод элементов массива\n");
	print_array(mas);


	memory_release(mas);
}