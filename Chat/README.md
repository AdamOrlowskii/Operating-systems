# Chat TCP – Komunikator sieciowy

1. Opis projektu
   
Projekt przedstawia prostą aplikację typu czat, która umożliwia komunikację wielu użytkowników w sieci lokalnej lub przez Internet.
Został zrealizowany w języku Python z wykorzystaniem gniazd (moduł socket) oraz graficznego interfejsu użytkownika w bibliotece Tkinter.

System składa się z dwóch części:

* Serwer (server.py) – przyjmuje połączenia od klientów, zarządza listą aktywnych użytkowników i rozsyła wiadomości do wszystkich podłączonych klientów.

* Klient (client.py) – pozwala użytkownikowi na dołączenie do czatu, wysyłanie wiadomości oraz wyświetlanie wiadomości od innych użytkowników.

Projekt stanowi demonstrację podstaw komunikacji sieciowej i obsługi wielu klientów przy użyciu wątków.

2. Instrukcja uruchomienia (Python3)

2.1. Uruchomienie servera

W terminalu lub wierszu poleceń przejdź do katalogu z projektem i uruchom serwer:

    py server.py

Serwer domyślnie działa na hoście 127.0.0.1 oraz porcie 1234. Te wartości można zmienić w pliku server.py (zmienne HOST i PORT).

2.2. Uruchomienie klienta:

W nowym terminalu uruchom klienta:

    py client.py

Po uruchomieniu otworzy się okno aplikacji, w którym należy wpisać swoją nazwę użytkownika (username) i nacisnąć przycisk „Join” lub klawisz Enter.
Następnie można wysyłać wiadomości, które będą widoczne dla wszystkich użytkowników podłączonych do czatu.

3. Wątki w programie

Każdy klient jest obsługiwany w osobnym wątku na serwerze. Dzięki temu możliwa jest równoczesna obsługa wielu użytkowników.

Główne wątki w programie:

* Wątek główny serwera – nasłuchuje nowych połączeń i tworzy nowe wątki dla każdego klienta.

* Wątki klientów – odbierają wiadomości od użytkownika i przekazują je dalej.

* Wątek nasłuchujący w aplikacji klienckiej – w tle odbiera nowe wiadomości z serwera i wyświetla je w interfejsie.

4. Przebieg komunikacji

4.1 Server

Po uruchomieniu serwera, oczekuje on na połączenia od klientów.

Po odebraniu połączenia, serwer oczekuje na wysłanie przez klienta nazwy użytkownika (username).

Serwer dodaje klienta do listy active_clients i informuje wszystkich uczestników o nowym użytkowniku.

Każda wiadomość od klienta jest odbierana w dedykowanym wątku i rozsyłana do wszystkich użytkowników.

4.2 Klient

Klient łączy się z serwerem i wysyła nazwę użytkownika.

Wiadomości wprowadzane w polu tekstowym są wysyłane do serwera po naciśnięciu „Send” lub klawisza Enter.

Odbierane wiadomości są wyświetlane w polu tekstowym w interfejsie graficznym
