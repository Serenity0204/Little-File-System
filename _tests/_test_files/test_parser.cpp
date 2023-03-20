#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>
//------------------------------------------------------------------------------
//Files we are testing:
#include "../../includes/cmd_parser/cmd_parser.h"
#include "../../includes/config/config.h"
//------------------------------------------------------------------------------

using namespace std;


// back->0
// mkdir -> 1 + 1 not space == 2
// cd -> 1 + 1 not space == 2
// ls->0 
// touch -> 1 + 1 not space and .txt == 6
// rm-> 1 + 1 not space == 2

// enum PARSE_KEY
// {
//     BACK=0,
//     MKDIR=1,
//     CD=2,
//     TOUCH=3,
//     LS = 4,
//     RM=5,
// };


const unordered_map<string, vector<int>> test_cmd = {{"back", {BACK, 0}}, {"touch", {TOUCH, 6}}, {"mkdir", {MKDIR, 2}}, {"cd", {CD, 2}}, {"ls", {LS, 0}}, {"rm", {RM, 2}}};
const string root1 = "root:\\user\\";
const string root2 = "root:\\my_user\\";

// test regular
bool test_parser1(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);
  string subcmd = "";

  string command = root1 + "lfs back";
  int check = p.parse(command, subcmd);
  if(check != BACK) return false;

  command = root1 + "lfs mkdir a";
  check = p.parse(command, subcmd);
  if(check != MKDIR) return false;

  command = root1 + "lfs cd a";
  check = p.parse(command, subcmd);
  if(check != CD) return false;

  command = root1 + "lfs ls";
  check = p.parse(command, subcmd);
  if(check != LS) return false;

  command = root1 + "lfs rm a";
  check = p.parse(command, subcmd);
  if(check != RM) return false;

  command = root1 + "lfs touch a.txt";
  check = p.parse(command, subcmd);
  if(check != TOUCH) return false;
  return true;
}

// test adding space
bool test_parser2(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);
  string subcmd = "";

  // adding extra space-> false
  string command = root1 + "lfs back ";
  int check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // two space-> true
  command = root1 + "lfs mkdir  ";
  check = p.parse(command, subcmd);
  if(check != MKDIR) return false;

  // two space-> true
  command = root1 + "lfs cd  ";
  check = p.parse(command, subcmd);
  if(check != CD) return false;


  // extra space->false
  command = root1 + "lfs ls ";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // extra space->false
  command = root1 + "lfs rm ";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  return true;
}


// test two space between system name and command
bool test_parser3(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);
  string subcmd = "";

  string command = root1 + "lfs  back";
  int check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  command = root1 + "lfs  mkdir a";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  command = root1 + "lfs  cd a";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  command = root1 + "lfs  ls";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  command = root1 + "lfs  rm";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  return true;
}



// test hybrid
bool test_parser4(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);
  string subcmd = "";

  // stick together is false
  string command = root1 + "lfsback";
  int check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // missing system name is false
  command = root1 + "lf mkdir a";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  //space between system name is false;
  command = root1 + "l fs cd a";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // not command is false  
  command = root1 + "lfs";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // no command but with space is false
  command = root1 + "lfs ";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // no command but with spaces is false
  command = root1 + "lfs  ";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // invalid command is false
  command = root1 + "lfs a";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // empty is false
  command = root1 + "       ";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  // with subcommand but not space is false
  command = root1 + "lfs mkdirabc";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;


  // subcommand with space is true
  command = root1 + "lfs mkdir a bc";
  check = p.parse(command, subcmd);
  if(check != MKDIR) return false;

  command = root1 + "lfs touch c.txt";
  check = p.parse(command, subcmd);
  if(check != TOUCH) return false;

  command = root1 + "lfs touch cccc";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  command = root1 + "lfs touch ccccc";
  check = p.parse(command, subcmd);
  if(check != INVALID) return false;

  command = root1 + "lfs touch cccc.txt";
  check = p.parse(command, subcmd);
  if(check != TOUCH) return false;

  return true;
}




//Lord help me! 
const bool debug = false;

TEST(TEST_PARSER, TestParser1)
{
  bool success = test_parser1(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_PARSER, TestParser2)
{
  bool success = test_parser2(debug);
  EXPECT_EQ(success, true);
}


TEST(TEST_PARSER, TestParser3)
{
  bool success = test_parser3(debug);
  EXPECT_EQ(success, true);
}

TEST(TEST_PARSER, TestParser4)
{
  bool success = test_parser4(debug);
  EXPECT_EQ(success, true);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}