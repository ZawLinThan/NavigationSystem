#include "stringSlicing.h"

std::vector<std::string> stringSlice(const std::string& pStr, char pDel)
{
    std::vector<std::string> vec;
    std::string substr;

    // iterate through the string
    for (int i = 0; i < pStr.size(); ++i)
    {
        // if the character is not same as pDel
        if (pStr[i] != pDel)
        {
            // add the char to substr
            substr += pStr[i];
        } else {
            // if it is pDel, push back to the vector
            vec.push_back(substr);
            // reset the substr
            substr.clear();
        }

        // for the last string, if 'i' is the last character
        if (i == pStr.size()-1)
        {
            // push back to the vector
            vec.push_back(substr);
        }
    }
    return vec;
}