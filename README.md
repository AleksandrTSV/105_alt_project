# CMP105 2026 Final Submission 

## Game 

**Dino Handyman** 

A 2D platformer built with C++ and SFML in which the player controls a dinosaur handyman. The player must navigate two levels, interact with levers and flags, defeat worm enemies, and survive using a limited life system.

**Controls:** 
*	A / D - Move left / right
*	Space - Jump (double jump available after collecting coin in Level 2)
*	Left Ctrl - Sprint dash
*	F - Interact with lever / complete level
*	E - Throw fireball (2 second cooldown)
*	Escape - Pause / resume game

## Student Details

**Student Name:** Aleksandr Tsvyatkov

**Student Number:** 2503161

**Course:** _CGAD_

## Changelist
* Pause Menu
    	Press Escape to pause the game at any time. The current frame is visible beneath a semi-transparent overlay. Resume and Main Menu buttons are available, with hover colour feedback.
* Lives System (HUD)
    	The player starts with 3 lives displayed as heart icons in the top-left corner of the screen. Hearts update in real time: a full heart becomes empty when a life is lost. The HUD is anchored to the camera so it always stays visible regardless of player position.
* Fireball Attack
    	Press E to throw an animated fireball in the direction the player is facing. Fireballs are destroyed on contact with tiles or enemies. A 2-second cooldown prevents spamming.
* Worm Enemies
    Animated worm enemies patrol platforms on Level 1. They reverse direction when they reach a wall or a ledge (detected via edge feelers). Touching a worm costs the player one life and triggers a brief invincibility period. Worms can be destroyed by fireballs, with a 30% chance to drop a heart pickup that restores one life.
* Game Over Screen
	When all lives are lost, a semi-transparent red overlay appears with a "Game Over!" message. Music stops and a game over sound effect plays. The player can press Enter to return to the main menu.


## Known Bugs

* Fireball may despawn immediately if spawned too close to a tile. This can occur when the player is standing directly against a wall and fires in the direction of the wall.

## Brief Overview of game 

Dino Handyman is a 2D side-scrolling platformer built in C++ using the SFML framework. The player controls a dinosaur character across two handcrafted levels, each with its own objective and challenges.
The player has access to a range of movement abilities: running, jumping, sprinting with a short dash, and throwing fireballs at enemies. The game can be paused at any time on any level via the Escape key, which overlays the current frame with a pause menu.
In Level 1, the player must traverse a wide map to reach a lever at the far right end of the level and activate it. After that, they must return to the starting flags and interact with them to complete the level. The level features worm enemies that patrol platforms and can be defeated using fireballs. The player has three lives displayed as heart icons in the HUD. Lives are lost by touching worm enemies and can be restored by collecting heart pickups that worms occasionally drop on death. If all lives are lost, a Game Over screen appears.
In Level 2, the player must explore the level to find a hidden breakable block, strike it from below to release a coin, and collect the coin to unlock the double jump ability. This ability is then required to navigate the rest of the level and reach the goal.

## Must Have Features

* Pause Menu: A functional in-game pause screen accessible via Escape, with Resume and Main Menu options. (Implemented.)
* Lives System: A health/lives system displayed via heart icons in the HUD, serving as the primary lose condition. (Implemented.)

## Should Have Features

* Worm Enemies: Animated enemies that patrol platforms, detect ledges, and interact with the player and fireballs. (Implemented.)
* Fireball Attack: A projectile the player can fire to defeat enemies, with a cooldown and directional animation. (Implemented.)


## Could Have Features

* Game Over Screen: A dedicated overlay displayed when all lives are lost, with audio feedback and a return to menu option. (Implemented.)
* Heart Pickups: Hearts dropped by defeated enemies that restore one life when collected. (Implemented.)


## Wish to Have Features

* Smooth camera with lookahead: A lerp-interpolated camera that leads the player in the direction of movement. (Implemented as part of the movement rework.)
* Multiple enemy types: Additional enemy varieties beyond the worm. (Not implemented.)
* Coyote Time: The platforming will be enhanced by coyote time, a grace period during which the player can still jump even if they are not on a platform.(Not Implemented)
