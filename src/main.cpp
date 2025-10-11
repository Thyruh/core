#include<iostream>
#include<array>
#include<cmath>
#include<time.h>

#include"tokenizer.cpp"

#ifdef _WIN32

const char RET = '\r';
#include <conio.h>

#else

#include <termios.h>
#include <unistd.h>

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

#define getch() _getch()

char instructions() {
   char mode;
   std::cout << "Control groups trainer: 1\n";
   std::cout << "Camera location trainer: 2\n";
   std::cout << "Mix: 3\n";

   mode = getch();
   if (mode == '1' || mode == '2' || mode == '3') {
      std::cout << mode << std::endl << std::endl;
      return mode;
   }
   exit(EXIT_FAILURE);
}

char generator(const char& mode) {
   static const std::array<char, 9> ctrlGroups = {'j', 'i', 'o', 'l', 'm', 'n', 'h', 'b', 'g'};
   static const std::array<char, 5> cameraLocations = {'0', '9', '8', 'u', 'b'};

   size_t i;

   if (mode == '1') {
      i = rand() % 9;
      std::cout << "Select the  " << i+1 << " control group" << std::endl;
      return ctrlGroups[i];
   }
   else if (mode == '2') {
      i = rand() % 5;
      if (i == 4) {
         std::cout << "Jump to the " << i+4 << " location" << std::endl;
      }
      else {
         std::cout << "Jump to the " << i+1 << " location" << std::endl;
      }
      return cameraLocations[i];
   }
   else if (mode == '3') {
      i = rand() % 14;
      if (i == 0) return generator(mode);
      if (i == 4) {
         std::cout << "Jump to the " << 8 << " location" << std::endl;
         return cameraLocations[i];
      }
      else if (i+1 > 5) {
         std::cout << "Select the  " << i-4 << " control group" << std::endl;
         return ctrlGroups[i-5];
      }
      else if (i != 4 && i+1 < 5) {
         std::cout << "Jump to the " << 5-i << " location" << std::endl;
         return cameraLocations[4-i];
      }
   }
   return generator(mode);
}

bool checker(const char& answer, const char& userInput) {
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

