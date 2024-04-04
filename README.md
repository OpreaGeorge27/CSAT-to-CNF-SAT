# Reducerea CSAT la CNF SAT

## Prezentare proiect

Acest proiect își propune să implementeze o reducere în timp polinomial de la problema de Satisfiabilitate a Circuitelor Booleene (CSAT) la problema Formei Normale Conjunctive a Satisfiabilității (CNF SAT). Reducerea implică transformarea unui circuit boolean într-o formulă echivalentă CNF SAT.

### CSAT

Un circuit boolean este reprezentat ca un arbore în care fiecare nod este o poartă logică (AND, OR sau NOT), cu copiii reprezentând intrările, respectiv ieșirea. Frunzele sunt variabile booleane, iar rădăcina este ieșirea circuitului. Un circuit este satisfiabil dacă există o asignare a valorilor booleane care face ieșirea adevărată.

### CNF SAT

O formulă logică în forma normală conjunctivă (CNF) constă în clauze, fiecare conținând disjuncții de literali. O formulă este satisfiabilă dacă există o asignare de valori de adevăr variabilelor care face întreaga formulă adevărată.


## Procedura de reducere

Reducerea are două etape:

1.  **Transformarea Circuitului în Formă Normală Conjunctivă (SAT):** Implementată în `utils.c`.
    
    -   Pentru fiecare intrare și ieșire a circuitului, se crează o variabilă booleană corespunzătoare.
    -   Se aplică recursiv următoarele reguli:
        -   Dacă un nod este o intrare, se returnează variabila corespunzătoare.
        -   Dacă un nod este ieșirea unei porți NOT, se returnează negația formulei obținute recursiv pentru intrarea sa.
        -   Dacă un nod este ieșirea unei porți AND cu m intrări, se returnează conjuncția formularelor obținute recursiv pentru intrările sale.
        -   Dacă un nod este ieșirea unei porți OR cu m intrări, se returnează disjuncția formularelor obținute recursiv pentru intrările sale.
2.  **Aplicarea Reducerii SAT la CNF SAT:** Implementată în `main.c`.
    
    -   Reducerile se bazează pe transformarea Tseytin.
    -   Se construiesc clauze pentru fiecare tip de poartă (AND, OR, NOT), respectând regulile transformării Tseytin.

## Implementare

Implementarea este în limbajul de programare C și constă în două fișiere principale:

-   `utils.h`: Fișierul antet care conține declarațiile funcțiilor și definițiile de structuri.
-   `utils.c`: Fișierul sursă care conține implementarea funcțiilor de reducere.
- `main.c`: Fișierul sursă principal care conține funcționalitatea de aplicare a reducerii și gestionarea intrărilor/ieșirilor.

## Utilizare

Programul primește doi parametri de linie de comandă:

1.  Fișierul de intrare care conține descrierea circuitului boolean.
2.  Fișierul de ieșire unde va fi scrisă formula CNF SAT rezultată.

### Compilare Program
>#### make build

### Rulare Program

>#### make run INPUT=inputFile OUTPUT = outputFile

## Note suplimentare

-   Reducerea implementată se bazează pe transformarea Tseytin, gestionând porțile AND, OR și NOT.
-   Implementarea acceptă circuite cu un număr maxim de 100 de porți, fiecare având maximum 60 de intrări.
- [METODA DE REDUCERE APLICATA ->Tseytin transformation - Wikipedia](https://en.wikipedia.org/wiki/Tseytin_transformation#Approach)
