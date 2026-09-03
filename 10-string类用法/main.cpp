#include <iostream>
#include <string>
#include <regex>

bool is_email(const std::string& text)
{
    std::regex pattern(R"((\w+)(\.?\w+)*@(\w+)(\.\w+)+)");

    if (std::regex_match(text, pattern)) return true;
    return false;
}
int main()
{
    std::string input{"123@qq.com"};
    std::string n_input{"1234"};

    std::cout << is_email(input) << '\n' << is_email(n_input) << std::endl;
}