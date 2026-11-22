"""T3 boundaries and independent oracles: trees, chemistry, RBAC, compression."""
from collections import Counter
from itertools import combinations
import random


def make_third_cases():
    fixed, random_cases = [], []
    def add(name, data, expected, boundary=False):
        (fixed if boundary else random_cases).append((name, data, str(expected)))
    long_name = 'a' * 20
    add('23_templates', f'2\n{long_name} 1 ok\nroot 2 @{long_name} @{long_name}\nroot\n', 'ok ok', True)
    add('19_path', '/' + 'a' * 10000 + '\n2\n.\n../z\n', '/' + 'a' * 10000 + '\n/z', True)
    add('22_selector', '10 1\n' + ''.join(f'{i} div -\n' for i in range(10)) + ' '.join(['div'] * 10), '1 10', True)
    add('69_selector_real', '6 4\nHTML\n..DIV #Main\n....p #A\n....DIV\n......P #a\n..p\nDIV p\n#Main #a\ndiv div p\n#A\n', '2 3 5\n1 5\n1 5\n1 3', True)
    add('69_selector_real', '1 3\nDiV #X\ndiv div\n#x\n#X\n', '0\n0\n1 1', True)
    add('70_chem', '4\nH2+O2=H2O\n2Al(OH)3+3H2SO4=Al2(SO4)3+6H2O\nK4(ON(SO3)2)2=K4O14N2S4\nCo=CO\n', 'N\nY\nY\nN', True)
    add('70_chem', '2\n' + '(' * 490 + 'H' + ')' * 490 + '=H\n1000000000H=H1000000000\n', 'Y\nY', True)
    add('71_rbac', '2 2 4\nreader 1 read 1 file 0\nadmin 1 * 1 * 0\nreader 1 g staff\nadmin 1 u bob\nalice 1 staff read file report\nalice 0 read file report\nbob 0 delete door front\nalice 1 staff write file report\n', '1\n0\n1\n0', True)
    # Different roles each satisfy a different part; names and user/group keys differ.
    add('71_rbac', '2 3 5\na 1 read 1 file 1 x\nb 1 write 1 door 1 y\na 1 u same\nb 1 g same\na 1 g both\nsame 1 same read door y\nsame 0 read file x\nother 1 same read file x\nother 1 both read file x\nsame 0 read file y\n', '0\n1\n0\n1\n0', True)
    add('71_rbac', '500 1 1\n' + ''.join(f'r{i} 1 * 1 * 0\n' for i in range(500)) + 'r499 1 u alice\nalice 0 read file x\n', '1', True)
    add('72_decompress', '5\n0900611101\n', '6161616161616161\n61', True)
    rng = random.Random(20261121)

    # Tree oracle: enumerate every ordered subsequence of each root-to-node path.
    for _ in range(45):
        n = rng.randint(1, 14)
        parents = [-1] + [rng.randrange(i) for i in range(1, n)]
        children = [[] for _ in range(n)]
        tags = [rng.choice(['div', 'p', 'a']) for _ in range(n)]
        for i in range(1, n): children[parents[i]].append(i)
        preorder, depths = [], {}
        def walk(u, depth):
            preorder.append(u); depths[u] = depth
            for v in children[u]: walk(v, depth + 1)
        walk(0, 0)
        lines = ['..' * depths[u] + tags[u].upper() + f' #Id{u}' for u in preorder]
        queries, expected = [], []
        for _q in range(12):
            tokens = [rng.choice(['div', 'p', 'a', '#missing', '#Id' + str(rng.randrange(n))])
                      for _k in range(rng.randint(1, 4))]
            queries.append(' '.join(t.upper() if t[0] != '#' else t for t in tokens))
            result = []
            for row, u in enumerate(preorder, 1):
                path, v = [], u
                while v != -1: path.append(v); v = parents[v]
                path.reverse()
                def match(v, t): return t == f'#Id{v}' if t[0] == '#' else t == tags[v]
                if match(u, tokens[-1]) and any(
                    all(match(v, t) for v, t in zip(chosen, tokens[:-1]))
                    for chosen in combinations(path[:-1], len(tokens) - 1)):
                    result.append(row)
            expected.append(' '.join(map(str, [len(result)] + result)))
        add('69_selector_real', f'{n} 12\n' + '\n'.join(lines + queries), '\n'.join(expected))

    # Chemistry oracle: construct a formula AST and counts together, then flatten it.
    def molecule(depth=0):
        text, count = '', Counter()
        for _ in range(rng.randint(1, 3)):
            if depth < 3 and rng.randrange(3) == 0:
                inner, values = molecule(depth + 1); term = '(' + inner + ')'
            else:
                term = rng.choice(['H', 'O', 'Na', 'Co', 'C', 'N'])
                values = Counter({term: 1})
            factor = rng.randint(1, 12)
            text += term + (str(factor) if factor != 1 else '')
            count.update({key: value * factor for key, value in values.items()})
        return text, count
    for _ in range(65):
        terms, count = [], Counter()
        for _t in range(rng.randint(1, 4)):
            term, values = molecule(); factor = rng.randint(1, 11)
            terms.append(str(factor) + term)
            count.update({key: value * factor for key, value in values.items()})
        if rng.randrange(2): count['H'] += 1; expected = 'N'
        else: expected = 'Y'
        right = ''.join(key + str(value) for key, value in sorted(count.items()))
        equation = '+'.join(terms) + '=' + right
        assert len(equation) <= 1000
        add('70_chem', '1\n' + equation, expected)

    # RBAC oracle: scan association rows and each role's three independent lists.
    for _ in range(55):
        n = rng.randint(1, 8); roles, lines = [], []
        for i in range(n):
            op = rng.sample(['read', 'write', '*'], rng.randint(1, 3))
            kind = rng.sample(['file', 'door', '*'], rng.randint(1, 3))
            name = rng.sample(['x', 'y', 'z', '*'], rng.randint(0, 4))
            roles.append((op, kind, name))
            lines.append(f'r{i} {len(op)} ' + ' '.join(op) + f' {len(kind)} ' + ' '.join(kind) + f' {len(name)} ' + ' '.join(name))
        associations = []
        for _m in range(12):
            role = rng.randrange(n)
            objects = [(rng.choice(['u', 'g']), rng.choice(['a', 'b', 'c'])) for _ in range(rng.randint(1, 5))]
            associations.append((role, objects))
            lines.append(f'r{role} {len(objects)} ' + ' '.join(t + ' ' + v for t, v in objects))
        answers = []
        for _q in range(20):
            user = rng.choice(['a', 'b', 'c', 'unknown'])
            groups = rng.sample(['a', 'b', 'c'], rng.randint(1, 3))
            op, kind, name = rng.choice(['read', 'write', 'other']), rng.choice(['file', 'door', 'other']), rng.choice(['x', 'y', 'z', '*'])
            related = {r for r, objects in associations if any((t == 'u' and v == user) or (t == 'g' and v in groups) for t, v in objects)}
            allowed = any((op in roles[r][0] or '*' in roles[r][0]) and
                          (kind in roles[r][1] or '*' in roles[r][1]) and
                          (not roles[r][2] or name in roles[r][2]) for r in related)
            lines.append(f'{user} {len(groups)} ' + ' '.join(groups) + f' {op} {kind} {name}')
            answers.append(str(int(allowed)))
        add('71_rbac', f'{n} 12 20\n' + '\n'.join(lines), '\n'.join(answers))

    # Construct valid compressed streams with known literal/copy operations.
    def stream(ops):
        payload, plain = bytearray(), bytearray()
        for op in ops:
            if op[0] == 'literal':
                _, raw, width = op
                value = len(raw) - 1
                if width == 0: payload.append(value << 2)
                else: payload.append((59 + width) << 2); payload += value.to_bytes(width, 'little')
                payload += raw; plain += raw
            else:
                _, offset, length, kind = op
                if kind == 1:
                    payload += bytes([((offset >> 8) << 5) | ((length - 4) << 2) | 1, offset & 255])
                else: payload += bytes([((length - 1) << 2) | 2]) + offset.to_bytes(2, 'little')
                # Repeat the initial window, independently of the incremental C++ copy.
                window = bytes(plain[-offset:])
                plain += (window * ((length + offset - 1) // offset))[:length]
        n = len(plain); header = bytearray()
        while n >= 128: header.append((n & 127) | 128); n >>= 7
        header.append(n); encoded = (header + payload).hex()
        inp = str(len(header + payload)) + '\n' + '\n'.join(encoded[i:i+16] for i in range(0, len(encoded), 16)) + '\n'
        out = '\n'.join(plain[i:i+8].hex() for i in range(0, len(plain), 8))
        return inp, out
    for width in range(5):
        size = 60 if width == 0 else 61
        inp, out = stream([('literal', bytes(range(size)), width)])
        add('72_decompress', inp, out, True)
    for offset, kind in [(1, 1), (256, 1), (2047, 1), (65535, 2)]:
        raw = bytes((i % 256 for i in range(offset)))
        ops = [('literal', raw, max(1, ((offset - 1).bit_length() + 7) // 8)),
               ('copy', offset, 11 if kind == 1 else 64, kind)]
        inp, out = stream(ops); add('72_decompress', inp, out, True)
    # Four-byte guide, maximum output size, zeros and line wrap.
    ops = [('literal', bytes(61), 1)]
    remaining = 2 * 2**20 - 61
    while remaining:
        length = min(64, remaining)
        ops.append(('copy', 1, length, 2)); remaining -= length
    inp, out = stream(ops); add('72_decompress', inp, out, True)
    for _ in range(65):
        size = rng.randint(1, 70)
        ops = [('literal', bytes(rng.randrange(256) for _ in range(size)), 0 if size <= 60 else 1)]
        total = size
        for _op in range(15):
            if rng.randrange(3) == 0:
                raw = bytes(rng.randrange(256) for _ in range(rng.randint(1, 90)))
                ops.append(('literal', raw, 0 if len(raw) <= 60 else rng.randint(1, 4)))
                total += len(raw)
            else:
                kind = rng.randint(1, 2); offset = rng.randint(1, min(total, 2047 if kind == 1 else 65535))
                length = rng.randint(4, 11) if kind == 1 else rng.randint(1, 64)
                ops.append(('copy', offset, length, kind)); total += length
        inp, out = stream(ops); add('72_decompress', inp, out)
    return fixed, random_cases
