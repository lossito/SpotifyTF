#pragma once
#include <vector>
#include <functional>
#include "Cola.h"

template <typename T>
class Grafo {
private:
    std::vector<T> vertices;
    std::vector<std::vector<int>> adyacencia;

    int buscarIndice(T v) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices[i] == v) {
                return i;
            }
        }
        return -1;
    }

public:
    void agregarVertice(T v) {
        if (buscarIndice(v) == -1) {
            vertices.push_back(v);
            adyacencia.push_back(std::vector<int>());
        }
    }

    void agregarArista(T origen, T destino, bool dirigido = false) {
        agregarVertice(origen);
        agregarVertice(destino);

        int i = buscarIndice(origen);
        int j = buscarIndice(destino);

        adyacencia[i].push_back(j);
        if (!dirigido) { adyacencia[j].push_back(i); }
    }

    bool existeVertice(T v) {
        return buscarIndice(v) != -1;
    }

    int cantidadVertices() {
        return vertices.size();
    }

    void recorrerAmplitud(T origen, int profundidad, std::function<void(T)> accion) { //BFS
        int indiceOrigen = buscarIndice(origen);
        if (indiceOrigen == -1) { return; }

        std::vector<bool> visitado(vertices.size(), false);
        std::vector<int> distancia(vertices.size(), -1);
        Cola<int> cola;

        cola.enqueue(indiceOrigen);
        visitado[indiceOrigen] = true;
        distancia[indiceOrigen] = 0;

        while (!cola.esVacia()) {
            int actual = cola.front();
            cola.dequeue();
            if (distancia[actual] >= profundidad) { continue; }

            for (int i = 0; i < adyacencia[actual].size(); i++) {
                int vecino = adyacencia[actual][i];
                if (!visitado[vecino]) {
                    visitado[vecino] = true;
                    distancia[vecino] = distancia[actual] + 1;
                    accion(vertices[vecino]);
                    cola.enqueue(vecino);
                }
            }
        }
    }
};