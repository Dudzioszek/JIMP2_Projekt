# JIMP 2 Projekt  w języku C



## Wstęp
Projekt jest programem stworzonym do nawigacji przez labirynty o różnych rozmiarach, dostarczając rozwiązania dzięki wykorzystaniu algorytmów przeszukiwania w głąb (DFS) i przeszukiwania wszerz (BFS). Celem projektu jest stworzenie narzędzia zdolnego do efektywnego rozwiązywania problemów nawigacyjnych w labiryntach, z ograniczonym zużyciem pamięci.

## Cechy
- Obsługa labiryntów zapisanych w formatach plików tekstowych oraz binarnych.
- Wybór między algorytmem DFS a BFS dla rozwiązania labiryntu.
- Optymalizacja zarządzania pamięcią, z maksymalnym limitem zużycia do 512 kB.
- Eksport wyniku w formie ścieżki w pliku txt, co umożliwia analizę i prezentację rozwiązania.
- Eksport wyników w formie listy wykonanych kroków
- Eksport wyników w pliku binarnym


## Formaty plików i wymogi

Pliki labiryntów muszą znajdować się w katalogu `source` projektu i być prawidłowo sformatowane:

### Plik tekstowy
- Plik `.txt` musi zawierać znaki reprezentujące:
  - `P` - punkt wejścia do labiryntu,
  - `K` - punkt wyjścia z labiryntu,
  - `X` - ściana,
  - spacja ` ` - wolne miejsce, po którym można się poruszać.

### Plik binarny
- Plik binarny składa się z nagłówka definiującego strukturę i wymiary labiryntu, oraz z sekcji zawierającej zakodowane informacje o ścianach i ścieżkach:
  - Nagłówek pliku określa rozmiary labiryntu, współrzędne wejścia i wyjścia oraz inne kluczowe metadane.
  - Dane labiryntu są kodowane binarnie, gdzie każda komórka (ściana lub ścieżka) jest opisana za pomocą określonego formatu, minimalizując rozmiar pliku.

### Uwagi
- Pliki z labiryntami muszą być odpowiednio sformatowane i znajdować się w odpowiednim katalogu przed uruchomieniem programu.
- Dla poprawnego działania programu, wprowadzony plik wejściowy musi być obecny w katalogu `source` i zawierać prawidłowo sformatowany labirynt.
- Aby uzyskać najlepsze wyniki i zapewnić kompatybilność, zaleca się, aby formatowanie i struktura plików były ściśle przestrzegane.


## Uruchamianie programu

### Przygotowanie
Upewnij się, że znajdujesz się w systemie operacyjnym Linux i masz zainstalowany kompilator `cc` oraz narzędzie `make`, które są niezbędne do kompilacji i uruchomienia programu.

### Kompilacja
1. Otwórz terminal.
2. Przejdź do katalogu projektu, gdzie znajdują się źródła programu: 
```bash
cd ścieżka/do/katalogu
```


3. Skompiluj program za pomocą polecenia:
```bash
make all
```


Spowoduje to utworzenie pliku wykonywalnego `app` w katalogu projektu.

### Uruchamianie
Aby uruchomić program, użyj polecenia:
```bash
./app
```

Możesz także określić, który labirynt ma być rozwiązany, i wybrać algorytm rozwiązywania:

- Wczytywanie labiryntu z pliku tekstowego:
  ```bash
  ./app -n plik.txt
  ```
- Wczytywanie labiryntu z pliku binarnego:
  ```bash
  ./app -n plik.bin
  ```
- Użycie algorytmu DFS (Depth-First Search):
  ```bash
  ./app -a dfs
  ```
- Użycie algorytmu BFS (Breadth-First Search), znanego z gwarantowania znalezienia najkrótszej ścieżki:
  ```bash
  ./app -a bfs
  ```

### Dodatkowe opcje
6. Aby uzyskać pomoc dotyczącą dostępnych opcji programu, wpisz:
```bash
./app -p
  ```



### Przykładowe uruchomienie
Aby uruchomić program, rozwiązać labirynt z pliku `maze.bin` algorytmem BFS używając plik `labirynt.txt`, możesz użyć poniższego zestawu poleceń:
```bin
./app -a BFS -n labirnyt.txt
```


## Autorzy

- **Stanisław Dutkiewicz**
- **Filip Kobus**

