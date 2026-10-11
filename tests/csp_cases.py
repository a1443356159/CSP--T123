"""Original OJ samples plus independent small-input oracles for CSP programs."""
import json, random, itertools, functools

def make_cases(root):
    fixed=[]; random_cases=[]
    def add(name, inp, out): random_cases.append((name,inp,str(out).rstrip('\r\n')))
    meta=json.loads((root/'data/csp-practice.json').read_text(encoding='utf-8'))
    for p in meta['problems']:
        for s in p['samples']:
            fixed.append((p['program'][:-4],s['input'],s['output'].rstrip('\r\n')))
    fixed.extend([
        ('36_digits','0\n','0'),('37_turns','1\n10\n','0'),
        ('40_intervals','1\n1 2\n2 3\n','0'),
        ('41_sparse','1000000000 1 1\n1 100\n1000000000 -100\n','0'),
        ('42_neighborhood','1 16 100 6\n6\n','1'),
        ('43_factor','3\n9999999967 2\n10000000000 10\n360 3\n','1\n10000000000\n8'),
        ('44_feeding','4 3\n1 60 100\n','120'),
        ('46_dorm','1000000000000000000 1 2000\n','1863756'),
        ('48_knight','1 100\n1 1\n','1'),
        ('49_soy','0\n','0'),('50_jump','0\n','0'),
        ('53_small_middle_large','2\n0 -1\n','0 -0.5 -1'),
        ('54_derive','3\n0 0 0\n','0\n0'),
        ('55_encoding','1 999999999\n1000000000\n','999999999'),
        ('60_nonzero','3\n0 0 0\n','0'),
        ('61_travel','1 1 10\n5 1\n1\n','0'),
        ('63_shipping','2 90\n50\n50\n','100'),
    ])
    # Compute large-integer dorm reference with Python exact arithmetic.
    def dorm_ok(n,k,m,x):
        for _ in range(m):
            n -= (n*k+99)//100
            if n<x: return False
            n-=x
        return True
    lo,hi=0,10**9
    while lo<hi:
        mid=(lo+hi+1)//2
        if dorm_ok(10**18,1,2000,mid):lo=mid
        else:hi=mid-1
    fixed=[(name,inp,str(lo) if name=='46_dorm' and inp.startswith('1000000000000000000') else out)
           for name,inp,out in fixed]
    rng=random.Random(20261011)
    for _ in range(30):
        n,m=rng.randint(1,6),rng.randint(1,6)
        a=[[rng.randrange(20) for _ in range(m)] for _ in range(n)]
        add('35_rotate',f'{n} {m}\n'+'\n'.join(' '.join(map(str,row)) for row in a),
            '\n'.join(' '.join(str(a[i][j]) for i in range(n)) for j in range(m-1,-1,-1)))
        x=rng.randrange(10**9+1);add('36_digits',str(x),sum(map(int,str(x))))
        a=[rng.randrange(100) for _ in range(rng.randint(1,10))]
        add('37_turns',str(len(a))+'\n'+' '.join(map(str,a)),
            sum(min(a[i-1],a[i+1])>a[i] or max(a[i-1],a[i+1])<a[i] for i in range(1,len(a)-1)))
        points=[(i,rng.randrange(-5,6),'A' if i%2 else 'B') for i in range(6)]
        lines=[(2*rng.randrange(-5,6)+1,2*rng.randrange(-3,4),2*rng.randrange(-3,4)) for _ in range(8)]
        lines=[(c,a,b if a or b else 2) for c,a,b in lines]
        expected=[]
        for c,a,b in lines:
            signs={label:{(c+a*x+b*y)>0 for x,y,t in points if t==label} for label in ['A','B']}
            expected.append('Yes' if len(signs['A'])==len(signs['B'])==1 and signs['A']!=signs['B'] else 'No')
        add('38_classifier','6 8\n'+'\n'.join(f'{x} {y} {t}' for x,y,t in points)+'\n'+
            '\n'.join(f'{c} {a} {b}' for c,a,b in lines),'\n'.join(expected))
        n,m=rng.randint(1,8),rng.randint(1,4)
        a=[[rng.randrange(-5,6) for _ in range(m)] for _ in range(n)]
        ans=[next((j+1 for j in range(n) if all(a[j][k]>a[i][k] for k in range(m))),0) for i in range(n)]
        add('39_warehouses',f'{n} {m}\n'+'\n'.join(' '.join(map(str,row)) for row in a),'\n'.join(map(str,ans)))
        n=rng.randint(1,6);groups=[]
        for g in range(2):
            pos=1; intervals=[]
            for i in range(n):
                l=pos+rng.randint(0,3);r=l+rng.randint(1,5);intervals.append((l,r));pos=r+1
            groups.append(intervals)
        slots=[{t for l,r in g for t in range(l,r)} for g in groups]
        add('40_intervals',str(n)+'\n'+'\n'.join(f'{l} {r}' for g in groups for l,r in g),len(slots[0]&slots[1]))
        u={i:rng.choice([-3,-2,-1,1,2,3]) for i in rng.sample(range(1,51),rng.randint(1,12))}
        v={i:rng.choice([-3,-2,-1,1,2,3]) for i in rng.sample(range(1,51),rng.randint(1,12))}
        add('41_sparse',f'50 {len(u)} {len(v)}\n'+'\n'.join(f'{i} {x}' for d in [u,v] for i,x in sorted(d.items())),
            sum(u.get(i,0)*v.get(i,0) for i in range(1,51)))
        n,r,t=rng.randint(1,6),rng.randint(1,8),rng.randint(2,14)
        a=[[rng.randrange(16) for _ in range(n)] for _ in range(n)]
        ans=0
        for i in range(n):
            for j in range(n):
                values=[a[x][y] for x in range(n) for y in range(n) if abs(x-i)<=r and abs(y-j)<=r]
                ans+=sum(values)<=t*len(values)
        add('42_neighborhood',f'{n} 16 {r} {t}\n'+'\n'.join(' '.join(map(str,row)) for row in a),ans)
        n,k=rng.randint(2,100000),rng.randint(2,8);x=n;p=2;ans=1
        while p*p<=x:
            e=0
            while x%p==0:x//=p;e+=1
            if e>=k:ans*=p**e
            p+=1
        add('43_factor',f'1\n{n} {k}\n',ans)
        n,m=rng.randint(1,10),rng.randint(1,5);v=[0]+[rng.randint(0,100) for _ in range(m)]
        def feed(left):
            if left==0:return 0
            return max(v[i]+feed(left-i) for i in range(1,min(m,left)+1))
        add('44_feeding',f'{n} {m}\n'+' '.join(map(str,v[1:])),feed(n))
        n=rng.randint(1,8);a=[rng.randint(0,15) for i in range(n+1)];b=[0]+[rng.randint(0,25) for i in range(n)]
        expected=[]
        for missing in range(1,n+1):
            initial=balance=0
            for j in range(n+1):
                if balance<a[j]:initial+=a[j]-balance;balance=a[j]
                balance-=a[j]
                if j<n and j+1!=missing:balance+=b[j+1]
            expected.append(initial)
        add('45_dream',str(n)+'\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,b[1:])), ' '.join(map(str,expected)))
        n,k,m=rng.randint(100,300),rng.randint(1,5),rng.randint(1,8)
        ans=max(x for x in range(n//m+1) if dorm_ok(n,k,m,x))
        add('46_dorm',f'{n} {k} {m}',ans)
        chars=list('aAbB01 ');dest=chars.copy();rng.shuffle(dest);mapping=dict(zip(chars,dest))
        s=''.join(rng.choice(chars) for i in range(30));ks=[rng.randint(1,80) for i in range(5)];expected=[]
        for k in ks:
            result=s
            for i in range(k):result=''.join(mapping[c] for c in result)
            expected.append('#'+result+'#')
        add('47_transform','#'+s+'#\n7\n'+'\n'.join('#'+c+mapping[c]+'#' for c in chars)+
            '\n5\n'+' '.join(map(str,ks)), '\n'.join(expected))
        n,k=rng.randint(1,8),rng.randint(1,8);sx,sy=rng.randint(1,n),rng.randint(1,n)
        layer={(sx,sy)};all_reached=set(layer)
        moves=[(x,y) for x in [-2,-1,1,2] for y in [-2,-1,1,2] if abs(x)+abs(y)==3]
        for step in range(k):
            layer={(x+dx,y+dy) for x,y in layer for dx,dy in moves if 1<=x+dx<=n and 1<=y+dy<=n}
            all_reached |= layer
        add('48_knight',f'{n} {k}\n{sx} {sy}',len(all_reached))
        money=10*rng.randrange(31);paid=money//10
        ans=max(7*f+4*t+(paid-5*f-3*t) for f in range(paid//5+1) for t in range(paid//3+1) if 5*f+3*t<=paid)
        add('49_soy',str(money),ans)
        jumps=[rng.choice([1,2]) for i in range(rng.randrange(29))];run=ans=0
        for x in jumps:
            if x==1:run=0;ans+=1
            else:run+=1;ans+=2*run
        add('50_jump',' '.join(map(str,jumps+[0])),ans)
        n=rng.randint(3,12);points=[(rng.randint(-8,8),rng.randint(-8,8)) for i in range(n)]
        X,Y=rng.randint(-3,3),rng.randint(-3,3)
        order=sorted(range(n),key=lambda i:((points[i][0]-X)**2+(points[i][1]-Y)**2,i))[:3]
        add('51_nearest',f'{n} {X} {Y}\n'+'\n'.join(f'{x} {y}' for x,y in points),'\n'.join(str(i+1) for i in order))
        # Disjoint unit cells meet the land problem's nonoverlap guarantee.
        a,b=rng.randint(1,8),rng.randint(1,8)
        cells=rng.sample(list(itertools.product(range(-3,11),repeat=2)),rng.randint(1,30))
        ans=sum(0<=x<a and 0<=y<b for x,y in cells)
        add('52_land',f'{len(cells)} {a} {b}\n'+'\n'.join(f'{x} {y} {x+1} {y+1}' for x,y in cells),ans)
        a=sorted(rng.randint(-20,20) for i in range(rng.randint(1,12)));n=len(a)
        twice=2*a[n//2] if n%2 else a[n//2-1]+a[n//2]
        middle=str(twice//2) if twice%2==0 else f'{twice/2:.1f}'
        expected=f'{a[-1]} {middle} {a[0]}'
        if rng.randrange(2):a.reverse()
        add('53_small_middle_large',str(n)+'\n'+' '.join(map(str,a)),expected)
        n=rng.randint(1,6);a=[rng.randrange(4) for i in range(n)]
        b=[max(a[:i+1]) for i in range(n)]
        sums=[sum(x) for x in itertools.product(range(4),repeat=n) if [max(x[:i+1]) for i in range(n)]==b]
        add('54_derive',str(n)+'\n'+' '.join(map(str,b)),f'{max(sums)}\n{min(sums)}')
        bases=[rng.randint(2,6) for i in range(rng.randint(1,8))];answers=[rng.randrange(x) for x in bases]
        encoded=0;place=1
        for base,x in zip(bases,answers):encoded+=place*x;place*=base
        add('55_encoding',f'{len(bases)} {encoded}\n'+' '.join(map(str,bases)),' '.join(map(str,answers)))
        n=rng.randint(1,8);k=rng.randint(1,5);t=[rng.randint(k,15) for i in range(n)];c=[rng.randint(1,8) for i in range(n)];budget=rng.randint(1,80)
        ans=next(T for T in range(k,max(t)+1) if sum(max(0,t[i]-T)*c[i] for i in range(n))<=budget)
        add('56_farming',f'{n} {budget} {k}\n'+'\n'.join(f'{x} {y}' for x,y in zip(t,c)),ans)
        words=['The','THE','tHe','and','And','a','aA','aa','Hello','hello']
        a=[rng.choice(words) for i in range(20)];b=[rng.choice(words) for i in range(20)]
        A,B=set(x.lower() for x in a),set(x.lower() for x in b)
        add('57_similarity','20 20\n'+' '.join(a)+'\n'+' '.join(b),f'{len(A&B)}\n{len(A|B)}')
        pts=set(rng.sample(list(itertools.product(range(-3,4),repeat=2)),rng.randint(1,40)));ans=[0]*5
        for x,y in pts:
            if all((x+dx,y+dy) in pts for dx,dy in [(1,0),(-1,0),(0,1),(0,-1)]):
                ans[sum((x+dx,y+dy) in pts for dx in [-1,1] for dy in [-1,1])]+=1
        add('58_recycle',str(len(pts))+'\n'+'\n'.join(f'{x} {y}' for x,y in sorted(pts)),'\n'.join(map(str,ans)))
        n,t=rng.randint(1,5),rng.randint(1,12);k=rng.randint(1,t);people=[];pass_count=stay_count=0
        for i in range(n):
            coords=[(rng.randint(-2,3),rng.randint(-2,3)) for j in range(t)];people.append(coords)
            inside=[0<=x<=2 and 0<=y<=2 for x,y in coords];pass_count+=any(inside)
            stay_count+=any(all(inside[j:j+k]) for j in range(t-k+1))
        add('59_risk',f'{n} {k} {t} 0 0 2 2\n'+'\n'.join(' '.join(f'{x} {y}' for x,y in p) for p in people),f'{pass_count}\n{stay_count}')
        a=[rng.randrange(10) for i in range(rng.randint(1,30))]
        counts=[sum(x>=p and (i==0 or a[i-1]<p) for i,x in enumerate(a)) for p in range(1,11)]
        add('60_nonzero',str(len(a))+'\n'+' '.join(map(str,a)),max(counts))
        n,m,k=rng.randint(1,8),rng.randint(1,10),rng.randint(1,10)
        plans=sorted((rng.randint(1,30),rng.randint(1,30)) for i in range(n));queries=sorted(rng.sample(range(1,31),m))
        ans=[sum(q+k<=t<=q+k+c-1 for t,c in plans) for q in queries]
        add('61_travel',f'{n} {m} {k}\n'+'\n'.join(f'{t} {c}' for t,c in plans)+'\n'+'\n'.join(map(str,queries)),'\n'.join(map(str,ans)))
        L,S=rng.randint(3,7),rng.randint(1,3);pts=set(rng.sample(list(itertools.product(range(L+1),repeat=2)),rng.randint(1,15)))
        pattern=[[rng.randrange(2) for j in range(S+1)] for i in range(S+1)];pattern[0][0]=1
        ans=sum(all(((x+i,y+j) in pts)==bool(pattern[i][j]) for i in range(S+1) for j in range(S+1))
                for x in range(L-S+1) for y in range(L-S+1))
        add('62_treasure',f'{len(pts)} {L} {S}\n'+'\n'.join(f'{x} {y}' for x,y in sorted(pts))+'\n'+
            '\n'.join(' '.join(map(str,row)) for row in reversed(pattern)),ans)
        a=[rng.randint(1,20) for i in range(rng.randint(1,12))];x=rng.randint(1,sum(a))
        ans=min(sum(a[i] for i in range(len(a)) if mask>>i&1) for mask in range(1<<len(a))
                if sum(a[i] for i in range(len(a)) if mask>>i&1)>=x)
        add('63_shipping',f'{len(a)} {x}\n'+'\n'.join(map(str,a)),ans)
    # These upper-range cases verify capacities, long-long sums and sentinel slots.
    size=500000
    fixed.append(('41_sparse',f'1000000000 {size} {size}\n'+
                  ''.join(f'{i} 100\n' for i in range(1,size+1))*2,'5000000000'))
    fixed.append(('60_nonzero','500000\n'+' '.join(['10000','0']*250000),'250000'))
    fixed.append(('56_farming','100000 1 1\n'+'100000 100000\n'*100000,'100000'))
    return fixed,random_cases
