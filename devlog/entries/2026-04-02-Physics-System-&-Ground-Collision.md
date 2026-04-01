# Devlog #05 — Physics System & Ground Collision

## What I worked on
The goal was to get proper physics working — gravity, ground collision, and jumping. No more hardcoded ground position or faked movement. Ended up also cleaning up the player code significantly while wiring everything together. The parallax background now owns static colliders for the ground so the physics system can detect them automatically.

## What I implemented
**Collider and RigidBody**

Two new classes form the base of the physics system. `Collider` wraps an `sf::FloatRect` with a type (`STATIC`, `KINEMATIC`, `DYNAMIC`) and a tag (`PLAYER`, `PLATFORM`, `ENEMY`, `PLAYER_SWORD`, `ENEMY_SWORD`). Tags are already set up for combat collision filtering later. `RigidBody` owns a `Collider` and adds velocity, gravity scale, and grounded state. `RigidBody::Update()` moves the collider position by velocity scaled by deltaTime each frame.

**PhysicsWorld**

Owns a list of `RigidBody` pointers and simulates them every frame. The update loop per body is: reset grounded, apply gravity, move by velocity, then check and resolve collision against all other registered bodies. Collision detection is standard AABB. Resolution finds the smallest overlap axis and pushes the body out. Landing on a static body from above zeros downward velocity and sets grounded to true. Static bodies are skipped entirely for gravity and movement.

**Ground Colliders in ParallaxBackground**

Rather than hardcoding a ground Y value, `ParallaxBackground` now owns a vector of `RigidBody` instances set as `STATIC` with `PLATFORM` tag, one per background tile. World registers these with `PhysicsWorld` at startup alongside the player body. This means ground collision works across the full scrollable world width automatically.

**Player Refactor**

Animation logic collapsed from three duplicated blocks into a single `PlayAnimation(texture, keyFrames)` function. State machine extracted into `ChangeState()`. `SetPosition()` handles syncing sprite to physics body every frame, offsetting by half the collider size so sprite center aligns with collider center. Movement now reads velocity from the RigidBody, updates only X from input, and lets physics own Y entirely.

## Problems I ran into
**Player sinking slowly into the ground**

Expected clean landing. Instead the player sank a few pixels per frame continuously even after landing.

**Jump not triggering**

`vel.y = -250` was being set correctly on Space press but the player never moved upward.

**Grounded state flickering every frame**

Console showed grounded alternating true and false every frame while standing still.

**Jump velocity getting killed before player moves**

Even after fixing the flickering, jump still didn't work when collision resolution ran before movement.

## How I solved them
**Player sinking**

Two separate causes. First, position wasn't being clamped to the ground surface on collision so floating point drift let the player sink slightly each frame. Second, `vel.y` was accumulating even while grounded because the grounded reset happened before collision ran, so gravity kept adding to it. Fixed by always clamping position on collision and only zeroing velocity when actually falling downward:

```cpp
if (bounds.position.y + bounds.size.y >= groundY) {
    rb->SetPosition({bounds.position.x, groundY - bounds.size.y});
    sf::Vector2f vel = rb->GetVelocity();
    if (vel.y > 0) {
        vel.y = 0.f;
        rb->SetVelocity(vel);
        rb->SetGrounded(true);
    }
}
```

**Grounded flickering**

`SetGrounded(false)` was inside the else branch of `CheckCollision`. One frame player was above ground, next frame slightly below due to gravity, alternating every frame. Fixed by resetting grounded only once at the top of the update loop, never inside `CheckCollision`.

**Jump getting killed**

Collision resolution was running before `rb->Update()` moved the player. On the frame Space was pressed, player still sat exactly on the ground, collision fired and zeroed `vel.y` before the player ever moved upward. Fixed by moving `rb->Update()` before the collision check so the player physically leaves the ground before collision runs:

```cpp
void PhysicsWorld::Update(const float& deltaTime) {
    for (RigidBody* bodyA : _rigidBodies) {
        bodyA->SetGrounded(false);
        ApplyGravity(bodyA, deltaTime);
        bodyA->Update(deltaTime);          // move first
        for (RigidBody* bodyB : _rigidBodies) {
            if (bodyA == bodyB) continue;
            if (CheckCollision(bodyA, bodyB))
                ResolveCollision(bodyA, bodyB);
        }
        bodyA->SetGrounded(grounded);
    }
}
```

## What's next
- [ ] Fix World::Update() physics and player order
- [ ] Enemy class and animations
- [ ] Multiple platform colliders beyond ground
- [ ] Dynamic vs dynamic collision for enemies
- [ ] Camera shake on landing

## Screenshots / GIFs

*Add GIF here*