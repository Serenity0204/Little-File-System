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
const string root1 = "root:\\user\\";
const string root2 = "root:\\my_user\\";

// test regular
bool test_parser1(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);

  string command = root1 + "lfs back";
  bool check = p.parse(command);
  if(!check) return false;

  command = root1 + "lfs mkdir a";
  check = p.parse(command);
  if(!check) return false;

  command = root1 + "lfs cd a";
  check = p.parse(command);
  if(!check) return false;

  command = root1 + "lfs ls";
  check = p.parse(command);
  if(!check) return false;

  command = root1 + "lfs rm";
  check = p.parse(command);
  if(!check) return false;

  return true;
}

// test adding space
bool test_parser2(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);

  // adding extra space-> false
  string command = root1 + "lfs back ";
  bool check = p.parse(command);
  if(check) return false;

  // two space-> true
  command = root1 + "lfs mkdir  ";
  check = p.parse(command);
  if(!check) return false;

  // two space-> true
  command = root1 + "lfs cd  ";
  check = p.parse(command);
  if(!check) return false;


  // extra space->false
  command = root1 + "lfs ls ";
  check = p.parse(command);
  if(check) return false;

  // extra space->false
  command = root1 + "lfs rm ";
  check = p.parse(command);
  if(check) return false;

  return true;
}


// test two space between system name and command
bool test_parser3(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);

  string command = root1 + "lfs  back";
  bool check = p.parse(command);
  if(check) return false;

  command = root1 + "lfs  mkdir a";
  check = p.parse(command);
  if(check) return false;

  command = root1 + "lfs  cd a";
  check = p.parse(command);
  if(check) return false;

  command = root1 + "lfs  ls";
  check = p.parse(command);
  if(check) return false;

  command = root1 + "lfs  rm";
  check = p.parse(command);
  if(check) return false;

  return true;
}



// test hybrid
bool test_parser4(bool debug=false)
{
  CmdParser p(root1, "lfs");
  p.set_available_cmd(test_cmd);

  // stick together is false
  string command = root1 + "lfsback";
  bool check = p.parse(command);
  if(check) return false;

  // missing system name is false
  command = root1 + "lf mkdir a";
  check = p.parse(command);
  if(check) return false;

  //space between system name is false;
  command = root1 + "l fs cd a";
  check = p.parse(command);
  if(check) return false;

  // not command is false  
  command = root1 + "lfs";
  check = p.parse(command);
  if(check) return false;

  // no command but with space is false
  command = root1 + "lfs ";
  check = p.parse(command);
  if(check) return false;

  // no command but with spaces is false
  command = root1 + "lfs  ";
  check = p.parse(command);
  if(check) return false;

  // invalid command is false
  command = root1 + "lfs a";
  check = p.parse(command);
  if(check) return false;

  // empty is false
  command = root1 + "       ";
  check = p.parse(command);
  if(check) return false;

  // with subcommand but not space is false
  command = root1 + "lfs mkdirabc";
  check = p.parse(command);
  if(check) return false;


  // subcommand with space is true
  command = root1 + "lfs mkdir a bc";
  check = p.parse(command);
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