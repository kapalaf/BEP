#include <bits/stdc++.h>
using namespace std;
int x[10000], y[10000];
int n;
vector <int> g[10000];
bool visited[10000];
bool indep[10000];
int maximalIndependentSet, counter;
void independent(int v){
    visited[v] = true;
    indep[v] = true;
    counter++;
    maximalIndependentSet = max(maximalIndependentSet, counter);
    for(int i=0; i<n; i++){
        int u = g[v][i];
        if(!visited[u]){
            visited[u] = true;
            indep[u] = false;
        }
    }
    for(int j=v+1; j<n; j++){
        if(!visited[j]){
            independent(j);
        }
    }
    indep[v] = false;
    counter--;
    if(v+1 < n){
        independent(v+1);
    }

}
int main(){
    cout<<"Enter the number of points: ";
    cin>>n;
    cout<<"Enter the coordinates of the points: "<<endl;
    for(int i=0; i<n; i++){
        cin>>x[i]>>y[i];
    }
    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]) <= 4){
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    counter =0;
    maximalIndependentSet = 0;
    independent(0);
    cout<<"Maximal Independent Set: "<<maximalIndependentSet<<endl;

    
}