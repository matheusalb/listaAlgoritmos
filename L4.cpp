#include <iostream>
#include <string>
#include <cmath>

using namespace std;
typedef struct{
    int id;
    int time;
    int rank;
}Soldier;

typedef struct{
    int squad;
    int positionHeap;
}par;

typedef struct{
    Soldier soldier[1000000];
    //int soldierIds[1000000];
    //int nIds;
    int nSoldiers;
    int crt;
}Squad;

bool checkCriterion(Soldier sold1, Soldier sold2, int ctr){ //sold1 §(domina) sold2 ? 1:0

    if(ctr == 0){
        if(sold1.time < sold2.time)
            return true;
        else if(sold1.time == sold2.time && sold1.rank > sold2.rank) 
            return true;
        else if(sold1.time == sold2.time && sold1.rank == sold2.rank && sold1.id<sold2.id)
            return true;
        else 
            return false;
    }
    else if(ctr == 1){
        if(sold1.time > sold2.time)
            return true;
        else if(sold1.time == sold2.time && sold1.rank < sold2.rank) 
            return true;
        else if(sold1.time == sold2.time && sold1.rank == sold2.rank && sold1.id<sold2.id)
            return true;
        else 
            return false;    
    }
    else if(ctr == 2){
        if(sold1.rank < sold2.rank)
            return true;
        else if(sold1.rank == sold2.rank && sold1.time > sold2.time)
            return true;
        else if(sold1.time == sold2.time && sold1.rank == sold2.rank && sold1.id<sold2.id)
            return true;
        else 
            return false;    
    }
    else if(ctr == 3){
        if(sold1.rank > sold2.rank)
            return true;
        else if(sold1.rank == sold2.rank && sold1.time < sold2.time)
            return true;
        else if(sold1.time == sold2.time && sold1.rank == sold2.rank && sold1.id<sold2.id)
            return true;
        else 
            return false;    
    }
}

void heapify(Soldier* soldier, int i,int n,int ctr,par* soldierIds){
    Soldier temp;
    int l = 2*i+1;
    int r = 2*i+2;
    int m = i;
    if(l < n && checkCriterion(soldier[l],soldier[m],ctr))
        m = l;
    if(r < n && checkCriterion(soldier[r],soldier[m],ctr))
        m = r;
    if(m != i){
        temp = soldier[i];
        soldier[i] = soldier[m];
        soldier[m] = temp;
        soldierIds [ soldier[i].id ].positionHeap = i;
        soldierIds [ soldier[m].id ].positionHeap = m ;
        heapify(soldier,m,n,ctr,soldierIds);
    }
    //return m;
}

void build_heap(Soldier* soldier,int n,int ctr,par* soldierIds){
    //int m;
    for(int i = floor(n/2)-1; i>=0 ; i--){
        heapify(soldier,i,n,ctr,soldierIds);
        //soldierIds[ soldier[i].id ].positionHeap = m;
    }
}

void bubble_up(Soldier* soldier, int ctr, int i,par* allSoldiers){
    int p;
    Soldier temp;

    p = floor((i-1)/2);
    while(i > 0 && checkCriterion(soldier[i],soldier[p],ctr)){
        temp = soldier[i];
        soldier[i] = soldier[p];
        soldier[p] = temp;
        
        allSoldiers[ soldier[p].id ].positionHeap = p;
        allSoldiers[ soldier[i].id ].positionHeap = i;

        i = p;
        p = floor((i-1)/2);
    }
}
Soldier heap_extract(Soldier* soldier,int n,int ctr,par* allSoldiers){
    Soldier r = soldier[0];
    Soldier temp;

    temp = soldier[0];
    soldier[0] = soldier[n-1];
    soldier[n-1] = temp;
    n--;
    
    allSoldiers[ r.id ].positionHeap = -1;
    allSoldiers[ r.id ].squad = -1;

    heapify(soldier,0,n,ctr,allSoldiers);
    
    return r;
}

void heap_insert(Soldier* soldier, int ctr, Soldier* add, int n, par* allSoldiers){

    soldier[n] = (*add);
    allSoldiers[ soldier[n].id ].positionHeap = n;
    bubble_up(soldier,ctr,n, allSoldiers); 
}

//soldier[id] = posição na heap

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int S,q,p,i,id,t,r,j,tam;
    int posHeap, tSquad;
    Squad *squad;
    string command;
    char sp = ' ';
    Soldier removed,add;
    par allSoldiers[1000000];
    int p0;

    cin >> S;
    squad = new Squad[S];

    for(i=0; i< S; i++){ //SQUAD;
        cin >> q >> p;

        for(j = 0; j < q; j++){
            cin >> squad[i].soldier[j].id >> squad[i].soldier[j].time >> squad[i].soldier[j].rank;
            allSoldiers[ squad[i].soldier[j].id ].squad = i;
            allSoldiers[ squad[i].soldier[j].id ].positionHeap = j;
        }
        squad[i].nSoldiers = q;
        squad[i].crt = p;
        build_heap(squad[i].soldier,squad[i].nSoldiers,squad[i].crt, allSoldiers);
        //cout << "i == "<< i <<endl;
      /*    for(int c = 0; c < q; c++)
            cout << squad[i].soldier[c].id << sp << squad[i].soldier[c].time <<sp<<  squad[i].soldier[c].rank <<endl; 
     */}
    do{
        cin >> command;
        
        if(command == "ADD"){
            cin >> i >> id >> t >> r; 
            tam = squad[i].nSoldiers;
            add.id = id;
            add.time = t;
            add.rank = r;
            allSoldiers[id].squad = i;
            heap_insert(squad[i].soldier,squad[i].crt,&add,tam,allSoldiers);

            squad[i].nSoldiers++;
            cout << squad[i].soldier[0].id << sp << squad[i].soldier[0].time << sp << squad[i].soldier[0].rank << endl;
        }
        else if(command == "UPD"){
            cin >> id >> t >> r;
            posHeap = allSoldiers[id].positionHeap;
            tSquad = allSoldiers[id].squad;
            //cout << "posHeap e tSquad:"<<posHeap<< sp << tSquad<<endl;

            squad[tSquad].soldier[posHeap].time = t;
            squad[tSquad].soldier[posHeap].rank = r;

            heapify(squad[tSquad].soldier,posHeap,squad[tSquad].nSoldiers,squad[tSquad].crt,allSoldiers);
            bubble_up(squad[tSquad].soldier, squad[tSquad].crt, posHeap, allSoldiers);
            //O SQUAD É TSQUAD, POSICAO PROBLEMATICA DA HEAP É POSHEAP
             cout << squad[tSquad].soldier[0].id << sp << squad[tSquad].soldier[0].time << sp << squad[tSquad].soldier[0].rank << endl;
        }
        else if(command == "MOV"){
            cin >> i >> j;
            removed = heap_extract(squad[i].soldier, squad[i].nSoldiers, squad[i].crt,allSoldiers);
            squad[i].nSoldiers--;
            
            tam = squad[j].nSoldiers;
            heap_insert(squad[j].soldier,squad[j].crt,&removed,tam,allSoldiers);
            allSoldiers[removed.id].squad = j;
            squad[j].nSoldiers++;
            if(squad[i].nSoldiers == 0)
                cout << "-1" << sp << "-1" << sp << "-1" << sp << squad[j].soldier[0].id << sp << squad[j].soldier[0].time << sp << squad[j].soldier[0].rank << endl;
            else
                cout << squad[i].soldier[0].id << sp << squad[i].soldier[0].time << sp << squad[i].soldier[0].rank << sp << squad[j].soldier[0].id << sp << squad[j].soldier[0].time << sp << squad[j].soldier[0].rank << endl;
        }
        else if(command == "CHG"){
            cin >> i >> j >> q >> p;
            
            for(int k = 0; k < q; k++){
                removed = heap_extract(squad[i].soldier, squad[i].nSoldiers, squad[i].crt,allSoldiers);
                squad[i].nSoldiers--;
            
                tam = squad[j].nSoldiers;
                heap_insert(squad[j].soldier,squad[j].crt,&removed,tam,allSoldiers);
                allSoldiers[removed.id].squad = j;
                squad[j].nSoldiers++;
            }
            squad[i].crt = p;
            build_heap(squad[i].soldier,squad[i].nSoldiers,squad[i].crt,allSoldiers);
            if(squad[i].nSoldiers == 0)
                cout << "-1" << sp << "-1" << sp << "-1" << sp << squad[j].soldier[0].id << sp << squad[j].soldier[0].time << sp << squad[j].soldier[0].rank << endl;
            else
                cout << squad[i].soldier[0].id << sp << squad[i].soldier[0].time << sp << squad[i].soldier[0].rank << sp << squad[j].soldier[0].id << sp << squad[j].soldier[0].time << sp << squad[j].soldier[0].rank << endl;
        }
        else if(command == "KIA"){
            cin >> id;
            posHeap = allSoldiers[id].positionHeap;
            tSquad = allSoldiers[id].squad;

            Soldier r = squad[tSquad].soldier[posHeap];
            Soldier temp;
            int n = squad[tSquad].nSoldiers;

            temp = squad[tSquad].soldier[posHeap];
            squad[tSquad].soldier[posHeap] = squad[tSquad].soldier[n-1];
            squad[tSquad].soldier[n-1] = temp;
            n--;
            squad[tSquad].nSoldiers--;
                //ultimo elemnto agora está na posicao removida
            allSoldiers[ squad[tSquad].soldier[posHeap].id ].positionHeap = allSoldiers[r.id].positionHeap;

            allSoldiers[ r.id ].positionHeap = -1;
            allSoldiers[ r.id ].squad = -1;

            heapify(squad[tSquad].soldier, posHeap, n,squad[tSquad].crt,allSoldiers);
            bubble_up(squad[tSquad].soldier,squad[tSquad].crt,posHeap,allSoldiers);

            if(squad[tSquad].nSoldiers == 0)
                cout << "-1" << sp << "-1" << sp << "-1" << endl;
            else
                cout << squad[tSquad].soldier[0].id << sp << squad[tSquad].soldier[0].time << sp << squad[tSquad].soldier[0].rank << endl;
        }

    }while(command != "END");


    return 0;
}