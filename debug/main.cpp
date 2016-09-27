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

    //auto data = readStringFromFile ("testfile.txt");
    auto data = readStringFromFile ("../wiki-vcl-css/compiled.css");

    StyleSheet sheet(data);
    auto body = sheet.select("body").get();
    auto head = sheet.select(".header").get();
    auto h2 = sheet.select(".header h2").get();

    auto combine = Style(Style(h2.derive(&head).getCombined()).derive(&body).getCombined());
    RuleSet set;
    set.rules.push_back(combine.getCombined());

    std::cout << set.toCss() << "\n";

    /*
    if (style)
    {
        RuleSet temp;
        temp.rules.push_back(style.get().mergeInlineCss("background-color: #123456;").getRule());
        std::cout << temp.toCss() << "\n";
        std::cout << temp.toJson() << "\n";
    }
    */

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
