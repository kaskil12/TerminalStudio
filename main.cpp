#include "main.h"
std::unordered_map<std::string, std::function<void()>> commands;
int main() {
	commands["help"] = help;
	commands["fcreate"] = fcreate;
	commands["fdelete"] = fdelete;
	commands["close"] = close;
	commands["color"] = color;
	commands["clear"] = clear;
	commands["tm"] = tm;
	commands["ls"] = ls;
	commands["cd"] = cd;

	char currentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentPath);
	string path(currentPath);
	std::cout << path << ": ";
	string Input;
	cin >> Input;
	if (commands.find(Input) != commands.end()) {
		commands[Input]();
	}
	else {
		std::cout << "Command not found\n";
		main();
	}
}
void help() {
	for (auto const& x : commands) {
		std::cout << x.first << "\n";
	}
	main();
}
void tm() {
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
void color() {
	string color;
	std::cout << "Enter color: ";
	cin >> color;
    system(("Color " + color).c_str());
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
	string name;
	cin >> name;
	std::cout << "Enter file type: ";
	string filetype;
	cin >> filetype;
	ofstream file(name + "." + filetype);
	file.close();
	std::cout << "File created\n";;
	main();
}
void fdelete() {
	std::cout << "Enter file name: ";
	string name;
	cin >> name;
	if (remove(name.c_str()) != 0) {
		std::cout << "Error deleting file\n";
	}
	else {
		std::cout << "File deleted\n";
	}
	main();
}
void cd(string path) {
	char currentPath[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, currentPath);
	SetCurrentDirectoryA((string(currentPath) + "\\" + path).c_str());
}
static void close() {
	std::cout << "Exiting\n";
	Sleep(100);
	system("exit");
}