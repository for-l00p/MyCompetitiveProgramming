/*************************************************************************
 *                                                                       *
 *                    XXI Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:              Mrowisko                                      *
 *   Autor:                Bartlomiej Dudek                              *
 *   Zlozonosc czasowa:    O(ng)                                         *
 *   Zlozonosc pamieciowa: O(n+g)                                        *
 *   Opis:                 Rozwiazanie wolne                             *
 *                         Dla kazdego liscia liczymy przedzial, w jakim *
 *                         musialby byc rozmiar grupy, by startujac tu   *
 *                         zostal zjedzony przez mrowkojada. Potem       *
 *                         liniowo sprawdzamy, czy kazda z grup miesci   *
 *                         sie w tym przedziale.                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int N= 1000000;
const int G= 1000000;
const int MAX = 1000000002;

vector<int> V[N];

int rozmiar[G];
int mrowa,mrowb;//krawedz przy ktorej jest mrowkojad
int k;
int ojc[N];//numer ojca w drzewie
int prz[N][2]; //przedzial, w jakim musialaby sie znalezc grupa, zeby doszla do mrowkojada


void dfs(int u)
{
    //   printf("%d: %d %d\n",u+1,prz[u][0],prz[u][1]);
    for(int i=0; i<(int)V[u].size(); ++i)
    {
        int t=V[u][i];
        if(t==ojc[u]) continue;
        int e=V[t].size();
        if(e>1) --e;
        for(int j=0; j<2; ++j)
        {
            long long q=1LL*prz[u][j]*e;
            if(q>MAX) q=MAX+1;
            prz[t][j]=q;
        }
        ojc[t]=u;
        dfs(t);
    }
}

int main()
{
    int n,g;
    scanf("%d%d%d",&n,&g,&k);
    for(int i=0; i<g; ++i) scanf("%d",&rozmiar[i]);
    for(int i=0; i<n-1; ++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        --a;
        --b;
        if(i==0)
        {
            mrowa=a;
            mrowb=b;
        }
        V[a].push_back(b);
        V[b].push_back(a);
    }
    for(int i=0; i<2; ++i)
    {
        ojc[mrowa]=mrowb;
        int e=V[mrowa].size();
        if(e!=1) --e;
        prz[mrowa][0]=min(1LL*k*e,MAX*1LL);
        prz[mrowa][1]=min(1LL*(k+1)*e,MAX*1LL);
        dfs(mrowa);
        swap(mrowa,mrowb);
        //zrob to samo po drugiej stronie mrowkojada
    }
    long long ile=0;
    for(int i=0; i<n; ++i) if(V[i].size()==1)
        {
            for(int j=0; j<g; ++j) if(rozmiar[j]>=prz[i][0] && rozmiar[j]<prz[i][1]) ++ile;
        }
    printf("%lld\n",ile*k);
}
