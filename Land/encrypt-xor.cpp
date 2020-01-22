#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    const int key = 394286451;
    cin>>t;
    cout<<(t^key)<<endl;
    for(int i=0;i<t;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        cout<<(a^key)<<" "<<(b^key)<<" "<<(c^key)<<" "<<(d^key)<<endl;
    }
    return 0;
}