#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string path;
    std::cout << "Enter directory to organize: ";
    std::getline(std::cin, path);

    if (!fs::exists(path) || !fs::is_directory(path)) {
        std::cout << "Invalid directory.\n";
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            fs::path filePath = entry.path();
            std::string extension = filePath.extension().string();

            // Remove the dot from extension (".txt" → "txt")
            if (!extension.empty() && extension[0] == '.') {
                extension = extension.substr(1);
            }

            // Folder name for this extension
            fs::path folderPath = path + "/" + extension;

            // Create folder if it doesn't exist
            if (!fs::exists(folderPath)) {
                fs::create_directory(folderPath);
            }

            // Move file into the folder
            fs::path newLocation = folderPath / filePath.filename();
            fs::rename(filePath, newLocation);

            std::cout << "Moved: " << filePath.filename()
                      << " → " << folderPath << "\n";
        }
    }

    std::cout << "Organization complete.\n";
    return 0;
}