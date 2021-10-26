// PRUEBA DE REGEX

#include<iostream>
#include<regex>
#include<fstream>
using namespace std;

int main(int argc, char const *argv[])
{
    string expresion = "";
    regex r ("(ini)\\s?(\\{)\\s?([a-zA-Z_]+\\d*)\\s?(=)\\s?((\\(?\\s?\\d+\\s?[\\+\\-\\*\\/\\^]*\\s?\\d*\\)?\\s?[\\+\\-\\*\\/\\^]?\\s?)+)\\s?(;)\\s?(\\})\\s?(fin)");
    smatch match;

    cout << "Ingrese una expresion: ";
    getline(cin, expresion);

    if (regex_search(expresion, match, r))
    {
        cout << "\nCADENA VALIDA\n\n";

        ofstream archivo;
        archivo.open("Ltokens.txt", ios::out);

        archivo << "\t\t.:TOKENS:.\n\n";
        cout << "\t\t.:TOKENS:.\n\n";
        // cout << match.str(5) << endl << endl;

        for (int i = 1; i < match.size(); i++)
        {
            if (match.str(i) == "ini" or match.str(i) == "fin")
            {
                archivo << match.str(i) << "\t\t\t\tPALABRA RESERVADA\n";
                cout << match.str(i) << "\t\t\t\tPALABRA RESERVADA\n";
            }
            else if (match.str(i) == "{" or match.str(i) == ";" or match.str(i) == "}")
            {
                archivo << match.str(i) << "\t\t\t\tSIMBOLO ESPECIAL\n";
                cout << match.str(i) << "\t\t\t\tSIMBOLO ESPECIAL\n";
            }
            else if (match.str(i) == "=")
            {
                archivo << match.str(i) << "\t\t\t\tASIGNACION\n";
                cout << match.str(i) << "\t\t\t\tASIGNACION\n";
            }
            else if (i == 3)
            {
                archivo << match.str(i) << "\t\t\t\tIDENTIFICADOR\n";
                cout << match.str(i) << "\t\t\t\tIDENTIFICADOR\n";
            }
            else if (i == 5)
            {
                string cuerpo = match.str(i);

                for (int j = 0; j < cuerpo.size(); j++)
                {
                    if (cuerpo[j] == '+' or cuerpo[j] == '-' or cuerpo[j] == '*' or cuerpo[j] == '/' or cuerpo[j] == '^')
                    {
                        archivo << cuerpo[j] << "\t\t\t\tOPERADOR ARIMETICO\n";
                        cout << cuerpo[j] << "\t\t\t\tOPERADOR ARIMETICO\n";
                    }
                    else if (cuerpo[j] == '(' or cuerpo[j] == ')')
                    {
                        archivo << cuerpo[j] << "\t\t\t\tSIMBOLO ESPECIAL\n";
                        cout << cuerpo[j] << "\t\t\t\tSIMBOLO ESPECIAL\n";
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
                        cout << num << "\t\t\t\tNUMERO\n";
                        j--;
                    }
                }
            }
        }

        archivo.close();
    }
    else
    {
        cout << "CADENA INVALIDA\n";
    }
    
    return 0;
}
