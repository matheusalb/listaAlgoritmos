#include <iostream>
#include <vector>
#include <string>

class Agent{

    private:
        bool** QRcode;
        vector <bool> formatKClick;

    public:
        bool exist;
        Agent(int n){
            this -> exist = false;
            this -> QRcode = new bool*[n];
            for(int i = 0; i < n; i++)
                this -> QRcode[i] = new bool[n];
        }

};

using namespace std;
int main(){
    int A, N, K, Q, X, Y;
    Agent* agents;
    string line;

    cin >> A >> N >> K >> Q; 
    agents = new Agent[A] = Agent(N);
#include <iostream>
#include <vector>
#include <string>

class Agent{

    private:
        bool** QRcode;
        vector <bool> formatKClick;

    public:
        bool exist;
        Agent(int n){
            this -> exist = false;
            this -> QRcode = new bool*[n];
            for(int i = 0; i < n; i++)
                this -> QRcode[i] = new bool[n];
        }

};

using namespace std;
int main(){
    int A, N, K, Q, X, Y;
    string line;

    cin >> A >> N >> K >> Q; 
    vector<Agent> agents(A, Agent(N));

    
    for(int i = 0;i < Q; i++){
        cin >> X >> Y;
        if(!agents[X].exist){
            for(int j = 0; j < n;j++)
                cin >> line;
                cin.ignore();
        }



    }


    return 0;
}
    for(int i = 0;i < Q; i++){
        cin >> X >> Y;
        if(!agents[X].exist){
            for(int j = 0; j < n;j++)
                cin >> line;
                cin.ignore();
        }



    }


    return 0;
}