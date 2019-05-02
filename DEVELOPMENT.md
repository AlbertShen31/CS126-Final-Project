# Week 1

## Testing Libraries

### ofxBox2d Library
* Messed around with the physics engine through creating different box2d objects
* Create movement of objects on key click


# Week 2

## Building the Car

### Wheels
* Created custom wheel class
* Allow user to rotate wheel using keys
* Fixed wheel's relative position using joint

### Car Body
* Created rectangle shape for car body
* Used wheel joints to fix car body position

# Week 3

## World Generation

### Created Hills
* Experimented with various methods to create smooth terrain

## Camera Tracking

### Fixate Axis
* Shift objects based on car's position on screen
* Appears as if Car is stuck in place
* Other objects fail to redraw positions

## Refactoring

### Restructured Code
* Put Car Body, Wheel, and Car into own separate class
* Separation of important values into various properties and constants of each class

# Week 4

## World Generation

### Bezier Curves
* Create Bezier Curves for Hilly Terain
* Reset Map when move past right edge of screen to continue Terrain
* Lose when move past left edge


## Menu

### Settings

### Resetting game
* Able to reset the terrain with car position
