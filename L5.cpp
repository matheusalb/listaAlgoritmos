#include <iostream>
#include <vector>
#include <string>

typedef struct node{
    int id;
    struct node* par;
}Node;

using namespace std;

class Agent{
    public:
        bool** QRcode;
        bool exist;
        Node* equivalencia;
        vector<int> nosClick;
        bool foundedClick;

        Agent(int k){
            this -> exist = false;
            this -> foundedClick = false;
            this -> nosClick.resize(k);
        }
};

Node* find_PC(Node* x){
    if( x->par == x )
        return x;
    x->par = find_PC(x->par);

    return x->par;
}

int main(){
    int A, N, K, Q, X, Y;
    int number;
    string line;
    Node* raizX;
    Node* raizY;

    cin >> A >> N >> K >> Q; 
    vector<Agent> agents(A, Agent(K));
    
//GERANDO PERMUTAÇÕES ********************************
    vector<vector<int>> numbers;
    vector<int> linha(K);
    for(int w = 0; w < K; w++){ //1 permutação
       linha[w] = w;
        if(w == K -1)
            linha[w]--;
    }

    for(int indice = K - 1; indice >= 0 ; indice --){
        linha[indice]++;

        while( linha[indice] < N - ( (K - 1) - indice)){ //nao passou do limite da casa, ou seja, vou testar!!!!

            for(indice = indice + 1; indice < K; indice++){
                linha[indice] = linha[indice - 1] + 1;
            }
            indice--;
            numbers.push_back(linha);

            linha[indice]++;
        }
    }
/*********************************************/

    for(int i = 0; i < Q; i++){ 
        cin >> X >> Y;

        if(!agents[X].exist){

            agents[X].QRcode = new bool*[N];
            for(int p = 0; p < N; p++)
                agents[X].QRcode[p] = new bool[N];

            for(int j = 1; j < N; j++){
                cin >> line;

                for(int k = 0; k < line.size(); k++){
                    number = line[k] - '0';
                    agents[X].QRcode[j][k] = number;
                }
            }

            agents[X].equivalencia = new Node;
            agents[X].equivalencia->id = X;
            agents[X].equivalencia->par = agents[X].equivalencia;

            agents[X].exist = true;
        }
        if(!agents[Y].exist){
            agents[Y].QRcode = new bool*[N];
            for(int p = 0; p < N; p++)
                agents[Y].QRcode[p] = new bool[N];

            for(int j = 1; j < N; j++){
                cin >> line;
                //cin.ignore();
                for(int k = 0; k < line.size(); k++){
                    number = line[k] - '0';
                    agents[Y].QRcode[j][k] = number;
                }
            }
            agents[Y].equivalencia = new Node;

            agents[Y].equivalencia->id = Y;
            agents[Y].equivalencia->par = agents[Y].equivalencia;
            agents[Y].exist = true;
        }

        if(agents[X].foundedClick == true || agents[Y].foundedClick == true){
            if(agents[X].foundedClick)
                raizX = find_PC(agents[X].equivalencia);
            else
                raizX = agents[X].equivalencia;
            if(agents[Y].foundedClick)
                raizY = find_PC(agents[Y].equivalencia);
            else
                raizY = agents[Y].equivalencia;

            if(raizX->id == raizY->id){
                cout << "SUCC ";
                for(int z = 0; z < K; z++){
                    if(z == K - 1)
                        cout << agents[raizX->id].nosClick[z] << endl;
                    else
                        cout << agents[raizX->id].nosClick[z] << " ";
                }
            }


            else{ //pegar o click encontrado e comparar com o outro

                if(agents[X].foundedClick == true && agents[Y].foundedClick == true){
                    bool identicos = true; 
                    for(int l = 0; l< K && identicos; l++){
                        if(agents[X].nosClick[l] != agents[Y].nosClick[l]){
                            identicos = false;
                            break;
                        }
                    }
                    if(identicos){
                        raizY->par = raizX;
                        cout << "SUCC ";
                        for(int z = 0; z < K; z++){
                            if(z == K - 1)
                                cout << agents[raizX->id].nosClick[z] << endl;
                            else
                                cout << agents[raizX->id].nosClick[z] << " ";
                        }
                    }
                    else
                        cout<< "FAIL"<<endl;     
                }



                else if(agents[X].foundedClick == true){ //diagonal inferior i > j
                    //verifico se X encaixa em Y;
                    bool identicos = true;
                    for(int c = 0; c < K && identicos; c++){ //vetor ordenado
                        for(int l = c + 1; l < K; l++){
                            if(agents[Y].QRcode[ agents[X].nosClick[l] ][ agents[X].nosClick[c] ] == false){ 
                                identicos = false;
                                break;
                            }
                        }
                    }
                    if(identicos){
                        agents[Y].nosClick = agents[X].nosClick;
                        agents[Y].foundedClick = true;
                        raizY->par = raizX;
                        cout << "SUCC ";
                        for(int z = 0; z < K; z++){
                            if(z == K - 1)
                                cout << agents[X].nosClick[z] << endl;
                            else
                                cout << agents[X].nosClick[z] << " ";
                        }
                    }
                    else
                        cout << "FAIL"<<endl;
                }
                else{ //diagonal inferior i > j
                    //verifico se Y encaixa em X;
                    bool identicos = true;
                    for(int c = 0; c < K && identicos; c++){ //vetor ordenado
                        for(int l = c + 1; l < K; l++){
                            if(agents[X].QRcode[ agents[Y].nosClick[l] ][ agents[Y].nosClick[c] ] == false){
                                identicos = false;
                                break;
                            }
                        }
                    }
                    if(identicos){
                        agents[X].nosClick = agents[Y].nosClick;
                        agents[X].foundedClick = true;
                        raizX->par = raizY;
                        cout << "SUCC ";
                        for(int z = 0; z < K; z++){
                            if(z == K - 1)
                                cout << agents[raizX->id].nosClick[z] << endl;
                            else
                                cout << agents[raizX->id].nosClick[z] << " ";
                        }
                    }
                    else
                        cout<< "FAIL"<<endl;
                }
            }
        }
        else{
            raizX = agents[X].equivalencia;
            raizY = agents[Y].equivalencia;


            bool identicos = true;
            for(int lperm = 0; lperm < numbers.size() && !agents[X].foundedClick; lperm++){ //para cada permutação
                identicos = true;
                //varrendo permutação
                for(int c = 0; c < K && identicos; c++){ 
                    for(int l = c + 1; l < K && identicos; l++){

                        if(agents[X].QRcode[ numbers[lperm][l] ][ numbers[lperm][c] ] ==false ){
                            identicos = false;
                            break;
                        }
                    }
                }
                if(identicos){ //encontrou o K-click
                    agents[X].nosClick = numbers[lperm]; //salvo em ordem crescente
                    agents[X].foundedClick = true;
                }
            }

            //apos encontrado k-click do X verifico no Y
            identicos = true; 
            for(int c = 0; c < K && identicos; c++){ //vetor ordenado
                for(int l = c + 1; l < K; l++){
                    if(agents[Y].QRcode[ agents[X].nosClick[l] ][ agents[X].nosClick[c] ] == false){ 
                        identicos = false;
                        break;
                    }
                }
            }
            if(identicos){
                agents[Y].nosClick = agents[X].nosClick;
                agents[Y].foundedClick = true;
                raizY->par = raizX;

                cout << "SUCC ";
                for(int z = 0; z < K; z++){
                    if(z == K - 1)
                        cout << agents[raizX->id].nosClick[z] << endl;
                    else
                        cout << agents[raizX->id].nosClick[z] << " ";
                }
            }
            else
                cout << "FAIL" <<endl;
        }
    }
    return 0;
}