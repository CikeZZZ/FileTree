# 🌲 FileTree – Generate Directory Tree via Right-Click

> Instantly generate a clean, tree-structured directory listing by right-clicking on any folder background or desktop—and save it as a text file! Automatically switches between Chinese and English, optimized for performance, and requires no dependencies.

---

## ✨ Key Features

- ✅ **Right-click integration**: Generate a directory tree directly from the context menu on folder/desktop backgrounds  
- 🌐 **Auto language detection**: Menu and prompts adapt to your system language (Chinese/English)  
- 🚀 **High-performance traversal**: Memory pre-allocation, minimized system calls, files listed before folders  
- 🎯 **Accurate path handling**: Uses `%V` to correctly receive the target directory path  
- 🖼 **Custom icon support**: Right-click menu displays your embedded application icon  
- 📁 **Smart output**: Results saved as `directory_tree.txt` with files before directories

---

## 📥 How to Use

### 1. First Run: Register the Context Menu

Run `FileTree.exe` **as Administrator**, then choose **1. Register**:

```text
=== Right-Click Menu Manager ===
1. Register "Generate File Tree" to folder background menu
2. Remove from menu
Choose (1/2): 1
```



✅ After successful registration, you’ll see the menu item when right-clicking on any **folder background or desktop**:

- Chinese systems: `生成文件树`  
- English systems: `Generate File Tree`

### 2. Generate a Directory Tree

Right-click → Select the menu item. The program will automatically:

- Traverse the current directory  
- Generate a tree structure  
- Save it as `directory_tree.txt` in the current folder

Sample output (`directory_tree.txt`):

```
Directory Tree: C:\MyProject
MyProject\
├──  src\
│   ├── main.cpp
│   └── resource.rc
├──  bin\
│   └── FileTree.exe
└──  README.md
```

### 3. Uninstall (Optional)

Run `FileTree.exe` **as Administrator** again and choose **2. Remove** to delete the context menu entry.

---

## 🌍 Multi-Language Support

The program auto-detects your system UI language:

| System Language                  | Menu Name          | Console Prompts | Output Title          |
| -------------------------------- | ------------------ | --------------- | --------------------- |
| Chinese (Simplified/Traditional) | 生成文件树         | Chinese         | `目录树: ...`         |
| Others (default)                 | Generate File Tree | English         | `Directory Tree: ...` |

> The output filename is always `directory_tree.txt` (in English) to avoid path compatibility issues.

---

## ⚙️ Technical Details

- Language detection via `GetUserDefaultUILanguage()`
- Registry path: `HKEY_CLASSES_ROOT\Directory\Background\shell\...`
- Command-line argument: `"%V"` passes the correct directory path
- Sorting order: **Files before folders**, alphabetical within each group
- Memory optimization: String pre-allocation, object reuse, minimal allocations

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.

---

## 💬 From the Author

> Questions? Suggestions?  
> Let’s learn and improve together!

---

**🌟 Enjoy!**  
One right-click, and your directory structure is revealed!