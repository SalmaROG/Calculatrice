#include "Expression.h"

int main() {
    string expression;
    cout << "Entrez une expression arithmetique : ";
    getline(cin, expression);

    Expression eval;
    try {
        double resultat = eval.evaluer(expression);
        cout << "Résultat: " << resultat << endl;
    }
    catch (const invalid_argument& e) {
        cout << "Erreur: " << e.what() << endl;
    }

    return 0;
}