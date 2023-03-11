# The Breakout

## Description

1. folder ```"include"``` contains all header files
2. folder ```"resources"``` contains two files
    - ```bricks.txt``` text file containg position data of each brick.
      - First line contains two space separated decimal numbers representing number of rows and collums.
      - Second line contains two space separated decimal numbers representing width and height of each brick.
      - Then, there is a new line for each row containing collums sequences of X and Y coordinates (decimal space seperated numbers). 
    - ```highscores.txt```
        text file containg highscores. 
3. folder ```"src"``` contains source code, makefile, font and a folder for binary files (```"obj"```)

---

## Source code:

1. ```gxf.c``` manages rendering
2. ```init.c``` initializes SDL library and game objects
3. ```input.c``` manages mouse and keyboard inputs
4. ```logic.c``` manages game logic
5. ```main.c``` includes game loop
6. ```res.c ```manages files
7. ```text.c``` includes a function for drawing text

---

## Requirements

- SDL2 library 
  - for Debian-based systems: 
    - ``` $ sudo apt-get install libsdl2-dev ```
    - ``` $ sudo apt-get install -y libsdl2-ttf-dev ``` 
  - more detail at https://wiki.libsdl.org/SDL2/Installation
- Unix based OS

---

## Build instructions

1. open terminal in folder ```"src"```
2. in the terminal type: ``` $ make ```
3. in the terminal type: ``` $ ./breakout ```
4. the game should be running

You may want to remove the binary files created by the ```make``` command.
To do so open terminal in folder ```"src"``` and in the terminal type:
``` $ make clean ```

---

Last update 09/01/2021.
