#include <iostream>
#include <string>
#include <regex>
#include <vector>

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

    std::vector<std::string> emails{"123.123@qq.com.cn", "abc.def.ghi@example.com"};

    // std::cout << is_email(input) << '\n' << is_email(n_input) << std::endl;
    std::cout << is_email(emails[0]) << '\n' << is_email(emails[1]) << std::endl;
}