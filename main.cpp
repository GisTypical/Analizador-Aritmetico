// ANALIZADOR ARITMETICO

#include<iostream>
#include<fstream>
using namespace std;

struct Expresion
{
    string ini;
    string cuerpo;
    string fin;
} e;


int main(int argc, char const *argv[])
{
    string expresion;

    cout << "Ingrese una expresion: ";
    getline(cin, expresion);

    int si_ini = expresion.find("ini");
    int si_llave_iz = expresion.find("{");
    int si_llave_der = expresion.find("}");
    int si_fin = expresion.find("fin");

    size_t npos = string::npos;

    if (si_ini != npos and si_llave_iz != npos and si_llave_der != npos and si_fin != npos)
    {
        e.ini = expresion.substr(si_ini, 3);
        e.cuerpo = expresion.substr(si_llave_iz, expresion.size() - 8);
        e.fin = expresion.substr(si_fin);

        cout << e.ini << endl << e.cuerpo << endl << e.fin << endl;

        ofstream archivo;

        archivo.open("Ltokens.txt", ios::out);

        archivo << e.ini << "\tPALABRA RESERVADA" << endl;
        archivo << e.cuerpo << "\tEXPRESION" << endl;
        archivo << e.fin << "\tPALABRA RESERVADA" << endl;

        archivo.close();
    }
    else
    {
        cout << "Not found\n";
    }

    return 0;
}

