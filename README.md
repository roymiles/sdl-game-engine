# Game-project

[Game programming pattern](http://gameprogrammingpatterns.com/component.html)

All game objects (entities) should inherit from GameObject. This is a class that outlines 2 functions that must be overridden.
Namely, the setup() and update() methods.

The main function will call setup() on all entities before the main loop and then proceed to call update() on every entity for every frame.

Each entity can have instances of components, these are useful classes that decouple logic in the program. For example, the player class can have a PhysicsComponent which states that it can interact with other physical objects.
