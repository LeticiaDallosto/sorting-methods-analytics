#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 

#define SIZE 6000

// Prototipo das funcoes
int menu();
void bubbleSort(int *v, int n);
void insertionSort(int *v, int n);
void selectionSort(int *v, int n);
void Ms(int *v, int n);
void mergeSort(int *v, int n);
void quickSort(int *v, int n);
void Qs(int *v, int left, int right);
void shellSort(int *v, int n);

main () {
	int *vector = (int *)malloc(SIZE * sizeof(int));
	int option;
	LARGE_INTEGER frequency;        
    LARGE_INTEGER t1, t2;           
    double elapsedTime;

    QueryPerformanceFrequency(&frequency);

	if (vector == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

	do {
		// Preencher vetor com valores aleatorios
		srand(time(NULL));
		for (int i = 0; i < SIZE; i++) {
			vector[i] = rand() % 1000;  
		}

		option = menu();

		switch (option)	{
			case 1:
				printf("\nMETODO BUBBLE SORT\n");
				QueryPerformanceCounter(&t1); 
				bubbleSort(vector, SIZE);
				QueryPerformanceCounter(&t2);
				break;
			case 2:
				printf("\nMETODO INSERTION SORT\n");
				QueryPerformanceCounter(&t1); 
				insertionSort(vector, SIZE);
				QueryPerformanceCounter(&t2);
				break;
			case 3:
				printf("\nMETODO SELECTION SORT\n");
				QueryPerformanceCounter(&t1); 
				selectionSort(vector, SIZE);
				QueryPerformanceCounter(&t2);
				break;
			case 4:
				printf("\nMETODO MERGE SORT\n");
				QueryPerformanceCounter(&t1); 
				Ms(vector, SIZE);
				QueryPerformanceCounter(&t2);
				break;
			case 5:
				printf("\nMETODO QUICK SORT\n");
				QueryPerformanceCounter(&t1); 
				quickSort(vector, SIZE);
				QueryPerformanceCounter(&t2);
				break;
			case 6:
				printf("\nMETODO SHELL SORT\n");
				QueryPerformanceCounter(&t1); 
				shellSort(vector, SIZE);
				QueryPerformanceCounter(&t2);
				break;
			case 7:
				printf("\nPROGRAMA ENCERRADO.\n");
				return 0;
			default:
				printf("\nOpcao invalida, digite novamente.\n\n");
				break;
		}

		if(option >= 1 && option <= 6) {
			// Imprimir o vetor ordenado
			printf("Vetor ordenado: ");
			for (int i = 0; i < SIZE; i++) {
				printf("%d ", vector[i]);
			}
			printf("\n\n");

			// Imprime o tempo de execucao do metodo - em segundos
			elapsedTime = (t2.QuadPart - t1.QuadPart) * 1.0 / frequency.QuadPart;
			printf("Tempo de execucao: %f segundos\n\n", elapsedTime);
		}

		free(vector);
		vector = (int *)malloc(SIZE * sizeof(int));
	} while (option != 7);
    return 0;
}

int menu() {
	int op;
	printf("ANALISE DOS METODOS DE ORDENACAO\n");
	printf("1 - Bubble Sort\n");
	printf("2 - Insertion Sort\n");
	printf("3 - Selection Sort\n");
	printf("4 - Merge Sort\n");
	printf("5 - Quik Sort\n");
	printf("6 - Shell Sort\n");
	printf("7 - Encerrar programa de analise\n");
	printf("Digite a opcao desejada: ");
	scanf("%d",&op);
	return op;
}

void bubbleSort(int *v, int n) {
	int i, end, aux;
	for (end = (n - 1); end > 0; end--) {
		for (i = 0; i < end; i++) {
			if (v[i] > v[i + 1]) {
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
			}
		}
	}
}

void insertionSort(int *v, int n) {
	int i, j , aux;
	for (i = 1; i < n; ++i) {
		aux = v[i];
		for (j = i - 1; j >= 0 && aux < v[j]; j--) {
			v[j + 1] = v[j];
		}	
		v[j + 1] = aux; 
	}
}

void selectionSort(int *v, int n) {
	int i, j, k, exchange, aux;
	for (i = 0; i < (n - 1); i++) {
		exchange = 0;
		k = i;
		aux = v[i];
		for (j = (i + 1); j < n; j++) {
			if (v[j] < aux) {
				k = j;
				aux = v[j];
				exchange = 1;
			}
		}
		if (exchange) {
			v[k] = v[i];
			v[i] = aux;
		}
	}
}

void Ms(int *v, int n) {
	int middle;
	if (n > 1) {
		middle = n / 2;
		Ms(v, middle);
		Ms(v + middle, n - middle);
		mergeSort(v, n);
	}
}
void mergeSort(int *v, int n) {
	int i, j, k;
	int middle, *aux;
	aux = (int *) malloc(n * sizeof(int));
	if (aux == NULL) {
		printf("Erro de alocacao de memoria\n");
		return;
	}
	middle = n / 2;
	i = 0;
	j = middle;
	k = 0;
	while (i < middle && j < n) {
		if (v[i] <= v[j]) {
			aux[k] = v[i++];
		} else {
			aux[k] = v[j++];
		}
		++k;
	}
	if (i == middle) {
		while (j < n) {
			aux[k++] = v[j++];
		}
	} else {
		while (i < middle) {
			aux[k++] = v[i++];
		}
	}
	for (i = 0; i < n; i++) {
		v[i] = aux[i];
	}
	free(aux);
}

void quickSort(int *v, int n) {
	Qs(v, 0, n - 1);
}
void Qs(int *v, int left, int right) {
	int i, j, x, y;
	i = left;
	j = right;
	x = v[(left + right) / 2];
	do {
		while (v[i] < x && i < right) {
			i++;
		}
		while (x < v[j] && j > left) {
			j--;
		}
		if (i <= j) {
			y = v[i];
			v[i] = v[j];
			v[j] = y;
			i++;
			j--;
		}
	} while (i <= j);
	if (left < j) {
		Qs(v, left, j);
	}
	if (i < right) {
		Qs(v, i, right);
	}
}

void shellSort(int *v, int n) {
	int i, j, value;
	int gap = 1;
	while(gap < n) {
		gap = 3 * gap + 1;
	}
	while(gap > 1) {
		gap /= 3;
		for (i = gap; i < n; i++) {
			value = v[i];
			j = i - gap;
			while(j >= 0 && value < v[j]) {
				v[j + gap] = v[j];
				j -= gap;
			}
			v[j + gap] = value;
		}
	}
} 


