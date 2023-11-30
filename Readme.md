# Zadanie

Treść zadania jest dostępny w pliku *Tresc_zadania.md*.

## Kompilacja

Standardowa kompilacja z użyciem CMake.
Projekt wykorzystuje definicję **MOVING_WINDOW_SIZE** do określenia wielkości pomocniczej kolejki. Domyślnie wynosi 500, aby ją zmienić wystarczy zmienić wartość w *CMakeLists.txt:15* i przekompilować.

## Użycie

Limit wielkości pliku wejściowego ograniczono do 8kB, natomiast liczę wartości do 2048 (wartości te mogą zostać zmodyfikowane poprzez zmianę linii 6 i 7 w pliku *main.c*)

`./trumpf_zadanie <ścieżka do pliku wejściowego> <ścieżka do pliku wyjściowego>`

np. `./trumpf_zadanie test.csv out_test.csv`