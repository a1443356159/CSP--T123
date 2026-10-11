"""Compile actual marked lecture snippets and compare against independent oracles."""
from pathlib import Path
import json
import re
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / 'build/knowledge-tests'
BUILD.mkdir(parents=True, exist_ok=True)
snippets = {}
for path in (ROOT / 'chapters').glob('*.tex'):
    for tag, code in re.findall(r'% snippet:([a-z0-9_]+)\s*\\begin\{lstlisting\}\n(.*?)\\end\{lstlisting\}', path.read_text(encoding='utf-8-sig'), re.S):
        assert tag not in snippets, tag
        snippets[tag] = code.strip()

units = []
tested = []
def add(tag, declarations, body, oracle, function_prefix=None, split=None):
    code = snippets[tag]
    functions = ''
    if function_prefix:
        pos = code.index(function_prefix)
        body_code = code[:pos]
        functions = code[pos:]
    elif split:
        before, functions, after = split(code)
        body_code = before + after
    else:
        body_code = code
    if body is None:
        functions = code
        body_code = ''
        body = ''
    namespace = 'test_' + tag
    units.append('namespace ' + namespace + ' {\n' + declarations + '\n' + functions +
                 '\nint run() {\n' + body + '\n' + body_code + '\n' + oracle + '\n}\n}\n')
    tested.append(tag)

add('prefix1d', 'int n=20; long long a[22],s[22];', 'for(int i=1;i<=n;i++) a[i]=(i*17)%23-11;',
    'for(int l=1;l<=n;l++) for(int r=l;r<=n;r++){long long want=0; for(int i=l;i<=r;i++) want+=a[i]; assert(range_sum(l,r)==want);} return n*(n+1)/2;',
    function_prefix='long long range_sum')
add('prefix2d', 'int n=7,m=9; long long a[10][12],s[10][12];',
    'for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) a[i][j]=(i*19+j*7)%31-15;',
    'int checks=0; for(int x=1;x<=n;x++) for(int xx=x;xx<=n;xx++) for(int y=1;y<=m;y++) for(int yy=y;yy<=m;yy++){long long want=0;for(int i=x;i<=xx;i++)for(int j=y;j<=yy;j++)want+=a[i][j];assert(rectangle_sum(x,y,xx,yy)==want); checks++;} return checks;',
    function_prefix='long long rectangle_sum')

def diff_split(code):
    pos = code.index('void add_range')
    end = code.index('// After all updates:')
    return code[:pos], code[pos:end], 'for(int t=0;t<80;t++){int l=1+gen()%n,r=l+gen()%(n-l+1);long long v=(int)(gen()%21)-10;add_range(l,r,v);for(int i=l;i<=r;i++)want[i]+=v;}\n' + code[end:]
add('difference1d','int n=20; long long a[22],d[22],want[22];',
    'for(int i=1;i<=n;i++) want[i]=a[i]=(int)(gen()%21)-10;',
    'for(int i=1;i<=n;i++) assert(a[i]==want[i]);return n;', split=diff_split)
def diff2_split(code):
    pos = code.index('void add_rectangle')
    end = code.index('// After all updates,')
    ops = 'for(int t=0;t<80;t++){int x=1+gen()%n,xx=x+gen()%(n-x+1),y=1+gen()%m,yy=y+gen()%(m-y+1);long long v=(int)(gen()%21)-10;add_rectangle(x,y,xx,yy,v);for(int i=x;i<=xx;i++)for(int j=y;j<=yy;j++)want[i][j]+=v;}\n'
    return code[:pos],code[pos:end],ops+code[end:]
add('difference2d','int n=7,m=9;long long d[10][12],want[10][12];','',
    'for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)assert(d[i][j]==want[i][j]);return n*m;', split=diff2_split)
add('binary_array','',None,
    'int a[40];int count=0;for(int n=0;n<=30;n++){for(int i=0;i<n;i++)a[i]=i/3-5;for(int x=-8;x<=9;x++){int want=0;while(want<n && a[want]<x)want++;assert(first_ge(a,n,x)==want);count++;}}return count;')
add('binary_answer','int target; bool check(int x){return x>=target;}','int checks=0; for(target=0;target<=100;target++){int L=0,R=100;',
    'assert(answer==target);checks++;}return checks;')
add('binary_real','',None,
    'double xs[]={0,1e-12,0.01,0.5,1,2,9,1e6,1e12};for(double x:xs){double actual=sqrt_binary(x);assert(std::abs(actual-std::sqrt(x))<=1e-9*std::max(1.0,std::sqrt(x)));}return 9;')
add('window','int a[20];',
    'for(int t=0;t<200;t++){int n=gen()%15;long long K=gen()%30;for(int i=0;i<n;i++)a[i]=gen()%9;',
    'int want=0;for(int l=0;l<n;l++){long long s=0;for(int r=l;r<n;r++){s+=a[r];if(s<=K)want=std::max(want,r-l+1);}}assert(best==want);}return 200;')
add('two_sequences','int a[20],b[20];',
    'for(int t=0;t<200;t++){int n=gen()%15,m=gen()%15;std::map<int,int> ca,cb;for(int i=0;i<n;i++)ca[a[i]=gen()%8]++;for(int i=0;i<m;i++)cb[b[i]=gen()%8]++;std::sort(a,a+n);std::sort(b,b+m);',
    'int want=0;for(std::pair<const int,int> item:ca)want+=std::min(item.second,cb[item.first]);assert(common==want);}return 200;')
def greedy_split(code):
    pos=code.index('// a[0..n-1]')
    return '', code[:pos]+'\nInterval a[10];',code[pos:]
add('greedy','', 'for(int t=0;t<120;t++){int n=gen()%9;int l[10],r[10];for(int i=0;i<n;i++){l[i]=(int)(gen()%15)-7;r[i]=l[i]+1+gen()%5;a[i]={l[i],r[i]};}',
    'int want=0;for(int mask=0;mask<(1<<n);mask++){bool ok=true;int k=0;for(int i=0;i<n;i++)if(mask>>i&1){k++;for(int j=0;j<i;j++)if(mask>>j&1)if(!(r[i]<=l[j]||r[j]<=l[i]))ok=false;}if(ok)want=std::max(want,k);}assert(count==want);}return 120;',
    split=greedy_split)
add('gcd','',None,
    'for(int i=0;i<200;i++){long long a=gen()%100000,b=gen()%100000;assert(gcd(a,b)==std::gcd(a,b));}return 200;')
# Capture the actual snippet's printed factor/exponent pairs.
add('factor','std::vector<std::pair<long long,int>> factors; void printf(const char*,long long p,int e=1){factors.push_back({p,e});}',
    'for(long long original=2;original<=200;original++){long long x=original;factors.clear();',
    'long long product=1;for(std::pair<long long,int> item:factors){for(long long d=2;d*d<=item.first;d++)assert(item.first%d!=0);for(int i=0;i<item.second;i++)product*=item.first;}assert(product==original);}return 199;')
add('dfs','int n, path[10], used[11];std::set<std::vector<int>> paths; void visit(int a[],int n){paths.insert(std::vector<int>(a,a+n));}',None,
    'int fact=1;for(n=0;n<=7;n++){paths.clear();dfs(0);if(n)fact*=n;assert((int)paths.size()==fact);for(std::vector<int> p:paths){std::sort(p.begin(),p.end());for(int i=0;i<n;i++)assert(p[i]==i+1);}for(int x=1;x<=n;x++)assert(!used[x]);}return 8;')
add('bfs','std::vector<int> adj[12];int dist[12],q[12];',
    'for(int t=0;t<100;t++){int n=1+gen()%10,start=gen()%n;int want[12][12];for(int i=0;i<n;i++){adj[i].clear();for(int j=0;j<n;j++){want[i][j]=(i==j?0:1000);if(i!=j&&gen()%4==0){adj[i].push_back(j);want[i][j]=1;}}}for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)want[i][j]=std::min(want[i][j],want[i][k]+want[k][j]);',
    'for(int i=0;i<n;i++)assert(dist[i]==(want[start][i]>=1000?-1:want[start][i]));}return 100;')
def lis_oracle(answer):
    return 'int want=0;for(int mask=0;mask<(1<<n);mask++){int count=0,last=0;bool ok=true;for(int i=0;i<n;i++)if(mask>>i&1){if(count&&last>=a[i])ok=false;last=a[i];count++;}if(ok)want=std::max(want,count);}assert('+answer+'==want);}return 160;'
for tag,answer in [('lis_quadratic','answer'),('lis_fast','len')]:
    add(tag,'int a[12],f[12],tail[12];',
        'for(int t=0;t<160;t++){int n=gen()%10;for(int i=0;i<n;i++)a[i]=(int)(gen()%9)-4;',
        lis_oracle(answer))
def lcs_oracle():
    return 'int want=0;for(int mask=0;mask<(1<<n);mask++){int p=1,k=0;bool ok=true;for(int i=1;i<=n;i++)if(mask>>(i-1)&1){while(p<=m&&b[p]!=a[i])p++;if(p>m){ok=false;break;}p++;k++;}if(ok)want=std::max(want,k);}assert(RESULT==want);}return 160;'
for tag,decl,result,reset in [
    ('lcs','int a[12],b[12],f[12][12];','f[n][m]','memset(f,0,sizeof(f));'),
    ('lcs_rolling','int a[12],b[12],f[12];','f[m]','memset(f,0,sizeof(f));')]:
    add(tag,decl,'for(int t=0;t<160;t++){int n=gen()%9,m=gen()%9;'+reset+'for(int i=1;i<=n;i++)a[i]=gen()%4;for(int i=1;i<=m;i++)b[i]=gen()%4;',
        lcs_oracle().replace('RESULT',result))
add('knapsack01','int v[10],w[10];long long f[25];',
    'for(int t=0;t<160;t++){int n=gen()%8,V=gen()%20;memset(f,0,sizeof(f));for(int i=1;i<=n;i++){v[i]=1+gen()%7;w[i]=(int)(gen()%15)-3;}',
    'long long want=0;for(int mask=0;mask<(1<<n);mask++){int vol=0;long long val=0;for(int i=1;i<=n;i++)if(mask>>(i-1)&1){vol+=v[i];val+=w[i];}if(vol<=V)want=std::max(want,val);}assert(f[V]==want);}return 160;')
# Enumeration of quantities is independent of the capacity-loop optimization.
add('knapsack_exact','int v[10],w[10];long long f[25];',
    'for(int t=0;t<160;t++){int n=gen()%8,V=gen()%20;for(int i=1;i<=n;i++){v[i]=1+gen()%7;w[i]=(int)(gen()%15)-3;}',
    'long long want=NEG;for(int mask=0;mask<(1<<n);mask++){int vol=0;long long val=0;for(int i=1;i<=n;i++)if(mask>>(i-1)&1){vol+=v[i];val+=w[i];}if(vol==V)want=std::max(want,val);}assert(f[V]==want);}return 160;')
quantity_reference = r'''
long long enumerate(int i,int n,int remaining) {
    if(i>n)return 0;
    long long best=0;
    for(int k=0;k<=std::min(count[i],remaining/v[i]);k++)
        best=std::max(best,k*w[i]+enumerate(i+1,n,remaining-k*v[i]));
    return best;
}
'''
for tag in ['knapsack_complete','knapsack_multiple']:
    add(tag,'int v[8],count[8];long long w[8],f[25];'+quantity_reference,
        'for(int t=0;t<120;t++){int n=gen()%5,V=gen()%18;memset(f,0,sizeof(f));for(int i=1;i<=n;i++){v[i]=1+gen()%6;w[i]=(int)(gen()%11)-2;count[i]='+('V/v[i]' if tag.endswith('complete') else 'gen()%8')+';}',
        'assert(f[V]==enumerate(1,n,V));}return 120;')
group_reference = r'''
long long enumerate(int g,int groups,int remaining) {
    if(g==groups)return 0;
    long long best=enumerate(g+1,groups,remaining);
    for(int k=0;k<size[g];k++)if(v[g][k]<=remaining)
        best=std::max(best,w[g][k]+enumerate(g+1,groups,remaining-v[g][k]));
    return best;
}
'''
add('knapsack_group','int size[6],v[6][5];long long w[6][5],f[25],old[25];'+group_reference,
    'for(int t=0;t<120;t++){int groups=1+gen()%4,V=gen()%18;memset(f,0,sizeof(f));for(int g=0;g<groups;g++){size[g]=1+gen()%3;for(int k=0;k<size[g];k++){v[g][k]=1+gen()%6;w[g][k]=(int)(gen()%11)-2;}}',
    'assert(f[V]==enumerate(0,groups,V));}return 120;')
count_reference = r'''
long long enumerate(int i,int n,int remaining){
    if(i>n)return remaining==0;
    long long answer=0;
    for(int k=0;k*v[i]<=remaining;k++) answer+=enumerate(i+1,n,remaining-k*v[i]);
    return answer;
}
'''
add('knapsack_count','int v[6];long long ways[25];'+count_reference,
    'for(int t=0;t<120;t++){int n=1+gen()%4,V=gen()%18,MOD=7;for(int i=1;i<=n;i++)v[i]=i;',
    'assert(ways[V]==enumerate(1,n,V)%MOD);}return 120;')

add('scan_number','',
    'char s[]="12345,7";int p=0;',
    'assert(value==12345&&p==5);return 1;')
add('scan_state','',
    'char s[]="a \\"b c\\" d";',
    'assert(separators==2&&!in_quote);return 1;')
add('synchronous','long long a[20],b[20],want[20];',
    'for(int t=0;t<120;t++){int n=gen()%15;for(int i=0;i<n;i++)a[i]=(int)(gen()%21)-10;for(int i=0;i<n;i++){want[i]=0;for(int j=0;j<n;j++)if(std::abs(i-j)<=1)want[i]+=a[j];}',
    'for(int i=0;i<n;i++)assert(a[i]==want[i]);}return 120;')
add('parse_stack','int st[40];',
    'for(int t=0;t<120;t++){int n=gen()%25;char s[40];for(int i=0;i<n;i++)s[i]=(gen()%2?\'(\':\')\');s[n]=0;int balance=0;bool want=true;for(int i=0;i<n;i++){balance+=(s[i]==\'(\'?1:-1);if(balance<0)want=false;}want=want&&balance==0;',
    'assert((bool)valid==want);}return 120;')
parser_generator = r'''
std::pair<std::string,long long> expression(int depth){
    if(!depth || gen()%3==0){long long x=gen()%100;return {std::to_string(x),x};}
    std::pair<std::string,long long> a=expression(depth-1),b=expression(depth-1);
    return {"("+a.first+"+"+b.first+")",a.second+b.second};
}
'''
add('recursive_parser',parser_generator,None,
    'for(int t=0;t<120;t++){std::pair<std::string,long long> e=expression(5);strcpy(s,e.first.c_str());p=0;assert(parse_expr()==e.second);assert(s[p]==0);}return 120;')
# Build adjacency from the actual array-based snippet, then validate subtree counts by parent chains.
tree_declarations='int n,parent[40],first[40],next[40];'
tree_function=snippets['tree_size']
add('tree_build',tree_declarations+tree_function,
    'for(int t=0;t<120;t++){n=1+gen()%30;parent[0]=-1;for(int v=1;v<n;v++)parent[v]=gen()%v;',
    'for(int u=0;u<n;u++){int want=0;for(int v=0;v<n;v++){int p=v;while(p!=-1&&p!=u)p=parent[p];if(p==u)want++;}assert(subtree_size(u)==want);}}return 120;')
tested.append('tree_size')
add('dependency','std::vector<int> dependency[12];int color[12],order[12],count;',None,
    'for(int t=0;t<160;t++){int n=1+gen()%10;bool reach[12][12]={};memset(color,0,sizeof(color));count=0;for(int u=0;u<n;u++){dependency[u].clear();for(int v=0;v<n;v++)if(gen()%7==0){dependency[u].push_back(v);reach[u][v]=true;}}for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)reach[i][j]=reach[i][j]||(reach[i][k]&&reach[k][j]);bool want=true;for(int i=0;i<n;i++)if(reach[i][i])want=false;bool actual=true;for(int u=0;u<n;u++)if(!solve(u)){actual=false;break;}assert(actual==want);if(actual){int pos[12];assert(count==n);for(int i=0;i<n;i++)pos[order[i]]=i;for(int u=0;u<n;u++)for(int v:dependency[u])assert(pos[v]<pos[u]);}}return 160;')

add('median','int a[20];',
    'for(int t=0;t<120;t++){int n=1+gen()%15;for(int i=0;i<n;i++)a[i]=(int)(gen()%21)-10;',
    'long long want=100000;for(int p=-10;p<=10;p++){long long sum=0;for(int i=0;i<n;i++)sum+=std::abs(a[i]-p);want=std::min(want,sum);}assert(answer==want);}return 120;')
add('matrix','int a[2][3]={{1,2,3},{4,5,6}},b[3][2]={{7,8},{9,10},{11,12}};long long c[2][2];',
    'int n=2,m=2,k=3;',
    'assert(c[0][0]==58&&c[0][1]==64&&c[1][0]==139&&c[1][1]==154);return 1;')
add('stairs','long long f[92];long long enumerate(int n){if(n<0)return 0;if(n==0)return 1;return enumerate(n-1)+enumerate(n-2);}',
    'for(int n=0;n<=20;n++){',
    'assert(f[n]==enumerate(n));}return 21;')
add('c_string','','','assert(len==3&&!strcmp(a,"cat")&&!strcmp(b,"bat")&&relation>0);return 1;')
add('line_input','','','assert(!strcmp(line,"a b"));return 1;')
add('char_class','','char line[]="A b3Z8!";','assert(digits==2&&!strcmp(line,"a b3z8!"));return 1;')

# Compile and run the STL demonstrations unchanged, with assertions on their final state.
stl_specs = {
    'stl_sort': ('', '', 'assert(a[0]==9 && students[0].id==1);return 1;'),
    'stl_unique': ('','','assert(len==3&&a[0]==1&&a[2]==3);assert((v==std::vector<int>{1,2,3}));return 1;'),
    'stl_lower': ('','','assert(p==2&&!exists);return 1;'),
    'stl_upper': ('','','assert(l==0&&r==2&&count==2);return 1;'),
    'discretize': ('','','assert(size==2&&rank[0]==1&&rank[1]==0&&rank[2]==1);return 1;'),
    'stl_vector': ('','','assert((v==std::vector<int>{2,2,2}));return 1;'),
    'stl_string': ('','','assert(s=="Yat!"&&part=="ca"&&p==std::string::npos);return 1;'),
    'stl_pair': ('','','assert(a[0].first==1&&a[1].second==3);return 1;'),
    'stl_stack': ('','','assert(st.size()==1&&st.top()==3);return 1;'),
    'stl_queue': ('','','assert(q.size()==1&&q.front()==5);return 1;'),
    'stl_heap': ('','','assert(maximum==9&&minimum==4);return 1;'),
    'stl_heap_struct': ('','','assert(pq.top().id==1);return 1;'),
    'stl_set': ('','','assert(s.size()==1&&*s.begin()==7);return 1;'),
    'stl_multiset': ('','','assert(copies==1&&s.size()==1&&*s.begin()==7);return 1;'),
    'stl_map': ('','','assert(freq.size()==1&&freq[7]==2);return 1;'),
    'stl_umap': ('','','assert(freq.empty());return 1;'),
    'stl_uset': ('','','assert(inserted&&exists&&seen.empty());return 1;'),
}
for tag,(decl,body,oracle) in stl_specs.items():
    split=None
    if tag=='stl_sort':
        def split(code):
            pos=code.index('// int a[n]')
            return '',code[:pos], 'int n=3,a[]={2,9,1};Student students[]={{90,3},{95,2},{95,1}};\n'+code[pos:]
    if tag=='stl_heap_struct':
        def split(code):
            pos=code.index('std::priority_queue<Task')
            return '',code[:pos],code[pos:]
    if tag=='discretize':
        body='int n=3,a[]={100,7,100},b[3],rank[3];'
    add(tag,decl,body,oracle,split=split)

header = r'''
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
std::mt19937 gen(20261011);
'''
source=BUILD/'knowledge.cpp'
assert set(tested)==set(snippets), (set(snippets)-set(tested),set(tested)-set(snippets))
source.write_text(header+'\n'.join(units)+'\nint main(){int checks=0;\n'+
    '\n'.join('checks+=test_'+tag+'::run();' for tag in tested if tag!='tree_size')+
    '\nprintf("CHECKS=%d\\n",checks);}\n',encoding='utf-8')
exe=BUILD/('knowledge.exe' if sys.platform=='win32' else 'knowledge')
result=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra','-pedantic',str(source),'-o',str(exe)],capture_output=True,text=True,encoding='utf-8',errors='replace')
if result.returncode:
    raise RuntimeError(result.stderr)
result=subprocess.run([str(exe)],input='a b\r\ncat\n',capture_output=True,text=True,timeout=30)
if result.returncode:
    raise RuntimeError(result.stderr)
checks=int(re.search(r'CHECKS=(\d+)',result.stdout)[1])
report={'snippets':len(tested),'checks':checks,'seed':20261011,'result':'passed','tested_tags':tested}
(BUILD/'report.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report,ensure_ascii=False))
