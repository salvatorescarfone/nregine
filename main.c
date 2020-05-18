#include <stdlib.h>
#include <stdio.h>
#include "nregine.h"

/*Posizionare su una scacchiera NxN N regine in modo che nessuna ne minacci un'altra. Trovare tutte le possibili soluzioni*/

void printmat(matrix* m) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%d ", m->data[i * m->cols + j]);
		}
		printf("\n");
	}
}

int checkRiga(matrix* m, int i) {
	int riga = i / m->cols;

	for (int j = 0; j < m->cols; j++) {
		if (m->data[riga * m->cols + j] == 1) return 0;
	}

	return 1;
}

int checkColonna(matrix* m, int i) {
	int colonna = i % m->cols;

	for (int j = 0; j < m->cols; j++) {
		if (m->data[j * m->cols + colonna] == 1) return 0;
	}

	return 1;
}

int checkDiagonale(matrix* m, int i) {
	
	int r = i / m->cols;
	int c = i % m->cols;

	//diagonale principale sotto
	for (int j = r + 1, k = c + 1; j < m->rows && k < m->cols; j++, k++) {
		if (m->data[j * m->rows + k] == 1) return 0;
	}
	//diagonale principale sopra
	for (int j = r - 1, k = c - 1; j >= 0 && k >= 0; j--, k--) {
		if (m->data[j * m->rows + k] == 1) return 0;
	}

	//diagonale secondaria sotto
	for (int j = r + 1, k = c - 1; j < m->rows && k >= 0; j++, k--) {
		if (m->data[j * m->rows + k] == 1) return 0;
	}

	//diagonale secondaria sopra
	for (int j = r - 1, k = c + 1; j >= 0 && k < m->cols; j--, k++) {
		if (m->data[j * m->rows + k] == 1) return 0;
	}

	return 1;
}

void stampa(matrix* m, int n) {

	int r = 1, c = 1;

	for (int i = 0; i < n * n; i++) {
		m->data[i] = rand() % 10;
	}

	printf("diagonale principale sotto\n");
	//diagonale principale sotto
	for (int j = r + 1, k = c + 1; j < m->rows && k < m->cols; j++, k++) {
		printf("%d ", m->data[j * m->rows + k]);
	}
	printf("\n");
	printf("diagonale principale sopra\n");
	//diagonale principale sopra
	for (int j = r - 1, k = c - 1; j >= 0 && k >= 0; j--, k--) {
		printf("%d ", m->data[j * m->rows + k]);
	}
	printf("\n");
	printf("diagonale secondaria sotto\n");
	//diagonale secondaria sotto
	for (int j = r + 1, k = c - 1; j < m->rows && k >= 0; j++, k--) {
		printf("%d ", m->data[j * m->rows + k]);
	}
	printf("\n");
	printf("diagonale secondaria sopra\n");
	//diagonale secondaria sopra
	for (int j = r - 1, k = c + 1; j >= 0 && k < m->cols; j--, k++) {
		printf("%d ", m->data[j * m->rows + k]);
	}

}

void nregine(matrix* mcurr, int n, int* nsol, int i, int npos) {
	if (i >= n * n)
		return;

	if (npos == n) {//se ho scorso tutta la matrice o ho posizionato tutte le regine
		(*nsol)++;
		printmat(mcurr);
		printf("\n");
		return;
	}

	mcurr->data[i] = 0;
	nregine(mcurr, n, nsol, i + 1, npos);

	if (checkRiga(mcurr, i) && checkColonna(mcurr, i) && checkDiagonale(mcurr, i)) {
		mcurr->data[i] = 1;
		nregine(mcurr, n, nsol, i + 1, npos + 1);
		mcurr->data[i] = 0;
	}
}

int main(void) {


	int n = 5;
	matrix* mat = malloc(sizeof(matrix));
	mat->cols = n;
	mat->rows = n;
	mat->data = calloc(mat->cols * mat->rows, sizeof(int));
	int nsol = 0;
	int npos = 0;

	nregine(mat, n, &nsol, 0, npos);

	//stampa(mat, n);

	printf("\nnsol: %d", nsol);


	return 0;
}