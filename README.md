# Game-project

[Game programming pattern](http://gameprogrammingpatterns.com/contents.html)

### The World
This is the instance of the entire game and acts as a container for all the entities.
```c++
World world;
```

This class

### Entities

An entity is a game object (e.g. Player, Light source) and can be added to the world using ```createEntity```. 

```c++
World world;
// ... 
Entity entity = world.createEntity();
```
To remove an entity from the world use ```removeEntity```

```c++
world.removeEntity(entity);
```

### Components

A Component adds functionality to an Entity. Any object that has a ```RigidBody``` Component, can interact with the environment within the physics engine.

You may add/remove/get components to entities through the public methods defined in the entity class.

- `addComponent`
- `removeComponent`
- `getComponent`

More components such as ```Sprite``` and ```AudioSource``` can be added.

The physics engine can collect all entities that have RigidBody Components.
```c++
std::list<Entity> colliders = world.getEntitiesWithComponent<RigidBody>();
```

### Event Manager
The event manager has an update function that is called once per frame. This is responsible for polling the SDL_Events and dispatching callbacks to registered entities.

At the moment, when any event is triggered, the overriden ```eventTriggered(id)``` is called on each Entity (This is very heavy and so a solution where only registered entities have callbacks would be better)
