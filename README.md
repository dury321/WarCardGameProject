# War Card Game

## Overview
This project is a **C++ implementation** of the Russian variant of the card game **War**. The game follows traditional War mechanics with additional logic to handle edge cases such as recursion during War rounds, sudden death rules, and automatic deck handling for both the player and the computer.

Developed in **Visual Studio**, it makes use of **polymorphism**, **operator overloading**, and **encapsulation**.

## Features
### Object-Oriented Design
- **Encapsulation** ensures that game elements are modular and maintainable.
- **Polymorphism** is leveraged in card comparison operations and deck handling, enabling flexible extensibility.
- **Operator Overloading** allows intuitive comparison of card objects (`<`, `>`, `==`), improving readability and maintainability of game logic.

### Deck Management
- Creates, shuffles, and distributes a deck of **52 cards** using an encapsulated deck class.
- Implements **deep copy semantics** to manage card ownership cleanly.

### Stack-Based Gameplay
- Uses **linked-list based stacks** to manage player hands, table cards, and winning piles, ensuring efficient push/pop operations.
- **Smart pointers** are used where applicable to ensure memory safety and avoid leaks.

### Game Logic
- **Automatic card comparison and transfers** handled through encapsulated class operations.
- **Recursive War resolution** using controlled recursion and a structured call stack to manage extended rounds efficiently.
- **Handles empty hands and winning stack transfers** with a self-sufficient stack structure.
- **Virtual functions** ensure extensibility for future rule variations or game modifications.

### User Interaction
- **Manual or automatic gameplay modes** with a structured game loop.
- **In-game user menu** with options to play manually, autoplay, or exit.
- **Formatted output system** to maintain structured console logs.

### Console-Based UI
- **Displays the current state of the game**.
- **Includes special handling for Windows 11 Unicode issues with card suits**.
- **Custom stream operators** allow for cleaner and more expressive output formatting.

## File Structure
### Core Components
- **`MainDriver.cpp`** - Entry point that initializes and runs the game.
- **`GameClass.h/cpp`** - Implements a game controller managing game flow, rounds, and recursion handling using an **abstracted game state model**.
- **`DeckClass.h/cpp`** - Manages the creation, shuffling, and distribution of the deck using a class-based approach with **proper resource management**.
- **`CardClass.h/cpp`** - Defines the card structure, including **operator overloading** for comparison and **stream insertion** for easy logging.
- **`StackClass.h/cpp`** - Implements a **linked-list based stack**, supporting efficient memory allocation and providing a **RAII-compliant destructor** for safe memory cleanup.

### Utility Components
- **`OutputClass.h/cpp`** - Provides formatted output utilities, leveraging encapsulated methods for standardized UI.
- **`Standards.h`** - Contains global constants and enums, ensuring modular and maintainable code.

## Edge Cases Handled
### Recursive Wars
- The game correctly handles **consecutive Wars** by continuing until a winner is determined using controlled recursion and backtracking strategies.

### Sudden Death
- If a player **runs out of cards during a War**, the last card is compared to decide the winner using a structured fallback condition.

### Efficient Memory Management
- Uses **RAII principles** to prevent memory leaks.
- **Destructor chaining** ensures that all dynamically allocated objects are properly cleaned up.

### Windows 11 Unicode Fixes
- **Card suits are displayed properly** despite known console rendering issues, ensuring smooth user experience across platforms.

## Author
Developed by **Christian Dury**.
