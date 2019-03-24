#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
struct pereche
{
    int nr_stare;
    unsigned int nr_litere;
};
ifstream in("fisier.in");
ofstream out("fisier.out");
int nfa(int stare_curenta, char *cuv, char **stari_finale, int nr_stari_finale, char **stari, int ***delta, char **simboluri,int nr_simboluri,int nr_stari,int drum_len,pereche* drum)
{
    int i,j=0,finala=0;
    drum_len++;
    drum[drum_len].nr_stare=stare_curenta;
    drum[drum_len].nr_litere=strlen(cuv);
    for(i=0;i<drum_len;i++)
        if(stare_curenta==drum[i].nr_stare && drum[i].nr_litere==strlen(cuv))
            return 0;
    for(i=0;i<nr_stari;i++)
    {
        if(delta[stare_curenta][nr_simboluri][i]==1)
            if(nfa(i,cuv,stari_finale,nr_stari_finale,stari,delta,simboluri,nr_simboluri,nr_stari,drum_len,drum))
                return 1;
    }
    if(strlen(cuv)==0)
    {
        while(j<nr_stari_finale)
        {
            if(strcmp(stari[stare_curenta],stari_finale[j])==0)
                finala=1;
            j++;
        }
        if(finala==1)
            {
                return 1;
            }
        else
            return 0;
    }
    else
    {
        int p=0;
        int indexs=0;
        char *point;
        while(p==0 && indexs<=nr_simboluri)
        {
            point=strstr(cuv,simboluri[indexs]);
            if(point!=NULL)
                if(point-cuv==0)
                    p=1;
            if(p==0)
                indexs++;   ///gasim al cate-lea simbol este primul simbol din cuvant din cuvant
        }
        if(p==0)
            return 0;
        for(i=0;i<nr_stari;i++)
        {
            if(delta[stare_curenta][indexs][i]==1)
                if(nfa(i,cuv+strlen(simboluri[indexs]),stari_finale,nr_stari_finale,stari,delta,simboluri,nr_simboluri,nr_stari,drum_len,drum))
                    return 1;
        }
        return 0;
    }
}
int cuv[1000],lencuv;
int main()
{
    int i,len,index1,index2,indexs,j,nr_cuvinte,drum_len;
    int nr_stari,nr_simboluri,nr_stari_finale,nr_tranzitii;
    char **stari,**stari_finale,*stare_initiala,**simboluri,cuvant[1000];
    char aux[1000];
    in>>nr_stari;
    in.get();
    stari=new char*[nr_stari];
    for(i=0;i<nr_stari;i++)
    {
        in.get(aux,1000);
        in.get();
        len=strlen(aux)+1;
        stari[i]=new char[len];
        strcpy(stari[i],aux);
    }
    in>>nr_simboluri;
    in.get();
    simboluri=new char*[nr_simboluri+1];
    for(i=0;i<nr_simboluri;i++)
    {
        in.get(aux,1000);
        in.get();
        len=strlen(aux)+1;
        simboluri[i]=new char[len];
        strcpy(simboluri[i],aux);
    }
    simboluri[nr_simboluri]=new char[7];
    //simboluri[nr_simboluri-1]="lambda";
    strcpy(simboluri[nr_simboluri],"lambda");
    in.get(aux,1000);
    in.get();
    len=strlen(aux)+1;
    stare_initiala=new char[len];
    strcpy(stare_initiala,aux);
    in>>nr_stari_finale;
    in.get();
    stari_finale=new char*[nr_stari_finale];
    for(i=0;i<nr_stari_finale;i++)
    {
        in.get(aux,1000);
        in.get();
        len=strlen(aux)+1;
        stari_finale[i]=new char[len];
        strcpy(stari_finale[i],aux);
    }
    in>>nr_tranzitii;
    in.get();
    int ***delta,k;
    delta=new int**[nr_stari];
    for(i=0;i<nr_stari;i++)
    {
        delta[i]=new int*[nr_simboluri+1];
        for(j=0;j<nr_simboluri+1;j++)
        {
            delta[i][j]=new int[nr_stari];
            for(k=0;k<nr_stari;k++)
            {
                delta[i][j][k]=-1;
            }
        }
    }
    char stare1[1000],stare2[1000],simbol[1000];
    for(i=0;i<nr_tranzitii;i++)
    {
        in.get(stare1,1000);
        in.get();
        in.get(stare2,1000);
        in.get();
        in.get(simbol,1000);
        in.get();
        index1=0;
        index2=0;
        indexs=0;
        while(strcmp(stari[index1],stare1))
                index1++;
        while(strcmp(stari[index2],stare2))
                index2++;
        while((strcmp(simboluri[indexs],simbol))!=0)
                indexs++;
        delta[index1][indexs][index2]=1;
    }
    in>>nr_cuvinte;
    in.get();
    for(i=0;i<nr_cuvinte;i++)
    {
        pereche drum[10000];
        drum_len=-1;
        in.get(cuvant,1000);
        in.get();
        index1=0;
        while(strcmp(stare_initiala,stari[index1]))
            index1++;
        if(nfa(index1,cuvant,stari_finale,nr_stari_finale,stari,delta,simboluri,nr_simboluri,nr_stari,drum_len,drum))
            out<<"DA"<<endl;
        else
            out<<"NU"<<endl;
    }
    return 0;
}
