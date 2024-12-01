#include "Expression.h"

Expression::Expression():pileOperateurs(10), pileOperandes(10)
{
}

bool Expression::estOperateur(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool Expression::estOperande(char c)
{
    return (isdigit(c));
}

bool Expression::estParentheseOuvrante(char c)
{
    return (c == '(' || c == '[' || c == '{');
}

bool Expression::estParentheseFermante(char c)
{
    return (c == ')' || c == ']' || c == '}');
}

bool Expression::correspondParenthese(char ouvrante, char fermante)
{
    return (ouvrante == '(' && fermante == ')') ||
        (ouvrante == '[' && fermante == ']') ||
        (ouvrante == '{' && fermante == '}');
}


double Expression::appliquerOperateur(double op1, double op2, char operateur)
{
    switch (operateur) {
    case '+': return op1 + op2;
    case '-': return op1 - op2;
    case '*': return op1 * op2;
    case '/': if(op2==0) throw runtime_error("Impossible de diviser par 0");
              return op1 / op2;
    default: throw invalid_argument("Op�rateur non valide");
    }
}

int Expression::priorite(char op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}


bool Expression::verifierExpression(const string& expr)
{
    Stack<char> pile(10);
    bool Operande = false;  // Indique si le dernier caract�re est un op�rande
    bool Operateur = false; // Indique si le dernier caract�re est un op�rateur

    for (int i = 0; i < expr.length(); i++) {
        char c = expr[i];

        // Ignorer les espaces
        if (isspace(c)) continue;

        // Si c'est une parenth�se ouvrante, empiler
        if (c == '(' || c == '{' || c == '[') {
            pile.push(c);
            Operande = false;
            Operateur = false;
        }
        // Si c'est une parenth�se fermante, v�rifier l'�quilibre
        else if (c == ')' || c == '}' || c == ']') {
            if (pile.IsEmpty() ||
                (c == ')' && pile.Sommet() != '(') ||
                (c == '}' && pile.Sommet() != '{') ||
                (c == ']' && pile.Sommet() != '[')) {
                return false;  // Parenth�se mal appari�e
            }
            pile.pop();
            Operande = true;
            Operateur = false;
        }
        // Si c'est un op�rande (chiffre ou lettre)
        else if (estOperande(c)) {

            Operande = true;
            Operateur = false;
        }
        // Si c'est un op�rateur
        else if (estOperateur(c)) {
            if (!Operande) {
                return false;  // Op�rateur sans op�rande avant lui 
            }
            Operateur = true;
            Operande = false;
        }
        // Si c'est un caract�re invalide
        else {
            return false;  // Expression invalide
        }
    }

    // V�rifier si la pile est vide et que l'expression ne se termine pas par un op�rateur
    return pile.IsEmpty() && Operande;
}

double Expression::evaluer(const string& expression)
{
    if (!verifierExpression(expression)) {
        throw invalid_argument("Expression invalide");
    }

    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];

        // Ignorer les espaces
        if (isspace(c)) continue;

        // Si c'est une parenth�se, crochet ou accolade ouvrante
        if (estParentheseOuvrante(c)) {
            pileOperateurs.push(c);
        }
        // Si c'est une parenth�se, crochet ou accolade fermante
        else if (estParentheseFermante(c)) {
            while (!pileOperateurs.IsEmpty() && !estParentheseOuvrante(pileOperateurs.Sommet())) {
                char op = pileOperateurs.Sommet();
                pileOperateurs.pop();
                double op2 = pileOperandes.Sommet();
                pileOperandes.pop();
                double op1 = pileOperandes.Sommet();
                pileOperandes.pop();
                pileOperandes.push(appliquerOperateur(op1, op2, op));
            }
            // Assurez-vous de retirer l'�l�ment ouvrant correspondant
            if (!pileOperateurs.IsEmpty()) {
                char ouvrante = pileOperateurs.Sommet();
                pileOperateurs.pop();
                if (!correspondParenthese(ouvrante, c)) {
                    throw invalid_argument("Parenth�ses non correspondantes");
                }
            }
        }
        // Si c'est un chiffre, on l'ajoute � la pile des op�randes
        else if (isdigit(c)) {
            double operand = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                operand = operand * 10 + (expression[i] - '0');
                ++i;
            }
            --i;  // Reculer d'un caract�re apr�s la boucle
            pileOperandes.push(operand);
        }
        // Si c'est un op�rateur
        else if (estOperateur(c)) {
            while (!pileOperateurs.IsEmpty() && priorite(pileOperateurs.Sommet()) >= priorite(c)) {
                char op = pileOperateurs.Sommet();
                pileOperateurs.pop();
                double op2 = pileOperandes.Sommet();
                pileOperandes.pop();
                double op1 = pileOperandes.Sommet();
                pileOperandes.pop();
                pileOperandes.push(appliquerOperateur(op1, op2, op));
            }
            pileOperateurs.push(c);
        }
    }

    // Appliquer les restes des op�rateurs
    while (!pileOperateurs.IsEmpty()) {
        char op = pileOperateurs.Sommet();
        pileOperateurs.pop();
        double op2 = pileOperandes.Sommet();
        pileOperandes.pop();
        double op1 = pileOperandes.Sommet();
        pileOperandes.pop();
        pileOperandes.push(appliquerOperateur(op1, op2, op));
    }

    return pileOperandes.Sommet();
}

Expression::~Expression()
{
}


