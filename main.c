#include <stdlib.h>
#include <stdio.h>
#include "nregine.h"

/*Posizionare su una scacchiera NxN N regine in modo che nessuna ne minacci un'altra. Trovare tutte le possibili soluzioni*/

void printmat(matrix* m) {
	for (int i = 0; i < m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%d ", m->data[i*m->cols + j]);
		}
		printf("\n");
	}
}
//
//int checkRiga(matrix* m, int i) {
//
//	for (int j = 0; j < m->cols; j++) {
//		if (m->data[i + j] == 1) return 0;
//	}
//	
//	return 1;
//}

int checkRiga(matrix* mcurr) {

	int ce = 0;
	for (int r = 0; r < mcurr->rows; r++) {
		for (int c = 0; c < mcurr->cols; c++) {
			if (mcurr->data[r * mcurr->cols + c] == 1) ce++;
		}
		if (ce > 1) return 0;
		ce = 0;
	}

	return 1;
}

int checkColonna(matrix* mcurr) {

	int ce = 0;
	for (int r = 0; r < mcurr->rows; r++) {
		for (int c = 0; c < mcurr->cols; c++) {
			if (mcurr->data[c * mcurr->cols + r] == 1) ce++;
		}
		if (ce > 1) return 0;
		ce = 0;
	}

	return 1;
}


void nregine(matrix *mcurr, int n, int *nsol, int i, int *npos) {

	if (i == n*n /*|| *npos == n*/) {//se ho scorso tutta la matrice o ho posizionato tutte le regine

		if (!checkRiga(mcurr) || !checkColonna(mcurr)) return;

		(*nsol)++;
		printmat(mcurr);
		printf("\n");
		return;
	}

	mcurr->data[i] = 0;
	nregine(mcurr, n, nsol, i + 1, npos);

	//if (checkRiga(mcurr, i)) {
		mcurr->data[i] = 1;
		//(*npos)++;
		nregine(mcurr, n, nsol, i + 1, npos);
	//}

}

int main(void) {
	
	int n = 3;
	matrix* mat = malloc(sizeof(matrix));
	mat->cols = n;
	mat->rows = n;
	mat->data = calloc(mat->cols * mat->rows, sizeof(int));
	int nsol = 0;
	int npos = 0;

	nregine(mat, n, &nsol, 0, &npos);
	printf("\nnsol: %d", nsol);

	return 0;
}