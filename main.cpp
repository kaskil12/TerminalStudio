#include "main.h"



int main() {
    char currentPath[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentPath);
    std::string path(currentPath);
    std::cout << path << ": ";
    std::string input;
    std::getline(std::cin, input);
    executeCommand(input);
    return 0;
}

void executeCommand(const std::string& command) {
    std::stringstream ss(command);
    std::string cmd;
    std::vector<std::string> args;
    while (ss >> cmd) {
        args.push_back(cmd);
    }
    History.insert(History.end(), args.begin(), args.end());

    if (args.empty()) {
        std::cout << "No command entered\n";
        main();
        return;
    }

    const std::string& cmdName = args[0];

    if (cmdName == "help") {
        help();
    }
    else if (cmdName == "fcreate") {
        fcreate();
    }
    else if (cmdName == "fdelete") {
        fdelete();
    }
    else if (cmdName == "close") {
        close();
    }
    else if (cmdName == "color" || cmdName == "cl") {
        if (args.size() < 2) {
            std::cout << "Example: color A5";
            main();
        }
        else {
            color(args[1]);
        }
    }
    else if (cmdName == "clear") {
        clear();
    }
    else if (cmdName == "tim" || cmdName == "timecheck") {
        tim();
    }
    else if (cmdName == "ls" || cmdName == "list") {
        ls();
    }
    else if (cmdName == "cd") {
        if (args.size() < 2) {
            std::cout << "Usage: cd <path>\n";
        }
        else {
            cd(args[1]);
        }
    }
    else if (cmdName == "history") {
        history();
    }
    else {
        std::cout << "Command not found\n";
        main();
    }
}

void help() {
    std::cout << "help\nfcreate\nfdelete\nclose\ncolor\nclear\ntim\nls\ncd\n";
    main();
}

void tim() {
    time_t t = time(nullptr);
    struct tm tt;
    localtime_s(&tt, &t);

    char buffer[26];
    asctime_s(buffer, sizeof(buffer), &tt);
    std::cout << "Current Day, Date and Time is = " << buffer;
    main();
}

void clear() {
    system("cls");
    main();
}

void color(const std::string& colorcode) {
    system(("Color " + colorcode).c_str());
    std::cout << "Color changed\n";
    main();
}

void ls() {
    std::filesystem::path currentPath = std::filesystem::current_path();
    for (const auto& entry : std::filesystem::directory_iterator(currentPath)) {
        std::cout << entry.path().filename().string() << std::endl;
    }
    main();
}

void fcreate() {
    std::cout << "Enter file name: ";
    std::string name;
    std::cin >> name;
    std::cout << "Enter file type: ";
    std::string filetype;
    std::cin >> filetype;
    std::ofstream file(name + "." + filetype);
    file.close();
    std::cout << "File created\n";
    main();
}

void fdelete() {
    std::cout << "Enter file name: ";
    std::string name;
    std::cin >> name;
    if (remove(name.c_str()) != 0) {
        std::cout << "Error deleting file\n";
    }
    else {
        std::cout << "File deleted\n";
    }
    main();
}

void cd(const std::string& path) {
    if (SetCurrentDirectoryA(path.c_str())) {
        char currentPath[MAX_PATH];
        GetCurrentDirectoryA(MAX_PATH, currentPath);
    }
    else {
        std::cerr << "Error: Unable to change directory to " << path << std::endl;
    }
    main();
}
void history() {
    for (const auto& item : History) {
        std::cout << item << " " << std::endl;
    }
    main();
}

void close() {
    std::cout << "Exiting\n";
    Sleep(100);
    exit(0);
}