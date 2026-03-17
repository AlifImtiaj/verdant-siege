# Project Structure
*Last updated: 2026-03-17*

## Architecture
upper classes own and manage their children, lower classes never 
reach upward and create objects above them.

```
Engine
├── World
│   ├── Camera
│   ├── Player
│   └── ParallaxBackground
│       └── Background
└── Input Handler
```

## What each class does
**Engine** — runs the game loop, owns World</br>
**World** — manages all game objects</br>
**Camera** - manages game view</br>
**Player** — handles movement, animation, state</br>
**InputHandler** — keyboard and mouse input</br>
**ParallaxBackground** — manages background layers</br>
**Background** — single background image layer</br>