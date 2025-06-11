# Dining philosophers problem - Problem jedzących filozofów

1. Opis problemu

Problem ucztujących filozofów to klasyczny problem synchronizacji w programowaniu współbieżnym. Pięciu filozofów siedzi wokół stołu, przy którym znajduje się pięć widelców. Każdy filozof musi posiadać dwa widelce, aby móc jeść. Problem polega na synchronizacji dostępu do wspólnych zasobów (widelców) w sposób zapobiegający zakleszczeniom (deadlock) i zagłodzeniu (starvation).

2. Instrukcja uruchomienia (Windows, Visual Studio)

2.1. Wersja bez tworzenia pliku .exe:

Otwórz x64 Native Tools Command Prompt for VS 2022.
Przejdź do katalogu z kodem:

    cd C:\ścieżka\do\katalogu\Philosophers\w\repozytorium

Skopiuj i wklej poniższą komendę, aby skompilować i uruchomić kod:

    cl /std:c++20 Philosophers.cpp && Philosophers 5

Ostatnia wartość to liczba filozofów, którą można dowolnie modyfikować.

2.2. Wersja z tworzeniem pliku .exe:

Skopiuj i wklej poniższą komendę:

    cl /std:c++20 Philosophers.cpp /Fe:Philosophers.exe

Uruchom program:

    Philosophers.exe 5

3. Wątki w programie

Każdy filozof jest reprezentowany jako osobny wątek, który wykonuje cyklicznie następujące czynności:

Myślenie – filozof nie korzysta z zasobów współdzielonych.

Próba podniesienia dwóch widelców – sekcja krytyczna, wymaga synchronizacji.

Jedzenie – filozof zajmuje dwa widelce.

Odkładanie widelców – zwalnianie zasobów.

Główne wątki w programie:

  Wątek główny (main) – tworzy i uruchamia wątki filozofów.

  Wątki filozofów – reprezentują zachowanie każdego filozofa.

4. Sekcje krytyczne i ich rozwiązanie

4.1. Dynamiczna alokacja mutexów i semaforów

Program dynamicznie alokuje tablicę mutexów (std::mutex) dla widelców oraz semafor (std::counting_semaphore<>), aby ograniczyć liczbę filozofów przy stole:

    forks = new mutex[number_of_philosophers];
    table = new counting_semaphore<>(number_of_philosophers - 1);

Po zakończeniu działania program zwalnia zaalokowaną pamięć:

    delete[] forks;
    delete table;

Dzięki temu co najmniej jeden filozof zawsze pozostaje w stanie myślenia, eliminując cykliczne oczekiwanie.

4.2. Dostęp do widelców (mutex)

Każdy widelec jest reprezentowany przez osobny mutex. Filozofowie próbują zablokować dwa widelce przed jedzeniem, ale robią to w różnej kolejności, aby zmniejszyć ryzyko zakleszczenia:

  Filozofowie o parzystych numerach najpierw podnoszą lewy widelec, a potem prawy.

  Filozofowie o nieparzystych numerach najpierw podnoszą prawy widelec, a potem lewy.

Kod implementujący tę strategię:

    if (id % 2 == 0) {
        forks[left].lock();
        forks[right].lock();
    } else {
        forks[right].lock();
        forks[left].lock();
    }

Po zakończeniu posiłku zwalniają widelce:

    forks[left].unlock();
    forks[right].unlock();
