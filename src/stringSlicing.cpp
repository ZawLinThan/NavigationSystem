#include "stringSlicing.h"

std::vector<std::string> stringSlice(const std::string& pStr, char pDel)
{
    std::vector<std::string> vec;
    std::string substr;
    for (int i = 0; i < pStr.size(); ++i)
    {
        if (pStr[i] != pDel)
        {
            substr += pStr[i];
        } else {
            vec.push_back(substr);
            substr.clear();
        }

        if (i == pStr.size()-1)
        {
            vec.push_back(substr);
        }
    }
    return vec;
}