Pentru testul de luni e bine sa aveti in vedere urmatoarele cerinte:

- Sa definiti o structura. Exemplu:
```
CursaAeriana
char* cod; // string, cod identificator al cursei
char* destinatie; // string
<> dataPlecare // puteti folosi fie char* sau un alt struct definit de voi
<> oraPlecare // la fel ca mai sus
short int nrMinuteIntarziere // 
```

### Lista Dublu Inlantuita

- Functie care determina un numar de elemente din lista care indeplinesc un anumit criteriu;
  - Exemplu: cautati toate cursele care au un numar de minute intarziere mai mare decat X;
  - aveti nevoie de o functie care parseaza lista si la fiecare nod face o verificare, incrementand sau nu o variabila care la final va fi intoarsa in main

- Functie care sterge noduri din lista care indeplinesc un anumit criteriu:
  - Exemplu: stergeti toate cursele care au data de intarziere mai veche decat data de azi;
  - stergerea ati avut-o ca tema;

- Functie care salveaza intr-o alta structura anumite noduri care indeplinesc o conditie;
  - Exemplu: salvati intr-un vector toate cursele care pleaca pana in 12:00;
  - Exemplus: salvati intr-o lista simpla/dubla cursele care pleaca dupa 12:00;
  - ca si implementare in cazul vectorului aveti doua optiuni:
    - parcurgeti lista cu functia de numarare de mai sus si numarati toate nodurile care indeplinesc conditia iar apoi cu valoarea respectiva initializati vectorul, apoi mai parcurgeti o data lista si salvati elementele in vector; in total veti avea doua parcurgeri
    - declarati un vector si setati-l pe NULL, parcurgeti lista o singura data iar la fiecare match apelati `realloc()`; la fiecare pas veti mari vectorul cu un element;
  - in cazul listei e mai usor pentru ca doar va declarati o lista noua si apelati un insert de fiecare data cand gasiti un match

### Hash Table

- Functie care determina numarul de curse aeriene din tabela care indeplinesc o anumita conditie;
  - Exemplu: toate calatoriile catre o anumita destinatie;
  - Cand cheia de cautare este destinatia, atunci veti avea toate nodurile cu aceeasi destinatie intr-o lista (amintiti-va de exemplul de la seminar cu masinile de aceeasi marca), deci va trebui sa faceti o parsare pe o lista simpla
  - Cand cheia de cautare este codul de identificare atunci trebuie sa parcurgeti toata tabela, cu un for si cautand in toate listele
  - Functia intoarce numarul de elemente gasite

- Functie care sterge din tabela curse care indeplinesc un anumit criteriu:
  - Exemplu: toate cursele care au plecat;
  - Parcurgeti toata tabela cu un for si cautati in toate listele, mai exact pe fiecare bucket veti apela acea functie de stergere din lista cu un anumit criteriu (seminarul 4)

- Functie care salveaza elementele care indeplinesc o anumita conditie intr-o alta structura;
  - Exemplu: toate cursele catre o anumita destinatie;
  - Parcurgeti toata tabela (cand cheia nu e destinatia, altfel veti parcurge doar o lista) si aplicati aceeasi logica ca mai sus, la liste duble;
