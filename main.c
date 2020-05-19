#include <stdlib.h>
#include <stdio.h>
#include "nregine.h"

/*Posizionare su una scacchiera NxN N regine in modo che nessuna ne minacci un'altra. Trovare tutte le possibili soluzioni*/

void printMat(matrix* m) {
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

void nregine(matrix* mcurr, int n, int* nsol, int i, int npos) {
	
	if (npos == n) {//se ho posizionato tutte le regine
		(*nsol)++;
		printMat(mcurr);
		printf("\n");
		return;
	}

	if (i >= n * n)
		return;

	mcurr->data[i] = 0;
	nregine(mcurr, n, nsol, i + 1, npos);

	if (checkRiga(mcurr, i) && checkColonna(mcurr, i) && checkDiagonale(mcurr, i)) {
		mcurr->data[i] = 1;
		nregine(mcurr, n, nsol, i + 1, npos + 1);
		mcurr->data[i] = 0;
	}
}

int main(void) {

	int n = 9;

	matrix* mat = malloc(sizeof(matrix));
	mat->cols = n;
	mat->rows = n;
	mat->data = calloc(mat->cols * mat->rows, sizeof(int));
	int nsol = 0;
	int npos = 0;

	nregine(mat, n, &nsol, 0, npos);

	printf("\nNumero soluzioni: %d", nsol);

	free(mat->data);
	free(mat);

	return 0;
}