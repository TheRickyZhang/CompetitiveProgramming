tpl_<tn_ T, tn_ U>
struct LazySegtree{
    int n;v<T> seg;v<U> lazy;T z;U lz;
    function<T(T,T)> combine;function<T(T,U,int)> apply;function<U(U,U)> merge;
    LazySegtree(int n,T z,U lz, function<T(T,T)>combine=[](T a,T b){return a+b;}, function<T(T,U,int)> apply=[](T s,U u,int len){return s+u*len;}, function<U(U,U)> merge=[](T a,T b){return a+b;}, const v<T>& init={}):
                n(n),seg(4*n,z),lazy(4*n,lz),z(z),lz(lz),combine(std::move(combine)),apply(std::move(apply)),merge(std::move(merge)){
        if(!init.empty())build(1,0,n-1,init);
    }
    void build(int i,int l,int r,const v<T>& init){
        if(l==r){seg[i]=init[l];return;}
        int m=(l+r)/2;build(2*i,l,m,init);build(2*i+1,m+1,r,init);
        seg[i]=combine(seg[2*i],seg[2*i+1]);
    }
    void push_down(int i,int l,int r){
        if(lazy[i]!=lz){
            int m=(l+r)/2; lazy[2*i]=merge(lazy[2*i],lazy[i]);
            lazy[2*i+1]=merge(lazy[2*i+1],lazy[i]);  seg[2*i]=apply(seg[2*i],lazy[i],m-l+1); seg[2*i+1]=apply(seg[2*i+1],lazy[i],r-m);  lazy[i]=lz;
        }
    }
    void update_range(int i,int l,int r,int ql,int qr,U val){
        if(ql>r||qr<l) return;
        if(ql<=l && r<=qr){ lazy[i]=merge(lazy[i],val); seg[i]=apply(seg[i],val,r-l+1); return;}
        push_down(i,l,r); int m=(l+r)/2;update_range(2*i,l,m,ql,qr,val);
        update_range(2*i+1,m+1,r,ql,qr,val);seg[i]=combine(seg[2*i],seg[2*i+1]);
    }
    T query_range(int i,int l,int r,int ql,int qr){
        if(ql>r||qr<l)return z; if(ql<=l && r<=qr)return seg[i];
        push_down(i,l,r);int m=(l+r)/2;return combine(query_range(2*i,l,m,ql,qr),
        query_range(2*i+1,m+1,r,ql,qr));
    }
    void update(int l,int r,U val){update_range(1,0,n-1,l,r,val);}
    T query(int l,int r){return query_range(1,0,n-1,l,r);}
};
tpl_<tn_ T, tn_ U> ostream& operator<<(ostream& os, const LazySegtree<T,U>& seg){
    int maxRows=20, rowCount=0, maxDepth=4; function<void(int,int,int,int)> pt; pt=[maxRows, maxDepth, &rowCount, &os, &seg, &pt](int i,int a,int b,int d){
        if(a>b||rowCount>=maxRows||d>maxDepth)return; os<<string(d*2,' ')<<"["<<a<<","<<b<<"]: "<<seg.seg[i]<<", "<<seg.lazy[i]<<"\n";
        rowCount++; if(a!=b){ int m=(a+b)/2; pt(2*i,a,m,d+1); pt(2*i+1,m+1,b,d+1); }}; os<<"Lazy Segtree:\n"; pt(1,0,seg.n-1,0); return os;
}
