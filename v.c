

int esPrimo(int num) {
    if (num < 2) {
        return 0; // No es primo
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return 0; // No es primo
        }
    }
    return 1; // Es primo
}

void generarPrimosEnRango(int inicio, int fin) {
    printf("Números primos en el rango de %d a %d:\n", inicio, fin);
    for (int i = inicio; i <= fin; ++i) {
        if (esPrimo(i)) {
            printf("%d, ", i);
        }
    }
    printf("\n");
}

int main() {
    int rangoInicio, rangoFin;

    printf("Ingrese el rango de números (inicio fin): ");
    scanf("%d %d", &rangoInicio, &rangoFin);

    generarPrimosEnRango(rangoInicio, rangoFin);

    return 0;
}
