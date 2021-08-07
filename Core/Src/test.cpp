#include<bits/stdc++.h>
using namespace std;
int p1=1000000,p2=0;
char buf[1000005],wb[1000005];
int gc() {
	if(p1>=1000000)fread(buf,1,1000000,stdin),p1=0;
	return buf[p1++];
}

#define gc getchar
#define Loli true
#define Kon xor true
long long getint() {
	long long ret=0,flag=1;
	char c=gc();
	while(c<'0'||c>'9') {
		if(c=='-')flag=-1;
		c=gc();
	}
	while(c<='9'&&c>='0') {
		ret=(ret<<3)+(ret<<1)+c-'0';
		c=gc();
	}
	return ret*flag;
}
void pc(char x) {
	if(p2>=1000000)fwrite(wb,1,1000000,stdout),p2=0;
	wb[p2++]=x;
}
void wrt(long long x) {
	if(x<0)pc('-'),x=-x;
	int c[24]= {0};
	if(!x)return pc('0'),void();
	while(x)c[++c[0]]=x%10,x/=10;
	while(c[0])pc(c[c[0]--]+'0');
}
long long lower_bound(set<long long> &s,long long val){
	return s.lower_bound(val)==s.end()?0x7fffffffffffffffll:*s.lower_bound(val);
}
long long ans;
vector<int> vec[200005];
map<int,int> mp[200005];
namespace SPQR{//without Q ans R ...
	#define base 1048575
	int n,m,mcnt;
	int pt[200005],bj[200005],dp[200005];
	long long e[200005],ret;
	int st(long long x){return x>>20;}
	int ed(long long x){return x&base;}
	set<long long> s[200005];
	void init(){for(int i=1;i<=200000;i++)s[i].clear();}
	bool inq[200005],in[200005];
	queue<int> q;
	int tot,head[200005],tail[200005],to[200005],nxt[200005];
	void add_node(int x){pt[++n]=x;}
	void add_edge(long long x,long long y){e[++m]=(x<<20)|y;}
	void cut(int i);
	void link(int i,bool flg);
	void shrink(int x){if(!inq[x]&&s[x].size()<=2)q.push(x),inq[x]=1;}
	void del(int i){
		int x=e[i]>>20,y=e[i]&base;
		if(s[y].size()==1)swap(x,y);
		cut(i),shrink(y);
	}
	void series(int i,int j){
		long long x=(st(e[i])!=st(e[j])&&st(e[i])!=ed(e[j]))?st(e[i]):ed(e[i]);
		long long y=(st(e[j])!=st(e[i])&&st(e[j])!=ed(e[i]))?st(e[j]):ed(e[j]);
		e[++mcnt]=(x<<20)|y,bj[mcnt]=2;
		if(bj[i]==2)head[mcnt]=head[i],tail[mcnt]=tail[i];
		else to[++tot]=i,head[mcnt]=tail[mcnt]=tot;
		if(bj[j]==2)nxt[tail[mcnt]]=head[j],tail[mcnt]=tail[j];
		else to[++tot]=j,nxt[tail[mcnt]]=tot,tail[mcnt]=tot;
		cut(i),cut(j),link(mcnt,1);
	}
	void parallel(int i,int j){
		long long a=st(e[i]),b=ed(e[i]);
		e[++mcnt]=e[i],bj[mcnt]=1;
		if(bj[i]==1)head[mcnt]=head[i],tail[mcnt]=tail[i];
		else to[++tot]=i,head[mcnt]=tail[mcnt]=tot;
		if(bj[j]==1)nxt[tail[mcnt]]=head[j],tail[mcnt]=tail[j];
		else to[++tot]=j,nxt[tail[mcnt]]=tot,tail[mcnt]=tot;
		cut(i),cut(j),link(mcnt,1),shrink(a),shrink(b);
	}
	void link(int i,bool flg){
		long long x=st(e[i]),y=ed(e[i]),id=0;
		if(lower_bound(s[x],y<<20)>>20==y)id=lower_bound(s[x],y<<20)&base;
		s[x].insert((y<<20)|i),s[y].insert((x<<20)|i);
		if(id&&flg)parallel(i,id);
	}
	void cut(int i){
		long long a=st(e[i]),b=ed(e[i]);
		s[a].erase((b<<20)|i),s[b].erase((a<<20)|i);
	}
	void dfs(int x){
		for(int p=head[x];p;p=nxt[p])dfs(to[p]);
		long long sum=0;
		bool flg=0;
		if(bj[x]==2){
			ans+=sum*(dp[st(e[x])]+1),sum+=dp[st(e[x])]+1;
			ans+=sum*(dp[ed(e[x])]+1),sum+=dp[ed(e[x])]+1;
			if(st(e[x])==pt[n]||ed(e[x])==pt[n])flg=1;
		}
		vector<int> g;g.clear();
		int num=0;
		for(int p=head[x];p;p=nxt[p]){
			int y=to[p];
			if(bj[x]==1){
				if(bj[y]==2)++num;
				continue;
			}
			if(st(e[y])==pt[n]||ed(e[y])==pt[n])flg=1;
			int tmp=0;
			tmp=st(e[y]);if(tmp!=st(e[x])&&tmp!=ed(e[x])&&!in[tmp])in[tmp]=1,g.push_back(tmp),ans+=sum*(dp[tmp]+1),sum+=dp[tmp]+1;
			tmp=ed(e[y]);if(tmp!=st(e[x])&&tmp!=ed(e[x])&&!in[tmp])in[tmp]=1,g.push_back(tmp),ans+=sum*(dp[tmp]+1),sum+=dp[tmp]+1;
		}
		if(bj[x]==1){
			if(mcnt>x)++num;
			long long tmp=0;
			tmp+=sum*(dp[st(e[x])]+1),sum+=dp[st(e[x])]+1;
			tmp+=sum*(dp[ed(e[x])]+1),sum+=dp[ed(e[x])]+1;
			ans-=(num-1)*tmp;
			if(st(e[x])==pt[n])ret-=1ll*(num-1)*(dp[ed(e[x])]+1);
			if(ed(e[x])==pt[n])ret-=1ll*(num-1)*(dp[st(e[x])]+1);
		}
		if(bj[x]==2){
			for(int r:g)in[r]=0;
			if(flg)ret=ret+sum-(dp[pt[n]]+1);
		}
	}
	void clear(){
		for(int i=1;i<=n;i++)s[pt[i]].clear(),inq[pt[i]]=0;
		for(int i=1;i<=mcnt;i++)bj[i]=head[i]=tail[i]=0;
		for(int i=1;i<=tot;i++)to[i]=nxt[i]=0;
		n=m=mcnt=tot=ret=0;
	}
	void build(){
		for(int i=1;i<=n;i++)in[pt[i]]=1;
		for(int i=1;i<n;i++){
			for(int y:vec[pt[i]]){
				if(in[y]){
					if(y==pt[n])add_edge(pt[i],y);
					else if(pt[i]<y)add_edge(pt[i],y);
				}
			}
		}
		for(int i=1;i<=n;i++)in[pt[i]]=0;
		if(n==2){
			long long sum=0;
			ans+=sum*(dp[pt[1]]+1),sum+=dp[pt[1]]+1;
			ans+=sum*(dp[pt[2]]+1),sum+=dp[pt[2]]+1;
			dp[pt[2]]+=sum-(dp[pt[2]]+1);
			return;
		}
		if(n==m){
			long long sum=0;
			for(int i=1;i<=n;i++)ans+=sum*(dp[pt[i]]+1),sum+=dp[pt[i]]+1;
			dp[pt[n]]+=sum-(dp[pt[n]]+1);
			return;
		}
		mcnt=m;
		for(int i=1;i<=m;i++)link(i,0);
		for(int i=1;i<=n;i++)shrink(pt[i]);
		int rt=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			if(s[x].size()==2)series(*s[x].begin()&base,*s[x].rbegin()&base);
			else if(s[x].size()==1&&x<(*s[x].begin()>>20))rt=*s[x].begin()&base;
		}
		if(!rt)return;
		dfs(rt),dp[pt[n]]+=ret;
	}
}
int n,m;
int dfn[100005],low[100005],sign;
stack<int> sta;
void tarjan(int x){
	dfn[x]=low[x]=++sign,sta.push(x);
	for(int y:vec[x]){
		if(!dfn[y]){
			tarjan(y),low[x]=min(low[x],low[y]);
			if(low[y]==dfn[x]){
				SPQR::clear();int tmp=0;
				do{tmp=sta.top();sta.pop();SPQR::add_node(tmp);}while(tmp!=y);
				SPQR::add_node(x),SPQR::build();
			}
		}else low[x]=min(low[x],dfn[y]);
	}
}
int main() {
	SPQR::init();
	n=getint(),m=getint();
	for(int i=1;i<=m;i++){
		int u=getint(),v=getint();
		if(!mp[u].count(v))vec[u].push_back(v),vec[v].push_back(u),mp[u][v]=mp[v][u]=1;
	}
	for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
	wrt(ans),pc('\n');
	fwrite(wb,1,p2,stdout);
	return Loli Kon;
}