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
#include <windows.h>
using namespace std;

int main();
void help(); 
void fcreate();
void fdelete();
void ls();
void color(const std::string& colorcode);
void clear();
void tim();
void close();
void cd(const std::string& path);
void executeCommand(const std::string& command);