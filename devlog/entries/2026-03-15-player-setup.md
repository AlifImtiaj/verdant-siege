# Devlog #02 — Player & Animation

## What I worked on
Today i was supposed to work on `sf::View` and fix the background movement, 
but i got distracted and ended up building the player instead
still haven't touched the `sf::View` problem, its sitting in the backlog.

## What I implemented
**Player**

Set up the player class with texture and sprite. all the assets are from itch io
in this current version player doesn't actually move across the screen
the background images move in the opposite direction to fake movement. 
the illusion is doing good job

**Player Animation**

Set up three animation states — idle, walking and attacking.
used `sf::Sprite::setTextureRect()` to cut out portions of the spritesheet 
and cycle through them frame by frame. each frame is 100x100px on the sheet.
```
Idle      --> cycles through idle spritesheet
Walking   --> plays when horizontal input detected  
Attacking --> plays on mouse click, locks other states until finished
```

## Problems I ran into
**Sprite flipping not working**

when the player moved left, i was just negating the X scale with `setScale()` to flip the sprite.
it was flipping, but the sprite was jumping sideways instead of flipping in place.

**Attack animation not playing**

click to attack, nothing happens — just keeps playing idle or walking.
took me a bit to figure out why.

**Attacking and Walking was possible on unfocused window**

attack animation was playing even when clicking outside the game window,
clicking on desktop, browser, anything would trigger it.
same with the walking animations and the parallax effect

## How I solved them
**Sprite flipping**

the issue was the origin was at top-left corner `(0,0)` by default.
so when i was negating the X scale it mirrors from that corner and shifts the whole sprite.
fix was just setting the origin to the center of the frame:
```cpp
_playerSprite.setOrigin({50.f, 50.f});
```
now it flips perfectly in place.

**Attack animation**

the bug was in `Update()` — every single frame this runs first:
```cpp
if (inputHandler.GetAxis().horizontal != 0) _playerState = PlayerState::WALKING;
else _playerState = PlayerState::IDLE;

if (inputHandler.GetMouseEvent().mouseDown && _playerState != PlayerState::ATTACKING) {
    _playerState = PlayerState::ATTACKING;
}
```

so even if i set `_playerState = PlayerState::ATTACKING`, 
next frame the first block immediately overwrites it back to IDLE or WALKING.
attack state was getting killed before `PlayAnimation()` ever saw it.

fix was to guard the movement block:
```cpp
if (_playerState != PlayerState::ATTACKING) {
    if (inputHandler.GetAxis().horizontal != 0) _playerState = PlayerState::WALKING;
    else _playerState = PlayerState::IDLE;
}

if (inputHandler.GetMouseEvent().mouseDown && _playerState != PlayerState::ATTACKING) {
    _playerState = PlayerState::ATTACKING;
}
```

now the movement block is skipped entirely while attacking,
attack plays through all its keyframes and resets itself when done.

**Animation outside game window**

`sf::Mouse::isButtonPressed()` is a global system call, it doesn't care 
about window focus at all. same goes for `sf::Keyboard::isKeyPressed()`.

fix was just checking `window.hasFocus()` at the top of `InputHandler::Update()` 
and returning early if the window isn't focused. resets all input state too so 
nothing gets stuck.

## What's next
- Get `sf::View` working properly with the background
- Player needs to actually move across the screen, right now its all faked
- this probably means a decent restructure of how the background and camera talk to each other

## Screenshots / GIFs
<img src="../images/2026-03-15-player-idle.gif" width="400"/>

*Idle Animation*

<img src="../images/2026-03-15-player-walking.gif" width="400"/>

*Walking Animation*

<img src="../images/2026-03-15-player-attacking.gif" width="400"/>

*Attack Animation*
