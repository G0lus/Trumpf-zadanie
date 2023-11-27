Napisz w języku C program, który:

Jako wejście przyjmuje plik *.csv, ze średnikiem jako separator
Jako wyjście tworzy plik *.csv, ze średnikiem jako separator
W danych wejściowych będzie jedna kolumna z wartościami liczbowymi – spróbkowany sygnał
Rezultatem ma być plik z 4 kolumnami:

Pierwsza – powielone wejście
Druga – wynik średniej kroczącej dla danej próbki. Wielkość okna uśredniania: 500 próbek
Trzecia – wynik kroczącego maximum dla danej próbki. Wielkość okna: 500 próbek
Czwarta – wynik kroczącego minimum dla danej próbki. Wielkość okna: 500 próbek

Liczby w pliku wynikowym powinny być wypisane z dokładnością do 2 miejsc po przecinku
Do wyliczenia minimum/maximum kroczącego, powinien zostać użyty algorytm z pomocniczą kolejką
Implementacja pomocniczej kolejki również jest częścią zadania, preferowane rozwiązanie nie wymagające dynamicznej alokacji pamięci

 

Przykładowo, dla danych:
```
Wejście;
1.00;
2.00;
5.00;
3.00;
4.00;
2.00;
```
I okna wielkości 3, powinniśmy otrzymać wynik:

```
Wejście;Avg;Max;Min;
1.00;1.00;1.00;1.00;
2.00;1.50;2.00;1.00;
5.00;2.66;5.00;1.00;
3.00;3.33;5.00;2.00;
4.00;4.00;5.00;3.00;
2.00;3.00;4.00;2.00;
```