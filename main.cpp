#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

class Vector{

    int dim;
    int *a;
public:

    int get_a(int i){
        return a[i];
    }

    int get_dim(){
        return dim;
    }

    void set_dim(int dim){
        this->dim = dim;
    }

    void a_mem(){
         a = new int[dim];
    }

    Vector(){
        dim = 0;
        a = 0;
    }


    Vector(int dim, int *b){
        this->dim = dim;
        a = new int[dim];
        for(int i=0;i<dim;i++){

            a[i] = b[i];
        }
    }

    Vector(const Vector &ob){

        dim = ob.dim;
        a = new int[dim];
        for(int i=0;i<dim;i++){

            a[i] = ob.a[i];
        }
    }

    ~Vector(){
        delete[] a;
    }

    friend istream& operator>> (istream& in, Vector& ob);
    friend ostream& operator<< (ostream& out, const Vector& ob);
    Vector& operator= (const Vector &v);
};

istream& operator>> (istream& in, Vector& ob){

    for(int i=0;i<ob.dim;i++){
        in>>ob.a[i];
    }
    return in;
}

ostream& operator<<(ostream &out, const Vector &ob){

    if(!ob.dim) out<<"Vector fara valori!";
    else{
        out<<"Valori: ";
        for(int i=0;i<ob.dim;i++){
            out<<ob.a[i]<<" ";
        }
    }
    return out;
}

Vector& Vector::operator= (const Vector &v){

    dim = v.dim;
    a = new int [dim];
    for(int i=0;i<dim;i++)
            a[i] = v.a[i];

    return *this;
}

class Matrice_abstracta{
protected:
    Vector *V;
public:

    virtual void afisare(){};

    Matrice_abstracta(){
        V = 0;
    }

};

class Matrice_oarecare : public Matrice_abstracta{

    int lin;

public:

    Matrice_oarecare():Matrice_abstracta(){
        lin = 0;
    }

    Matrice_oarecare(int lin, int col, Vector *B){

        this->lin = lin;

        V = new Vector[lin];

        for(int i=0;i<lin;i++){
            V[i].set_dim(col);
            V[i].a_mem();
            V[i] = B[i];
        }
    }

    Matrice_oarecare(const Matrice_oarecare &M){

        lin = M.lin;
        V = new Vector[lin];
        for(int i=0;i<M.lin;i++){
            V[i].set_dim(M.V[i].get_dim());
            V[i].a_mem();
            V[i] = M.V[i];
        }
    }

    friend ostream& operator<< (ostream &out, const Matrice_oarecare &M);
    friend istream& operator>> (istream &in, Matrice_oarecare &M);
    Matrice_oarecare& operator= (const Matrice_oarecare &M);

    void afisare(){

        cout<<"Matrice oarecare"<<endl;
        for(int i=0;i<lin;i++)
            cout<<V[i]<<endl;
    }
};

ostream& operator<< (ostream &out, const Matrice_oarecare &M){
    cout<<"Matrice oarecare"<<endl;
    for(int i=0;i<M.lin;i++){
        out<<M.V[i]<<endl;
    }
    return out;
}

istream& operator>> (istream &in, Matrice_oarecare &M){

    if(M.lin == 0) {cout<<"Introduceti numarul de linii al matricei: "; in>>M.lin; M.V = new Vector[M.lin];}
    cout<<"Introduceti numarul de coloane al matricei oarecare: "; int x; in>>x;
    cout<<endl<<"Matrice oarecare cu "<<M.lin<<" linii si "<<x<<" coloane"<<endl<<endl;
    for(int i=0;i<M.lin;i++){
        M.V[i].set_dim(x);
        M.V[i].a_mem();
        in>>M.V[i];
    }
    return in;
}

Matrice_oarecare& Matrice_oarecare::operator= (const Matrice_oarecare &M){

    lin = M.lin;
    V = new Vector[lin];
    for(int i=0;i<M.lin;i++){
        V[i].set_dim(M.V[i].get_dim());
        V[i].a_mem();
        V[i] = M.V[i];
    }
    return *this;
}

class Matrice_patratica : public Matrice_abstracta{

    int dim;
public:

    Matrice_patratica():Matrice_abstracta(){
        dim = 0;
    }

    Matrice_patratica(int dim, Vector *B){

        this->dim = dim;

        V = new Vector[dim];

        for(int i=0;i<dim;i++){
            V[i].set_dim(dim);
            V[i].a_mem();
            V[i] = B[i];
        }
    }

    Matrice_patratica(const Matrice_patratica &M){

        dim = M.dim;
        V = new Vector[dim];
        for(int i=0;i<M.dim;i++){
            V[i].set_dim(M.V[i].get_dim());
            V[i].a_mem();
            V[i] = M.V[i];
        }
    }

    friend ostream& operator<< (ostream &out, const Matrice_patratica &M);
    friend istream& operator>> (istream &in, Matrice_patratica &M);
    Matrice_patratica& operator= (const Matrice_patratica &M);

    ///virtuala
    void afisare(){

        cout<<"Matrice patratica"<<endl;
        for(int i=0;i<dim;i++)
            cout<<V[i]<<endl;
    }

    bool triunghiulara(){
        int x = 1;int y = 1;
        int i,j;
         for (i=0; i<dim; i++)
                for (j=0; j<dim; j++)
                    {if (i>j&&V[i].get_a(j)!=0) x = 0;
                    if (i<j&&V[i].get_a(j)!=0) y = 0;}
        int z=x+y;
        if(z == 2) return true;
        else return false;
    }
};

ostream& operator<< (ostream &out, const Matrice_patratica &M){
    cout<<"Matrice patratica"<<endl;
    for(int i=0;i<M.dim;i++){
        out<<M.V[i]<<endl;
    }
    return out;
}

istream& operator>> (istream &in, Matrice_patratica &M){

    if(M.dim== 0) {cout<<"Introduceti dim matricei: "; in>>M.dim; M.V = new Vector[M.dim];}
    cout<<endl<<"Matrice patratica"<<M.dim<<" x "<<M.dim<<endl;
    for(int i=0;i<M.dim;i++){
        M.V[i].set_dim(M.dim);
        M.V[i].a_mem();
        in>>M.V[i];
    }
    return in;
}

Matrice_patratica& Matrice_patratica::operator= (const Matrice_patratica &M){

    dim = M.dim;
    V = new Vector[dim];
    for(int i=0;i<M.dim;i++){
        V[i].set_dim(M.V[i].get_dim());
        V[i].a_mem();
        V[i] = M.V[i];
    }
    return *this;
}

int main()
{
    cout<<"Numar matrici: ";
    int x,y;
    cin>>x;
    Matrice_abstracta *Matrici[x];
    for(int i=0;i<x;i++){
        cout<<"1. Matrice oarecare / 2. Matrice patratica"<<endl;
        cin>>y;
        if(y==1) Matrici[i] = new Matrice_oarecare();
        else if(y==2) Matrici[i] = new Matrice_patratica();
        if(typeid(*Matrici[i])==typeid(Matrice_oarecare))
            cin>>*(Matrice_oarecare*)(Matrici[i]);
        else if(typeid(*Matrici[i]) == typeid(Matrice_patratica))
            cin>>*(Matrice_patratica*)(Matrici[i]);
    }

    for(int i=0;i<x;i++){
        if(typeid(*Matrici[i])==typeid(Matrice_oarecare))
            cout<<*(Matrice_oarecare*)(Matrici[i]);
        else if(typeid(*Matrici[i]) == typeid(Matrice_patratica))
            cout<<*(Matrice_patratica*)(Matrici[i]);
    }
}
