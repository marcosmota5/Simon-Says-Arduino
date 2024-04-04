# Simon Says Game v1.1

# Credits

COMP 1045 Group Assignment - Simon Says Game

Group: 5

Group Members: Marcos, Lucas, Sergio, Vinicius, Natália

Member Responsible for Code and Circuit: Marcos Mota

Created on: 2024-02-23

Version v1.1

# Description

This is an Arduino project that features a Simons Says game. This project was built for a group assignment, check the details inside the comments on the circuit to see the tutorials and information about how the game works.  Also, all code are commented to make it easier to understand the logic behind each variable and function.

# Instructions

1. Click on "Start Simulation".
2. The game will start in the "Setup Mode". In this mode you can select the difficulty level, the speed and the color pattern, check the details on these topics below.
3. After finishing the desired setup, click on the "Start/Reset" button and the game will begin.
4. The lights will light in a random order and you need to click on the lights in that same order.

Remember to turn your sound on ;)

# Levels

The game total amount of levels depends on the difficulty selected, please check the Difficulty section below for more information. Each level represents one more light into the sequence.

# Score

The score is calculated based on how many seconds you took to click on each light. The base score value starts at a number that varies depending on the difficulty (check the Difficulty section for details of each level) and will decrease 5 points for each second you take to click on a light, but you will get a minimum of 10 points for a correct answer even if you take a very long time.

# Setup Mode

In the setup mode you can select the difficulty, the speed and the color pattern (for people with color blindness, for accessibility purposes).

Changing these options will only take effect when entering the Setup Mode.

# Difficulty

The game has 7 difficulty levels. The difference between each difficulty is how many levels you have to pass to beat the game, that means, harder = more levels, and how many points you get per correct answer. The levels and their time values and base points are:

    Baby: 3 levels to be beaten, 25 points per correct answer.
    Very Easy: 4 levels to be beaten, 50 points per correct answer.
    Easy: 5 levels to be beaten, 75 points per correct answer.
    Normal: 8 levels to be beaten, 100 points per correct answer.
    Hard: 10 levels to be beaten, 125 points per correct answer.
    Very Hard: 14 levels to be beaten, 150 points per correct answer.
    Insane: 20 levels to be beaten, 175 points per correct answer.

To change the difficulty level, turn the corresponding potentiometer (blue wheel on the left). The easiest difficulties are on the left side and the hardest difficulties are on the right side. You will see the difficulty on the screen when you change it.

# Speed

You can set the speed between lights by turning the corresponding potentiometer (blue wheel on the middle). The speed does not affect in score or difficulty, it's just for users that prefers a faster or slower game. The minimum (slowest) speed that can be set (when the potentiometer is on the bottom left) is 700 miliseconds and the maximum (fastest) speed that can be set (when the potentiometer is on the bottom right) is 100 miliseconds.

# Color Pattern

Focusing on accessibility for people with color blindness, you can select different colors for the lights. The game has 7 different color patterns.
To change the color pattern, turn the corresponding potentiometer (blue wheel on the right). You will see the lights changing colors right away.

# License

Shield: [![CC BY-NC-SA 4.0][cc-by-nc-sa-shield]][cc-by-nc-sa]

This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
