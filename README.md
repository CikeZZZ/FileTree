当然可以！以下是为你这个 **“生成文件树”右键菜单工具** 量身定制的 `README.md`，包含功能介绍、使用方法、编译指南、多语言支持说明等，风格专业清晰，适合开源或个人项目使用。

---

# 🌲 FileTree - 右键生成目录结构树工具

> 一键在文件夹空白处右键生成美观的目录树，并保存为文本文件！支持中文/英文自动切换，高性能递归遍历，轻量无依赖。

![示例效果图](https://via.placeholder.com/600x300?text=Directory+Tree+Example+-+📁+src+├──+main.cpp+└──+resource.rc)  
*(实际使用时可替换为真实截图)*

---

## ✨ 功能亮点

- ✅ **右键集成**：在文件夹或桌面空白处右键，直接生成目录树
- 🌐 **自动中英文切换**：根据系统语言显示对应提示和菜单名
- 🚀 **高性能遍历**：预分配内存、减少系统调用、文件优先排序
- 🎯 **精准路径传递**：使用 `%V` 正确获取右键所在目录
- 🖼 **带图标菜单**：右键项显示自定义图标（需嵌入资源）
- 📁 **智能输出**：结果保存为 `directory_tree.txt`，文件在前、目录在后

---

## 📥 使用方法

### 1. 首次运行：注册右键菜单

以**管理员身份运行** `FileTree.exe`，选择 **1. 注册**：

```text
=== 右键菜单管理 ===
1. 注册“生成文件树”到目录背景右键菜单
2. 从右键菜单中删除“生成文件树”
请选择 (1/2): 1
```

✅ 注册成功后，在任意**文件夹空白处或桌面**右键，即可看到：

- 中文系统：`生成文件树`
- 英文系统：`Generate File Tree`

### 2. 生成目录树

右键点击 → 选择菜单项，程序将自动：
- 遍历当前目录
- 生成树形结构
- 保存为 `当前目录\directory_tree.txt`

示例输出 (`directory_tree.txt`)：
```
目录树: C:\MyProject
MyProject\
├──  src\
│   ├── main.cpp
│   └── resource.rc
├──  bin\
│   └── FileTree.exe
└──  README.md
```

### 3. 卸载（可选）

再次运行程序，选择 **2. 删除**，即可移除右键菜单项。

---

## 🛠 编译指南

### 环境要求
- Windows 7 或更高
- MinGW / MSVC / Visual Studio
- （可选）图标文件 `app_icon.ico`

### 步骤

#### 1. 准备图标（可选但推荐）
- 将你的 `app_icon.ico` 放入项目目录
- 或使用 [在线工具](https://icoconvert.com) 生成

#### 2. 创建资源文件 `resource.rc`
```rc
// resource.rc
#include "winres.h"
1 ICON "app_icon.ico"
```

#### 3. 编译（MinGW 示例）
```bash
# 编译资源
windres resource.rc -O coff -o resource.res

# 编译主程序
g++ FileTree.cpp resource.res -o FileTree.exe -ladvapi32

# （可选）隐藏控制台窗口（用于最终分发）
g++ FileTree.cpp resource.res -o FileTree.exe -ladvapi32 -mwindows
```

> 💡 **提示**：注册时建议保留控制台（不加 `-mwindows`），方便查看提示。

---

## 🌍 多语言支持

程序自动检测系统 UI 语言：

| 系统语言 | 菜单名 | 控制台提示 | 输出标题 |
|--------|--------|----------|--------|
| 中文（简体/繁体） | 生成文件树 | 中文提示 | `目录树: ...` |
| 其他（默认英文） | Generate File Tree | English | `Directory Tree: ...` |

> 输出文件名始终为英文 `directory_tree.txt`，避免路径兼容性问题。

---

## ⚙️ 技术细节

- 使用 `GetUserDefaultUILanguage()` 判断语言
- 注册表路径：`HKEY_CLASSES_ROOT\Directory\Background\shell\...`
- 命令行参数：`"%V"` 传递右键目录路径
- 文件排序：**文件在前，目录在后**，同类型按名称升序
- 内存优化：字符串预分配、复用对象、减少分配次数

---

## 📄 许可证

本项目为个人工具，**免费使用**。代码可自由修改、分发。

> 📌 **注意**：图标文件需自行提供，避免版权问题。

---

## 💬 作者说

> “Windows 的 PNG 壁纸透明 bug 我修不了，但一个干净的目录树工具，我可以做好。”  
> —— 献给所有追求效率与整洁的开发者

---

**🌟 Enjoy!**  
右键一下，目录结构尽在掌握！
