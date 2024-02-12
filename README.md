# Grid

![image](https://github.com/doru434/Grid/assets/12116007/5fd14b4b-fadf-414d-a8be-1b2c3455657c)

My variation about grids that are used on varius of games genres like strategy, rpg, survival.
In early stages of development/ work in progress

The idea is to be able to have any kind of 2D grid of any size with the right interface to build on that. 
To achieve this, I gave up on actors / meshes / instanced static meshes and chose a mathematical representation to be able to create unlimited (to be honest, it's never unlimited, but its huge maximum value uint32 2^32 - 1 => 4,294,967,295 in one axis) grid sizes.

In order to visualize changes on them, I think there is a need to implement an additional system, which I called "PastedArea". This is a decal system that will create / track / destroy decals that will help visualize changes on the grid (e.g., selected area / locked tiles / available to build, etc.) This is currently in the conceptual/experimental stage.
In addition, it is possible that decals will not be enough and will need help with materials.
