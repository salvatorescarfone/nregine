#include <stdlib.h>
#include <stdio.h>

void Scelta0(int* riga, int* colonna, int* DiagP, int* DiagS, int i, int j, int N){

	riga[i] = 0;
	colonna[j] = 0;
	DiagP[i + j - 1] = 0;
	DiagS[i - j + N] = 0;
}

void Scelta1(int* riga, int* colonna, int* DiagP, int* DiagS, int i, int j, int N){

	riga[i] = 1;
	colonna[j] = 1;
	DiagP[i + j - 1] = 1;
	DiagS[i - j + N] = 1;
}

void Nregine(int* riga, int* colonna, int* DiagP, int* DiagS, int i, int j, int N, int* Sol){

	if((i == N + 1)&&(j == N + 1))
	{
		for (int r = 0; r < i; i++)
		{
			printf("%d", riga[r]);
		}
		printf("/n");
		(*Sol)++;
		return;
	}

	Scelta0(riga, colonna, DiagP, DiagS, i, j, N);
	Nregine(riga, colonna, DiagP, DiagS, i + 1, j + 1, N, &Sol);
	Scelta1(riga, colonna, DiagP, DiagS, i, j, N);
	Nregine(riga, colonna, DiagP, DiagS, i + 1, j + 1, N, &Sol);

}

int main(void) {
	
	int N = 3;
	int Sol = 0;
	int* riga = calloc(N, sizeof(int));
	int* colonna = calloc(N, sizeof(int));
	int* DiagP = calloc((2 * N - 1), sizeof(int));
	int* DiagS = calloc((2 * N - 1), sizeof(int));
	Nregine(riga, colonna, DiagP, DiagS, 0, 0, N - 1, &Sol);
	printf("nsol: %d", Sol);
	
	return 0;
}