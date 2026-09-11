# Tarea 1 INF221 2026-2 Sergio Fonseca 202404559-8
#
# Lee data/measurements/sorting_measurements.csv (generado por sorting.cpp),
# promedia las 3 muestras (a, b, c) de cada combinacion (algoritmo, n, tipo,
# dominio) y genera graficos de tiempo y memoria vs n en data/plots/.

import os
import pandas as pd
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

MEASUREMENTS_FILE = os.path.join("..", "data", "measurements", "sorting_measurements.csv")
PLOTS_DIR = os.path.join("..", "data", "plots")

ALGORITMOS = ["mergesort", "quicksort", "patiencesort", "sort"]
TIPOS = ["ascendente", "descendente", "aleatorio"]
DOMINIOS = ["D1", "D7"]


def cargar_datos():
    df = pd.read_csv(MEASUREMENTS_FILE)
    # Promedio sobre las 3 muestras (a, b, c) de cada combinacion.
    resumen = df.groupby(["algoritmo", "n", "tipo", "dominio"], as_index=False).agg(
        tiempo_segundos=("tiempo_segundos", "mean"),
        memoria_kb=("memoria_kb", "mean"),
    )
    return resumen


def graficar_metrica(df, tipo, dominio, columna, ylabel, titulo, nombre_archivo):
    subset = df[(df["tipo"] == tipo) & (df["dominio"] == dominio)]
    if subset.empty:
        return

    plt.figure(figsize=(7, 5))
    for algo in ALGORITMOS:
        datos_algo = subset[subset["algoritmo"] == algo].sort_values("n")
        if datos_algo.empty:
            continue
        plt.plot(datos_algo["n"], datos_algo[columna], marker="o", label=algo)

    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("n (cantidad de elementos)")
    plt.ylabel(ylabel)
    plt.title(titulo)
    plt.legend()
    plt.grid(True, which="both", linestyle="--", alpha=0.5)
    plt.tight_layout()

    os.makedirs(PLOTS_DIR, exist_ok=True)
    plt.savefig(os.path.join(PLOTS_DIR, nombre_archivo), dpi=150)
    plt.close()


def main():
    df = cargar_datos()

    for tipo in TIPOS:
        for dominio in DOMINIOS:
            graficar_metrica(
                df, tipo, dominio, "tiempo_segundos",
                "Tiempo de ejecucion (s)",
                f"Tiempo de ejecucion vs n -- {tipo}, {dominio}",
                f"tiempo_{tipo}_{dominio}.png",
            )
            graficar_metrica(
                df, tipo, dominio, "memoria_kb",
                "Memoria pico (KB)",
                f"Memoria pico vs n -- {tipo}, {dominio}",
                f"memoria_{tipo}_{dominio}.png",
            )

    print(f"Graficos guardados en {PLOTS_DIR}")
    print(pd.__version__)



if __name__ == "__main__":
    main()
