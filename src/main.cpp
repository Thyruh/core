#include<iostream>
#include<array>
#include<cmath>
#include<time.h>

#ifdef _WIN32
   const char RET = '\r';

#  include <conio.h>

#else

#  include <termios.h>
#  include <unistd.h>

   char _getch() {
      termios oldt{}, newt{};
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      char c = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      return c;
   }
   const char RET = '\n';
#endif

#define ctrl_size 10 
#define camera_size 8
#define getch() _getch()

char instructions() {
   char mode;
   std::cout << "Control groups trainer: 1\n";
   std::cout << "Camera location trainer: 2\n";
   std::cout << "Mix: 3\n";

   while (true) {
      mode = getch();
      if (mode == '1' || mode == '2' || mode == '3') {
         std::cout << mode << std::endl << std::endl;
         return mode;
      }
   }
}


char generator(const char& mode) {
   static const std::array<char, ctrl_size> ctrlGroups = {'j', 'i', 'o', 'l', 'm', 'n', 'h', 'b', 'g', ' '};
   static const std::array<char, camera_size> cameraLocations = {'0', '9', '8', 'u', ' ', ' ', ' ', 'b'};

   size_t i;

   if (mode == '1') {
      i = rand() % ctrl_size;
      if (ctrlGroups[i] != ' ') {
         std::cout << "Select the  " << i+1 << " control group" << std::endl;
         return ctrlGroups[i];
      }
      else generator(mode);
   }
   else if (mode == '2') {
      i = rand() % camera_size;
      if (cameraLocations[i] != ' ') {
         std::cout << i << " - ";
         std::cout << "Jump to the " << i+1 << " location" << std::endl;
         return cameraLocations[i];
      }
      else generator(mode);
   }
   else if (mode == '3') {
      i = rand() % (camera_size + ctrl_size); // Merging the two arrays but not actually.
      if (i >= camera_size) {
         if (ctrlGroups[i-camera_size] != ' ') {
            std::cout << i << " - ";
            std::cout << "Select the  " << i+1 - camera_size << " control group\n";
            return ctrlGroups[i-camera_size]; // UB sometimes. No idea why. Probably something in conditions...
         }
         else generator(mode);
      }
      else if (i < camera_size) {
         if (cameraLocations[camera_size-1-i] != ' ') {
            std::cout << i << " - ";
            std::cout << "Jump to the " << camera_size-i << " location\n";
            return cameraLocations[camera_size-1-i]; // UB sometimes. No idea why.
         }
         else generator(mode);
      }
   }
   return EXIT_FAILURE;
}

bool checker(const char& answer, const char &userInput) {
   if (userInput == answer) {
      std::cout << "Correct\n\n";
      return true; // For future stat tracking
   }
   else if (userInput == ' ') {
      return EXIT_FAILURE;
   }
   else {
      std::cout << "Incorrect\n";
      std::cout << "User inputted - " << userInput << std::endl;
      std::cout << "The correct key was -- " << answer << std::endl;
      std::cout << std::endl;
   }
   return false;
}

int main() {
   srand(time(NULL));

   char mode = instructions();
   while (true) {
      char answer = generator(mode);
      char userInput = getch();
      if (userInput != RET){
         checker(answer, userInput);
      }
      else return EXIT_FAILURE;
   }
}
