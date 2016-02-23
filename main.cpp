#include "main.hpp"

#include <iostream>

using namespace std;

int main()
{
    using namespace TwistedSpirit;

    auto data = readStringFromFile ("testfile.txt");

    TYPEDEF_GRAMMAR(color_grammar);
    auto res = parse <grammar> (data);
    auto color = res.second;

    cout << "Hello world!" << endl;
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
