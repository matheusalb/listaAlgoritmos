#include <iostream>
#include <string>

struct node{
    int id;
    struct node *next;
};

struct queue{
    struct node* head;
    struct node* tail;
};

struct node* list_insert(struct node* cur,int v){
   // std::cout << "entrou list insert \n";
    struct node* newNodo = new struct node;
    newNodo->id = v;
    newNodo->next = cur->next;
    cur->next = newNodo;
    
    return cur;
}
struct node* list_delete(struct node* cur){
    struct node* p = cur->next;
    cur->next = p->next;
    delete p;

    return cur;
}

struct node* enqueue(struct node* head, struct node* tail, int id){
    struct node *t = list_insert(tail,id);
    //t->next->next = NULL;

    return t->next; //return new tail
}

int dequeue(struct node* head, struct node** tail){
    int id_removed = head->next->id;
    head = list_delete(head);
    if(head->next == NULL)
        *tail = head;

    return id_removed;
}
//stack_push(top,v) == list_insert(top,v)
//stack_pop(top) == list_delete(top)




using namespace std;
int main() {
    int m,x,i;//m == Number of rows
    int id;
    string command;
    struct queue* queues;
    struct node** top;
    
    

    cin >> m;
    queues = new queue[m];
    top = new node*[m];
    for(i=0;i<m;i++){
        queues[i].head = new node;
        queues[i].head->next = NULL;
        queues[i].tail = queues[i].head;
        top[i] = new node; 
        top[i]->next = NULL;
    }   

     
    do{
        cin >> command >> x;

        if(command == "NEW"){
            //cout << "entrou \n";
            queues[0].tail = enqueue(queues[0].head,queues[0].tail,x);

        }
        else if(command == "MOV"){
            id = dequeue(queues[0].head,&queues[0].tail);
            queues[x].tail = enqueue(queues[x].head,queues[x].tail,id);
        }
        else if(command == "DEF"){
            id = dequeue(queues[x].head,&queues[x].tail);
            top[x] = list_insert(top[x],id);
        }
        else if(command == "FIX"){
            id = top[x]->next->id;
            top[x] = list_delete(top[x]);
            queues[x].tail = enqueue(queues[x].head,queues[x].tail,id);
        }
        else if(command == "TSH"){
            id = top[x]->next->id;
            top[x] = list_delete(top[x]);
            cout << id << " BAD" << endl;
        }
        else if(command == "RDY"){
            id = dequeue(queues[x].head,&queues[x].tail);
            cout << id<<" OK"<< endl;
        }

    }while(command != "END");

    delete queues;

    return 0;
}