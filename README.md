---
__Creaters:__

- __[Ofir Matasas](https://github.com/OfirMatasas)__
- __[Lin Moskovich](https://github.com/linkimos)__

---

# Arcade Project

## Description of the project
    This project made as part of Oriented Objects Programming in C++ 
    course, taken on summer semester in 2021.
    In this project, I've created an arcade, which contains 3 games: 
    Chess, Checkers and Amazons (PVP).
___
## Functions of the arcade
    1. The user can choose which game they'd like to run, and a new game can be created,
       while saving the progress of the last game played
       (no limit of running games in the background).
    2. Each game can be played until one of the players wins the game (or loses, in some cases),
       and the finished game will be saved in the list of running games, or be deleted, for user's choice.
    3. If the player is not satisfied of their current game, it can be deleted,
       and the arcade will load the next game the user created (if existed).
    4. The user can choose to save their current game in a file, and load it when necessary.

## Arcade Options List

    1.  Add a new game
        - Choosing between Chess, Checkers and Amazons.
    2.  Move to the next game
        - Load the game which was created right after the current one running.
    3.  Delete current game
        - Delete the game and move to the next game, if existed.
    4.  Show game details
        - Is the game still on?
        - Who's turn is it?
        - Who's the winner if the game ended?
    5.  Show possible Moves
        - Choose a position on the board, and show all possible repositions for the chosen stone.
    6.  Show threats
        - Choose a position on the board, and show all the stones threating it.
    7.  Make a move
        - Move a chosen stone from current position to a new one.
    8.  Exit menu
        - Shutting all games (without saving them), and exiting the arcade.
    9.  Save game to file
        - Save current game progress to a file.
    10. Load game from file
        - Load a game from a file, and continue the game from its last stop

## Games' Rules

+ [Chess](https://en.wikipedia.org/wiki/Rules_of_chess)
+ [Checkers](https://en.wikipedia.org/wiki/English_draughts)
+ [Amazons](https://en.wikipedia.org/wiki/Game_of_the_Amazons)
