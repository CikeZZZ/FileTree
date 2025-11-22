#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <chrono>
#include <sstream>
#include <algorithm>

// =============== 语言检测 ===============
enum class AppLanguage {
    Chinese,
    English
};

AppLanguage DetectLanguage() {
    LANGID lang = GetUserDefaultUILanguage();
    return (PRIMARYLANGID(lang) == LANG_CHINESE) ? AppLanguage::Chinese : AppLanguage::English;
}

// =============== 多语言文本 ===============
struct Texts {
    std::string menuName;               // 右键菜单显示名
    std::string registerPrompt;         // 注册提示
    std::string registerSuccess;
    std::string registerFailed;
    std::string removeSuccess;
    std::string outputTitle;            // 输出文件标题
    std::string outputFileName;         // 输出文件名（建议用英文，避免路径问题）
};

Texts GetTexts(AppLanguage lang) {
    if (lang == AppLanguage::Chinese) {
        return {
            "生成文件树",
            "=== 右键菜单管理 ===\n1. 注册“生成文件树”到目录背景右键菜单\n2. 从右键菜单中删除“生成文件树”\n请选择 (1/2): ",
            "\n✅ 注册成功！\n现在可以在文件夹或桌面空白处右键，选择“生成文件树”。\n⚠️ 首次注册后可能需要刷新（或重启资源管理器）才能看到菜单。\n",
            "\n❌ 注册失败！请尝试以管理员身份运行本程序。\n",
            "\n✅ 已成功从右键菜单中移除“生成文件树”。\n",
            "目录树: ",
            "directory_tree.txt"
        };
    }
    else {
        return {
            "Generate File Tree",
            "=== Right-Click Menu Manager ===\n1. Register \"Generate File Tree\" to folder background menu\n2. Remove from menu\nChoose (1/2): ",
            "\n✅ Registered successfully!\nRight-click on folder/desktop background and select \"Generate File Tree\".\n⚠️ May need to refresh Explorer to see the menu.\n",
            "\n❌ Registration failed! Please run as Administrator.\n",
            "\n✅ Successfully removed from right-click menu.\n",
            "Directory Tree: ",
            "directory_tree.txt"
        };
    }
}


void generatePrefix(std::string& prefix, int depth, bool isLast) {
    prefix.clear();
    prefix.reserve(depth * 8);
    for (int i = 0; i < depth - 1; ++i) {
        prefix += "│       ";
    }
    if (depth > 0) {
        prefix += isLast ? "└──  " : "├──  ";
    }
}

void processEntry(const std::string& name, std::stringstream& outputStream,
    const std::string& prefix, bool isDir) {
    outputStream << prefix << name;
    if (isDir) {
        outputStream << "\\";
    }
    outputStream << "\n";
}

void processDirectory(const std::string& currentPath, const std::string& fileName,
    std::stringstream& outputStream, std::string& prefix,
    int depth, bool isLast, bool isDir);

void processDirectory(const std::string& currentPath, const std::string& fileName,
    std::stringstream& outputStream, std::string& prefix,
    int depth, bool isLast, bool isDir) {
    generatePrefix(prefix, depth, isLast);
    processEntry(fileName, outputStream, prefix, isDir);

    DWORD attr = GetFileAttributesA(currentPath.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) {
        outputStream << prefix << "[Access Denied]\n";
        return;
    }
    if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) {
        return;
    }

    std::vector<std::pair<std::string, bool>> entries;
    std::string searchPath = currentPath + "\\*.*";
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            std::string name = findData.cFileName;
            if (name != "." && name != "..") {
                bool isDir = (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
                entries.emplace_back(name, isDir);
            }
        } while (FindNextFileA(hFind, &findData) != 0);
        FindClose(hFind);
    }
    else {
        outputStream << prefix << "[Cannot Open Directory]\n";
        return;
    }

    std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b) {
        if (!a.second && b.second) return true;
        if (a.second && !b.second) return false;
        return a.first < b.first;
        });

    std::string childPath;
    childPath.reserve(currentPath.size() + 256);

    for (size_t i = 0; i < entries.size(); ++i) {
        bool lastEntry = (i == entries.size() - 1);
        const auto& entry = entries[i];
        childPath.assign(currentPath);
        childPath += "\\";
        childPath += entry.first;

        if (entry.second) {
            processDirectory(childPath, entry.first, outputStream, prefix, depth + 1, lastEntry, true);
        }
        else {
            generatePrefix(prefix, depth + 1, lastEntry);
            processEntry(entry.first, outputStream, prefix, false);
        }
    }
}

int main(int argc, char** argv) {
    auto start = std::chrono::high_resolution_clock::now();
    AppLanguage lang = DetectLanguage();
    Texts txt = GetTexts(lang);

    if (argc == 1) {
        // ========== 注册/删除模式 ==========
        std::cout << txt.registerPrompt;
        int choice;
        std::cin >> choice;

        std::string menuPath = std::string(R"(Directory\Background\shell\)") + txt.menuName;
        std::string commandPath = menuPath + R"(\command)";

        if (choice == 1) {
            HKEY hKey = nullptr;
            if (RegCreateKeyA(HKEY_CLASSES_ROOT, menuPath.c_str(), &hKey) == ERROR_SUCCESS) {
                RegSetValueA(hKey, nullptr, REG_SZ, txt.menuName.c_str(), 0);

                // 图标
                char modulePath[MAX_PATH];
                GetModuleFileNameA(NULL, modulePath, MAX_PATH);
                std::string iconPath = std::string(modulePath) + ",0";
                RegSetValueExA(hKey, "Icon", 0, REG_SZ,
                    (const BYTE*)iconPath.c_str(),
                    (DWORD)iconPath.size() + 1);

                // 命令
                HKEY hCommandKey = nullptr;
                if (RegCreateKeyA(hKey, "command", &hCommandKey) == ERROR_SUCCESS) {
                    std::string command = "\"" + std::string(modulePath) + "\" \"%V\"";
                    RegSetValueA(hCommandKey, nullptr, REG_SZ, command.c_str(), 0);
                    RegCloseKey(hCommandKey);
                    std::cout << txt.registerSuccess;
                }
                else {
                    std::cerr << txt.registerFailed;
                }
                RegCloseKey(hKey);
            }
            else {
                std::cerr << txt.registerFailed;
            }
        }
        else if (choice == 2) {
            RegDeleteKeyA(HKEY_CLASSES_ROOT, commandPath.c_str());
            RegDeleteKeyA(HKEY_CLASSES_ROOT, menuPath.c_str());
            std::cout << txt.removeSuccess;
        }
        return 0;
    }

    // ========== 功能模式：生成目录树 ==========
    try {
        std::string currentPath = argv[1];
        std::cout << (lang == AppLanguage::Chinese ? "正在生成目录树: " : "Generating directory tree: ") << currentPath << "\n";

        std::stringstream outputStream;
        outputStream << txt.outputTitle << currentPath << "\n"; // 本地化标题

        std::string prefix;
        size_t lastSlash = currentPath.find_last_of("\\/");
        std::string rootName = (lastSlash != std::string::npos) ?
            currentPath.substr(lastSlash + 1) : currentPath;

        prefix.reserve(1024);
        processDirectory(currentPath, rootName, outputStream, prefix, 0, true, true);

        // 输出文件名统一用英文（避免中文路径/文件名问题）
        std::ofstream outputFile(txt.outputFileName);
        if (!outputFile.is_open()) {
            std::cerr << (lang == AppLanguage::Chinese ? "无法创建输出文件" : "Failed to create output file") << ": " << txt.outputFileName << "\n";
            return 1;
        }
        outputFile << outputStream.str();
        outputFile.close();

        std::cout << (lang == AppLanguage::Chinese ? "目录树已保存到: " : "Directory tree saved to: ")
            << currentPath << "\\" << txt.outputFileName << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << (lang == AppLanguage::Chinese ? "错误: " : "Error: ") << e.what() << "\n";
        return 1;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << (lang == AppLanguage::Chinese ? "运行耗时 " : "Execution time: ")
        << duration_ns.count() << (lang == AppLanguage::Chinese ? " 纳秒" : " nanoseconds") << "\n";

    return 0;
}