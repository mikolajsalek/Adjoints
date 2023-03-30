#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

void zapisz(vector<vector<int>> &vect, int N)
{
    ofstream plik;
    plik.open("lista_nastepnikow.txt");
    int help;

    plik << vect[0][0] << " " <<vect[0][1]<<" ";

    for (int i = 1; i < vect.size(); i++){

        if(vect[i][0] == vect[i-1][0]){
            plik << vect[i][1] << " ";
        }

        else if(vect[i][0] != vect[i-1][0]){

            plik<<endl;


            for(int j=0; j<vect[i].size(); j++)
            plik << vect[i][j]<<" ";
        }

    }
    plik.close();

}

void odczyt(int N, vector<int> vect[])
{
    ifstream plik1("nowalista.txt");
    string tekst;

    vector<int> temp;

    while(getline(plik1, tekst)){

        stringstream text_stream(tekst);
        string liczba;

        if(!cin != '\n'){

            while(getline(text_stream, liczba, ' ')){
                temp.push_back(stoi(liczba));
            }


            for(int m=0; m<temp.size()-1; m++){
                vect[temp.at(0)].push_back(temp.at(m+1));
            }

        }
        temp.clear();
    }

    for(int i=0; i < N; i++){
        sort(vect[i].begin(), vect[i].end());
    }

    plik1.close();
}

bool if_unique(vector<int> vect[], int i)
{
    for(int j=0; j < vect[i].size() - 1; j++){

        if(vect[i].at(j) == vect[i].at(j+1))
            return false;
    }

    return true;
}


bool czy_1graph(vector<int> vect[], int N)
{

    for(int i=0; i<N; i++){

        for(int j=0; j < vect[i].size(); j++){

            if(if_unique(vect, i) == false)
                return false;
        }
    }

    return true;
}

bool porownywanie(vector<int> a, vector<int> b)
{
    for(int i=0; i<a.size(); i++){

        for(int j=0; j<b.size(); j++){

            if(a.at(i) == b.at(j))
                return false;
        }
    }

    return true;
}

bool czy_sprzezony(vector<int> vect[], int N)
{

    for(int i=0; i<N-1; i++){

        for(int j=1; j<N; j++){

            if(porownywanie(vect[i], vect[j]) == false){

                if(vect[i] != vect[j])
                    return false;
            }
        }
    }
    return true;
}

void lista_poprzednikow(vector<int> vect1[], vector<int> vect[], int N)
{
    for(int i=0; i<N; i++){
        for(int j=0; j<vect[i].size(); j++){

            vect1[vect[i].at(j)].push_back(i);
        }
    }

}

bool czy_liniowy(vector<int> vect[], vector<int> vect1[], int N)
{
    for(int i=0; i<N-1; i++){

        for(int j=1; j<N; j++){

            if(porownywanie(vect[i], vect[j]) == false){

                if((vect[i]==vect[j]) && (porownywanie(vect1[i], vect[j]) == true))
                    return false;
            }
        }
    }

    return true;

}

vector<vector<int>> przeindeksowanie(vector<int> temp[], int N)
{
    int help3=0;
    int help2;
    vector<int> bez;

    for(int i=0; i<N; i++){

        help3 = 0;
        help2 = temp[i].at(1);

        for(int m=0; m<N; m++){

            if(help2 == temp[m].at(0)){
                help3++;
            }

        }

        if(help3==0){
            bez.push_back(temp[i].at(1));
        }

    }

    vector<vector<int>> grafW;

    for(int i=0; i<N; i++){

        grafW.push_back(temp[i]);
    }

    for(int i=0; i<bez.size(); i++){

        vector<int> v1;
        v1.push_back(bez.at(i));
        grafW.push_back(v1);
    }

    sort(grafW.begin(), grafW.end());

    for (int i = 0; i < grafW.size(); i++)
    {
        for (int j = 0; j < grafW[i].size(); j++)
        {
            cout << grafW[i][j] + 1<< " ";
        }
        cout << endl;
    }

    int W = N+bez.size();
    int help,wolny,licznik = 0;

    for(int i=0; i<W-1; i++){

        help = grafW[i][0];
        grafW[i][0] = licznik;

        for(int k=0; k<W; k++){
            for(int m=0; m<grafW[k].size(); m++){

                if(grafW[k][m] == help){
                    grafW[k][m] = licznik;
                }
            }
        }
        licznik++;

        if(W!=N){

                if(i+1==W-1){
           wolny = grafW[i+1][0];
           grafW[i+1][0] = licznik;

           for(int k=0; k<W; k++){
            for(int m=0; m<grafW[k].size(); m++){

                if(grafW[k][m]==wolny){
                    grafW[k][m] = licznik;
                }

            }
           }

        }


        }


        if(grafW[i][0] == grafW[i+1][0]){
            licznik--;
        }

    }

    return grafW;
}
vector<vector<int>> transformacja(vector<int> vect[], vector<int> temp[], int N)
{
    int licznik=0;
    vector<vector<int>> grafW;


    for(int i=0; i<N; i++){

        for(int j=0; j<2; j++){
            temp[i].push_back(licznik);
            licznik++;
        }
    }

    int help;

    for(int i=0; i<N; i++){

        for(int j=0; j<vect[i].size(); j++){

            help = temp[vect[i].at(j)].at(0);
            temp[vect[i].at(j)].at(0) = temp[i].at(1);

            for(int m=0; m<N; m++){

                for(int k=0; k<temp[m].size(); k++){

                    if(temp[m].at(k) == help){
                         temp[m].at(k) = temp[i].at(1);
                    }

                }
            }

        }
    }


    grafW = przeindeksowanie(temp, N);
    cout<<endl;
    for (int i = 0; i < grafW.size(); i++)
    {
        for (int j = 0; j < grafW[i].size(); j++)
        {
            cout << grafW[i][j] << " ";
        }
        cout << endl;
    }

    return grafW;
}



int main()
{
    int N=15;

    vector<int> vect[N]; //lista nastepnikow
    vector<int> vect1[N]; //lista poprzednikow
    vector<int> temp[N]; //org




    odczyt(N, vect);



    if(czy_1graph(vect, N) == false){
        cout<<"Nie jest to 1-graph"<<endl;
        cout<<"Nie jest to graf sprzezony";

        return 0;
    }
    else if(czy_1graph(vect, N) == true)
        cout<<"To jest 1-graph";

    cout<<endl;
    lista_poprzednikow(vect1, vect, N);

    if(czy_sprzezony(vect, N) == false)
        cout<<"Nie jest to graf sprzezony";
    if(czy_sprzezony(vect, N) == true){
            cout<<endl;
        vector<vector<int>> graf_wyjsciowy = transformacja(vect, temp, N);
        zapisz(graf_wyjsciowy, N);
         cout<<"Jest to graf sprzezony";

    }

    cout<<endl;

    if(czy_liniowy(vect, vect1, N) == false)
        cout<<"Nie jest to graf liniowy";
    if(czy_liniowy(vect, vect1, N) == true)
        cout<<"Jest to graf liniowy";

    cout<<endl;









    return 0;
}
