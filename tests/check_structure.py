"""Verify chapter placement, standalone source, and example deduplication."""
import ast
from collections import Counter
from pathlib import Path
import re

ROOT=Path(__file__).resolve().parents[1]
tree=ast.parse((ROOT/'scripts/build.py').read_text(encoding='utf-8'))
values={}
for node in tree.body:
    if isinstance(node,ast.Assign):
        for target in node.targets:
            if isinstance(target,ast.Name) and target.id in {'order','knowledge'}:
                values[target.id]=ast.literal_eval(node.value)
order=values['order']
texts={name:(ROOT/'chapters'/name).read_text(encoding='utf-8-sig') for name in order}
codes=Counter(re.findall(r'\\Code\{([^}]+)\}','\n'.join(texts.values())))
expected={path.name for path in (ROOT/'code').glob('*.cpp')}
assert set(codes)==expected
assert all(count==1 for count in codes.values()),codes
for name in values['knowledge']:
    assert not re.search(r'\\(?:Code|example|practice|ojpractice|exercise|training)\b',texts[name]),name
    assert not re.search(r'\\begin\{verbatim\}',texts[name]),name
for name in ['first-practice.tex','second-practice.tex','12-practice.tex']:
    assert not re.search(r'\\(?:Code|example)\b|\\begin\{(?:lstlisting|verbatim)\}',texts[name]),name
assembled=(ROOT/'main.tex').read_text(encoding='utf-8')
assert not re.search(r'\\(?:input|include|lstinputlisting)\b',assembled)
assert assembled.count('\\textbf{完整参考实现}')==len(expected)
assert not any(word in assembled for word in ['真题速看','考点总结','已逐项核对','先做原题单'])
section_counts=[]
count=0
for name in order:
    text=texts[name]
    if '\\part{' in text:
        if count:
            section_counts.append(count)
        count=0
    count+=len(re.findall(r'\\section\{',text))
section_counts.append(count)
assert section_counts==[3,4,3],section_counts
archive=ROOT/'archive/lecture-before-knowledge-rewrite/chapters'
for name in ['13-extensions.tex','team-practice.tex']:
    assert (archive/name).is_file()
print(f'Passed: sections {section_counts}; {len(codes)} examples each included once; knowledge/practice placement; standalone LaTeX; original drafts preserved.')
