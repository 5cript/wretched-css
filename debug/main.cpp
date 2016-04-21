#include "main.hpp"

#include "../rule_set/rule_set.hpp"

#include "../rule_set/rule/property/value/color.hpp"

#include "../style_sheet.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    using namespace WretchedCss;

    auto data = readStringFromFile ("testfile.txt");

    StyleSheet sheet(data);
    auto style = sheet.select(".bla");

    if (style)
    {
        RuleSet temp;
        temp.rules.push_back(style.get().mergeInlineCss("background-color: #123456;").getRule());
        std::cout << temp.toCss() << "\n";
    }

    return 0;
}

std::string readStringFromFile(std::string const& fileName)
{
    std::ifstream reader (fileName, std::ios_base::binary);

    std::string data;
    do {
        char buffer[4096];
        reader.read(buffer, 4096);
        data.append(buffer, reader.gcount());
    } while (reader.gcount() == 4096);

    return data;
}
