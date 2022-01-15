#include <iostream>
#include <vector>
#include <assert.h>
#include <math.h>
#include <chrono>


using namespace std;

typedef vector<bool> VB ;
typedef vector<unsigned> VU;
typedef vector<VU> VVU ;


/* Consigne
 * Quelque soit un entier n pair, n est la somme de deux nombres premiers n1 et n2 (conjecture de Goldbach)
 * Quelque que soit n, afficher (stocker) toutes les pairs de (n1, n2)
*/

bool estPremier(const unsigned & nbr, const unsigned & maximum) {
    for (unsigned i = 2; i < sqrt(maximum); i += 1) {
        //En partant de 2 car 2 est premier et jusqu à sqrt(maximum)
        if (nbr%i == 0) {
            //Si i divise nbr
            if (i != nbr) {
                //Et que i et nbr ne sont pas les memes chiffres/nombres
                return false;
                //Alors nbr est pas premier
            }
        }
    }
    return true;
    //nbr est premier
}


template <typename T>
void afficherVV(const vector<T> & vec) {
    for (const auto & i : vec) {
        for (const auto & j : i) {
            cout << j << ' ';
        }
        cout << endl;
    }
}

VU cribleEra(const unsigned & n) {
    VB vecBool(n, true);
    VU vecTest;
    for (unsigned i = 3; i < sqrt(n); i += 2) {
        //i partant de 3 et incrémenté de 2 pour aller au plus petit nombre impair
        if (vecBool[i]) {
            for (unsigned j = i * i; j < n; j += i) {
                //j devient un multiple de i
                vecBool[j] = false;
            }
        }
    }
    for (unsigned i = 3; i < n/2 + 1; i += 2) {
        //Jusqu'à n/2 + 1 pour éviter les doublons
        if (vecBool[i]) {
            vecTest.push_back(i);
        }
    }
    return vecTest;
}



VVU goldbachV2(const unsigned & n, VU & vecNP) {
    assert(n%2 == 0);
    if (n == 4) {
        //Seul cas où 2 forme une pair pour un n pair
        return {2, 2};
    }
    VVU vvuPaireNP;
    for (const unsigned & n1 : vecNP) {
        unsigned n2 = n - n1;
        if (estPremier(n2, n)) {
            vvuPaireNP.push_back({n2, n1});
        }
    }
    return vvuPaireNP;
}


/*Fonction permettant de vérifier si tous les éléments d'un VVU sont premiers

bool verification(const VVU & vecTest, const unsigned & n) {
    for (unsigned i = 0; i < vecTest.size(); ++i) {
        for (unsigned j = 0; j < vecTest[i].size(); ++j) {
            if (!estPremier(vecTest[i][j], n)) {
                return false;
            }
        }
    }
    return true;
}
*/


int main() {
    unsigned n = 1000000;
    VU vecT = cribleEra(n);
    VVU  vvuTest = goldbachV2(n, vecT);
    afficherVV(vvuTest);
    return 0;
}
