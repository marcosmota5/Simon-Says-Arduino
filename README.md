# Simon Says Game v1.0

# Description

This is an Arduino project that features a Simons Says game. This project was built for a group assignment, check the details inside the comments on the circuit to see the tutorials and information about how the game works.  Also, all code are commented to make it easier to understand the logic behind each variable and function.

# Instructions

1. Click on "Start Simulation".
2. The game will start in the "Setup Mode". In this mode you can select the difficulty level and the color pattern, check the details on these topics below.
3. After finishing the desired setup, click on the "Start/Reset" button and the game will begin.
4. The lights will light in a random order and you need to click on the lights in that same order.

Remember to turn your sound on ;)

# Levels

The game total amount of levels can be changed at will by changing the variable totalLevels, but it's set to 10 by default. Each level represents one more light into the sequence.

# Score

The score is calculated based on how many seconds you took to click on each light. The score starts at 100 and will decrease 5 points for each second you take to click on a light, but you will get a minimum of 10 points for a correct answer even if you take a very long time.

# Setup Mode

In the setup mode you can select the difficulty and the color pattern (for people with color blindness, for accessibility purposes). Check below the details.
Changing difficulty and color pattern will only take effect when entering the Setup Mode.

# Difficulty

The game has 7 difficulty levels. The difference between each level is the delay between lights, that means, harder = less time. The levels and their time values are:

    Baby: 7 seconds between each light
    Very Easy: 6 seconds between each light
    Easy: 5 seconds between each light
    Normal: 4 seconds between each light
    Hard: 3 seconds between each light
    Very Hard: 2 seconds between each light
    Insane: 1 second between each light

To change the difficulty level, turn the corresponding potentiometer (blue wheel on the left). The easiest difficulties are on the left side and the hardest difficulties are on the right side. You will see the difficulty on the screen when you change it.

# Color Pattern

Focusing on accessibility for people with color blindness, you can select different colors for the lights. The game has 7 different color patterns.
To change the color pattern, turn the corresponding potentiometer (blue wheel on the right). You will see the lights changing colors right away.
