# Exam: "Introduction to Software Development"
## Instructions for Building the Project

### Specifications and How to Run the Program
- **Written using:** XCODE / Clang (AppleClang 12.0.5.12050022) / Qt5.12.11
- **Processor:** Apple M1 Arm64 -> QT with Rosetta, everything else native

### How to Get the Project Running
1. Run the following command:
    ```sh
    cmake CMakeLists.txt -B "Your desired output directory" -DCMAKE_OSX_ARCHITECTURES=x86_64
    ```
   > **Note:** `-DCMAKE_OSX_ARCHITECTURES=x86_64` is only needed when building on an ARM64 architecture. Normally, this flag can be omitted.

2. Then, execute:
    ```sh
    make (in the specified directory)
    ```

3. Copy the contents of the `copyme` folder into the same directory.

4. The program can be started. In my case, it only worked through the terminal because otherwise the maps from the `copyme` folder would not function correctly.

## Notes to the Reviewers

### Controls 
#### Menu
- **Keys to select level:** 1 - 4
- **Key to exit the game:** e

#### Regular Gameplay
- **Character movement:** Arrow keys
- **Switch monster:** Numbers for a specific monster

#### Battle Mode
- **Switch monster:** p
- **Continue dialogue:** a
- **Attack:** 1
- **Heal:** 2
- **Flee:** 3
- **Special attack:** s

#### Monster Catching
- **Catch:** 1
- **Flee:** 2

#### End Screen
- **Return to menu:** a

### Unicode Symbols
(From the sample solution)

- **Protagonist:** `QString::fromUtf8("\xF0\x9F\x98\x83")`
- **Forest/Wild Monster Field:** `QString::fromUtf8("\xF0\x9F\x8C\xB2")`
- **Opponent:** `QString::fromUtf8("\xF0\x9F\x98\x92")`
- **Monster Center/Healing:** `QString::fromUtf8("\xF0\x9F\xA4\x8E")`
- **Monster Gym/Muscle Symbol:** `QString::fromUtf8("\xF0\x9F\x92\xAA")`
- **Wall:** `QString("\u2591")`
- **Exit:** `QString("\u27A5")`
- **Bonus (created by me):** `QString("\u2B50")`

### Additional Information

- At the time of submission, the program runs without errors on the system described above.

- When a monster is defeated in the game, it dies and cannot be revived. However, this frees up a slot in the monster inventory, allowing the player to catch a new one.
To prove that this was an intentional design decision, I will briefly explain how it could have been done differently. Instead of removing the monster from the vector, we could have kept the monster in the vector and added a variable to indicate whether the monster is alive (a `bool`). This would have allowed us to show that the monster is not available in the monster list and to disable the respective button. In the heal method, we could reset all monsters to alive.
I found it more reasonable to generate new monsters in each level, treating each level as a fresh start, which made reviving defeated monsters unnecessarily easy.

### Extras 
- There are 5 different possible monsters that can appear:

1. **Fish** | 1 HP | 1 AP
2. **OverPower** | 50 HP | 50 AP
3. **Tanki** | 50 HP | 3 AP
4. **SuperStrong** | 5 HP | 10 AP

> Currently, all probabilities are equal. For the game to make more sense, it should be extremely unlikely to find the OverPower monster. However, I left the probabilities equal so that players could find and test all monsters.

- You can train your monster during a battle. This reduces the maximum HP by 5 and increases AP by 2.
> **Reason:** Training your monster during a fight makes it stronger but also distracts it, causing permanent damage.

### Score System
- Each monster that dies: -5 points
- Each monster caught: +5 points
- Reaching the goal: +50 points
- Bonus points: +20 points (I added a new block that appears 3 times on the advanced map)
- Winning a battle: +20 points
- Dying: -50 points

### Menu
- At the start, you can choose which level to play.
- You can quit the game from the menu.
- On the end-screen (win or lose), you can return to the menu and start a new level.
- I added a new level to easily and quickly test all functions.
- An additional boss level was also added. The levels demonstrate that new levels can be integrated easily without many changes.
- It would be simple to add more maps.

### Special Attacks
- **SuperPigeon** can flee from any battle, with a success rate of 100% instead of 80%.
- **OverPower** can weaken the opponent by reducing their AP by 2 (the opponent's AP cannot fall below 1).
- **SuperStrong** can steal 2 HP from the opponent and add it to its own HP. However, its maximum HP cannot be exceeded, and the opponent cannot be killed by this attack (HP cannot drop below 1).

> After each special attack, the opponent still gets a chance to attack.

### Architecture
In the following, I will describe the architecture of my program.

#### Responsibilities of the Gui Class
The Gui class handles everything related to display and input. I chose this approach to keep the game logic as separated from the user interface as possible. In the `onRefresh` method, it constantly checks which phase of the game the player is in at any given time (one of the battle phases, normal state, whether a monster has been found, or if the game has been won or lost, etc.). The display and the available key presses are determined based on this status. Additionally, a specific amount of time is always waited to prevent the player from moving too quickly. This wait time can be adjusted as needed.

The Gui class has a game object that manages the game logic. When a key is pressed, the corresponding method in the game logic is invoked. For example, when the "up arrow" key is pressed in normal mode, the `movePlayer` method is called with the parameter "up" through the game object. In certain cases, a new phase must also be initiated directly. For instance, during dialogue in a battle, only a key press is awaited, and no game logic is processed.

The game object is created whenever a level is selected, and the constructor of the game receives the selected level as a parameter.

#### Responsibilities of the Game Class
This class takes care of all the "background logic." The constructor also reads the corresponding map. The `movePlayer` method is invoked whenever the player needs to move in a specific direction. This direction is passed as a parameter to the method when called. The method checks what type of field the player is currently on and calls the appropriate methods accordingly. These methods can change phases, heal the monster, etc. When the player encounters an opponent, the `fight` method is called, which executes all battle-related game logic.

Furthermore, the Game class contains all other essential objects and variables, such as the player object. This object holds the player's monsters and the active monster, which is continuously displayed by the Gui.

## Sources
- [Line-by-Line Reading in C and C++](https://im-coder.com/zeile-fuer-zeile-lesen-in-c-und-c.html) -> How to read a complete line in C++
- [Unicode Table for Bonus Star](https://unicode-table.com/de/search/?q=stern) -> Unicode code for the bonus star
- [C++ Documentation on Time Integration](https://www.cplusplus.com/reference/chrono/) -> How to properly integrate time (documentation)
- [Why Not Just Use random_device](https://stackoverflow.com/questions/39288595/why-not-just-use-random-device) -> Why you shouldn't just use `random_device`
- [Program Termination in C++](https://docs.microsoft.com/de-de/cpp/cpp/program-termination?view=msvc-160) -> How to terminate a program

> All sources used are factual references.