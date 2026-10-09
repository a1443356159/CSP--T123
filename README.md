# CCF-CSP 前三题备考讲义

以 CCF-CSP 认证前三题为目标，汇总原始课件和练习材料，按“基础实现、常用算法、综合模拟”编写一份系统讲义。

## 当前内容

本次完成的是**资料汇总与总讲义编写方案**，包括 12 章详细提纲、原资料页码对应、重点勘误、练习入口、教学安排和编写标准。完整学生讲义与全部题解将按方案逐章扩写。

- [LaTeX 主文件](main.tex)
- [编译后的阅读版](dist/main.pdf)
- [原始资料](sources/)
- [资料清单](data/sources.json)
- [练习链接索引](data/exercise-links.json)

现有资料为 5 份 PPTX（160 页）和 2 份 PDF（7 页）。其中两份动态规划课件共 71 页。整理时将基础背包放入正文，高级变式放入选读，并重点补充字符串解析与第三题完整案例。

## 规划目录

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
11. 第三题综合模拟专题
12. 真题训练与限时复盘

主线讲义建议约 160–200 页。该数字是规划预算，不是当前方案的页数。

## 编译

使用安装了 `ctex`、`fontspec`、`geometry`、`amsmath`、`booktabs`、`longtable`、`enumitem`、`listings`、`hyperref` 等宏包的 TeX Live 或 MiKTeX，通过 **XeLaTeX** 编译两次，以生成目录和内部链接。

```sh
mkdir -p dist
xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
```

Windows PowerShell 可运行：

```powershell
New-Item -ItemType Directory -Force dist | Out-Null
xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
xelatex -interaction=nonstopmode -halt-on-error -output-directory=dist main.tex
```

字体优先使用 TeX 发行版中的 Fandol；未找到时使用 Windows 的宋体和黑体。非 Windows 环境请安装 Fandol 字体包。

## 资料使用说明

原始文件保留原样。勘误写入编写方案，后续落实到正文；不覆盖源课件。历年考点中的顺序编号尚未全部对应到认证编号，练习链接也尚未按真题去重。链接索引明确记录这些待核对项，不据网址猜测题名。

建议先完成第 1–4 章，再完成第 5–10 章；第三题案例选题同步推进，最后补全限时训练和附录。教师用的编写方案与未来学生版讲义分开保留。

原始资料及所引题目的权利归原作者或平台所有；本仓库未另行授予这些材料新的许可。
