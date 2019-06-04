#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef struct{
    int book;
    int quantity;
}request;

typedef struct{
    int local;
    int coefficient;
    int distance;
    float custo;
}graf;
typedef struct{
    int v;
    int dv;
}dupla;

class library{
    public:
        int getQuantityBook(int idBook){
            return this->books[idBook];
        }
        void replacementBook(int idBook, int quantify){
            this->books[idBook] += quantify;
        }
        void insertBook(int idBook, int quantify){
            this->books[idBook] = quantify; 
        }
        void sellBook(int idBook, int quantify){
            this->books[idBook] -= quantify;
        }
        bool dijkstraCalculated(){
            this->bDijkstra;
        }
        int idMenorDistancia(int id){
            return (this->leastCust[id].v);
        }
        int menorCustoPara(int id){
            return (this->leastCust[id].dv);
        }
        int idPrecusor(int id){
            return this->precusor[id]; 
        }
        void saveDijkstra(vector<dupla> custo, vector<int> precursores){
            this->leastCust = custo;
            this->precusor = precursores;
            this->bDijkstra = true;
        }
        void changedDikstra(){
            this->bDijkstra = false;
        }
        library(int quantityBook, int nPlaces){
            this-> books.resize(quantityBook);
            this-> precusor.resize(nPlaces); // id == armazem
            this-> leastCust.resize(nPlaces); //nao necessariamente
            this-> bDijkstra = false;
        }
    private:
        vector<int> books;
        vector<dupla> leastCust;
        vector<int> precusor;
        bool bDijkstra;
};
bool compare(dupla a, dupla b){
    if(a.dv != b.dv){
        return a.dv < b.dv;
    }
    return a.v < b.v;
}

void heapify(vector<dupla>&H, int i,vector<int>&indexes){
    int l= 2*i+1, r= 2*i+2, m = i;
    if(l < H.size() && compare(H[l],H[m]))
        m = l;
    if(r<H.size() && compare(H[r],H[m]))
        m = r;
    if(m!=i){
        int aux;
        /* aux = indexes[H[i].v]; //aux == posicao na heap
        indexes[H[i].v] = indexes[H[m].v];
        indexes[H[m].v] = aux; */

        swap(H[i],H[m]);
        heapify(H,m,indexes);
    }
}

void build_heap(vector<dupla>&H, vector<int>&indexes){
    for(int i = floor(H.size()/2)-1; i>=0; i--){
        heapify(H,i,indexes);
    }
}

dupla heap_extract(vector<dupla>& H, vector<int>& indexes){
    dupla r = H[0];
    
    /*int aux = indexes[H[0].v]; //aux == posicao na heap
    indexes[H[0].v] = indexes[H[H.size()-1].v];
    indexes[H[H.size()-1].v] = aux; */
    
    swap(H[0],H[H.size()-1]);
    H.pop_back();
    heapify(H,0,indexes);
    return r;
}

void bubble_up(vector<dupla>& H, int i, vector<int>& indexes){
    int p;
    p = floor((i-1)/2);
    while(i > 0 && compare(H[i],H[p])){
        int aux;
        /* aux = indexes[H[i].v]; //aux == posicao na heap
        indexes[H[i].v] = indexes[H[p].v];
        indexes[H[p].v] = aux; */

        swap(H[i],H[p]);
        i = p;
        p = floor((i-1)/2);
    }
}
void heap_insert(vector<dupla>&H, dupla v,vector<int>& index){
    H.push_back(v);
    int i = H.size() - 1;
    bubble_up(H,i,index);
}

vector<int> dijkstra(vector<vector<graf> >&Grafo, vector<dupla>& custo, int size,int origin){
    vector<int> precursor(size, -1);
    vector<int> indexes(size);
    custo[origin].dv = 0;
    custo[origin].v = origin;

    vector<dupla> H; //HEAP
    dupla rem;
    rem.v = origin;
    rem.dv = 0;
    heap_insert(H,rem,indexes);

    while(H.size() > 0){
        rem = heap_extract(H,indexes);
        for(int i=0; i < Grafo[rem.v].size(); i++){
            if( custo[Grafo[rem.v][i].local].dv > rem.dv + Grafo[rem.v][i].custo){
                
                custo[Grafo[rem.v][i].local].dv = rem.dv + Grafo[rem.v][i].custo;
                precursor[Grafo[rem.v][i].local] = rem.v;
                
                //heap update -------
                dupla add;
                add.v = Grafo[rem.v][i].local;
                add.dv = custo[Grafo[rem.v][i].local].dv;
                custo[Grafo[rem.v][i].local].v = Grafo[rem.v][i].local;
                heap_insert(H,add,indexes);
            }
        }
    }
    return precursor;
}


bool compareTwoElements(const dupla &a,const dupla &b){
    return a.dv < b.dv;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int x,y,d,w,q,t,m,id;
    int nLocality, nRoad, nBooks; //nLocality = V, nRoad = E
    string command;

    cin >> nLocality >> nRoad >> nBooks;
    vector<library> librarys(nLocality, library(nBooks,nLocality));

    vector<vector<graf> > distances(nLocality); //matriz de lista adjacencia do grafo
    vector<vector<int> > auxId(nLocality,vector<int>(nLocality));

    vector<request> requests;
    graf add;

    for(int k=0; k<nRoad; k++){
        cin >> x >> y >> add.distance >> add.coefficient;
        add.custo = (add.distance*(100 + add.coefficient))/100.;

        add.local = y; //index do armazém
        distances[x].push_back(add);
        auxId[x][y] = distances[x].size()-1;

        add.local = x;
        distances[y].push_back(add);
        auxId[y][x] = distances[y].size()-1;
    }
    for(int a = 0; a < nLocality; a++){
        for(int b=0; b<nBooks; b++){
            cin >> q;
            librarys[a].insertBook(b, q);
        }
    }
    do{
        cin >> command; 
        if(command == "ORD"){
            cin>> t >> m; // pedido a ser entregue na localidade t, m= quantidade de itens
            requests.resize(m);
            for(int k=0; k < m; k++){
                cin >> id >> q;
                requests[k].book = id;
                requests[k].quantity = q;
            }
            //verificando se tenho os pedidos na loja que está requerindo
            bool quantidadeSuficiente = true;
            for(int i = 0; i < m && quantidadeSuficiente; i++){
                if(librarys[t].getQuantityBook(requests[i].book) < requests[i].quantity)
                    quantidadeSuficiente = false;
            }
            if(quantidadeSuficiente){
                for(int i = 0; i < m; i++){
                    librarys[t].sellBook(requests[i].book,requests[i].quantity);
                }
                cout << t<< " "<< "0"<<endl;
            }
            //não tem na loja que o comprador está
            else{
                    dupla ex;
                    ex.v = 0;
                    ex.dv = 0x3f3f3f3f;
                    vector<dupla> custo(nLocality,ex);

                    vector<int> precursores = dijkstra(distances,custo,nLocality,t);

                    sort(custo.begin(),custo.end(),compareTwoElements);

                    librarys[t].saveDijkstra(custo,precursores);
                    //-------------------dijkstra calculado...
                    bool vendido = false;
                    for(int j = 1; j < nLocality && !vendido; j++){ //varre localidades, vetor dos menores custos

                        bool quantidadeSuficiente = true;
                        for(int i = 0; i < m && quantidadeSuficiente ; i++){ //varre pedidos
                            if(librarys[librarys[t].idMenorDistancia(j)].getQuantityBook(requests[i].book) < requests[i].quantity)
                                quantidadeSuficiente = false;
                        }
                        if(quantidadeSuficiente){
                            // j vai vender para t
                            vendido = true;
                            for(int i = 0; i < m; i++){
                                librarys[librarys[t].idMenorDistancia(j)].sellBook(requests[i].book,requests[i].quantity);
                            }
                            int id = custo[j].v;
                            cout << id;

                            while(id != t){
                                id = precursores[id];
                                cout <<" "<<id;
                            }
                            cout << " " <<librarys[t].menorCustoPara(j)<<endl;
                        }
                    }
                    if(!vendido)
                        cout << "OOS"<<endl;
                }
        }
        else if(command == "UPD"){
            cin >> x >> y >> w;
            distances[x][auxId[x][y]].coefficient = w;
            distances[x][auxId[x][y]].custo = (distances[x][auxId[x][y]].distance*(100 + distances[x][auxId[x][y]].coefficient))/100.;
            distances[y][auxId[y][x]].coefficient = w;
            distances[y][auxId[y][x]].custo = (distances[y][auxId[y][x]].distance*(100 + distances[y][auxId[y][x]].coefficient))/100.;

        }
        else if(command == "STK"){
            int I;
            cin >> x >> I >> q;
            librarys[x].replacementBook(I,q);
        }

    }while(command != "END");


    return 0;
}