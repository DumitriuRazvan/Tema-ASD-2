#include <cmath>
#include <cstdlib>
#include <iostream>
#include <malloc.h>
#include <cstring>

using namespace std;

class Node;


class Node
{
private:


    Node* m_tata;
    Node* m_fiu;
    Node* m_stanga;
    Node* m_dreapta;
    int m_val;
    int m_grad;
    bool m_marcaj;
    bool m_c;

public:

    Node* mini = NULL;
    int no_nodes = 0;

    Node()=default;

    Node(Node* tata, Node* fiu, Node* stanga, Node* dreapta,int val,int grad,bool marcaj,bool c):
        m_tata(tata),m_fiu(fiu),m_stanga(stanga),m_dreapta(dreapta),m_val(val),m_grad(grad),m_marcaj(marcaj),m_c(c){}

    ~Node()=default;

    void Inserare(int val)
{
    Node* new_node = new Node ;
    new_node->m_val = val;
    new_node->m_grad = 0;
    new_node->m_marcaj = false;
    new_node->m_c = false;
    new_node->m_tata = NULL;
    new_node->m_fiu = NULL;
    new_node->m_stanga = new_node;
    new_node->m_dreapta = new_node;
    if (mini != NULL) {
        (mini->m_stanga)->m_dreapta = new_node;
        new_node->m_dreapta = mini;
        new_node->m_stanga = mini->m_stanga;
        mini->m_stanga = new_node;
        if (new_node->m_val < mini->m_val)
            mini = new_node;
    }
    else {
        mini = new_node;
    }
    no_nodes++;
}
void Sterge_min()
{
    if (mini == NULL)
        cout << "The heap is empty" << endl;
    else {
        Node* t = mini;
        Node* p;
        p = t;
        Node* x = NULL;
        if (t->m_fiu != NULL) {

            x = t->m_fiu;
            do {
                p = x->m_dreapta;
                (mini->m_stanga)->m_dreapta = x;
                x->m_dreapta = mini;
                x->m_stanga = mini->m_stanga;
                mini->m_stanga = x;
                if (x->m_val < mini->m_val)
                    mini = x;
                x->m_tata = NULL;
                x = p;
            } while (p != t->m_fiu);
        }
        (t->m_stanga)->m_dreapta = t->m_dreapta;
        (t->m_dreapta)->m_stanga = t->m_stanga;
        mini = t->m_dreapta;
        if (t == t->m_dreapta && t->m_fiu == NULL)
            mini = NULL;
        else {
            mini = t->m_dreapta;
            Build();
        }
        no_nodes--;
    }
}

void BuildLink(Node* p2, Node* p1)
{
    (p2->m_stanga)->m_dreapta = p2->m_dreapta;
    (p2->m_dreapta)->m_stanga = p2->m_stanga;
    if (p1->m_dreapta == p1)
        mini = p1;
    p2->m_stanga = p2;
    p2->m_dreapta = p2;
    p2->m_tata = p1;
    if (p1->m_fiu == NULL)
        p1->m_fiu = p2;
    p2->m_dreapta = p1->m_fiu;
    p2->m_stanga = (p1->m_fiu)->m_stanga;
    ((p1->m_fiu)->m_stanga)->m_dreapta = p2;
    (p1->m_fiu)->m_stanga = p2;
    if (p2->m_val < (p1->m_fiu)->m_val)
        p1->m_fiu = p2;
    p1->m_grad++;
}

void Build()
{
    int t1;
    float t2 = (log(no_nodes)) / (log(2));
    int t3 = t2;
    Node* a[t3];
    for (int i = 0; i <= t3; i++)
        a[i] = NULL;
    Node* p1 = mini;
    Node* p2;
    Node* p3;
    Node* p4 = p1;
    do {
        p4 = p4->m_dreapta;
        t1 = p1->m_grad;
        while (a[t1] != NULL) {
            p2 = a[t1];
            if ((*p1).m_val > (*p2).m_val) {
                p3 = p1;
                p1 = p2;
                p2 = p3;
            }
            if (p2 == mini)
                mini = p1;
            BuildLink(p2, p1);
            if (p1->m_dreapta == p1)
                mini = p1;
            a[t1] = NULL;
            t1++;
        }
        a[t1] = p1;
        p1 = p1->m_dreapta;
    } while (p1 != mini);
    mini = NULL;
    for (int j = 0; j <= t3; j++) {
        if (a[j] != NULL) {
            a[j]->m_stanga = a[j];
            a[j]->m_dreapta = a[j];
            if (mini != NULL) {
                (mini->m_stanga)->m_dreapta = a[j];
                a[j]->m_dreapta = mini;
                a[j]->m_stanga = mini->m_stanga;
                mini->m_stanga = a[j];
                if (a[j]->m_val < mini->m_val)
                    mini = a[j];
            }
            else {
                mini = a[j];
            }
            if (mini == NULL)
                mini = a[j];
            else if (a[j]->m_val < mini->m_val)
                mini = a[j];
        }
    }
}
void InitializeazaHeap()
{
    this->no_nodes = 0;
    this->mini = NULL;
}

void Merge(const Node &h1, const Node &h2)
{
    this->InitializeazaHeap();
    this->mini = h1.mini;
    if(h1.mini == NULL || (h2.mini != NULL && h2.mini < h1.mini) )
        this->mini = h2.mini;
    this->no_nodes = h1.no_nodes + h2.no_nodes;
}

friend ostream& operator<< (ostream &out, const Node &n);
friend istream& operator>> (istream &in, Node &n);
};

istream& operator>>  (istream &in, Node &n)
{
    cout<<"Valoare de citit: ";
    int nr;
    in>>nr;
    n.Inserare(nr);
    return in;
}

ostream& operator<< (ostream &out, const Node &n)
{
    Node* p = n.mini;
    if (p == NULL)
        out << "Heap-ul este gol" << endl;

    else {
            if(p->m_fiu != NULL)
                out << "Nodul radacina al heap-ului este:" << endl;
            else
                out << "Nodurile radacina ale heap-ului sunt: " << endl;
        do {
            out << p->m_val;
            p = p->m_dreapta;
            if (p != n.mini) {
                out << "||";
            }
        } while (p != n.mini && p->m_dreapta != NULL);
        out  << endl
             << "Heap-ul are " << n.no_nodes << " noduri" << endl
             << endl;
        return out;
    }
}

int main()
{
    Node h1;
    cout << "Creem heap-ul:" << endl;
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin>>h1;
    cout<<h1;

//    h.Build();
//    cout<<h1;

    cout << "Stergem minim-ul" << endl;
    h1.Sterge_min();
    cout<<h1;


    Node h2;
    cout << "Creem heap-ul:" << endl;
    cin >> n;
    for(int i=1;i<=n;i++)
        cin>>h1;
    cout<<h1;
    cout << "Stergem minim-ul" << endl;
    h1.Sterge_min();
    cout<<h1;
    //
    Node h3;
    h3.Merge(h1,h2);
    cout << h3;




    return 0;
}
