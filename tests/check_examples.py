"""Compile all complete examples and check samples, boundaries and small oracles."""
from pathlib import Path
import subprocess, random, itertools, json, collections, sys

ROOT = Path(__file__).resolve().parents[1]
BUILD = ROOT / 'build' / 'tests'
BUILD.mkdir(parents=True, exist_ok=True)
cases = []
def add(name, data, expected):
    cases.append((name, data, str(expected).strip()))

fixed = [
('01_stats','6\n3 -1 3 2 -1 5\n','11 -1 5\n-1 2'),
('02_grid','2 3\n1 0 1\n0 1 0\n','0 1 0\n1 0 1'),
('03_rank','4\nb02 90\na01 95\na02 90\na03 90\n','a01 95\na02 90\na03 90\nb02 90'),
('04_tokens','add "hello world" "" x\n','4\n[add]\n[hello world]\n[]\n[x]'),
('04_tokens','a"b c"d\n','1\n[ab cd]'),('04_tokens','   \n','0'),
('04_tokens','"abc\n','ERROR'),('04_tokens','""\n','1\n[]'),
('05_prefix','5 3\n2 -1 3 4 5\n1 3\n2 4\n5 5\n','4\n6\n5'),
('06_difference','5 2\n1 2 3 4 5\n2 4 3\n1 5 -1\n','0 4 5 6 4'),
('07_wood','4 7\n20 15 10 17\n','7'),('07_wood','2 3\n1 1\n','0'),
('08_window','4 100\n10 5 2 6\n','8'),('08_window','3 1\n1 1 1\n','0'),
('09_merge','4\n1 2 3 4\n','19'),('09_merge','1\n9\n','0'),
('10_permutations','3\n','1 2 3\n1 3 2\n2 1 3\n2 3 1\n3 1 2\n3 2 1'),
('11_bfs','3 4\n....\n.##.\n....\n','5'),
('11_bfs','1 1\n.\n','0'),('11_bfs','1 1\n#\n','-1'),
('12_lis','6\n3 1 2 2 5 4\n','3'),
('13_maxsum','5\n-2 3 -1 4 -5\n','6'),('13_maxsum','3\n-5 -2 -7\n','-2'),
('14_triangle','3\n2\n-1 3\n4 -2 1\n','6'),('14_triangle','1\n-9\n','-9'),
('15_knapsack01','3 5\n2 3\n3 4\n4 5\n','7'),
('16_knapsack_complete','2 7\n2 3\n3 4\n','10'),
('17_coin_count','3 5\n1 2 5\n','4'),('17_coin_count','2 0\n2 3\n','1'),
('18_group','2 5\n2\n2 3\n3 5\n2\n2 4\n4 7\n','9'),
('18_group','1 5\n2\n2 3\n3 5\n','5'),
('19_path','/a/b\n5\n../c\n/x//./y/../\n../../../\n.\ntmp/../../z\n','/a/c\n/x\n/\n/a/b\n/a/z'),
('20_permissions','8\nCHECK alice file1\nGRANT alice file1\nGRANT alice file1\nCHECK alice file1\nREVOKE alice file1\nCHECK alice file1\nREVOKE bob file2\nCHECK bob file2\n','NO\nYES\nNO\nNO'),
('21_expression','2 * (3 + 4) - -5\n','19'),
('21_expression','1 + (2 * 3\n','ERROR'),('21_expression','1 2\n','ERROR'),
('21_expression','\n','ERROR'),('21_expression','-2*-3+4\n','10'),
('21_expression','8-3-2\n','3'),('21_expression','2(3+4)\n','ERROR'),
('22_selector','7 5\n0 html -\n1 body -\n2 div main\n3 p one\n2 div side\n3 p two\n2 p three\np\ndiv p\n#main p\ndiv div p\n#side\n','3 4 6 7\n2 4 6\n1 4\n0\n1 5'),
('22_selector','1 2\n0 div root\ndiv div\n#root\n','0\n1 1'),
('23_templates','3\ntitle 1 world\nline 3 hello @title !\nall 2 @line @line\nall\n','hello world ! hello world !'),
('23_templates','2\na 1 @b\nb 1 @a\na\n','ERROR'),
('23_templates','1\na 1 @missing\na\n','ERROR'),
('23_templates','2\na 0\nb 1 @b\na\n',''),
('24_pairs','5 2\n1 3 1 3 3\n','6'),('24_pairs','3 0\n7 7 7\n','3'),
('25_rectangle','3 3 2\n1 1 2 2 2\n2 2 3 3 3\n','5 1'),
('25_rectangle','2 2 0\n','0 4'),('25_rectangle','2 2 1\n1 1 2 2 -5\n','-5 4'),
('26_scheduler','4\n0 1 5\n1 1 2\n2 3 1\n5 2 2\n','0 5\n8 10\n5 6\n6 8\n7'),
('26_scheduler','2\n4 1 2\n0 1 1\n','4 6\n0 1\n0'),
]
for x in fixed: add(*x)

rng = random.Random(20261009)
for _ in range(25):
    n = rng.randint(1,8); a = [rng.randint(-8,8) for _ in range(n)]
    freq = collections.Counter(a); mode = min(a, key=lambda x:(-freq[x],x))
    add('01_stats',f'{n}\n'+ ' '.join(map(str,a)),f'{sum(a)} {min(a)} {max(a)}\n{mode} {freq[mode]}')
    add('13_maxsum',f'{n}\n'+' '.join(map(str,a)),max(sum(a[l:r]) for l in range(n) for r in range(l+1,n+1)))
    lis = 0
    for mask in range(1<<n):
        b = [a[i] for i in range(n) if mask>>i&1]
        if all(x<y for x,y in zip(b,b[1:])):lis=max(lis,len(b))
    add('12_lis',f'{n}\n'+' '.join(map(str,a)),lis)
    c = rng.randint(0,8)
    add('24_pairs',f'{n} {c}\n'+' '.join(map(str,a)),sum(abs(a[i]-a[j])==c for i in range(n) for j in range(i+1,n)))
    pairs = [(rng.randint(1,n),rng.randint(1,n)) for _ in range(5)]
    pairs = [(min(x,y),max(x,y)) for x,y in pairs]
    add('05_prefix',f'{n} 5\n'+' '.join(map(str,a))+'\n'+'\n'.join(f'{l} {r}' for l,r in pairs),'\n'.join(str(sum(a[l-1:r])) for l,r in pairs))
    b=a[:]; ops=[]
    for l,r in pairs:
        v=rng.randint(-5,5);ops.append((l,r,v))
        for i in range(l-1,r):b[i]+=v
    add('06_difference',f'{n} 5\n'+' '.join(map(str,a))+'\n'+'\n'.join(' '.join(map(str,x)) for x in ops),' '.join(map(str,b)))
    wood=[rng.randint(1,20) for _ in range(n)]; k=rng.randint(1,50)
    best=max([0]+[x for x in range(1,max(wood)+1) if sum(v//x for v in wood)>=k])
    add('07_wood',f'{n} {k}\n'+' '.join(map(str,wood)),best)
    pos=[rng.randint(1,8) for _ in range(n)]; k=rng.randint(0,100); ans=0
    for l in range(n):
        product=1
        for rr in range(l,n):product*=pos[rr];ans+=product<k
    add('08_window',f'{n} {k}\n'+' '.join(map(str,pos)),ans)
    capacity=rng.randint(0,12);items=[(rng.randint(1,6),rng.randint(0,10)) for _ in range(n)]
    best=max(sum(items[i][1] for i in range(n) if mask>>i&1) for mask in range(1<<n) if sum(items[i][0] for i in range(n) if mask>>i&1)<=capacity)
    data=f'{n} {capacity}\n'+'\n'.join(f'{c} {w}' for c,w in items)
    add('15_knapsack01',data,best)
    from functools import lru_cache
    @lru_cache(None)
    def unlimited(i,v):
        if i==n:return 0
        c,w=items[i]
        return max(t*w+unlimited(i+1,v-t*c) for t in range(v//c+1))
    add('16_knapsack_complete',data,unlimited(0,capacity))
    coins=rng.sample(range(1,8),rng.randint(1,4));target=rng.randint(0,15)
    @lru_cache(None)
    def combos(i,t):
        if i==len(coins):return int(t==0)
        return sum(combos(i+1,t-k*coins[i]) for k in range(t//coins[i]+1))
    add('17_coin_count',f'{len(coins)} {target}\n'+' '.join(map(str,coins)),combos(0,target))
    groups=[[(rng.randint(1,5),rng.randint(0,8)) for _ in range(2)] for _ in range(3)]
    best=max(sum(t[1] for t in selected) for selected in itertools.product(*[[(0,0)]+g for g in groups]) if sum(t[0] for t in selected)<=capacity)
    add('18_group',f'3 {capacity}\n'+'\n'.join('2\n'+'\n'.join(f'{c} {w}' for c,w in g) for g in groups),best)
    h=rng.randint(1,5);w=rng.randint(1,5);grid=[[0]*w for _ in range(h)];ops=[]
    for _ in range(5):
        x1,x2=sorted([rng.randrange(h),rng.randrange(h)]);y1,y2=sorted([rng.randrange(w),rng.randrange(w)]);v=rng.randint(-5,5)
        ops.append((x1+1,y1+1,x2+1,y2+1,v))
        for x in range(x1,x2+1):
            for y in range(y1,y2+1):grid[x][y]+=v
    flat=sum(grid,[]);best=max(flat)
    add('25_rectangle',f'{h} {w} 5\n'+'\n'.join(' '.join(map(str,t)) for t in ops),f'{best} {flat.count(best)}')
    tasks=[(rng.randint(0,12),rng.randint(0,3),rng.randint(1,6)) for _ in range(n)]
    remaining=set(range(n)); now=0;ans=[None]*n;wait=0
    while remaining:
        available=[i for i in remaining if tasks[i][0]<=now]
        if not available:now=min(tasks[i][0] for i in remaining);continue
        i=min(available,key=lambda i:(-tasks[i][1],tasks[i][0],i));remaining.remove(i)
        arrival,_,duration=tasks[i];ans[i]=(now,now+duration);wait=max(wait,now-arrival);now+=duration
    add('26_scheduler',str(n)+'\n'+'\n'.join(' '.join(map(str,t)) for t in tasks),'\n'.join(f'{a} {b}' for a,b in ans)+'\n'+str(wait))

sources=sorted((ROOT/'code').glob('*.cpp'))
for source in sources:
    exe=BUILD/(source.stem+('.exe' if sys.platform=='win32' else ''))
    result=subprocess.run(['g++','-std=c++17','-O2','-Wall','-Wextra','-pedantic',str(source),'-o',str(exe)],capture_output=True,text=True,encoding='utf-8',errors='replace')
    if result.returncode:
        raise RuntimeError(result.stderr)
print(f'Compiled {len(sources)} programs',flush=True)
for name,data,expected in cases:
    exe=BUILD/(name+('.exe' if sys.platform=='win32' else ''))
    result=subprocess.run([str(exe)],input=data,text=True,capture_output=True,check=True,timeout=5)
    if result.stdout.strip()!=expected:
        raise AssertionError(f'{name}\ninput={data!r}\nexpected={expected!r}\nactual={result.stdout!r}')
report={'programs':len(sources),'checks':len(cases),'sample_and_boundary_checks':len(fixed),'random_oracle_checks':len(cases)-len(fixed),'seed':20261009,'result':'passed'}
(BUILD/'report.json').write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
print(json.dumps(report),flush=True)
