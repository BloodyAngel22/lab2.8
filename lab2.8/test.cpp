//#include <stdio.h>
//#include <stdlib.h>
//#include <malloc.h>
//
//struct RaggedArray {
//	int** data = NULL;
//	int rows = 0;
//	int* cols = NULL;
//};
//
//int main() {
//	system("chcp 1251");
//
//	RaggedArray mas;
//	int limiter = 99999;
//	int counter_2 = 0;
//	printf("rows = "); scanf_s("%d", &mas.rows);
//
//	mas.data = (int**)malloc(sizeof(int*) * mas.rows);
//	mas.cols = (int*)malloc(sizeof(int) * limiter);
//	for (int i = 0; i < mas.rows; i++) {
//		printf("������� ���������� ����� � ������� ");
//		scanf_s("%d", &mas.cols[i]);
//		mas.data[i] = (int*)malloc(sizeof(int) * mas.cols[i]);
//	}
//
//	for (int i = 0; i < mas.rows;i++) {
//		printf("������� ����� ��� %d ������ ", i);
//		for (int j = 0; j < mas.cols[i]; j++) {
//			scanf_s("%d", &mas.data[i][j]);
//		}
//	}
//
//
//	printf("\n\n"); printf("����� ��������� �������\n");
//	for (int i = 0; i < mas.rows; i++) {
//		for (int j = 0; j < mas.cols[i]; j++) {
//			printf("%d ", mas.data[i][j]);
//		}
//		printf("\n");
//	}
//
//	for (int i = 0; i < mas.rows; i++)
//		free(mas.data[i]);
//
//	free(mas.data);//������
//
//	free(mas.cols);
//}