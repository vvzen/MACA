# README

Structure
---------
Every generative animation is contained inside one of the 4 main functions who are called by `draw()`. Each of the functions represents a different **scene**.

 This allowed my to encapsulate the logic of each different stage of the mapping into separate functions, so that each one is independent from the others.
When a scene is over, the relative function sets the checkpoint (a bool variable) for the next function to `true`, so that **I don't need to worry about how much time every function will take, I simply know that when one function ends it will call the next one**. If I did use the Scenes Manager, I'd have to hard code the duration of each scene inside it, so everytime I made some edits to a scene I would have to compute how much time it took and put that value inside the .json. 

The first function called is `VVSource::drawFlashingIntro()`, then `VVSource::drawMovingLines()`, `VVSource::drawFadingQuads()` and finally `VVSource::drawColouredLines()`.

Compiling
---------
The building process of this sketch was tested using the **make** system on OSX El Capitan 10.11.2 (15C50).
To build and run the app, type in terminal:
```make && make RunRelease```

Other infos
--------
There are also a `vv_math.h` and `vv_math.cpp` files, which contain a little function useful to know what should be the size of a square in order to evenly cover my fbo surface when repeated. 