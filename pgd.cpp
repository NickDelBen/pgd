#include <string>
#include <iostream>
#include <stdio.h>

//Color codes to color terminal output
#define COLOR_RED "\033[0;31m"
#define COLOR_WHITE "\033[1;37m"
#define COLOR_BLUE "\033[1;34m"
#define COLOR_NONE "\033[0m"
#define COLOR_GREEN "\033[1;32m"

//Size of buffer to hold incoming command response
#define MAX_COMMAND_LENGTH 256

//Execute a command and return the result as a string
std::string exec(char* cmd) {
    //Open a pipe for communication with the new thread
    FILE* pipe = popen(cmd, "r");
    //Ensure the pipe opened successfully
    if (!pipe) {
        return "ERROR";
    }
    //Allocate space to store the output of the command
    char buffer[MAX_COMMAND_LENGTH];
    std::string result = "";
    //Listen for output down the pipe
    while(!feof(pipe)) {
    	if(fgets(buffer, MAX_COMMAND_LENGTH, pipe) != NULL) {
    		result += buffer;
        }
    }
    //Close the pipe
    pclose(pipe);
    //Trim the newline character
    if (result.length() > 0) {
        result.erase(result.end() - 1);
    }    
    return result;
}

//Return a styled output string of the current "Git working directory"
std::string getDirectory() {
    //Git commands needed
    char command_url_git[] = "git config --get remote.origin.url";
    char command_directory_git[] = "git rev-parse --show-prefix";
    char command_branch_git[] = "git rev-parse --abbrev-ref HEAD";
    char command_untracked_git[] = "git ls-files -mo";
    
    //Execute the commands and store the result
    std::string gitRemote = exec(command_url_git);    
    std::string currentDirectory = exec(command_directory_git);
    std::string gitBranch = exec(command_branch_git);
    std::string gitUntracked = exec(command_untracked_git);

    //Combine the commands into one nice output
    return COLOR_BLUE + gitRemote + (gitUntracked.length() > 0 ? COLOR_RED : COLOR_GREEN) + "(" + gitBranch + ")" + COLOR_WHITE + "/" + currentDirectory + COLOR_NONE;
}


int main() {
    //Print the git command
    std::cout << getDirectory() << std::endl;
    return 0;
}