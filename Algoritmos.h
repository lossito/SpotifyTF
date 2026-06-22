#pragma once
#include <vector>
#include <functional>

template <typename T>
void heapify(std::vector<T>& A, int n, int i, std::function<bool(T, T)> comparar) {
    int extremo = i;
    int izquierda = 2 * i + 1;
    int derecha = 2 * i + 2;

    if (izquierda < n && comparar(A[extremo], A[izquierda])) { extremo = izquierda; }
    if (derecha < n && comparar(A[extremo], A[derecha])) { extremo = derecha; }

    if (extremo != i) {
        std::swap(A[i], A[extremo]);
        heapify(A, n, extremo, comparar);
    }
}

template <typename T>
void heapSort(std::vector<T>& A, std::function<bool(T, T)> comparar) {
    int n = A.size();
    for (int i = n / 2 - 1; i >= 0; i--) { heapify(A, n, i, comparar); }

    for (int i = n - 1; i > 0; i--) {
        std::swap(A[0], A[i]);
        heapify(A, i, 0, comparar);
    }
}

template <typename T>
int particion(std::vector<T>& A, int low, int high, std::function<bool(T, T)> comparar)
{
    T pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (comparar(A[j], pivot))
        {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[high]);
    return i + 1;
}

template <typename T>
void quickSort(std::vector<T>& A, int low, int high, std::function<bool(T, T)> comparar)
{
    if (low < high)
    {
        int pi = particion<T>(A, low, high, comparar);
        quickSort<T>(A, low, pi - 1, comparar);
        quickSort<T>(A, pi + 1, high, comparar);
    }
}

template <typename T>
void merge(std::vector<T>& A, int left, int mid, int right, std::function<bool(T, T)> comparar) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<T> L(n1);
    std::vector<T> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = A[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = A[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comparar(L[i], R[j])) {
            A[k] = L[i];
            i++;
        }
        else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(std::vector<T>& A, int left, int right, std::function<bool(T, T)> comparar) {
    if (left >= right) { return; }
    int mid = left + (right - left) / 2;
    mergeSort<T>(A, left, mid, comparar);
    mergeSort<T>(A, mid + 1, right, comparar);
    merge<T>(A, left, mid, right, comparar);
}