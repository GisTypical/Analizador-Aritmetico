/**
 * Analizador Aritmético
 * Realizador por Gerardo Torres y  Nathalie Zambrano
**/

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// PROTOTYPE
bool analizarExp(vector<string> arr);
int operadores(char op);
int op_aritmetica(int a, int b, char op);
int resolverExpresion(string tokens);

// MAIN
int main(int argc, char const *argv[])
{
    string expresion = "";
    regex r("(ini)\\s?(\\{)\\s?([a-zA-Z_]+\\d*)\\s?(=)\\s?(.+)\\s?(;)\\s?(\\})\\s?(fin)");
    smatch match;
    vector<string> tokensExp;

    string resultado = "";

    cout << "Ingrese una expresion: ";
    getline(cin, expresion);

    if (regex_search(expresion, match, r))
    {

        ofstream archivo;
        archivo.open("Ltokens.txt", ios::out);

        archivo << "\t\t.:TOKENS:.\n\n";

        for (int i = 1; i < match.size(); i++)
        {
            if (match.str(i) == "ini" or match.str(i) == "fin")
            {
                archivo << match.str(i) << "\t\t\t\tPALABRA RESERVADA\n";
            }
            else if (match.str(i) == "{" or match.str(i) == ";" or match.str(i) == "}")
            {
                archivo << match.str(i) << "\t\t\t\tSIMBOLO ESPECIAL\n";
            }
            else if (match.str(i) == "=")
            {
                archivo << match.str(i) << "\t\t\t\tASIGNACION\n";
            }
            else if (i == 3)
            {
                archivo << match.str(i) << "\t\t\t\tIDENTIFICADOR\n";
            }
            else if (i == 5)
            {
                string cuerpo = match.str(i);
                resultado = cuerpo;

                for (int j = 0; j < cuerpo.size(); j++)
                {
                    if (cuerpo[j] == '+' or cuerpo[j] == '-' or cuerpo[j] == '*' or cuerpo[j] == '/' or cuerpo[j] == '^')
                    {
                        archivo << cuerpo[j] << "\t\t\t\tOPERADOR ARIMETICO\n";
                        tokensExp.push_back("op");
                    }
                    else if (cuerpo[j] == '(' or cuerpo[j] == ')')
                    {
                        archivo << cuerpo[j] << "\t\t\t\tSIMBOLO ESPECIAL\n";
                        if (cuerpo[j] == '(')
                        {
                            tokensExp.push_back("parA");
                        }
                        else
                        {
                            tokensExp.push_back("parC");
                        }
                    }
                    else if (cuerpo[j] == ' ')
                    {
                        continue;
                    }
                    else if (isdigit(cuerpo[j]))
                    {
                        string num = "";
                        while (isdigit(cuerpo[j]))
                        {
                            num.push_back(cuerpo[j]);
                            j++;
                        }
                        archivo << num << "\t\t\t\tNUMERO\n";
                        tokensExp.push_back("num");
                        j--;
                    }
                }
            }
        }
        archivo.close();

        if (analizarExp(tokensExp))
        {
            cout << "\nCADENA VALIDA\n";
            int r = resolverExpresion(resultado);
            cout << "Resultado de la expresion: " << r << endl;
        }
        else
        {
            cout << "\nX CADENA NO VALIDA X\n\n";
        }
    }
    else
    {
        cout << "\nX CADENA NO VALIDA X\n\n";
    }

    return 0;
}

// DEFINITION
bool analizarExp(vector<string> arr)
{
    bool anteriorOp = false;   // Anterior Operador?
    bool anteriorNum = false;  // Anterior Numero?
    bool anteriorParA = false; // Anterior Parentesis Abierto?
    int nParA = 0;             // Número de paréntesis abiertos

    // Verificar que no comience con un operador
    if (arr[0] == "op" || arr.back() == "op")
    {
        return false;
    }

    for (string tipo : arr)
    {
        if (tipo == "parA")
        {
            if (nParA < 0 || anteriorNum)
            {
                return false;
            }
            nParA++;
            anteriorParA = true;
            anteriorNum = false;
            anteriorOp = false;
        }
        if (tipo == "parC")
        {
            if (anteriorParA || anteriorOp)
            {
                return false;
            }
            nParA--;
            anteriorParA = false;
            anteriorNum = false;
            anteriorOp = false;
        }
        if (tipo == "op")
        {
            if (anteriorOp || anteriorParA)
            {
                return false;
            }
            anteriorOp = true;
            anteriorNum = false;
            anteriorParA = false;
        }
        if (tipo == "num")
        {
            if (anteriorNum)
            {
                return false;
            }
            anteriorNum = true;
            anteriorOp = false;
            anteriorParA = false;
        }
    }
    if (anteriorParA || anteriorOp)
    {
        return false;
    }

    /**
     * Si el número de parentesis abiertos es distinto a 0
     * Hubo un paréntesis que no se cerró o que no se abrió
    **/
    if (nParA != 0)
    {
        return false;
    }
    return true;
}


int operadores(char op){
    if(op == '+'||op == '-')
    return 1;
    if(op == '*'||op == '/')
    return 2;
    return 0;
}
 

int op_aritmetica(int a, int b, char op){
    switch(op){
        case '+': 
            return a + b;
        case '-': 
            return a - b;
        case '*': 
            return a * b;
        case '/': 
            return a / b;
    }
}


int resolverExpresion(string tokens){
    // int i;
     
    stack <int> numeros;
     
    stack <char> ops;
     
    for(int i = 0; i < tokens.length(); i++){
         
        if(tokens[i] == ' ')
            continue;
         
        else if(tokens[i] == '('){
            ops.push(tokens[i]);
        }
         
        else if(isdigit(tokens[i])){
            int val = 0;
             
            while(i < tokens.length() &&
                        isdigit(tokens[i]))
            {
                val = (val*10) + (tokens[i]-'0');
                i++;
            }
             
            numeros.push(val);
            i--;
        }
         
        else if(tokens[i] == ')')
        {
            while(!ops.empty() && ops.top() != '(')
            {
                int val2 = numeros.top();
                numeros.pop();
                 
                int val1 = numeros.top();
                numeros.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                numeros.push(op_aritmetica(val1, val2, op));
            }
             
            if(!ops.empty())
               ops.pop();
        }
         
        else
        {
            while(!ops.empty() && operadores(ops.top())
                                >= operadores(tokens[i])){
                int val2 = numeros.top();
                numeros.pop();
                 
                int val1 = numeros.top();
                numeros.pop();
                 
                char op = ops.top();
                ops.pop();
                 
                numeros.push(op_aritmetica(val1, val2, op));
            }
             
            ops.push(tokens[i]);
        }
    }
     
    while(!ops.empty()){
        int val2 = numeros.top();
        numeros.pop();
                 
        int val1 = numeros.top();
        numeros.pop();
                 
        char op = ops.top();
        ops.pop();
                 
        numeros.push(op_aritmetica(val1, val2, op));
    }
     
    return numeros.top();
}