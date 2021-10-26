// ANALIZADOR ARITMETICO

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

struct Expresion
{
    string ini;
    string cuerpo;
    string fin;
} e;

bool analizarExp(string cuerpo);

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

bool analizarExp(string cuerpo)
{
    vector<string> arr;

    arr.push_back("num");
    arr.push_back("op");
    arr.push_back("parA");
    arr.push_back("num");
    arr.push_back("op");
    arr.push_back("num");
    arr.push_back("op");
    arr.push_back("parC");

    bool anteriorOp = false;   // Anterior Operador?
    bool anteriorNum = false;  // Anterior Numero?
    bool anteriorParA = false; // Anterior Parentesis Abierto?
    int nParA = 0;             // Número de paréntesis abiertos

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
    if (nParA != 0)
    {
        return false;
    }

    return true;
}