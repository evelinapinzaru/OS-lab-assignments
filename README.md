# OS-lab-assignments
In cel de-al doilea semestru al primului an de licență, am făcut un curs despre sistemele de operare cu accent pe Linux.
Acestea sunt cerințele celor 3 teme pe care le-am avut de rezolvat în cadrul laboratoarelor de SO:

# Table of Contents 📃
1. [Shell script for retrieving system info](#shell-script)
2. [File system replicator in C + makefile](#file-system)
3. [Managing inter-process communication with C](#process)

<a name="shell-script"></a>
# Shell script for retrieving system info | ![](https://geps.dev/progress/100?dangerColor=800000&warningColor=ff9900&successColor=006600)
Să se realizeze un script ce colectează și afișează informații despre sistemul de operare.
Scriptul va afișa un meniu cu următoarele opțiuni:
1. Ieșire
2. Afișare: ID-ul procesului initiat la executarea scriptului, tipul sistemului de operare, numărul de secunde de când 
s-a executat scriptul și calea curentă
3. Afișarea numarului săptămânii din an, si a zilei săptămânii în care va fi Crăciunul în acest an
4. Afișarea primelor 2 shell-urilor instalate în sistem
5. Afișarea pentru toți utilizatorii din sistem a numelui de login, a user ID-ului, a numelui complet și a directorului 
de home
6. Afişare ultimele linii începând cu linia 9 din fișierul /etc/protocols folosind comanda tail
7. Afișare tip procesor şi mărimea cache-ului
8. Scrieți comanda ls care afișează toate numele de directoare din directorul /proc care nu reprezintă imaginea unui 
proces pe disc (numele directorului care reprezintă imaginea unui proces pe disc este format doar din cifre)

<a name="file-system"></a>
# File system replicator in C + makefile | ![](https://geps.dev/progress/100?dangerColor=800000&warningColor=ff9900&successColor=006600)
Realizați un program C care primește 2 argumente din linia de comandă: un director sursă și un director destinație.\
Se va parcurge recursiv structura de directoare din directorul sursă. Pentru fiecare intrare din directorul sursă, se 
vor executa următoarele operații, în funcție de tipul intrării:
1. Pentru directoare, se va crea un director echivalent în directorul destinație, cu aceleași drepturi ca directorul 
original. Astfel, structura de directoare din directorul destinație va fi asemănătoare cu cea din sursă.\
2. Pentru fișierele obișnuite, în funcție de dimensiunea fișierului se va crea o copie sau o legătura simbolică:
    * Pentru fișierele mai mici de 500 octeți, se va crea o copie a fișierului în directorul destinație (și, după caz, 
în subfolderul echivalent). Aceste fișiere copie vor avea aceleași drepturi de read ca și fișierele originale (Ex: 
dacă fișierul original are –rwx-wxr-x, fisierul nou va avea –r-----r--).
    * Pentru celelalte fișiere, se vor crea legături simbolice către fișierul original. Aceste linkuri vor avea aceleași 
drepturi de acces ca și fișierele originale.\
3. Pentru (soft) linkuri, nu se va executa nici o operație.

Tema va fi însoțită de fișierul makefile corespunzător.

<a name="process"></a>
# Managing inter-process communication with C | ![](https://geps.dev/progress/100?dangerColor=800000&warningColor=ff9900&successColor=006600)
Se consideră un program C ce conţine două procese (părinte + fiu). Procesul părinte va trimite, printr-un pipe, timp 
de 7s caracterul “e” către procesul fiu, în plus la fiecare secundă o să trimită semnalul SIGUSR1. Procesul fiu va 
citi caracterele din pipe şi va realiza o statistică ce va conţine numărul total de caractere, precum şi numărul de 
caractere primite după fiecare semnal SIGUSR1. 

La final, statistica va fi trimisă printr-un pipe procesului părinte ce o va afişa.
