# Project Structure
*Last updated: 2026-04-02*

## Architecture
Upper classes own and manage their children, lower classes never
reach upward and create objects above them.
```
Engine
├── World
│   ├── Camera
│   ├── PhysicsWorld
│   │   ├── RigidBody (player, enemies, objects)
│   │   └── RigidBody (static ground, platforms)
│   ├── Player
│   │   └── RigidBody
│   └── ParallaxBackground
│       ├── Background
│       └── RigidBody (static ground colliders)
└── InputHandler
```

## What each class does
**Engine** — runs the game loop, owns World

**World** — manages all game objects, wires Player and PhysicsWorld together

**Camera** — manages game view and deadzone following

**PhysicsWorld** — owns list of RigidBody pointers, runs gravity, collision detection and resolution every frame

**Player** — handles input, movement, animation state machine, owns a RigidBody

**InputHandler** — keyboard and mouse input, focus-aware

**ParallaxBackground** — manages background layers, owns static ground RigidBodies

**Background** — single background image layer with parallax speed

**RigidBody** — velocity, gravity scale, grounded state, owns a Collider

**Collider** — FloatRect bounds, ColliderType, ColliderTag, debug draw

## Collider Types
**STATIC** — never moves, platforms and ground owned by ParallaxBackground

**KINEMATIC** — moves by input, not fully simulated, reserved for player later

**DYNAMIC** — fully simulated by PhysicsWorld, player and enemies currently

## Collider Tags
**PLAYER** — player body

**PLATFORM** — ground and platform colliders

**ENEMY** — enemy body (not yet implemented)

**PLAYER_SWORD** — player attack hitbox (not yet implemented)

**ENEMY_SWORD** — enemy attack hitbox (not yet implemented)