# CSC 305 Team G
[![Contribute](https://img.shields.io/badge/Add-issue-blue.svg)](https://github.com/CSC305/s22g/issues)
[![made with java](https://img.shields.io/badge/Made_with-Java-red.svg)](https://www.java.com/en/)
[![made with libgdx](https://img.shields.io/badge/Made_with-libGDX-orange.svg)](https://libgdx.com/wiki/)

Contributors: Christian Tropeano, Christian Collins, Jayro Catlin, Jake Vaillancourt, Connor Gray, John Bevilacqua, Bilguuntur Munkhzaya, Cody Chu, Mark Wightman, Brennan Rivera
## What our Project Is
Our project for CSC 305 - Software Engineering is a fictional card game, similar to Slay the Spire. There is a player that draws cards in order to attack an enemy. The view is a first-person view of the player which is looking directly at the enemy.  
There are two kinds of cards, an attack card which can attack an enemy and a defend card which defends the user from the enemy. Once the player's turn is over, the Enemy hits the player, dealing damage.
The user wins when the enemy's health goes to 0 before the user's health does.

## To Run the Game:
1. First you have to clone the repository to your computer **(make sure that you remember what directory/folder you cloned into)**.
2. Then you want to use your terminal or command line to navigate to where you cloned the repository (using the cd command until you are in the folder where you cloned the repository).
3. Once you are in the correct folder, make sure you use the line ```git checkout GUI``` (this line switches you to the correct branch with the working game).
4. Run this line in your terminal:```./gradlew desktop:run``` (this runs your game and opens the window).

## Rules and How to Play
1. You will first be dealt two cards at the beginning of the game
    - You and the enemy will start at 100 health
2. You can pick what cards to play against the Enemy
    - Each card has a certain mana cost required to play it.
3. To end the turn, press the red button with the ```x``` at the bottom right of your screen.
4. After your turn ends, the Enemy will hit you once for 25 damage and then it is your turn again.
    - Your maximum mana increments by one
    - Your mana refreshes to full
    - You draw 2 more cards
5. You and the Enemy will keep going until one of you gets to 0 health, at which point the game ends and the window will close.

### Some general things to keep in mind about the game:
- When the enemy hits you, damage is first subtracted from your shield, then leftover damage is dealt to you
- You start at 5 mana and it increments and refills after every turn.
- Maximum hand size is 5
- Deck starts with 3 copies of each of 10 different cards
- Cards go into the graveyard after being played, if you run out of cards in deck the graveyard shuffles back into the deck
- **Enemy Vulnerable** The enemy takes the amount specified per instance of damage plus the vulnerable count
    - Example: Enemy is at 6 vulnerable, you play a card that does 5 damage => The enemy takes 11 damage
- The enemy does 25 damage to you between each of your turns

### Available Cards in the Deck:

*Note that there will be 3 of each card at the start of the game in the deck*

|     Name     | Cost |                   Functionality                   |
| ------------ | ---- | ------------------------------------------------- |
| Strike       |   1  | Deal 5 Damage                                     |
| Block        |   1  | Gain 5 Shield                                     |
| Pot of Greed |   3  | Draw 2 Cards                                      |
| Expedite     |   2  | Deal 5 Damage, Draw 1 Card                        |
| Enforce      |   2  | Gain 5 Shield, Draw 1 Card                        |
| Bloodletting |   0  | Gain 2 Mana this turn, Draw 1 Card, Lose 5 Health |
| Siphon Soul  |   2  | Deal 3 Damage, Gain that much Life                |
| Drop Kick    |   2  | Deal 10 Damage, Apply 1 Vulnerable                |
| War Cry      |   1  | Apply 2 Vulnerable, Gain 4 Shield                 |
| Boomerang    |   3  | Deal 2 Damage 4 times                             |
