#include<fstream>
#include<iostream>
#include<sstream>
#include<array>

struct Keyword {
   std::string camera_save = "CameraSave";
   std::string jump_to_camera_location = "CameraView";

   std::string create_ctrl_group = "ControlGroupAssign";
   std::string create_steal_ctrl_group = "ControlGroupAssignAndSteal";

   std::string add_to_ctrl_group = "ControlGroupAppend";
   std::string add_steal_to_ctrl_group = "ControlGroupAppendAndSteal";

   std::string select_ctrl_group = "ControlGroupRecall";
};

struct Token {
   Keyword keyword;
   char identifier;
   char hotkey;
};


std::array<Token, 10> tokenize(const char* path) {
   std::fstream strm;
   strm.open(path, std::ios_base::in);
   if (!strm.is_open()) {
      fprintf(stderr, "Cannot find %s: No such file or directory\n", path);
   }

   std::stringstream contents;

   contents << strm.rdbuf();

   std::string str = contents.str();
   std::cout << str;

   return {};
}


