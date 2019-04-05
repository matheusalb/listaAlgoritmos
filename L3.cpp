#include <iostream>


using namespace std;
struct node{
    int val;
    struct node* left;
    struct node* right;
};
int max (int a, int b) {
    return (a<b)?b:a;
}


struct node* bst_search(struct node* root,int val,int* prof){
    //retorna o ponteiro do nó que com o valor ou ponteiro nulo caso-contrário
    if(root == NULL)
        return NULL;
    if(val == root->val)
        return root;
    else if(val < root->val){
        *prof = *prof + 1;
        return bst_search(root->left,val,prof);
    }
    else{ //value > root-> value
        *prof = *prof + 1;
        return bst_search(root->right,val,prof);
    }
}

struct node* bst_insert(struct node* root, int val,int* prof){
    //saída é a nova raiz apos a inserção
    struct node* N = new struct node;

    if(root == NULL){
        N->val = val;
        N->right = NULL;
        N->left = NULL;
        return N;
    }
    else if(val < root->val){
        *prof = *prof + 1; 
        root->left = bst_insert(root->left,val,prof);
        return root;
    }   
    else{
        *prof = *prof + 1;
        root->right = bst_insert(root->right,val,prof);
        return root;
    }
}

struct node* bst_delete_min(struct node* root,int* val){
    //saida = nova saida apos a remoção  e valor removido
    struct node* r;

    if(root->left == NULL){
        *val = root->val;
        r = root->right;
        delete root;
        return r;
    }
    else{
        root->left = bst_delete_min(root->left, val);
        return root;
    }
}

struct node* bst_delete(struct node* root, int val, int* prof, bool* found){
    //saida == nova raiz apos a remoção
    if(root == NULL)
        return NULL;
    else if(val < root->val){
        *prof = *prof +1;
        root->left = bst_delete(root->left,val,prof,found);
        return root;
    }
    else if(val > root->val){
        *prof = *prof +1;
        root->right = bst_delete(root->right,val,prof,found);
        return root;
    }
    else{   //val == root->val
        *found = true;
        if(root->left == NULL){
            struct node* r = root->right;
            delete root;
            return r;
        }
        else if(root->right == NULL){
            struct node* l = root->left;
            delete root;
            return l;
        }
        else{
            root->right = bst_delete_min(root->right,&(root->val));
            return root;
        }
    }
}

int height(struct node* root){
    int l;
    int r;
    if(root == NULL)
        return 0;
    else{
        l = height(root->left);
        r = height(root->right);
        return (1 + max(l,r));
    }
}



int main(){
    int N,val;
    struct node* root = NULL;
    struct node* aux;
    string instruc;
    int prof = 0,valorRemovido;
    bool found;
    int alturaArvore;

    cin >> N;

    for(int i = 0 ; i < N; i++){
        cin >> val;
        root = bst_insert(root,val,&prof);
    }

    alturaArvore = height(root);
    cout<< alturaArvore<<endl;

    do{
        cin >> instruc >> val;    
        found = false;
        aux = NULL;
        prof = 0;

        if(instruc == "SCH"){
            aux = bst_search(root,val,&prof);
            if(aux == NULL)
                cout << "-1" << endl;
            else
                cout << prof << endl;
        }

        else if(instruc == "INS"){
            root = bst_insert(root,val,&prof);
            cout << prof << endl;
        }
        else if(instruc == "DEL"){
            root = bst_delete(root,val,&prof,&found);
            if(!found)
                cout << "-1" << endl;
            else
                cout << prof << endl;
        }

    }while(instruc != "END");

    alturaArvore = height(root);
    cout << alturaArvore<< endl;

    return 0;
}