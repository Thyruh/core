#include <iostream>
#include <array>
#include <cmath>
#include <ctime>
#include <random>

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
            std::cout << mode << "\n\n";
            return mode;
        }
    }
}

char generator(const char& mode) {
    static const std::array<char, ctrl_size> ctrlGroups =
        {'j','i','o','l','m','n','h','b','g',' '};

    static const std::array<char, camera_size> cameraLocations =
        {'0','9','8','u',' ',' ',' ','b'};

    static std::mt19937 rng(std::random_device{}());

    if (mode == '1') {
        while (true) {
            size_t i = rng() % ctrl_size;
            if (ctrlGroups[i] != ' ') {
                std::cout << "Select the " << i + 1 << " control group\n";
                return ctrlGroups[i];
            }
        }
    }

    if (mode == '2') {
        while (true) {
            size_t i = rng() % camera_size;
            if (cameraLocations[i] != ' ') {
                std::cout << i << " - Jump to the " << i + 1 << " location\n";
                return cameraLocations[i];
            }
        }
    }

    if (mode == '3') {
        std::uniform_int_distribution<size_t> dist(0, camera_size + ctrl_size - 1);
        while (true) {
            size_t i = dist(rng);
            if (i >= camera_size) {
                size_t idx = i - camera_size;
                if (ctrlGroups[idx] != ' ') {
                    std::cout << "Select the  " << idx + 1 << " control group\n";
                    return ctrlGroups[idx];
                }
            }
            else {
                size_t idx = camera_size - 1 - i;
                if (cameraLocations[idx] != ' ') {
                    std::cout << "Jump to the " << idx + 1 << " location\n";
                    return cameraLocations[idx];
                }
            }
        }
    }

    return static_cast<char>(EXIT_FAILURE);
}

auto checker(const char& answer, const char& userInput) -> bool {
    if (userInput == answer) {
        std::cout << "Correct\n\n";
        return true;
    }

    if (userInput == ' ')
        return false;

    std::cout << "Incorrect\n";
    std::cout << "User inputted - " << userInput << "\n";
    std::cout << "The correct key was -- " << answer << "\n\n";
    return false;
}

int main() {
    std::srand(std::time(nullptr));
    char mode = instructions();

    while (true) {
        char answer = generator(mode);
        char userInput = getch();
        if (userInput != RET) checker(answer, userInput);
        else return EXIT_FAILURE;
    }
}

