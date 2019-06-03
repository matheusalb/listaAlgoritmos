#include <iostream>
#include <vector>
#include <math>

using namespace std;
typedef struct{
    int book;
    int quantity;
}request;

typedef struct{
    int local;
    int coefficient;
    int distance;
}graf;

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
        library(int quantityBook){
            this-> books.resize(quantityBook);
            this-> precusor.resize(quantityBook); 
            this->leastDistance.resize(quantityBook);
            this->bDijkstra = false;
        }
    private:
        vector<int> books;
        vector<int> leastDistance;
        vector<int> precusor;
        bool bDijkstra;
};

void heapify(vector<int>&H, int i){
    int l= 2*i+1, r= 2*i+2, m = i;
    if(l < H.size() && H[l] <= H[m])
        m = l;
    if(r<H.size() && H[r] <= H[m])
        m = r;
    if(m!=i)
        swap(H[i],H[m]);
        heapify(H,m);
}

vector<int> build_heap(vector<int>H){
    for(int i = floor(H.size()/2)-1; i>=0; i--){
        heapify(&H,i);
    }
    return H;
}
int heap_extract(vector<int>& H){
    int r = H[0];
    swap(H[0],H[H.size()-1]);
    H.pop_back();
    heapify(H,0);
    return r;
}

void dijkstra(vector<vector<int>>&Grafo,int size,int origin){
    vector<int> distance(size, 0x3f3f3f3f);
    vector<int> precursor(size, -1);
    distance[origin] = 0;
    vector<int> H(size);
    H = build_heap(distance);
    
    while(H.size() > 0){

    }
}

int main(){
    int x,y,d,w,q,t,m,id;
    int nLocality, nRoad, nBooks; //nLocality = V, nRoad = E
    string command;

    cin >> nLocality >> nRoad >> nBooks;
    //cin.ignore();
    vector<library> librarys(nLocality, library(nBooks));
    vector<vector<graf>> distances(nLocality); //matriz de lista adjacencia do grafo
    vector<request> requests;

    for(int k=0; k<nRoad; k++){
        cin >> x >> y >> d >> w;
        
        coefficient[x][y] = w;
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
                if(librarys[t].dijkstraCalculated()){
                    
                }
            }
        }


    }while(command != "END");


    return 0;
}