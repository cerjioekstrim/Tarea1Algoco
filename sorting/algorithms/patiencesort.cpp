//Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8

//Idea general (piles + merge) tomada de:
//GeeksforGeeks. (2025, 12 de julio). Patience Sorting.
//https://www.geeksforgeeks.org/dsa/patience-sorting/
//
//Modificado respecto a la fuente: busqueda binaria para ubicar el pile y
//cola de prioridad (min-heap) para la mezcla, en vez de busqueda lineal.
//Wikipedia. (2026). Patience sorting.
//https://en.wikipedia.org/wiki/Patience_sorting
//Justificacion detallada y mediciones de este cambio en el informe.

#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

std::vector<int> patienceSortArray(std::vector<int>& arr) {

    if (arr.empty())
        return arr;

    // Cada pile se representa por su carta superior (top). Los piles se
    // mantienen ordenados de forma creciente por su top, por lo que el
    // pile correspondiente a cada carta se puede ubicar con busqueda binaria.
    // pileTops[i] = valor de la carta en la cima del pile i.
    std::vector<int> pileTops;

    // pileStacks[i] contiene todas las cartas del pile i (para poder
    // reconstruir cada pile completo durante la fase de mezcla).
    std::vector<std::vector<int>> pileStacks;

    for (int carta : arr) {
        // Busca el primer pile cuyo top sea mayor o igual a la carta actual
        // (primer pile sobre el que la carta puede apilarse).
        auto it = std::lower_bound(pileTops.begin(), pileTops.end(), carta);

        if (it == pileTops.end()) {
            // No hay pile valido: se crea un pile nuevo.
            pileTops.push_back(carta);
            pileStacks.push_back({carta});
        } else {
            // Se apila sobre el pile encontrado.
            size_t idx = it - pileTops.begin();
            pileTops[idx] = carta;
            pileStacks[idx].push_back(carta);
        }
    }

    // Fase de mezcla: se usa un min-heap con el top de cada pile para ir
    // extrayendo el menor elemento disponible en O(log k) por operacion,
    // con k = cantidad de piles.
    // Cada entrada es (valor_top, indice_del_pile).
    std::priority_queue<std::pair<int, int>,
                         std::vector<std::pair<int, int>>,
                         std::greater<std::pair<int, int>>> minHeap;

    for (size_t i = 0; i < pileStacks.size(); i++)
        minHeap.push({pileStacks[i].back(), static_cast<int>(i)});

    std::vector<int> ans;
    ans.reserve(arr.size());

    while (!minHeap.empty()) {
        auto [valor, idx] = minHeap.top();
        minHeap.pop();

        ans.push_back(valor);
        pileStacks[idx].pop_back();

        if (!pileStacks[idx].empty())
            minHeap.push({pileStacks[idx].back(), idx});
    }

    return ans;
}
