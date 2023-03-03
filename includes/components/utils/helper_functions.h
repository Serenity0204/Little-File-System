#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <memory>
using namespace std;

int first_not_space(string str, int startIdx);
int first_space(string str, int startIdx);
string remove_space(string str);
#endif // !HELPER_FUNCTIONS_H