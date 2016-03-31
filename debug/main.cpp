#include "main.hpp"

#include "../rule_set/rule_set.hpp"

#include "../rule_set/rule/property/value/color.hpp"

#include <iostream>
#include <fstream>
#include <string>

int main()
{
    using namespace WretchedCss;

    auto data = readStringFromFile ("testfile.txt");

    RuleSet set;
    set.fromCss(data);

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
