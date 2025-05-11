#include <stdio.h>
#include <stdbool.h>

// da se napsat v jednom smeru a otocit kvuli zarazce
void incestSort(int pole[], int n)
{
    for (int i = n - 1; i >= 0; i--) {
        int vkladany = pole[i];
        int j = i + 1;
        for (; j < n && pole[j] < vkladany; j++) {
            pole[j - 1] = pole[j];
        }
        pole[j - 1] = vkladany;
    }
}


void incestSortBreak(int pole[], int n)
{
    for (int i = n - 1; i >= 0; i--) {
        int vkladany = pole[i];
        int j = i + 1;
        pole[n] = vkladany;
        for (; pole[j] < vkladany; j++) {
            pole[j - 1] = pole[j];
        }
        pole[j - 1] = vkladany;
    }
}

void selectionSort(int pole[], int n)
{
    for (int i = 0; i < n; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (pole[j] < pole[min]) {
                min = j;
            }
        }
        int h = pole[min];
        pole[min] = pole[i];
        pole[i] = h;
    }
}

void bublinovka(int pole[], int n)
{
    int posledni_vymena = n - 1;
    for (int i = n - 1; posledni_vymena > 0; i--) {
        int vymena = 0;
        for (int j = 0; j < posledni_vymena; j++) {
            if (pole[j] > pole[j + 1]) {
                int h = pole[j];
                pole[j] = pole[j + 1];
                pole[j + 1] = h;
                vymena = j;
            }
        }
        posledni_vymena = vymena;
    }
}

void merge(int array[], int temp_array[], int start, int middle, int end) {
    int i = start;
    int j = middle;
    int k = start;
    while (i < middle && j < end) {
        if (array[i] <= array[j]) {
            temp_array[k] = array[i];
            i++;
        } else {
            temp_array[k] = array[j];
            j++;
        }
        k++;
    }

    while (i < middle) {
        temp_array[k++] = array[i];
        i++;
    }

    while (j < middle) {
        temp_array[k++] = array[i];
        j++;
    }
}

void copy(int array[], int temp_array[], int start, int end) 
{
    for (int i = start; i < end; i++) {
        array[i] = temp_array[i];
    }
}

void _mergeSort(int array[], int temp_array[], int start, int end)
{
    if (end - start == 1) {
        return;
    }
    int middle = (start + end) / 2;
    _mergeSort(array, temp_array, start, middle);
    _mergeSort(array, temp_array, middle, end);

    merge(array, temp_array, start, middle, end);
    copy(array, temp_array, start, end);
}

void mergeSort(int array[], int n)
{
    int temp_array[n];
    _mergeSort(array, temp_array, 0, n);
}

int main(void) 
{
    int pole[9] = {8, 7, 6, 5, 4, 3, 2, 1};
    mergeSort(pole, 8);
    for (int i = 0; i < 8; i++) {
        printf("%i\n", pole[i]);
    }
}
