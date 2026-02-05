
//  Password strength checker 

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

struct PasswordAnalysis {
    bool hasUpper = false;
    bool hasLower = false;
    bool hasDigit = false;
    bool hasSpecial = false;
    std::size_t length = 0;
    int score = 0;
};
//  To analyze password

PasswordAnalysis analyzePassword(const std::string &pwd) { 
    PasswordAnalysis res;
    res.length = pwd.size();

// it check each character in the password
    for (unsigned char ch : pwd) {
        if (std::isupper(ch)) res.hasUpper = true;
        else if (std::islower(ch)) res.hasLower = true;
        else if (std::isdigit(ch)) res.hasDigit = true;
        else if (std::ispunct(ch)) res.hasSpecial = true;
    }
//  score based on length & character 
    if (res.length >= 8) res.score += 2;
    if (res.length >= 12) res.score += 1;
    res.score += static_cast<int>(res.hasUpper) + static_cast<int>(res.hasLower)
               + static_cast<int>(res.hasDigit) + static_cast<int>(res.hasSpecial);

    return res;
}
// To provide suggestions for improving password
std::vector<std::string> generateFeedback(const PasswordAnalysis &a) {
    std::vector<std::string> suggestions;
    if (a.length < 8) suggestions.push_back("Increase yourpassword length to atleast 8 characters.");
    if (!a.hasUpper) suggestions.push_back("Add atleast one uppercase letter ");
    if (!a.hasLower) suggestions.push_back("Add atleast one lowercase letter ");
    if (!a.hasDigit) suggestions.push_back("Include at least one digit ");
    if (!a.hasSpecial) suggestions.push_back("Include at least one special character ");

    if (suggestions.size() > 2)
        suggestions.push_back("Consider using a passphrase.");

    if (suggestions.empty())
        suggestions.push_back(" Good :-) = Your password meets the recommended criteria.");

    return suggestions;
}

std::string strengthLabel(const PasswordAnalysis &a) {
    if (a.score <= 2) return "Weak";
    if (a.score <= 4) return "Moderate";
    return "Strong";
}
int main() {
    std::cout << "* Password Strength Checker *\n";
    std::cout << "Please enter password: ";

    std::string password;
    std::getline(std::cin, password);
// Analyze password
    PasswordAnalysis analysis = analyzePassword(password);
// Display results
    std::cout << "\nStrength = " << strengthLabel(analysis) << "\n";
    std::cout << "Details:\n";
    std::cout << " - Length = " << analysis.length << "\n";
    std::cout << " - Has uppercase Alphab = " << (analysis.hasUpper ? "Yes" : "No") << "\n";
    std::cout << " - Has lowercase Alphab = " << (analysis.hasLower ? "Yes" : "No") << "\n";
    std::cout << " - Has digit = " << (analysis.hasDigit ? "Yes" : "No") << "\n";
    std::cout << " - Has special char = " << (analysis.hasSpecial ? "Yes" : "No") << "\n";
// Display suggestions
    auto suggestions = generateFeedback(analysis);
    std::cout << "\nSuggestions: \n";
    for (const auto &s : suggestions) std::cout << " - " << s << "\n";
    return 0;
}
