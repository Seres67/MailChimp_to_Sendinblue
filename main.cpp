#include <fstream>
#include <cstring>
#include <iostream>
#include "main.hpp"

static const convert_t CONVERT_TAB[] = {
        {"*|UNSUB|*",            "{{ unsubscribe }}"},
        {"*|ARCHIVE|*",          "{{ mirror }}"},
        {"*|MC:SUBJECT|*",       ""},
        {"*|MC_PREVIEW_TEXT|*",  ""},
        {"*|UPDATE_PROFILE|*",   "{{ update_profile }}"},
        {"*|EMAIL|*",            "{{ contact.EMAIL }}"},
        {"*|LIST:ADDRESSLINE|*", "REDACTED"},
        {"*|REWARDS|*",          ""},
        {"*|ABOUT_LIST|*",       ""}
};

bool read_file(int argc, char *argv[], std::ifstream &file, std::ofstream &out)
{
    std::string filename;

    if (argc != 2) {
        std::cout << "Only one argument needed (must be a file)" << std::endl;
        return (false);
    }
    filename = argv[1];
    if (filename.find(".html") == std::string::npos) {
        std::cout << "Only supports HTML files" << std::endl;
        return (84);
    }
    file.open(filename);
    if (file.fail()) {
        std::cout << "Couldn't open file" << std::endl;
        return (false);
    }
    out.open(filename.substr(0, filename.find('.html')) + "_sendinblue.html");
    if (out.fail()) {
        std::cout << "Couldn't create output file" << std::endl;
        return (false);
    }
    return (true);
}

int main(int argc, char *argv[])
{
    std::ifstream file;
    std::ofstream out;
    std::string tmp;
    int pos;

    if (!read_file(argc, argv, file, out))
        return (84);
    while (std::getline(file, tmp)) {
        for (auto convert : CONVERT_TAB)
            if (tmp.find(convert.base) != std::string::npos)
                while ((pos = tmp.find(convert.base)) != std::string::npos)
                    tmp.replace(pos, strlen(convert.base), convert.convert);
        out << tmp << '\n';
    }
}
