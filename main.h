#pragma once
#include <iostream>
#include <unordered_map>
#include <functional>
#include <ctime>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
#include "psapi.h"
#include <random>
#include <cstdio>
using namespace std;

//History String
std::vector<std::string> History;
//games difficulty
int difficulty;

int main();
void help(); 
void fcreate(const std::string& fileName);
void dcreate(const std::string& dir);
void fdelete(const std::string& file);
void ls();
void color(const std::string& colorcode);
void clear();
void tim();
void close();
void cd(const std::string& path);
void executeCommand(const std::string& command);
void history();
void vmload();
void run(const std::string& file);
void neofetch();
void games();
void git(const std::string& argument, const std::string& repo);