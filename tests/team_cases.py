"""Independent exhaustive oracles for the five complete team-list examples."""
import itertools
import random


def make_team_cases():
    fixed = [
        ('64_k_intervals', '5 3\n1 2 3 4 5\n', '7'),
        ('65_gallery', '7 3\n1 2 1 3 2 1 3\n', '2 4'),
        ('66_diamonds', '7 2\n1 2 3 8 9 10 20\n', '6'),
        ('67_black_rectangle', '2 3 3\n101\n011\n', '4'),
        ('68_unsigned_prefix', '2\n1 2 2\n18446744073709551615 1\n1 1 1 2\n1 1 1 1\n1 1 1\n0\n1 1 1 1\n',
         '18446744073709551615\n0'),
    ]
    cases = []
    rng = random.Random(20261012)
    for _ in range(50):
        n, k = rng.randint(1, 12), rng.randint(1, 8)
        a = [rng.randint(1, 15) for _ in range(n)]
        answer = sum(sum(a[l:r]) % k == 0 for l in range(n) for r in range(l+1, n+1))
        cases.append(('64_k_intervals', f'{n} {k}\n'+' '.join(map(str,a)), str(answer)))

        m = rng.randint(1, 5)
        a = list(range(1, m+1))+[rng.randint(1, m) for _ in range(rng.randint(0, 8))]
        rng.shuffle(a)
        n = len(a)
        intervals = [(r-l, l+1, r) for l in range(n) for r in range(l+1, n+1)
                     if len(set(a[l:r])) == m]
        _, left, right = min(intervals)
        cases.append(('65_gallery', f'{n} {m}\n'+' '.join(map(str,a)), f'{left} {right}'))

        n, k = rng.randint(1, 8), rng.randint(0, 6)
        a = [rng.randint(1, 15) for _ in range(n)]
        answer = 0
        # Enumerate all assignments: unused, first cabinet, second cabinet.
        for assignment in itertools.product(range(3), repeat=n):
            groups = [[a[i] for i in range(n) if assignment[i] == group] for group in (1,2)]
            if all(not g or max(g)-min(g) <= k for g in groups):
                answer = max(answer, sum(map(len,groups)))
        cases.append(('66_diamonds', f'{n} {k}\n'+' '.join(map(str,a)), str(answer)))

        n, m = rng.randint(1, 5), rng.randint(1, 5)
        k = rng.randint(1, n*m)
        grid = [[rng.randrange(2) for _ in range(m)] for _ in range(n)]
        areas = [(b-t)*(r-l) for t in range(n) for b in range(t+1,n+1)
                 for l in range(m) for r in range(l+1,m+1)
                 if sum(grid[i][j] for i in range(t,b) for j in range(l,r)) >= k]
        data = f'{n} {m} {k}\n'+'\n'.join(''.join(map(str,row)) for row in grid)
        cases.append(('67_black_rectangle', data, str(min(areas, default=0))))

        data, answers = ['3'], []
        mask = (1 << 64)-1
        for _ in range(3):
            n, m, q = rng.randint(1,4), rng.randint(1,4), rng.randint(1,12)
            grid = [[rng.choice([0, 1, mask, rng.getrandbits(64)]) for _ in range(m)] for _ in range(n)]
            data.append(f'{n} {m} {q}')
            data.extend(' '.join(map(str,row)) for row in grid)
            answer = 0
            for _ in range(q):
                t, b = sorted([rng.randrange(n), rng.randrange(n)])
                l, r = sorted([rng.randrange(m), rng.randrange(m)])
                data.append(f'{t+1} {l+1} {b+1} {r+1}')
                answer ^= sum(grid[i][j] for i in range(t,b+1) for j in range(l,r+1)) & mask
            answers.append(str(answer))
        cases.append(('68_unsigned_prefix', '\n'.join(data), '\n'.join(answers)))
    return fixed, cases
