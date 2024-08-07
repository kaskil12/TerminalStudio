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
        if (args.size() < 2) {
			std::cout << "Usage: fdelete <file>\n";
			main();
		}
		else {
			fdelete(args[1]);
		
        }
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
    else if (cmdName == "vmload") {
        vmload();
    }
    else if (cmdName == "games") {
        games();
    }
    else if (cmdName == "git") {
        if (args.size() < 2) {
            std::cout << "Example: git clone *repo*" << std::endl;
            main();
        }
        else if (args.size() < 3){
            git(args[1], "");
        }
        else {
            git(args[1], args[2]);
            main();
        }
    }
    else {
        std::cout << "Command not found\n";
        main();
    }
}

void help() {
    //list all functions
    std::cout << "fcreate - create a file\n fdelete - delete a file\n close - close terminal\n color or cl - change color\n clear - clear the terminal\n tim or timecheck - check time and date\n ls or list - lists all files and folders in the current directory\n cd - change directory\n history - lists all commands used in current session\n vmload - displays the current virtual memory load of the current app\n games - games you can play\n git - github clone or push\n help - lists all commands for help";
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

void fdelete(const std::string& path) {
    try {
        if (std::filesystem::exists(path)) {
            if (std::filesystem::is_directory(path)) {
                std::filesystem::remove_all(path);
                std::cout << "Directory deleted\n";
            }
            else if (std::filesystem::is_regular_file(path)) {
                std::remove(path.c_str());
                std::cout << "File deleted\n";
            }
            else {
                std::cout << "Path exists but is neither a file nor a directory\n";
            }
        }
        else {
            std::cout << "Path does not exist\n";
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error deleting path: " << e.what() << '\n';
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
void git(const std::string& argument, const std::string& repo) {
    std::string command = "git " + argument + " " + repo;
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "An error occurred: " << result << std::endl;
    }
    main();
}
void history() {
    for (const auto& item : History) {
        std::cout << item << " " << std::endl;
    }
    main();
}
void vmload() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;
    std::cout << virtualMemUsedByMe << std::endl;
    main();
}
void games() {
    string input;
    std::cout << "choose game: ";
    cin >> input;
    if (input == "guessing") {
        std::random_device rd;  // Non-deterministic random number generator
        std::mt19937 gen(rd()); // Mersenne Twister engine initialized with random_device

        // Define the range of random numbers
        std::uniform_int_distribution<> dis(1, 10); // Range [1, 10]

        // Generate the random number
        int randomNumber = dis(gen);
        std::cout << "A random runber between 0-10 will be chosen. your job is to guess the righ one: ";
        int guessinput;
        cin >> guessinput;

        if (guessinput == randomNumber) {
            std::cout << "YOU GOT IT :)" << std::endl;
            main();
        }
        else {
            std::cout << "WRONG" << std::endl;
            std::cout << "The number was: " << randomNumber << std::endl;
            main();
        }
    }
}

void close() {
    std::cout << "Exiting\n";
    Sleep(100);
    exit(0);
}