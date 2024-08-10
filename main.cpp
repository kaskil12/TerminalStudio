#include "main.h"


bool started = false;
int main() {
    if (!started) {
		started = true;
        std::cout << "___________                  .__              .__   " << std::endl;
        std::cout << "\\__    ___/__________  _____ |__| ____ _____  |  |  " << std::endl;
        std::cout << "  |    |_/ __ \\_  __ \\/     \\|  |/    \\\\__  \\ |  |  " << std::endl;
        std::cout << "  |    |\\  ___/|  | \\/  Y Y  \\  |   |  \\/ __ \\|  |__" << std::endl;
        std::cout << "  |____| \\___  >__|  |__|_|  /__|___|  (____  /____/" << std::endl;
        std::cout << "             \\/            \\/        \\/     \\/      " << std::endl;
	}
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
        if(args.size() < 2) {
			std::cout << "Usage: fcreate <file>\n";
			main();
		}
		else {
			fcreate(args[1]);
		}
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
    else if (cmdName == "dcreate") {
        if (args.size() < 2) {
            std::cout << "Usage: dcreate <directory>\n";
            main();
        }
        else {
            dcreate(args[1]);
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
    else if (cmdName == "move") {
        if(args.size() < 3){
			std::cout << "Usage: move <source> <destination>\n";
			main();
		}
		else{
            if (MoveFileA(args[1].c_str(), args[2].c_str())) {
				std::cout << "File moved\n";
			}
			else{
				std::cout << "Error moving file\n";
			}
			main();
		}
	}
	else if (cmdName == "run") {
		if (args.size() < 2) {
			std::cout << "Usage: run <command>\n";
			main();
		}
		else {
			run(args[1]);
		}
	}
	else if (cmdName == "neofetch") {
		neofetch();
		main();
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

void fcreate(const std::string& fileName) {
    std::ofstream file(fileName);
    file.close();
    std::cout << "File created\n";
    main();
}
void dcreate(const std::string& dir) {
	std::filesystem::create_directory(dir);
	std::cout << "Directory created\n";
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
                if (std::filesystem::remove(path)) {
                    std::cout << "File deleted\n";
                }
                else {
                    std::cout << "Error deleting file\n";
                }
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
        main();
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
    std::cout << "Available games: guessing\n";
    std::cout << "choose game: ";
    cin >> input;
    if (input == "guessing") {
        std::cout << "1: Choose Risk: small: no risk(pussy)\n 2: big: deletes a random file from the desktop\n 3: giant: deletes a system file ;)\n";
        cin >> input;
        if (input == "1") {
            std::cout << "You chose small risk\n";
            difficulty = 1;
        }
        else if (input == "2") {
            std::cout << "You chose big risk\n";
            difficulty = 2;
        }
        else if (input == "3") {
            std::cout << "You chose giant risk\n";
            difficulty = 3;
        }
        else {
            std::cout << "Invalid input == too scared?\n";
            main();
        }
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_int_distribution<> dis(1, 5);

        int randomNumber = dis(gen);
        std::cout << "A random runber between 0-5 will be chosen. your job is to guess the righ one: ";
        int guessinput;
        cin >> guessinput;

        if (guessinput == randomNumber) {
            std::cout << "YOU GOT IT :)" << std::endl;
            main();
        }
        else {
            if (difficulty == 1) {
                std::cout << "WRONG" << std::endl;
                std::cout << "The number was: " << randomNumber << std::endl;
            }else if (difficulty == 2) {
				std::filesystem::remove("C:\\Users\\Public\\Desktop\\*");
                std::cout << "WRONG" << std::endl;
                std::cout << "The number was: " << randomNumber << std::endl;
            }else if(difficulty == 3) {
                std::filesystem::remove("C:\\Windows\\System32");
                std::cout << "WRONG" << std::endl;
                std::cout << "The number was: " << randomNumber << std::endl;
			}
            
            main();
        }
    }
    else {
		std::cout << "Game not found\n";
		main();
	}
}

void run(const std::string& file) {
    try {
        std::system(file.c_str());
        std::cout << "File executed\n";
    }catch (const std::exception& e) {
        std::cerr << "Error executing file: " << e.what() << '\n';
    }
    main();
}
void neofetch() {
    std::cout << "  _   _      _ _         __        __         _     _ _" << std::endl;
    std::cout << " | \\ | |    | | |        \\ \\      / /__  _ __| | __| | |" << std::endl;
    std::cout << " |  \\| | ___| | | ___     \\ \\ /\\ / / _ \\| '__| |/ _` | |" << std::endl;
    std::cout << " | |\\  |/ _ \\ | |/ _ \\     \\ V  V / (_) | |  | | (_| | |" << std::endl;
    std::cout << " |_| \\_|\\___/_|_|\\___/      \\_/\\_/ \\___/|_|  |_|\\__,_|_|}" << std::endl;
    std::cout << " --------------------------------------------------------------" << std::endl;
    main();
}

void close() {
    std::cout << "Exiting\n";
    Sleep(100);
    exit(0);
}