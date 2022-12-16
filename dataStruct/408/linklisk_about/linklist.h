#ifndef _LINKLIST_H_
#define _LINKLIST_H_  


using namespace std;

typedef struct node
{
    int data;
    struct node * next;
    node():data(-1),next(nullptr){}
    node(int m_data):data(m_data),next(nullptr){}
    node(int m_data,struct node * m_next):data(m_data),next(m_next){}
}*LinkList;

/**
 * 尾插
*/
LinkList create_LinklistWithoutHead(int n){
    struct node * head = new node(-1);
    struct node * rear = head;
    if(n == 0) return nullptr;
    for(int i=0;i<n;++i){
        int data = -1;
        cin>>data;
        struct node * newnode = new node(data);
        rear->next = newnode;
        rear = rear->next;
    }
    rear= nullptr;
    return head->next;
}

LinkList create_LinklistWittHead(int n){
    struct node * head = new node(-1);
    struct node * rear = head;
    if(n == 0) return nullptr;
    for(int i=0;i<n;++i){
        int data = -1;
        cin>>data;
        struct node * newnode = new node(data);
        rear->next = newnode;
        rear = rear->next;
    }
    return head;
}

void print_List(LinkList  head){
    if(!head || head->data == -1)   cout<<endl<<"list is empty!";
    while(head){
        if(head->next)
        cout<<head->data<<"->";
        else cout<<head->data;
        head=head->next;
    }
    cout<<endl;
}


#endif