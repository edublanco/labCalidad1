
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void resultados(int lBlanco, int lCom, int lCod, string nombre, bool vacio){
    int total= lCod + lBlanco + lCom;
    if(total == 0){
        cout << "Nombre del archivo: " << nombre<< "\n";
        cout << "--------------------------------------------"<<"\n";
        cout << "---------------- Archivo inexistente -------------"<< "\n";

    }
    else if(vacio == true){
        cout << "Nombre del archivo: " << nombre<< "\n";
        cout << "--------------------------------------------"<<"\n";
        cout << "---------------- Archivo vacio -------------"<< "\n";

    }else{
        cout << "Nombre del archivo: " << nombre<< "\n";
        cout << "--------------------------------------------"<<"\n";
        cout << "Cantidad de lineas en blanco: " << lBlanco << "\n";
        cout << "Cantidad de lineas con comentarios: " << lCom << "\n";
        cout << "Cantidad de lineas con c�digo: " << lCod<< "\n";
        cout << "--------------------------------------------"<<"\n";
        cout << "Cantidad total de lineas: " << total << "\n";

    }
}

bool docVacio(ifstream& doc){

    if ( doc.peek() == ifstream::traits_type::eof() )
        {
          return true;
        }
    return false;

}

void lector(ifstream& doc,string name){
    string S;
    int lBlanco = 0;
    int lCom = 0;
    int lCod = 0;
    int aux = 0;
    int sT = 0;
    bool com = false;
    bool dobleB = false;
    bool iCom =  false;
    bool iCom2 = false;
    bool eof = true;
    bool vacio =false;

    vacio = docVacio(doc);
    while (getline(doc, S)  || (doc.eof() && eof)) {


        if(doc.eof()){
            eof = false;
           // vacio = true;
        }
        if(eof== false && (S.empty()== true) /*(S[S.size()-1] != ' ')*/  ){
            vacio == true;
        }

        for(int i =0; i < S.size(); i ++){
            if(S[i] == ' ' || S[i] == '\t' ){
                sT ++;
            } else if(S[i] == '/' && S[i+1] == '/'){
                dobleB =true;

            }
             if(S[i] == '/' && S[i+1] ==  '*'){
                iCom = true;
                iCom2 = true;
            }
        }

        if(S.empty() || sT == S.size() ){
            lBlanco ++;
        }else if((dobleB) || (iCom) || (S[(S.size() - 1) ] == '/' && S[(S.size()-2)] ==  '*') ){
            lCom ++;
            dobleB = false;
            iCom=false;
        }else{
            lCod ++;
        }
        if((S[(S.size() - 1) ] == '/' && S[(S.size()-2)] ==  '*')){
                com = false;
                iCom2 = false;
            }
        if (com && (S.empty() || sT == S.size()) ){
            aux ++;
            lBlanco --;
        }else if(com){
            aux ++;
            lCod--;
        }
        if(iCom2){
            com = true;
        }
        sT = 0;
    }

    resultados(lBlanco, lCom + aux, lCod, name, vacio);

}

int main ()
{
string r;
cin >> r ;
ifstream doc(r);
lector(doc, r);


}



