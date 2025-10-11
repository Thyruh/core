#define NOB_IMPLEMENTATION

#include "include/nob.h"

#define BUILD_FOLDER "build/"
#define SRC_FOLDER "src/"

int main(int argc, char** argv) {
   NOB_GO_REBUILD_URSELF(argc, argv);
   if (!nob_mkdir_if_not_exists(BUILD_FOLDER)) return 1;

   Nob_Cmd cmd = {0};
#if !defined(_MCS_VER)
   nob_cmd_append(&cmd, "g++", "-O3", "-Wall", "-Wextra", "-Werror", "-o", BUILD_FOLDER"main", SRC_FOLDER"main.cpp");
#else 
   nob_cmd_append(&cmd, "g++", "-O3", "-I.", "-o"NOB_ASSERT, BUILD_FOLDER"main.exe", SRC_FOLDER"main.cpp");
#endif
   if (!nob_cmd_run(&cmd)) return 1;
   return 0;
}

