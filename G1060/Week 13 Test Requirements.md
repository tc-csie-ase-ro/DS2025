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

### Heap
- functie de numarare cu conditie (toate cursele cu o intarziere mai mare decat x), parcurgerea vectorului de heap
- stergere cu criteriu (toate cursele care au plecat), apelati heapify la fiecare stergere pentru a mentine conditia de heap
- salvare din heap in lista dubla, lista simpla sau vector, cu filtru (ex. toate cursele care au data de plecare inainte de o anumita data specificata de voi); parcurgeti vectorul de heap si salvati elementul in structura noua

### AVL
- functie de numarare cu conditie, parcurgeti arborele in inordine, postordine sau preordine si la fiecare nod daca este verificata conditia incrementati un contor (ex. toate cursele cu > n minute intarziere)
- stergere cu criteriu (in functia de stergere apelati functiile de rotire astfel incat arborele sa ramana mereu balansat)
- copiere in alta structura (parcurgeti in inordine si salvati intr-un vector toate cursele cu o anumita destinatie specificata de voi).