# CCF-CSP 前三题备考讲义

一份可独立阅读的中文 LaTeX 讲义。知识章节讲概念、处理规则、关键代码和复杂度；完整题目与解答集中在例题区，练习区仅列题型和做题链接。

## 阅读与下载

- [最新讲义 PDF（120 页）](dist/main.pdf)
- [可独立编译的 LaTeX 主文件](main.tex)
- [分章编辑源文件](chapters/)
- [72 份完整 C++17 参考程序](code/)
- [原始备考材料](sources/)

## 三篇结构

| 篇章 | 章节 |
| --- | --- |
| 第一题：基础实现 | 1 程序基本功与做题技巧；2 例题速看；3 练习题 |
| 第二题：工具与算法 | 1 基础算法；2 STL；3 例题速看；4 练习题 |
| 第三题：字符串解析与综合模拟 | 1 大模拟拆题方法与字符串工具；2 七大底层构件；3 历年真题全流程精讲；4 T3真题刷题阶梯 |

第一篇包括格式化输入输出、整型与浮点运算、函数、数组、结构体，以及数组容量、数值范围、时间与空间复杂度估算。

第二篇包括前缀和、差分、二分、双指针、贪心、基础数学、搜索、动态规划和背包；保留二维前缀和与差分、实数二分、剪枝、LIS 优化、LCS、滚动数组、多重与分组背包、背包计数。

STL 单列一章，分别讲区间与迭代器、sort、unique、lower_bound、upper_bound、vector、string、pair、stack、queue、priority_queue、set、multiset、map、unordered_map、unordered_set，每项说明用途、常用操作、代码与复杂度。

第三篇先讲对象、规则、输出的四步拆题法，补齐 std::string 切分、sscanf、名称编号映射与 strtok 的使用条件。七个教学构件覆盖分词、路径栈、授权状态、递归解析、祖先链、依赖图和事件调度。

四道完整真题为**元素选择器、化学方程式、角色授权、解压缩**。每题按规则摘要、边界、数据结构、子任务推进和完整代码展开，配可手算的推演。练习表按四档组织13道 T3 真题。差值数对和矩形增量已移入第二篇。

原资料的 **23 道真题**均保留完整解答和程序，另有六道历年真题与四道 T3 真题补充，共33份真题程序、39份教学与专项程序。认证真题标注认证次数、年月、题号和做题入口；72个完整程序各在正文出现一次。

## 格式与做题入口

- 代码以普通数组、结构体、独立函数、scanf/printf 为主，STL 使用明确类型，按 C++17 编译。
- 代码保留语法高亮与行号。PDF 行号用空 ActualText 排除在复制文本之外，代码正文可复制，需要阅读器支持。
- 输入输出样例分别装框，保留空格与换行；代码框不跨页拆开。
- 主要平台为[曙梦 OJ](https://oj.shumeng.tech/p)。没有已核对曙梦入口的旧题保留原资料的 AcWing 链接。
- 练习从[洛谷团队题单](https://www.luogu.com.cn/team/113242/training)及原资料中选取。团队的 64 道原讲解保存在归档；当前例题区保留其中五道完整专项例题。对应位置记录在[团队题单索引](data/team-practice.json)。

## 编译与验证

main.tex 内嵌全部正文和代码，只下载该文件即可使用 XeLaTeX 编译。需要 ctex、fontspec、amsmath、listings、tcolorbox、accsupp、hyperref 等常用宏包；字体优先 Fandol，Windows 可回退到宋体、黑体。

    xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
    xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex

编辑分章文件后重新合成：

    python scripts/build.py
    python tests/check_structure.py
    python tests/check_knowledge.py
    python tests/check_examples.py

本版 **52 个知识片段通过 4864 项检查**，**72 个完整程序通过 2048 项检查**。片段验证直接提取正文代码，并使用枚举、直接求和、Floyd 最短路等独立方法对照；详见[测试说明](tests/README.md)。

## 原稿与来源

- [重写前的完整分章原稿](archive/lecture-before-knowledge-rewrite/)保留原知识、练习解答及计数撤销、可删堆、三分等提高内容，不参与当前编译。
- 原始 5 份 PPTX、2 份 PDF 原样保留，[文件清单与 SHA-256](data/sources.json)可核对材料。
- [原题入口索引](data/exercise-links.json)、[真题样例与程序索引](data/csp-practice.json)、[补充题索引](data/online-practice.json)保留来源记录。
- [编写方案](planning.tex)与[方案 PDF](dist/planning.pdf)记录当前三篇目录及程序统计，并保留原资料迁移和授课参考。

原资料及所引平台题目的权利归原作者或平台所有。
