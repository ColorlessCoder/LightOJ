#include<bits/stdc++.h>
using namespace std;
#define vi vector<int>
#define vll vector<LL>
#define pii pair<int,int>
#define fr first
#define sc second
#define  LL   long long int
#define inf 1<<29
#define mod 4294967296
#define LSOne(a) (a&(-a))
#define maxL  50010
#define REP(a,b) for(int a=0;a<b;a++)
LL AA[200010];
LL BB[200010];
LL Map[200010];
class ST{
private :
    vll fix,Atree,Tree;
    vll A;
    LL n;
    inline pair<LL,LL> Min(pair<LL,LL> a,pair<LL,LL> b)
    {
        return (a.fr+a.sc   <   b.fr+b.sc) ? a:b;
    }
    void recover(LL a,LL L,LL R)
    {
        if(fix[a]!=-1)
           {
             fix[a*2 ]=fix[a*2 +1]=fix[a];
             Tree[a*2]=fix[a*2]+Atree[a*2];
             Tree[a*2 +1]=fix[a*2 +1]+Atree[a*2 +1];
           }
            return;
    }
    void update(LL p,LL L,LL R,LL i,LL j,LL x) // O(lg n )
    {
        if(L>j   ||  R<i)
                return;
        if(L>=i   && R<=j)
        {//cout<<2;
            fix[p]=x;
            Tree[p]=Atree[p]+fix[p];
            return;
        }//cout<<2;
        recover(p,L,R);
        fix[p]=-1;
        update(p<<1,L,(L+R)>>1,i,j,x);
        update((p<<1)   +1,((L+R)>>1)  +1,R,i,j,x);
        Tree[p]=min(Tree[p<<1],Tree[(p<<1)  +1]);
        return;
    }
    void update(LL p,LL L,LL R,LL i,LL x) // O(lg n )
    {
        if(L>i   ||  R<i)
                return;
        if(L==i   && R==i)
        {
            A[p]=x;
            Tree[p]=x+fix[p];
            Atree[p]=Tree[p];
            return;
        }//cout<<2;
        recover(p,L,R);
        update(p<<1,L,(L+R)>>1,i,x);
        update((p<<1)   +1,((L+R)>>1)  +1,R,i,x);
        Tree[p]=min(Tree[p<<1],Tree[(p<<1)  +1]);
        Atree[p]=min(Atree[p<<1],Atree[(p<<1)  +1]);
        return;
    }
    LL query(LL p,LL L,LL R,LL i,LL j) //O (lg n)
    {
        if(L>j  || R<i) return -1;
        if(L>=i  &&  R<=j) return  Tree[p];
        recover(p,L,R);
       LL d=query(p<<1,L,(L+R)>>1,i,j);
       LL q=query((p<<1)   +1,((L+R)>>1 ) +1,R,i,j);
       if(d==-1) return q;
       if(q==-1) return d;
       return min(d,q);
    }
public:
    ST(LL a)
    {
        n=a;
        Tree.assign(4*n,0);
        A.assign(4*n,0);
        Atree.assign(4*n,0);
        fix.assign(4*n,0);
    }
    void update(LL i,LL j,LL x)
    {
        update(1,0,n-1,i,j,x);
    }
    void update(LL i,LL x)
    {
        update(1,0,n-1,i,x);
    }
    LL query(LL i,LL j)
    {
        return query(1,0,n-1,i,j);
    }
};

class SegmentTree {         // the segment tree is stored like a heap array
private: vll st, A;            // recall that vi is: typedef vector<LL> vi;
  LL n;
  LL left (LL p) { return p << 1; }     // same as binary heap operations
  LL right(LL p) { return (p << 1) + 1; }
  LL rmq(LL p, LL L, LL R, LL i, LL j) {                  // O(log n)
    if (i >  R || j <  L) return -1; // current segment outside query range
    if (L >= i && R <= j) return st[p];               // inside query range

     // compute the min position in the left and right part of the LLerval
    LL p1 = rmq(left(p) , L              , (L+R) / 2, i, j);
    LL p2 = rmq(right(p), (L+R) / 2 + 1, R          , i, j);

    if (p1 == -1) return p2;   // if we try to access segment outside query
    if (p2 == -1) return p1;                               // same as above
    return (A[p1] <= A[p2]) ? p1 : p2; }          // as as in build routine

  LL update_point(LL p, LL L, LL R, LL idx, LL new_value) {
    // this update code is still preliminary, i == j
    // must be able to update range in the future!
    LL i = idx, j = idx;

    // if the current LLerval does not LLersect
    // the update interval, return this st node value!
    if (i > R || j < L)
      return st[p];

    // if the current interval is included in the update range,
    // update that st[node]
    if (L == i && R == j) {
      A[i] = new_value; // update the underlying array
      return st[p] = L; // this index
    }

    // compute the minimum pition in the
    // left and right part of the interval
    LL p1, p2;
    p1 = update_point(left(p) , L              , (L + R) / 2, idx, new_value);
    p2 = update_point(right(p), (L + R) / 2 + 1, R          , idx, new_value);

    // return the pition where the overall minimum is
    return st[p] = (A[p1] <= A[p2]) ? p1 : p2;
  }

public:
  SegmentTree(LL a,LL b=0) {
    n=a;            // copy content for local usage
    A.assign(n,b);
    st.assign(4 * n, b);
  }

  LL rmq(LL i, LL j) { return A[rmq(1, 0, n - 1, i, j)]; }   // overloading

  LL update_point(LL idx, LL new_value) {
    return update_point(1, 0, n - 1, idx, new_value); }
};

int main()
{
    //freopen("input.txt",)
    int T,I=1;
    cin>>T;
    while(T--)
    {
        printf("Case %d: ",I++);
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
        scanf("%lld %lld",&BB[i],&AA[i]);
        for(int i=0;i<200010;i++)    Map[i]=n+2;
        ST A(n+1);
        SegmentTree B(n+1),C(200010,n+2);
        LL ans=AA[n-1];
        Map[BB[n-1] ]=n-1;
        A.update(n-1,AA[n-1]);
        A.update(n,n,AA[n-1]);
        B.update_point(n-1,AA[n-1]);
        C.update_point(AA[n-1],n-1);
        LL k=n,x;
        for(int i=n-2;i>=0;i--)
        {
            k=min(k,Map[BB[i]]);
            Map[BB[i]]=i;
            C.update_point(AA[i],i);
            x=C.rmq(AA[i]+1,200002);
            LL j=min(x,k);
            ans=B.rmq(i+1,j) + AA[i];
            if(j+1 <= k)
            ans=min(ans,A.query(j+1,k));
            A.update(i+1,j,AA[i]);
            A.update(i,ans);
            B.update_point(i,ans);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
