# Game-project

[Game programming pattern](http://gameprogrammingpatterns.com/contents.html)

### The World
This is the instance of the entire game and acts as a container for all the entities.
```c++
World world;
```

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

A Component adds functionality to an Entity. For example, you can make add a RigidBody Component to make the object interact with the environment using the physics engine.

You may add/remove/get components to entities through the public methods defined in the entity class.

- `addComponent`
- `removeComponent`
- `getComponent`

