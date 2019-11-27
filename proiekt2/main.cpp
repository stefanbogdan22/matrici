#include <iostream>
#include <math.h>
using namespace std;

class Vector{

private:
    int dime;
    int *a;

public:

    void set_a(int index, int numar){
        a[index] = numar;
    }


    int get_a(int nr){
        return a[nr];
    }

    void set_dim(int dim){
        this->dime=dim;
    }

    void alocare_memorie_a(int dim){

        this->a = new int[dim];
    }

    ~Vector(){
        delete[] a;
    }

    Vector(){
        dime= 0;
    }

    Vector(int dim ){

        this->dime = dim;
        a = new int[dime];
    }

    Vector(const Vector &v) {

        dime = v.dime;
        a = new int[dime];
        for(int i=0;i<dime;i++)
            a[i] = v.a[i];
    }


    friend ostream& operator<< (ostream &out, const Vector &vect);
    friend istream& operator>> (istream &in, Vector &vect);
    Vector& operator= (const Vector &v);
};

ostream& operator<<(ostream &out, const Vector &vect){

    cout<<"Elemente vector: ";
    for(int i = 0; i<vect.dime; i++){

        out<<vect.a[i]<<" ";
    }

    return out;
}

istream& operator>> (istream& in, Vector &vect){
    if(vect.dime == 0)
    {cout<<"Introduceti dimensiune vector: ";
    in>>vect.dime;}
    else cout<<"Vectorul trebuie sa contina "<<vect.dime<<" elemente"<<endl;
    vect.a = new int[vect.dime];
    cout<<"Introduceti cele "<<vect.dime<<" elemente in vector: ";
    for(int i=0;i<vect.dime;i++){

        in>>vect.a[i];
    }
    return in;
}

Vector& Vector::operator= (const Vector &v){

    dime = v.dime;
    a = new int [dime];
    for(int i=0;i<dime;i++)
            a[i] = v.a[i];

    return *this;
}

class Matrice : public Vector {

protected:
    Vector *V;
public:
};

class Matrice_oarecare : public Matrice{

    int lin;

public:

    Matrice_oarecare(){

        lin=0;
    }

    Matrice_oarecare(int lin){

        this->lin=lin;
        V = new Vector[lin];
    }

    Matrice_oarecare(const Matrice_oarecare &M){

        lin = M.lin;
        V = new Vector[lin];
        for(int i=0; i<lin; i++){
                V[i] = M.V[i];
        }
    }

    friend ostream& operator<< (ostream &out, const Matrice_oarecare &M);
    friend istream& operator>> (istream &in, Matrice_oarecare &M);
    Matrice_oarecare& operator= (const Matrice_oarecare &M);

};

ostream& operator<< (ostream &out, const Matrice_oarecare &M){
    for(int i=0;i<M.lin;i++){
        out<<M.V[i]<<endl;
    }
    return out;
}

istream& operator>> (istream &in, Matrice_oarecare &M){

    if(M.lin == 0) {cout<<"Introduceti numarul de linii al matricei: "; cin>>M.lin; M.V = new Vector[M.lin];}
    cout<<"Introduceti numarul de coloane al matricei oarecare: "; int x; cin>>x;
    cout<<endl<<"Matrice oarecare cu "<<M.lin<<" linii si "<<x<<" coloane"<<endl<<endl;
    for(int i=0;i<M.lin;i++){
        M.V[i].set_dim(x);
        in>>M.V[i];
    }
    return in;
}

Matrice_oarecare& Matrice_oarecare::operator= (const Matrice_oarecare &M){

    lin = M.lin;
    for(int i=0;i<M.lin;i++){

        V[i] = M.V[i];
    }
    return *this;
}
//////////////////////////////////////////////////////////////////
class Matrice_patratica : public Matrice{

    int dim;

public:

    Matrice_patratica(){

        dim=0;
    }

    Matrice_patratica(int dim){

        this->dim=dim;
        V = new Vector[dim];
    }

    Matrice_patratica(const Matrice_patratica &M){

        dim = M.dim;
        V = new Vector[dim];
        for(int i=0; i<dim; i++){
                V[i] = M.V[i];
        }
    }

    friend ostream& operator<< (ostream &out, const Matrice_patratica &M);
    friend istream& operator>> (istream &in, Matrice_patratica &M);
    Matrice_patratica& operator= (const Matrice_patratica &M);

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

int determinant()
{
    int num1,num2,det = 1,index,total = 1;
    int temp[dim + 1];
    for(int i = 0; i < dim; i++)
    {
        index = i;
        while(V[index].get_a(i) == 0 && index < dim) {
            index++;
        }
        if(index == dim)
        {
            continue;
        }
        if(index != i)
        {   int aux;
            for(int j = 0; j < dim; j++)
            {
                ///swap(V[index].get_a(i),V[i].get_a(j));
                aux = V[index].get_a(i);
                V[index].set_a(i,V[i].get_a(j));
                V[i].set_a(j,aux);
            }
                det = det*pow(-1,index-i);
       }
       for(int j = 0; j < dim; j++)
       {
           temp[j] = V[i].get_a(j);

       }
       for(int j = i+1; j < dim; j++)
       {
           num1 = temp[i]; //value of diagonal element
           num2 = V[j].get_a(i); //value of next row element

           //traversing every column of row
           // and multiplying to every row
           for(int k = 0; k < dim; k++)
           {
               //multiplying to make the diagonal
               // element and next row element equal
               V[j].set_a(k,(num1 * V[j].get_a(k)) - (num2 * temp[k]));
           }
           total = total * num1; // Det(kA)=kDet(A);
           }

    }
    //mulitplying the diagonal elements to get determinant
    for(int i = 0; i < dim; i++)
    {
        det = det * V[i].get_a(i);
    }
    return (det/total); //Det(kA)/k=Det(A);
    }

};

ostream& operator<<(ostream &out, const Matrice_patratica &M){
    for(int i=0;i<M.dim;i++){
        out<<M.V[i]<<endl;
    }
    return out;
}

istream& operator>> (istream &in, Matrice_patratica &M){

    if(M.dim== 0) {cout<<"Introduceti dim matricei patratice: "; cin>>M.dim; M.V = new Vector[M.dim];}
    cout<<"Matrice patratica "<<M.dim<<"x"<<M.dim<<endl;
    for(int i=0;i<M.dim;i++){
        M.V[i].set_dim(M.dim);
        in>>M.V[i];
    }
    return in;
}

Matrice_patratica& Matrice_patratica::operator= (const Matrice_patratica &M){

    dim = M.dim;
    for(int i=0;i<M.dim;i++){

        V[i] = M.V[i];
    }
    return *this;
}


int main()
{
/*    Matrice_patratica *a;
    cout<<"Introduceti nr de matrici patratice: ";
    int x; cin>>x;
    a = new Matrice_patratica[x];
    for(int i =0;i<x;i++)
        cin>>a[i];
*/
        Matrice_patratica x;
        cin>>x;

        int y = x.determinant();


}

