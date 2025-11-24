# 🌲 FileTree - 右键生成目录结构树工具  
# 🌲 FileTree – Generate Directory Tree via Right-Click

> 一键在文件夹空白处右键生成美观的目录树，并保存为文本文件！  
> Instantly generate a clean, tree-structured directory listing by right-clicking on any folder background or desktop—and save it as a text file!

> 支持中文/英文自动切换，高性能递归遍历，轻量无依赖。  
> Automatically switches between Chinese and English, optimized for high-performance recursive traversal, and requires no dependencies.

> 它可以帮助你方便地查看你的项目结构，同时你可以将生成的内容发给 AI 来介绍你的项目。  
> It helps you easily visualize your project structure—and you can send the generated output to an AI to describe your project.

---

## ✨ 功能亮点  
## ✨ Key Features

- ✅ **右键集成**：在文件夹或桌面空白处右键，直接生成目录树  
  - ✅ **Right-click integration**: Generate a directory tree directly from the context menu on folder or desktop backgrounds

- 🌐 **自动中英文切换**：根据系统语言显示对应提示和菜单名  
  - 🌐 **Auto language detection**: Menu and prompts adapt to your system language (Chinese/English)

- 🚀 **高性能遍历**：预分配内存、减少系统调用、文件优先排序  
  - 🚀 **High-performance traversal**: Memory pre-allocation, minimized system calls, files listed before folders

- 🎯 **精准路径传递**：使用 `%V` 正确获取右键所在目录  
  - 🎯 **Accurate path handling**: Uses `%V` to correctly receive the target directory path

- 🖼 **带图标菜单**：右键项显示自定义图标（已嵌入程序）  
  - 🖼 **Custom icon support**: Right-click menu displays your embedded application icon

- 📁 **智能输出**：结果保存为 `directory_tree.txt`，文件在前、目录在后  
  - 📁 **Smart output**: Results saved as `directory_tree.txt` with files before directories

---

## 📥 使用方法  
## 📥 How to Use

### 1. 首次运行：注册右键菜单  
### 1. First Run: Register the Context Menu

以**管理员身份运行** `FileTree.exe`，选择 **1. 注册**：  
Run `FileTree.exe` **as Administrator**, then choose **1. Register**:

```text
=== 右键菜单管理 ===  
=== Right-Click Menu Manager ===
1. 注册“生成文件树”到目录背景右键菜单  
1. Register "Generate File Tree" to folder background menu
2. 从右键菜单中删除“生成文件树”  
2. Remove from menu
请选择 (1/2): 1  
Choose (1/2): 1
```

✅ 注册成功后，在任意**文件夹空白处或桌面**右键，即可看到：  
✅ After successful registration, you’ll see the menu item when right-clicking on any **folder background or desktop**:

- 中文系统：`生成文件树`  
  - Chinese systems: `生成文件树`

- 英文系统：`Generate File Tree`  
  - English systems: `Generate File Tree`

### 2. 生成目录树  
### 2. Generate a Directory Tree

右键点击 → 选择菜单项，程序将自动：  
Right-click → Select the menu item. The program will automatically:

- 遍历当前目录  
  - Traverse the current directory

- 生成树形结构  
  - Generate a tree structure

- 保存为 `当前目录\directory_tree.txt`  
  - Save it as `directory_tree.txt` in the current folder

示例输出 (`directory_tree.txt`)：  
Sample output (`directory_tree.txt`):

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
### 3. Uninstall (Optional)

以**管理员身份运行** `FileTree.exe`，选择 **2. 删除**，即可移除右键菜单项。  
Run `FileTree.exe` **as Administrator** again and choose **2. Remove** to delete the context menu entry.

---

## 🌍 多语言支持  
## 🌍 Multi-Language Support

程序自动检测系统 UI 语言：  
The program auto-detects your system UI language:

| 系统语言 | System Language | 菜单名 | Menu Name | 控制台提示 | Console Prompts | 输出标题 | Output Title |
|--------|----------------|------|----------|----------|----------------|--------|---------------|
| 中文（简体） | Chinese (Simplified/Traditional) | 生成文件树 | 生成文件树 | 中文提示 | Chinese | `目录树: ...` | `目录树: ...` |
| 其他（默认英文） | Others (default) | Generate File Tree | Generate File Tree | English | English | `Directory Tree: ...` | `Directory Tree: ...` |

> 输出文件名始终为英文 `directory_tree.txt`，避免路径兼容性问题。  
> The output filename is always `directory_tree.txt` (in English) to avoid path compatibility issues.

---

## ⚙️ 技术细节  
## ⚙️ Technical Details

- 使用 `GetUserDefaultUILanguage()` 判断语言  
  - Language detection via `GetUserDefaultUILanguage()`

- 注册表路径：`HKEY_CLASSES_ROOT\Directory\Background\shell\...`  
  - Registry path: `HKEY_CLASSES_ROOT\Directory\Background\shell\...`

- 命令行参数：`"%V"` 传递右键目录路径  
  - Command-line argument: `"%V"` passes the correct directory path

- 文件排序：**文件在前，目录在后**，同类型按名称升序  
  - Sorting order: **Files before folders**, alphabetical within each group

- 内存优化：字符串预分配、复用对象、减少分配次数  
  - Memory optimization: String pre-allocation, object reuse, minimal allocations

---

## 📄 许可证  
## 📄 License

本项目采用 **MIT 许可证** —— 详情见 LICENSE 文件。  
This project is licensed under the **MIT License** — see the LICENSE file for details.

---

## 💬 作者说  
## 💬 From the Author

> 欢迎提出各种问题!  
> Questions? Suggestions?

> 一起进步！  
> Let’s learn and improve together!

---

**🌟 Enjoy!**  
**🌟 Enjoy!**

右键一下，目录结构尽在掌握！  
One right-click, and your directory structure is revealed!

---
