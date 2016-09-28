#include "CUtilities.h"

using namespace CZ4004;
using namespace std;

string CUtilities::directory = "..\\models\\";

void CUtilities::SplitString(const std::string & full_string, const std::string & token, std::vector<std::string> & sub_strings)
{
    std::string updated_string = full_string;
    unsigned int result = updated_string.find_first_of(token);

    while (result != std::string::npos)
    {
        sub_strings.push_back(updated_string.substr(0, result));
        updated_string = updated_string.substr(result + 1, updated_string.size());
        result = updated_string.find_first_of(token);
    }

    if (!updated_string.empty())
    {
        sub_strings.push_back(updated_string);
    }
}