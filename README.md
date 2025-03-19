# **Pick Up Sticks**

## **Authors**

Idit Halevi

If you have any questions or encounter any issues with this project, feel free to contact me at [idit8886@gmail.com](mailto\:idit8886@gmail.com).

## **Gameplay Video**

### Watch Pick Up Sticks in Action
[![Pick Up Sticks Gameplay](https://img.youtube.com/vi/VH_MNT_RC6k/0.jpg)](https://youtu.be/VH_MNT_RC6k)  


## **About the Game**

**Pick Up Sticks** is a digital version of the classic game, developed using **SFML** and **STL**. The goal is simple: carefully remove sticks from a scattered pile without disturbing others. Players must strategize to maximize their score within a limited time.

### **Key Features:**

- **Dynamic Scoring** – Each stick's value depends on its color (ranging from 1 to 5 points).
- **Time-Limited Gameplay** – The time limit is three times the number of sticks in the game.
- **Randomized Stick Placement** – Each game session generates a new board with sticks at different angles.
- **Visual Cues** – Players can see which sticks are free to pick up.
- **Save & Load System** – Resume gameplay from the last saved point.

## **Getting Started**

### **Prerequisites**

- Visual Studio ([Download](https://visualstudio.microsoft.com/))
- SFML library installed ([Installation Guide](https://www.sfml-dev.org/download/sfml/2.6.0/))

### **How to Run**

1. Clone the repository:
   ```bash
   git clone https://github.com/iditha/Pick-Up-Sticks-Game.git
   ```
2. Ensure **SFML** is installed and linked properly.
3. Build and run the project.

## **How to Play**

- **Click on a stick** to attempt picking it up.
- A stick can only be removed if no other sticks rest on top of it.
- The game ends when all sticks are removed or time runs out.
- The player’s score is based on the sticks collected.

## **Core Algorithms & Techniques**

### **1. Data Structures**

- **Stick Data Structures** – Each stick maintains two lists to manage blocking relationships efficiently:
  - `m_interruptingSticks` – Stores iterators to sticks that are blocking this stick.
  - `m_interruptedSticks` – Stores iterators to sticks that this stick is blocking.
  
  These lists allow for quick traversal and updates when checking whether a stick can be picked up.
  
  _For the exact implementation, refer to the Stick class in the source code [here](./include/Stick.h)._

- **List of Sticks** – Stores all the sticks currently on the board.
- **List of Free Sticks** – Keeps track of which sticks are available for picking.
- **Iterators** – Used to navigate through the lists efficiently.
- **STL-Style Containers** – The game leverages STL containers like `std::vector` and `std::list` for efficient data storage and management.

### **2. Collision & Blocking Detection**

- Each stick keeps track of **which sticks it is blocking** and **which sticks are blocking it** using iterators.
- Before picking up a stick, the game checks if it has no other sticks on top of it.
- **Line Segment Intersection Algorithm** ([GeeksforGeeks](https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/)) – Used to detect if two sticks are overlapping and determine whether a stick is blocked.

### **3. STL Algorithms**

- The game makes use of **STL algorithms** such as iterator-based traversal and standard library functions to efficiently process stick interactions, game state updates, and board management.

### **4. Game State Management**

- **Singleton Pattern** – Used in `Resources` to manage textures, fonts, and game assets efficiently.
- **Save & Load System** – Saves game state (time, score, remaining sticks) and reloads it when needed.

### **5. Object-Oriented Design**

- **`Controller`** – Manages game flow, calling board updates and menu interactions.
- **`Board`** – Handles stick placement, collision detection, and game logic.
- **`Stick`** – Represents an individual stick, storing its position, angle, and interactions.
- **`Menu`** – Manages the game’s **main menu**, allowing players to start a new game, load a saved game, or exit.
- **`Toolbar`** – Displays game status (time, score, remaining sticks).
- **Exception Handling** – Custom error classes (`FileError`, `SaveFileError`) handle save/load issues.

## **Customization**

- Stick colors: **Red, Blue, Green, Orange, Yellow** (Each with a unique score value).
- Game duration is calculated dynamically based on the number of sticks.
- Stick positions are randomized at the start of each session.

## **Acknowledgments**

Special thanks to instructors and peers for their guidance in developing this project.

