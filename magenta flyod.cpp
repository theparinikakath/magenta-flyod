#include <iostream>
#include <cstdlib>

// Function to execute shell commands and retrieve the output
std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) {
        return "Error";
    }
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    return result;
}

int main() {
    std::string searchTerm;
    std::cout << "Enter the song you want to listen to: ";
    std::getline(std::cin, searchTerm);

    // Use YouTube API to search for the song
    std::string command = "youtube-dl --quiet --extract-audio --audio-format mp3 \"ytsearch1:" + searchTerm + "\"";
    std::string output = exec(command.c_str());

    if (output.find("ERROR") != std::string::npos) {
        std::cerr << "Error occurred while searching for the song.\n";
        return 1;
    }

    std::cout << "Song downloaded successfully. Now playing...\n";

    // Play the downloaded song
    std::string playCommand = "mpg123 \"" + searchTerm + ".mp3\"";
    system(playCommand.c_str());

    return 0;
}
