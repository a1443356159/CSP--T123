# CCF-CSP 前三题备考讲义

一份可独立阅读的中文学习讲义，包含知识讲解、完整教学例题、输入输出、样例推演、解答、复杂度分析、关键代码和章末练习答案。链接仅用于补充训练，学习正文不需要打开外部题面。

## 阅读与下载

- **[正式讲义 PDF](dist/main.pdf)**
- **[可单独编译的 LaTeX 主文件](main.tex)**
- [分章编辑源文件](chapters/)
- [26 份完整 C++17 参考程序](code/)
- [原始资料](sources/)

正文教学题围绕原资料知识点重新组织，包含完整规则。它们不是对应平台原题的逐字转载，规则和数据范围可能不同；进一步练习平台原题时，应重新核对题面。

## 内容

1. 备考方法与程序基本功
2. 基础枚举与小模拟
3. 排序与常用 STL 工具
4. 字符串处理与解析基础
5. 前缀和与差分
6. 二分与双指针
7. 贪心与基础数学
8. 搜索与剪枝
9. 动态规划入门
10. 基础背包与计数
11. 第三题综合模拟：路径规范化、授权管理、表达式解析、树形查询、模板展开
12. 综合训练与复盘：差值数对、二维差分、非抢占任务调度

附录补充多重背包、混合背包、多维费用、方案恢复、计数撤销、LIS 优化、实数搜索、可删堆与 KMP。

## 编译讲义

主文件已内嵌全部正文和代码，**只下载 `main.tex` 也可以编译**。使用 XeLaTeX，安装 `ctex`、`fontspec`、`geometry`、`amsmath`、`booktabs`、`longtable`、`enumitem`、`listings`、`fancyvrb`、`needspace`、`hyperref` 等常用宏包。字体优先 Fandol；Windows 缺少 Fandol 时回退到宋体、黑体。

```sh
mkdir -p dist
xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
```

PowerShell 创建输出目录：

```powershell
New-Item -ItemType Directory -Force dist | Out-Null
```

## 编辑与代码验证

编辑 `chapters/*.tex` 和 `code/*.cpp` 后，先重新合成主文件，再编译。合成过程不依赖第三方 Python 包。

```sh
python scripts/build.py
python tests/check_examples.py
```

检查脚本需要 Python 3.9+ 和可执行 C++17 的 GNU g++。它编译全部 26 个参考程序，运行 53 组样例与边界检查，并对多个算法执行 350 组固定随机种子的小规模对照测试，共 403 项。测试细节见 [验证说明](tests/README.md)。

`main.tex` 是合成结果，应修改分章或程序源文件后重新生成，以免下次合成覆盖手工修改。正文中较短的讲解片段保留在分章文件里。

## 原始资料与整理记录

保留 5 份 PPTX（160 页）和 2 份 PDF（7 页），原文件未改写。

- [文件清单与校验值](data/sources.json)
- [原资料中的 23 个真题入口及 5 个专题题单](data/exercise-links.json)
- [教师用整理方案 LaTeX](planning.tex)
- [教师用整理方案 PDF](dist/planning.pdf)

整理方案是前期编写蓝图，含资料迁移表和勘误。其 160–200 页建议是扩展版预算；当前独立讲义采用较紧凑的讲解与代码布局，实际页数以正式 PDF 为准。

原资料里的年份与题号对应、外部题单内容没有全部重新核对，索引对此保留标记。正文已经改写容易误导的概念，包括 `unique`、DP 无后效性、背包状态语义与“消失之物”的计数目标。

原始资料及所引平台题目的权利归原作者或平台所有，本仓库未另行授予这些材料新的许可。
