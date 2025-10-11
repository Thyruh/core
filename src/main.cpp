#include<iostream>
#include<array>
#include<cmath>
#include<time.h>

#if 0
#include"tokenizer.cpp"
#endif

#ifdef _WIN32
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
#endif

#define getch() _getch()

char instructions() {
   char mode;
   std::cout << std::endl;
   std::cout << "Control groups trainer: 1\n";
   std::cout << "Camera location trainer: 2\n";
   std::cout << "Mix: 3\n";

   mode = getch();
   if (mode == '1' || mode == '2' || mode == '3') {
      return mode;
   }
   return EXIT_FAILURE;
}

char generator(const char& mode) {
   static const std::array<char, 9> ctrlGroups = {'j', 'i', 'o', 'l', 'm', 'n', 'h', 'b', 'g'};
   static const std::array<char, 5> cameraLocations = {'0', '9', '8', 'u', 'b'};

   srand(time(NULL));
   size_t i;

   if (mode == '1') {
      i = rand() % 9;
      std::cout << "Select the " << i+1 << " control group" << std::endl;
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
   else {
      i = rand() % 14;
      if (i+1 > 5) {
         std::cout << "Select the " << i-4 << " control group" << std::endl;
         return ctrlGroups[i-5];
      }
      else {
         std::cout << "Jump to the " << 5-i << " location" << std::endl;
         return cameraLocations[4-i];
      }
   }
   return EXIT_FAILURE;
}

bool checker(const char& answer, const char& userInput) {
   if (userInput == answer) {
      std::cout << "Correct\n";
      return true; // For future stat tracking
   }
   else if  (userInput == 'q') {
      exit(EXIT_SUCCESS);
   }
   else {
      std::cout << std::endl;
      std::cout << "Incorrect\n";
      std::cout << "User inputted - " << userInput << std::endl;
      std::cout << "The correct key was -- " << answer << std::endl;
      std::cout << std::endl;
   }
   return EXIT_FAILURE;
}

int main() {
   char mode = instructions();
   while (1) {
      char answer = generator(mode);
      char userInput = getch();

      if (sizeof (userInput) == 1/* && userInput != '\n'*/){
         checker(answer, userInput);
      }
      else return 1;
   }
   return 0;
}
