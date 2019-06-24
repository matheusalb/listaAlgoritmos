#include <bits/stdc++.h>
using namespace std;

class Rainha{
    public:
        int r, c;
        Rainha(int x, int y){
            this->r = x;
            this->c = y;
        }
};

vector<vector<int>> sol2d;
vector<vector<int>> solRestrita;
vector<vector<vector<int>>> sol3d;

bool conflict(Rainha a, Rainha b){
    if(a.r == b.r) return true;
    if(a.c == b.c) return true;
    if((a.r + a.c)==(b.r + b.c)) return true; //diagonal '/'
    if((a.r - a.c)==(b.r - b.c)) return true; //diagonal '\'
    else return false;
}

void backtracking2D(int r, int N, vector<int>& sol, bool restrita, vector<int> rainhasFixas){
    if(r < 0){
        sol2d.push_back(sol);
        if(restrita == true)
            solRestrita.push_back(sol);
        return;
    }
    //varrendo colunas
    for(int c = 0; c < N; c++){
        bool conflito = false;
        //varrendo vetor das rainhas postas até o momento
        for(int i = r + 1; i < sol.size(); i++){ //i diz a linhas, v[i]== coluna
            //if(sol[i] != -1){
                if(conflict(Rainha(i,sol[i]),Rainha(r,c))){
                    conflito = true; 
                    break;
                }
            //}
        }
        if(!conflito){
            bool ent = false;
            if(rainhasFixas[r] != -1 && rainhasFixas[r] != c && restrita){
                restrita = false;
                ent = true;
            }
            sol[r] = c;
            backtracking2D(r - 1, N, sol,restrita, rainhasFixas);
            if(ent == true)
                restrita = true;
            sol[r] = -1;
        }
    }
    return;
}
bool conflict3D(vector<int> a, vector<int> b){
    for(int i = 0; i< a.size(); i++){
        if(a[i] == b[i])
            return true;
    }
    return false;
}

void backtracking3D(int plane, int N, int F, vector<vector<int>>& sol){
    if(plane < 0){
        sol3d.push_back(sol);
        return;
    }
    if(plane != F){
        for(int s = 0; s < sol2d.size(); s++){
            bool conflito = false;

            for(int i = plane + 1; i< sol.size(); i++){
                if(conflict3D(sol2d[s], sol[i])){
                    conflito = true;
                    break;
                }
            }
            if(!conflito){
                sol[plane] = sol2d[s];
                backtracking3D(plane - 1, N, F, sol);
                sol[plane] = vector<int>(N, -1);
            }
        }
    }
    else{ //plane == F
        for(int s = 0; s < solRestrita.size(); s++){
            bool conflito = false;

            for(int i = plane + 1; i < sol.size(); i++){
                if(conflict3D(solRestrita[s], sol[i])){
                    conflito = true;
                    break;
                }
            }
            if(!conflito){
                sol[plane] = solRestrita[s];
                backtracking3D(plane - 1,N, F, sol);
                sol[plane] = vector<int>(N, -1);
            }
        }
    }

    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N,P,F;
    int x, y;
    cin >> N >> P >> F;
    vector<int> rainhasFixas(N, -1);

    for(int i = 0; i < P;i++){
        cin >> x >> y;
        rainhasFixas[x] = y;
    }
    //calculo soluções 2D
    vector<int> sol(N, -1);
    bool restrita = true;
    backtracking2D(N-1,N, sol, restrita, rainhasFixas);
   /*  for(int i =0 ;i <sol2d.size(); i++){
        for(int j = 0; j < N; j++)
            cout<< sol2d[i][j] << " ";
        cout << endl;
    }
 */

    cout<< solRestrita.size()<< endl;
    for(int i = 0; i< solRestrita.size(); i++){
        cout << i<<":";
        for(int j = 0; j< N; j++){
            cout << " " << solRestrita[i][j];
        }
        cout<<endl<<endl;
    }

    vector<vector<int>> solution3d(N, vector<int>(N, -1));
    backtracking3D(N-1, N, F, solution3d);

    cout << sol3d.size() <<endl;
    for(int k = 0; k < sol3d.size(); k++){
        cout << k<<":"<<endl;
        for(int i=0; i < N; i++){ //varendo planos
            for(int j = 0; j < N; j++){ //tabuleiro do plano
                cout << sol3d[k][i][j];
                if(j!= N-1)
                    cout << " ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    return 0;
}