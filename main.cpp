// ANALIZADOR ARITMETICO

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

//^ PROTOTYPE
bool analizarExp(vector<string> arr);

//^ MAIN
int main(int argc, char const *argv[])
{
    string expresion = "";
    regex r("(ini)\\s?(\\{)\\s?([a-zA-Z_]+\\d*)\\s?(=)\\s?(.+)\\s?(;)\\s?(\\})\\s?(fin)");
    smatch match;

    vector<string> tokensExp;

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
            cout << "\nCADENA VALIDA\n\n";
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

//^ DEFINITION
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