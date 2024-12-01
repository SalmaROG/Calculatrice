#include"Stack.h"
#include <string>
#include <cctype>
class Expression {
private:
    Stack<char> pileOperateurs;
    Stack<double> pileOperandes;
public:
    Expression();

    bool estOperateur(char c);
    bool estOperande(char c);
    bool estParentheseOuvrante(char c);
    bool estParentheseFermante(char c);
    bool correspondParenthese(char ouvrante, char fermante);

    bool verifierExpression(const string& expr);
    double appliquerOperateur(double op1, double op2, char operateur);
    int priorite(char op);
    double evaluer(const string& expression);

    ~Expression();
};