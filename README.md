This is a repo to train your hotkeys in games like StarCraft 2 and Dota 2.
The plan is to have the program "read" the C:\Users\<user>\Documents\StarCraft\Accounts\<id>\Hotkeys file.
(Not yet implemented) !!!

To compile the program you will need gcc and g++ on Windows or gcc and g++ on Linux:

```
cc -o nob nob.c
./nob
./build/main
```

The reason for linux here is that I develop on wsl and can't be bothered to test everything on windows all the time - so i just made
it compile on both OS's without any overhead. You just enter the above in the terminal - and voilà, you have the executable for 
the right OS.


For now the version is extremely raw and my personal hotkeys (TheCoreRight6_qwerty) are literally hardcoded in the code, so you
would have to change them yourself if you want to use this.

TheCore as in the famous layout is itself the inspiration for the name of the project

The reason this repo exists in the first place is that i didn't find anything quite like that for training inside the game. 
Let me explain, while there is plenty good maps like Darglein, hotkey trainer and others, I was looking for something more
forceful, like learning how to type first time. They literally tell you what to type - you dont need to think about what
YOU want to do next - but instead somebody has the study flow covered. Hope that explains it. 

Contributors:
Thyruh,
...

Resources:

https://drive.google.com/drive/folders/1ui2HNwaUa4FkHzRwATgXHNVEpolLNOzA   -- TheCore official drive with everything you need 
to get started.

https://github.com/tsoding/nob.h     -- I had a lot of fun learning to work with this library by Alexei. As he says himself -
it might not be the best tool for building projects - but there is something very inspirational about building your project with C.

