# Corto 5: Final, MP

### Javier Mombiela

## Compilacion

```bash
g++ qSort.cpp -fopenmp -o qSort
./qSort
```

## Resultados

Se realizaron dos pruebas, con 3 corridas cada una, en donde cada vez la cantidad de numeros generados aumentaba por 10 (10^5, 10^6, 10^7).

| Prueba   | Corrida   | n         | Tiempo Secuencial (s) | Tiempo Paralelo (s) | Speedup   |
|----------|-----------|-----------|-----------------------|---------------------|-----------|
| Prueba 1 | Corrida 1 | 100000    | 0.0239                | 0.0220              | 1.0864    |
| Prueba 1 | Corrida 2 | 1000000   | 1.1156                | 0.2955              | 3.7737    |
| Prueba 1 | Corrida 3 | 10000000  | 105.6688              | 21.9332             | 4.8217    |
| Prueba 2 | Corrida 1 | 100000    | 0.0239                | 0.0190              | 1.2605    |
| Prueba 2 | Corrida 2 | 1000000   | 1.1675                | 0.3181              | 3.6697    |
| Prueba 2 | Corrida 3 | 10000000  | 104.9370              | 21.1430             | 4.9597    |