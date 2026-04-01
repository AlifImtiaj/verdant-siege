# Verdant Siege

A 2D wave survival game built from scratch in C++ and SFML — enemies spawn in increasing difficulty waves, with powerups and frame-based animation system.

![Gameplay](devlog/images/2026-03-14-parallax-effect.gif)

## Features

- Parallax scrolling background with layered depth
- Frame-based sprite animation system (idle, walk, attack states)
- Wave survival gameplay with increasing difficulty
- Powerup system
- Built entirely from scratch in C++ with SFML

## Tech Stack

- **Language:** C++17
- **Graphics:** SFML 3.x
- **UI:** ImGui
- **Build System:** CMake 3.15+
- **IDE:** Visual Studio Code

## Project Structure
```
verdant-siege/
├── src/              # Source files (.cpp)
├── include/          # Header files (.h)
├── Resources/        # Game assets (sprites, textures)
├── vendor/
│   └── imgui/        # ImGui source (included)
│   └── sfml/         # SFML (not included, see setup below)
├── devlog/
│   ├── entries/      # Development log entries
│   └── images/       # GIFs and screenshots
├── CMakeLists.txt
└── main.cpp
```

## Getting Started

### Prerequisites

- CMake 3.15 or higher
- C++17 compatible compiler (MSVC, GCC, Clang)
- SFML 3.x

### Setting Up SFML

SFML is not included in this repository due to size.

1. Go to [sfml-dev.org/download](https://www.sfml-dev.org/download/)
2. Download the prebuilt package matching your compiler (MSVC, MinGW, etc.)
   - If no prebuilt matches your compiler, download the source and build it with CMake
3. Copy the following into `vendor/sfml/`:
```
vendor/
└── sfml/
    ├── include/     ← from SFML download
    └── lib/         ← from SFML download
```

4. Copy SFML `.dll` files (Windows) or `.so` files (Linux) into the same directory as your executable after building.

### Building
```bash
# Clone the repository
git clone https://github.com/Alifimtiaj/verdant-siege.git
cd verdant-siege

# Create build directory
mkdir build
cd build

# Generate build files for Release configuration
cmake .. -G "Visual Studio 15 2017" -A x64 -DCMAKE_BUILD_TYPE=Release

# Build the Release configuration
cmake --build . --config Release
```

### Running

The executable will be generated in one of these locations depending on your compiler and platform:

| Platform / Compiler | Executable Location |
|---|---|
| MSVC Debug | `build/Debug/Siege.exe` |
| MSVC Release | `build/Release/Siege.exe` |
| GCC / MinGW (Windows) | `build/Siege.exe` |
| GCC (Linux) | `build/Siege` |

**Windows — copy SFML `.dll` files from the SFML `bin/` folder into the same directory as the executable before running.**

**Linux — SFML shared libraries must be installed system-wide or placed next to the executable.**
```bash
# Windows (PowerShell)
./run.ps1

# Linux
./build/Siege
```

## Devlogs

Development progress documented in [/devlog/entries](/devlog/entries)

| Date | Entry |
|------|-------|
| 2026-03-14 | [Project Setup](/devlog/entries/2026-03-14-setup.md) |
| 2026-03-15 | [Player Setup](/devlog/entries/2026-03-15-player-setup.md) |
| 2026-03-17 | [Camera](/devlog/entries/2026-03-17-camera.md) |
| 2026-03-26 | [Dear ImGui](/devlog/entries/2026-03-24-ImGui.md)
| 2026-04-02 | [Physics System](/devlog/entries/2026-04-02-Physics-System-&-Ground-Collision.md)

## Assets

- Background assets - [Nature Landscapes Free Pixel Art](https://free-game-assets.itch.io/nature-landscapes-free-pixel-art) by [CraftPix](https://craftpix.net)
- Character sprites — [Tiny RPG Character Asset Pack v1.03](https://zerie.itch.io/tiny-rpg-character-asset-pack) by zerie

> Note: Asset files are not included in this repository. Download them from the links above and place them in the `Resources/` folder.

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.