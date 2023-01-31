#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
//------------------------------------------------------------------------------
//Files we are testing:
#include "../../lib/cmd_parser/cmd_parser.h"

//------------------------------------------------------------------------------

using namespace std;


  // back->0
  // mkdir -> 1 + 1 not space == 2
  // cd -> 1 + 1 not space == 2
  // ls->0 
  // touch -> 1 + 1 not space == 2
  // rm->0


const unordered_map<string, int> test_cmd = {{"back", 0}, {"mkdir", 2}, {"cd", 2}, {"ls", 0}, {"rm", 0}};
const string root = "root:\\user\\>";



bool test_parser1(bool debug=false)
{
  CmdParser p(12, "lfs");
  p.set_available_cmd(test_cmd);

  string command = root + "lfs back";
  bool check = p.parse(command);
  if(!check) return false;
  command = root + "lfs mkdir a";
  if(!check) return false;
  command = root + "lfs cd a";
  if(!check) return false;
  command = root + "lfs ls";
  if(!check) return false;
  command = root + "lfs rm";
  if(!check) return false;

  return true;
}





//Lord help me! 
const bool debug = false;

TEST(TEST_PARSER, TestParser1)
{
  bool success = test_parser1(debug);
  EXPECT_EQ(success, true);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}