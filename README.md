# so_long

Welcome to **so_long**, a 2D game developed using the [MLX42](https://github.com/codam-coding-college/MLX42) graphics library. The objective of the game is to guide the player through a maze, collecting items and reaching the exit. The game is based on a `.ber` map file that defines the layout of the game world.

---

## Table of Contents

- [Features](#features)
- [Requirements](#requirements)
- [Installation](#installation)
- [How to Run](#how-to-run)
- [Gameplay Instructions](#gameplay-instructions)
- [File Structure](#file-structure)
- [Example Maps](#example-maps)
- [Development Notes](#development-notes)
- [Game Interface](#game-interface)

---

## Features

- Supports customizable maps defined in `.ber` files.
- Map validation ensures proper structure and playability.
- Collect items to unlock the exit and win the game.
- Tracks and displays the number of moves made by the player.
- Handles errors gracefully with meaningful messages.
- Dynamic screen size validation to ensure the map fits on the monitor.

---

## Requirements

- **Operating System**: Linux or macOS (Windows is not officially supported).
- **Graphics Library**: [MLX42](https://github.com/codam-coding-college/MLX42).
- **Compiler**: GCC or Clang with C99 support.
- **Libraries**: 
  - OpenGL
  - `libft` (included in the project).

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/Oshintha/so_long.git
   ```
  ```bash
  cd so_long
  ```
   
2. Build the project:
   
  ```bash
  make
  ```

## How to Run

Run the game with a .ber map file:
```bash
./so_long path/to/map_file.ber
```

Example:
```bash
./so_long maps/example_map.ber
```

Controls:

W / ↑: Move up
A / ←: Move left
S / ↓: Move down
D / →: Move right
ESC: Quit the game

## Gameplay Instructions

Objective: Collect all the collectibles (C) and reach the exit (E).
The map is made up of the following tiles:
1: Wall
0: Empty space
P: Player's starting position
C: Collectible
E: Exit
The game ends when the player collects all the items and exits the map.

## File Structure

![Screenshot from 2025-01-27 14-46-43](https://github.com/user-attachments/assets/2094504c-e505-4b15-8218-b7d57200d1c9)

## Example Maps
Valid Map Example (maps/example_map.ber):
11111
1P0C1
10001
1C0E1
11111

Invalid Map Example (maps/invalid_map.ber):
11111
1P001
1000C
1E001
11111
This map is invalid because the exit (E) is inaccessible.

## Development Notes
Key Challenges
Flood Fill Algorithm: Implemented to validate that all collectibles and the exit are accessible from the player's starting position.
Dynamic Screen Validation: Ensured the map fits within the screen dimensions using mlx_get_monitor_size.
Potential Enhancements
Add animations for collectibles and player movement.
Introduce new tile types, such as enemies or traps.
Implement a scoring system based on the number of moves.

## Game Interface
Below are screenshots of the game interface for so_long:

![Screenshot from 2025-01-27 14-40-35](https://github.com/user-attachments/assets/b95f52fe-fef4-4590-9e4a-1fcba73128a9)
![Screenshot from 2025-01-27 14-42-07](https://github.com/user-attachments/assets/9e54b316-dcde-4f0d-abe3-dcb60ddf09fb)


