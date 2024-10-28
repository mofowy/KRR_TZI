#include <iostream>
#include <string>
#include <unordered_set>
#include <fstream>
#include <regex>

std::unordered_set<std::string> loadPasswordDictionary(const std::string& filename) {
    std::unordered_set<std::string> dictionary;
    std::ifstream file(filename);
    std::string password;

    if (file.is_open()) {
        while (std::getline(file, password)) {
            dictionary.insert(password);
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open password dictionary file." << std::endl;
        return {};
    }

    return dictionary;
}

bool isPasswordStrong(const std::string& password) {
    const int minLength = 8;
    if (password.length() < minLength) return false;

    std::regex strongPattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]+$");
    return std::regex_match(password, strongPattern);
}

bool isPasswordInDictionary(const std::string& password, const std::unordered_set<std::string>& dictionary) {
    return dictionary.find(password) != dictionary.end();
}

int main() {
    std::unordered_set<std::string> passwordDictionary = loadPasswordDictionary("G:\\tzi\\KRR\\code\\Source\\password_dictionary.txt");

    std::string password;
    while (true) {
        std::cout << "Enter a password to check (or 'exit' to quit): ";
        std::getline(std::cin, password);

        if (password == "exit") break;

        if (!isPasswordStrong(password)) {
            std::cout << "The password \"" << password << "\" does not meet security requirements." << std::endl;
        }
        else if (isPasswordInDictionary(password, passwordDictionary)) {
            std::cout << "The password \"" << password << "\" is found in the password dictionary." << std::endl;
        }
        else {
            std::cout << "The password \"" << password << "\" is secure." << std::endl;
        }
    }

    return 0;
}
