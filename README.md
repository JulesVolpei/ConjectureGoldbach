# ConjectureGoldbach

Dans le cadre d'une proposition de stage, un petit problème mathématique s'est dressé en face de moi :

 _Quelque soit un entier n pair, n est la somme de deux nombres premiers n1 et n2.
 Quelque que soit n, afficher (stocker) toutes les paires de (n1, n2)._

Le but était donc de réaliser un programme permetttant de calculer toutes les paires de nombres premiers qui, en les additionnant, forment notre nombre **n**, un entier pair fixé. Il faut également faire en sorte que le programme soit suffisament optimisé pour atteindre des **n** de plus en plus grand.

Ce document markdown a donc comme but d'expliquer les différentes étapes de l'algorithme ainsi que les réflexions qui ont permis d'aboutir à ce résultat.

Le document est divisé en trois parties distinctes :

* _Trouver les nombres premiers_
* _Stocker les nombres premiers_
* _Trouver les paires_

### Temps moyen pour un n donné :

* n = 1 000 000 :
  * __6__ millisecondes.
* n = 10 000 000 :
  * __95__ millisecondes
* n = 100 000 000 :
  * __1,2__ secondes.
* n = 1 000 000 000 :
  * __17,1__ secondes.

## 1 - Trouver les nombres premiers

Faire un test de primalité semble être l'option la plus logique, mais bien trop couteuse en temps. Pour trouver les nombres premiers, utiliser le **crible d'Érathostène** sera bien moins coûteux. 

### Le crible d'Ératosthène - 

Le crible d'Ératosthène est une méthode permettant de déterminer une liste de nombres premiers. Pour se faire, on prend une liste partant de 2 jusqu'à notre entier **n**. Ensuite, en partant de 2, il suffit de cocher tous les multiples du chiffre / nombre que l'on étudie (au premier tour ce sera 2, enlevant ainsi tous les chiffres / nombres pairs). Un indice non barré correspond donc à un nombre premier. 


<img alt="GIF" src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/8c/New_Animation_Sieve_of_Eratosthenes.gif/440px-New_Animation_Sieve_of_Eratosthenes.gif" /> 

On réitère l'opération en prenant le prochain entier non coché dans la liste. À noter qu'avec ce crible, il est possible de parcourir notre liste jusqu'à sqrt(n). On obtient une boucle :

```c++
for (size_t i = 0; i < sqrt(n): i += 1) { for (size_t j = i; j < sqrt(n); j += i) { ... } }
```

On peut dans un premier temps penser à une petite optimisation. On sait que **presque** tous les nombres premiers sont impairs, tous sauf 2. On peut également déduire 
qu'il n'y a une seule possibilité où 2 est nécessaire ( *n = 4, n1 = 2, n2 = 2* ). Il nous suffit donc de créer une solution à part dans notre programme pour n = 4. Ainsi, on peut uniquement parcourir l'ensemble des nombres impairs :

```c++
for (size_t i = 3; i < sqrt(n): i += 2) { for (size_t j = i; j < sqrt(n); j += i) { ... } }
```

On ajoute également une dernière optimisation concernant la boucle en elle-même, on applique la fonction carré de chaque côté de l'égalité car l'appel de la fonction ```sqrt( ... )``` nous fait perdre de précieuses millisecondes. On obtient finalement :

```c++
for (size_t i = 3; i*i < n: i += 2) { for (size_t j = i*i; j < n; j += i) { ... } }
```

## 2 - Stocker les nombres premiers

Le vecteur dans lequel sont nos nombres premiers (et non premier également) à la fin du crible peut se faire sous plusieurs formes. La manière la plus intuisitve serait de faire un vecteur d'entiers naturels en le remplissant de ``` 0 ``` et mettre par exemple ``` 1 ``` aux indices non premiers. Cette méthode a quelques défauts. Tout d'abord, un entier naturel peut prendre entre 2 et 4 octets de mémoire. De plus, lorsque l'on crée un vecteur d'entier naturel de taille n, ce dernier se remplie forcément de 0. 

On peut donc refaire le même procédés mais en remplaçant la liste d'entier par une chaine de caractère. Un charactère ne prend que 1 octet, ce qui est bien moins gourmand qu'un entier naturel. C'est donc un gain de mémoire et de temps. Il nous suffit donc de prendre la boucle plus haut est de remplacer un caractère qui n'est pas premier par un caractère quelconque (ici ``` 1 ```).

Une fois notre chaine de caractère obtenu, il faut maintenant en ressortir tous les nombres premiers. Ces derniers correspondent aux indices dans notre chaine de caractères. Il nou faut donc parcourir notre chaine et en ressortir les indices premiers. Seul problème, il nous faut éviter les doublons. En effet, si on prend toutes la chaine de caractères, on va se retrouver avec le résultat suivant :

```c++
10 = 7 + 3
10 = 3 + 7
```

Or, l'addition étant une opération 3 + 7 et 7 + 3 sont les mêmes, une seule nous suffit. Il va donc falloir prendre uniquement la moitié des indices de notre chaine de caractères (ça peut être difficile à comprendre pour l'instant, ça va surtout s'expliquer avec la prochaine étape).
On parcourt donc la chaine avec une boucle du style :

```c++
for (size_t i = 3; i < n / 2 + 1; i += 2) { ... }
```

## 3 - Trouver toutes les paires

Une méthode naïve pour trouver toutes les paires seraient de faire deux boucles imbriquées dans notre vecteur et de tester toutes les additions entre nos entiers pour savoir lesquels, une fois additionés, sont égaux à n :

```c++
for (size_t i = 0; i < vecteur.size(); i += 1) {
    for (size_t j = 0; j < vecteur.size(); j += 1) {
        if (vecteur[i] + vecteur[j] == n) {
           ...
        }
    }
}
```

On peut simplifier notre méthode en prenant directement la valeur dans le vecteur avec une boucle :

```c++
for (const unsigned & n1 : vecteur) { ... }
```

Ensuite, on donne n1 et n2, les deux entiers premiers dont l'addition est égale à n. On sait donc que n1 + n2 = n. 
On connait déjà n, si l'on parcourt le vecteur une fois on peut également savoir n1. Donc on peut connaitre n2 en écrivant : n2 = n - n1. On peut l'écrire avec une boucle :

```c++
for (const unsigned & n1) {
    unsigned n2 = n - n1;
    ...
}
```

Enfin, il nous faut savoir si n2 est un nombre premier, pour se faire nous allons reprendre notre précédent vecteur avec les indices de nombres premiers et nous allons vérifier si l'indice n2 de notre vecteur est vide (ce qui correspond à un nombre premier). On obtient :

```c++
for (const unsigned & n1) {
    unsigned n2 = n - n1;
    if (vecteur[n2] == vecteur[n + 1]) {
        vecteurStockage.push_back({n2, n1});
    }
}
```
