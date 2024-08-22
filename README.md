# Terminal studio

This project is a custom terminal application implemented in C++. It supports various commands for interacting with the filesystem and performing other operations. The terminal is designed to run on Windows and can be built using Visual Studio or Visual Studio Code with the `g++` compiler.

## Table of contents
<div id="user-content-toc">
  <ul>
    <li><a href="#features">Features</a></li>
    <li><a href="#prerequisites">Prerequisites</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#usage">Usage</a>
      <ul>
        <li><a href="#commands">Commands</a>
        <li><a href="#example">Example</a>
      </ul>
    </li>
    <li><a href="#license">License</a>
    <li><a href="#acknowledgments">Acknowledgments</a>
    <li><a href="#disclaimer">Disclaimer</a>
    <li><a href="#contact">Contact</a>
      
  </ul>
</div>

## Features

- Create and delete files and directories
- Change console colors and clear the screen
- Display current time and directory listings
- Manage and display command history
- Execute system commands and run external programs
- Built-in "games" feature with different risk levels
- 
## Prerequisites

- Windows operating system
- [Visual Studio](https://visualstudio.microsoft.com/), [Visual Studio Code](https://code.visualstudio.com/) (recommended) or any other code editor if you want to edit the project
- [MinGW](https://www.mingw-w64.org/) for the `g++` compiler (recommended) or any other c++ compiler

## Installation

1. **Clone the repository**:

   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. **Open the project**:

   - For **Visual Studio**: Open the `.sln` file.
   - For **Visual Studio Code**: Open the folder containing your project files.

3. **Configure the build environment**:

   - Ensure `g++` is installed and available in your PATH.
   - If using Visual Studio Code, set up a `tasks.json` file to build the project with `g++`.

4. **Build and run the project**:

   - In Visual Studio, use the "Build" and "Run" commands.
   - In Visual Studio Code, execute the build task and then run the compiled executable.

## Usage

When you start the terminal application, it displays a command prompt with the current directory path. You can enter commands to interact with the terminal. Below is a list of available commands:

### Commands

- **help**: Displays a help message with a list of available commands.

- **fcreate `<file>`**: Creates a new file with the specified name.

- **fdelete `<file>`**: Deletes the specified file or directory.

- **dcreate `<directory>`**: Creates a new directory with the specified name.

- **close**: Exits the terminal application.

- **color `<colorcode>`**: Changes the console color using a color code (e.g., `color A5`).

- **clear**: Clears the console screen.

- **tim**: Displays the current time and date.

- **ls**: Lists all files and directories in the current directory.

- **cd `<path>`**: Changes the current working directory to the specified path.

- **history**: Displays a history of all entered commands.

- **vmload**: Displays the virtual memory usage of the application.

- **games**: Access a guessing game with varying levels of risk.

- **git `<command>` `<repo>`**: Executes a Git command on the specified repository (e.g., `git clone <repo>`).

- **move `<source>` `<destination>`**: Moves a file from the source to the destination path.

- **run `<command>`**: Executes a system command or runs an external program.

- **neofetch**: Displays a simple ASCII art logo.

### Example

Here's a brief example of how to use the terminal:

```bash
C:\Users\YourName\Project> fcreate example.txt
File created

C:\Users\YourName\Project> ls
example.txt

C:\Users\YourName\Project> cd ..
C:\Users\YourName>

C:\Users\YourName> color A5
Color changed
```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project uses the Windows API for operations like changing directories and managing memory.

## Disclaimer

The "games" feature includes options that may delete files or system directories. Use these options with caution.

## Contributing

Contributions are welcome! You can follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Make your changes and commit them (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

## Contact

For questions or suggestions, feel free to reach out via [GitHub Issues](https://github.com/kaskil12/TerminalStudio/issues).
