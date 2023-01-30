#include "helper_functions.h"

int first_not_space(string str, int startIdx)
{
    for(int i = startIdx; i < str.length(); ++i) if(str[i] != ' ') return i;
    return -1;
}