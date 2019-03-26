#include <iostream>
#include <string>
#include <cmath>
//#include <chrono>

using namespace std;
//using namespace std::chrono;
struct livro{
    string ID;
    int quantidade;
    int nPrateleiras;
};
struct allBooks{
    struct livro* livros; 
    int nLivrosDiferentes; //numero de elementos do vetor acima
    int qAlocado;
    int nLivrosTotais;
};

class armario{
    public:
        struct allBooks andares[11]; //pra cada andar
        struct allBooks infoGerais[2][4][11]; //se idbd[0]<5 elemento ta no infogerais[0] , caso contrario infogerais[1]
        armario(){
            int j;
            for(int i = 0; i<11; i++){
                this -> andares[i].nLivrosTotais = 0;
                this -> andares[i].livros = NULL;
                this -> andares[i].nLivrosDiferentes = 0;
                for(j=0;j<4;j++){
                    this -> infoGerais[0][j][i].nLivrosDiferentes = 0;
                    this -> infoGerais[1][j][i].nLivrosDiferentes = 0;
                    this -> infoGerais[0][j][i].livros = NULL;
                    this -> infoGerais[1][j][i].livros = NULL;
                    this -> infoGerais[0][j][i].qAlocado = 0;
                    this -> infoGerais[1][j][i].qAlocado = 0;
                }
                this -> andares[i].qAlocado = 0;
            }
        }
        struct livro* dobra_vetor(struct livro* livros,int* tamanhoAlocado,int numeroElementos){
            struct livro *aux = new struct livro[ 2*(*tamanhoAlocado) + 1];

            for(int i = 0; i < numeroElementos; i++){
                aux[i] = livros[i];
            }
            *tamanhoAlocado = (*tamanhoAlocado)* 2 + 1;
            delete[] livros;

            return aux;
        }
        int busca_binaria(struct livro* livros, string& id, int* ultimoIndice, int tamanho){
            int h = 0;
            *ultimoIndice = 0;
            int l=0, r = tamanho - 1;
            while(l <= r){
                h = floor((l+r)/2);
                *ultimoIndice = h;
                if(id == livros[h].ID)
                    return h;

                else if(id < livros[h].ID) 
                    r = h - 1;
                else
                    l = h + 1;    
            }
            return -1;
        }
        int buscaLivros(string& id,int* nPrateleiras,int* index, int dv, int tipo,bool* encontrou,int tipo2){
            //busca livro nO INFO GERAL!!!
            int nLivros = 0,i,ultimoIndex;
            *nPrateleiras = 0;
            *encontrou = false;
            *index = this->busca_binaria( this -> infoGerais[tipo][tipo2][dv].livros, id, &ultimoIndex, this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes);         

            if(*index > -1){ //o livro existe
                *encontrou = true;
                nLivros = this->infoGerais[tipo][tipo2][dv].livros[*index].quantidade;
                *nPrateleiras = this->infoGerais[tipo][tipo2][dv].livros[*index].nPrateleiras;
            }
            else
                *index = ultimoIndex;

            return nLivros;
        }
        int addLivros(string& id,int tipo, int quantidade, int limitePorAndar, int dv, int* nPrateleiras,int tipo2){
            int nLivros;
            int j;
            int andarAtual,index,indexVetor;
            bool encontrou;
            nLivros = this -> buscaLivros(id,nPrateleiras,&indexVetor,dv,tipo,&encontrou,tipo2); //indexvetor == pro info geral, indice adicionar o novo elemento << ou >> caso nao exista
            int maxAddPorAndar,ultimoIndex,novoIndex;
            bool cria = false;
            int valor = quantidade;
            
            if(nLivros == 0){
                if(!encontrou){
                    cria = true;
                    if(this->infoGerais[tipo][tipo2][dv].qAlocado == this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes)
                        this->infoGerais[tipo][tipo2][dv].livros = this->dobra_vetor(this->infoGerais[tipo][tipo2][dv].livros,&(this->infoGerais[tipo][tipo2][dv].qAlocado),this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes);
                }
            } 
            for(j=0;j < 11 && quantidade > 0; j++){
                andarAtual = (dv + j)% 11;
                index = this -> busca_binaria(andares[andarAtual].livros,id,&ultimoIndex,andares[andarAtual].nLivrosDiferentes); //indice do elemento do vetor que contem o livro no andar
                //busca binária no ANDAR
                //ultimo index é a posicao boa para andar.livro novo caso nao exista
                if(index > -1){   //já existe livro nesse andar
                    maxAddPorAndar = limitePorAndar - this->andares[andarAtual].nLivrosTotais ;//quantos que PODERM ser adcionados nesse andar
                    
                    if(maxAddPorAndar > 0){ //posso adicionar nesse andar
                    
                        if(andares[andarAtual].livros[index].quantidade == 0)
                            *nPrateleiras = *nPrateleiras + 1;

                        if(quantidade <= maxAddPorAndar){ //posso add tudo nesse andar
                            this->andares[andarAtual].livros[index].quantidade += quantidade;
                            this->andares[andarAtual].nLivrosTotais += quantidade;
                            quantidade = 0;
                        }
                        else{
                            this->andares[andarAtual].livros[index].quantidade += maxAddPorAndar;
                            this->andares[andarAtual].nLivrosTotais += maxAddPorAndar;
                            quantidade = quantidade - maxAddPorAndar;
                        }
                    }
                    /* cout<< "ja existe livro andar"<<endl;
                    for(int i=0;i<this->andares[andarAtual].nLivrosDiferentes;i++)
                        cout <<  this->andares[andarAtual].livros[i].ID << " " <<  this->andares[andarAtual].livros[i].quantidade << " " << endl;
                    cout<<endl; */ 
                }  
                else{ //não existe esse livro no andar
                    maxAddPorAndar = limitePorAndar - this->andares[andarAtual].nLivrosTotais ;//quantos podem ser adcionados nesse andar
        
                    if(maxAddPorAndar > 0){ //posso add

                        if(this->andares[andarAtual].qAlocado == this->andares[andarAtual].nLivrosDiferentes){
                            andares[andarAtual].livros = this -> dobra_vetor(this->andares[andarAtual].livros, &(this->andares[andarAtual].qAlocado),this->andares[andarAtual].nLivrosDiferentes); 
                        }               
                        novoIndex = this->criaLivro(id,andarAtual,ultimoIndex,&indexVetor,cria,dv,tipo,tipo2); //cria e coloca-o ordenado
                        cria = false; 
                        *nPrateleiras = *nPrateleiras + 1;

                        if(quantidade <= maxAddPorAndar){
                            this->andares[andarAtual].livros[novoIndex].quantidade += quantidade;
                            this->andares[andarAtual].nLivrosTotais += quantidade;
                            quantidade = 0;
                        }
                        else{
                            this->andares[andarAtual].livros[novoIndex].quantidade += maxAddPorAndar;
                            this->andares[andarAtual].nLivrosTotais += maxAddPorAndar;
                            quantidade = quantidade - maxAddPorAndar;
                        }
/* 
                            cout<< "nao existe livro andar\n";
                        for(int i=0;i<this->andares[andarAtual].nLivrosDiferentes;i++)
                            cout <<  this->andares[andarAtual].livros[i].ID << " " <<  this->andares[andarAtual].livros[i].quantidade << " " << endl;
                        cout<<endl;  */
                    }
                }       
            }        
            nLivros += valor;
            this->infoGerais[tipo][tipo2][dv].livros[indexVetor].nPrateleiras = (*nPrateleiras);
            this->infoGerais[tipo][tipo2][dv].livros[indexVetor].quantidade = nLivros; 

          /*    for(int i=0;i<this->infoGerais[tipo][dv].nLivrosDiferentes;i++)
                cout <<  this->infoGerais[tipo][dv].livros[i].ID << " " <<  this->infoGerais[tipo][dv].livros[i].quantidade<< " " <<this->infoGerais[tipo][dv].livros[i].nPrateleiras <<endl;
            */return nLivros; 
        }
        int criaLivro(string& id,int andar,int ultimoIndex,int* indexVetor, bool cria,int dv,int tipo,int tipo2){
            int novoIndex = -1,ni2 = -1; //retorna indice do novo elemento do vetor andar.livro
            livro aux, livroADD;
            livroADD.ID = id;
            livroADD.nPrateleiras = 0;
            livroADD.quantidade = 0;
            bool entrou = false;

            for(int i = ultimoIndex; i < this->andares[andar].nLivrosDiferentes; i++){

                if(this->andares[andar].livros[i].ID > livroADD.ID){
                    if(livroADD.ID == id && !entrou){
                        entrou = true;
                        novoIndex = i;
                    }
                    aux = livroADD;
                    livroADD = this->andares[andar].livros[i];
                    this->andares[andar].livros[i] = aux;
                }
            }
            if(novoIndex == -1)
                novoIndex = this->andares[andar].nLivrosDiferentes;
            this->andares[andar].livros[ this->andares[andar].nLivrosDiferentes ] = livroADD;
            this->andares[andar].nLivrosDiferentes++;

            if(cria){
                entrou = false;
                livroADD.ID = id;
                livroADD.nPrateleiras = 0;
                livroADD.quantidade = 0;
                for(int i = (*indexVetor); i < this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes;i++){

                    if( this->infoGerais[tipo][tipo2][dv].livros[i].ID > livroADD.ID){
                        if(livroADD.ID == id && !entrou){
                            entrou = true;
                            ni2 = i;
                            *indexVetor = i;
                        }
                        aux = livroADD;
                        livroADD = this->infoGerais[tipo][tipo2][dv].livros[i];
                        this->infoGerais[tipo][tipo2][dv].livros[i] = aux;
                    }
                }
                if(ni2 == -1)
                    *indexVetor = this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes;
                this->infoGerais[tipo][tipo2][dv].livros[this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes] = livroADD;
                this->infoGerais[tipo][tipo2][dv].nLivrosDiferentes++;
            }
            return novoIndex;
        }
        int removeLivros(string& id, int quantidade, int dv, int* nPrateleiras,int tipo,int tipo2){

            int nLivros,andar,index,prateleira,indexVetor,ultimoIndice;
            bool a;
            int ultimo;
            nLivros = this->buscaLivros(id,nPrateleiras,&indexVetor,dv,tipo,&a,tipo2); //indexVetor == indice do vetor infoGerais
            nLivros -= quantidade;
            prateleira = *nPrateleiras;

            for(int j = 0; j < 11 && quantidade > 0; j++){
                andar = ((dv + (prateleira - 1)) - j)%11;
                index = this -> busca_binaria(this->andares[andar].livros,id,&ultimoIndice,this->andares[andar].nLivrosDiferentes);

                if(this->andares[andar].livros[index].quantidade >= quantidade){

                    this->andares[andar].livros[index].quantidade -= quantidade;
                    this->andares[andar].nLivrosTotais -= quantidade;
                    quantidade = 0;

                    if(this->andares[andar].livros[index].quantidade == 0){
                        *nPrateleiras = *nPrateleiras - 1;
                        this->andares[andar].livros[index].nPrateleiras = *nPrateleiras;
                    }
                }
                else if(this->andares[andar].livros[index].quantidade > 0){
                    this -> andares[andar].nLivrosTotais -= this->andares[andar].livros[index].quantidade;
                    quantidade = quantidade - this->andares[andar].livros[index].quantidade;
                    this -> andares[andar].livros[index].quantidade = 0;
                    *nPrateleiras = *nPrateleiras - 1;
                    this -> andares[andar].livros[index].nPrateleiras = *nPrateleiras;
                }
               /*      for(int i=0;i<this->andares[andar].nLivrosDiferentes;i++)
                    cout <<  this->andares[andar].livros[i].ID << " " <<  this->andares[andar].livros[i].quantidade << " " << endl;
                cout<<endl;  */
            }
            this->infoGerais[tipo][tipo2][dv].livros[indexVetor].quantidade = nLivros;
            this->infoGerais[tipo][tipo2][dv].livros[indexVetor].nPrateleiras = (*nPrateleiras);

            return nLivros;
        }
};

int calculationCore(string& isbn){
    int k = 0, mult = 10;

    for(int i = 0; i < 9; i++){
        k += mult * (isbn[i] - '0');
        mult--;
    }
  
    return k;
}

/* void verificaDigitos(string& isbn){
    int soma = 0;
    int index,i;
    bool digitoCorrompido = false;

    for(i = 0; i < 10; i++){
        if(isbn[i] != '?'){
            if(isbn[i] == 'x')
                soma += (10 - i) * (10);
            else  
                soma += (10 - i) * (isbn[i] - '0');
        }
        else{
            index = i;
            digitoCorrompido = true;
        }
    }

    for(i = 0; i < 11 && digitoCorrompido; i++){
        if( (soma + (10 - index)*i)%11 == 0){

            if(i == 10)
                isbn[index] = 'x';
            else
                isbn[index] = i + '0';
            
            break;
        }
    }
}
 */
int main(){
    //high_resolution_clock::time_point t1 = high_resolution_clock::now();
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M,Q; // M == número de estantes, Q = quantidades de livros por andar das estantes
    int tipo2;
    armario* estantes;
    string instruction,isbn;
    bool a;
    int copies,tipo;
    int core, r,unidades,dv = 0;
    int nPrateleiras,i,u;
    int soma, index;
    bool digitoCorrompido;
    int k,mult;

    cin >> M >> Q;
    estantes = new armario[M];
    do{
        cin >> instruction;

        if(instruction == "QRY"){
            cin >> isbn;


      //      verificaDigitos(isbn);
            soma = 0;
            digitoCorrompido = false;
                    for(i = 0; i < 10; i++){
                if(isbn[i] != '?'){
                    if(isbn[i] == 'x')
                        soma += (10 - i) * (10);
                    else  
                        soma += (10 - i) * (isbn[i] - '0');
                }
                else{
                    index = i;
                    digitoCorrompido = true;
                }
            }

            for(i = 0; i < 11 && digitoCorrompido; i++){
                if( (soma + (10 - index)*i)%11 == 0){

                    if(i == 10)
                        isbn[index] = 'x';
                    else
                        isbn[index] = i + '0';
                    
                    break;
                }
            }


            if(isbn[0] - '0' <= 5)
                tipo = 0;
            else
                tipo = 1;

            core = 0; mult = 10;

            for(int i = 0; i < 9; i++){
                core += mult * (isbn[i] - '0');
                mult--;
            }

            tipo2 = core % 4;
            r = core % M; //calculo da função de disperção (r == estante)
            
            if(isbn[9] == 'x')
                dv = 10;
            else 
                dv = isbn[9] - '0'; //calculando o DV

            unidades = estantes[r].buscaLivros(isbn,&nPrateleiras,&u,dv,tipo,&a,tipo2);
            std::cout << r <<" "<< unidades<<" "<< nPrateleiras << endl;
        }

        else if(instruction == "ADD"){
            cin >> isbn >> copies;
           // verificaDigitos(isbn);

            soma = 0;
            digitoCorrompido = false;
            for(i = 0; i < 10; i++){
                if(isbn[i] != '?'){
                    if(isbn[i] == 'x')
                        soma += (10 - i) * (10);
                    else  
                        soma += (10 - i) * (isbn[i] - '0');
                }
                else{
                    index = i;
                    digitoCorrompido = true;
                }
            }

            for(i = 0; i < 11 && digitoCorrompido; i++){
                if( (soma + (10 - index)*i)%11 == 0){

                    if(i == 10)
                        isbn[index] = 'x';
                    else
                        isbn[index] = i + '0';
                    
                    break;
                }
            }


            if(isbn[0] - '0' <= 5)
                tipo = 0;
            else
                tipo = 1;

            core = 0; mult = 10;

            for(int i = 0; i < 9; i++){
                core += mult * (isbn[i] - '0');
                mult--;
            }

            tipo2 = core % 4;
            r = core % M; //calculo da função de disperção (r == estante)

            if(isbn[9] == 'x')
                dv = 10;
            else 
                dv = isbn[9] - '0'; //calculando o DV

            unidades = estantes[r].addLivros(isbn,tipo,copies,Q,dv,&nPrateleiras,tipo2);
            std::cout << r <<" "<< unidades<<" "<< nPrateleiras << endl;
        }
        else if(instruction == "REM"){
            cin >> isbn >> copies;
           
            soma = 0;
            digitoCorrompido = false;
            for(i = 0; i < 10; i++){
                if(isbn[i] != '?'){
                    if(isbn[i] == 'x')
                        soma += (10 - i) * (10);
                    else  
                        soma += (10 - i) * (isbn[i] - '0');
                }
                else{
                    index = i;
                    digitoCorrompido = true;
                }
            }

            for(i = 0; i < 11 && digitoCorrompido; i++){
                if( (soma + (10 - index)*i)%11 == 0){

                    if(i == 10)
                        isbn[index] = 'x';
                    else
                        isbn[index] = i + '0';
                    
                    break;
                }
            }


            if(isbn[0] - '0' <= 5)
                tipo = 0;
            else
                tipo = 1;

            core = 0; mult = 10;

            for(int i = 0; i < 9; i++){
                core += mult * (isbn[i] - '0');
                mult--;
            }

            tipo2 = core % 4;
            r = core % M; //calculo da função de disperção (r == estante)   

            if(isbn[9] == 'x')
                dv = 10;
            else 
                dv = isbn[9] - '0'; //calculando o DV

            unidades = estantes[r].removeLivros(isbn,copies,dv,&nPrateleiras,tipo,tipo2);
            std::cout << r <<" "<< unidades<<" "<< nPrateleiras << endl;
        
        }
    }while(instruction != "END");
    
    return 0;
}