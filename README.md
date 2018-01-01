# maze-generators
Mazes can be automatically created thanks to algorithms.

There are two main types of mazes:
- simply connected (or perfect) mazes
- imperfect mazes

In a perfect maze, for a given starting point and a given ending point, there is only one way to go from the starting point to the ending point. In an imperfect maze there are several ways to do so as it contains some loops (whereas the perfect mazes don't).
In this repository we'll only focus on perfect mazes. Generating an imperfect maze is similar to generating a perfect maze and then breaking some walls.

## Algorithm

There are a lot of algorithms in order to build a 2D maze. We'll implement one of them.

### Terminology

A maze is a rectangular grid of dimensions `m` and `n`, it contains `m * n` cells. Each cell have between 0 and 3 walls (indeed, having 4 walls is not possible otherwise the cell is not reachable). There are 4 directions for the walls: north wall, south wall, west wall, east wall.
In order not to use too many resources for no reason, we'll only memorize the north wall and the west wall for a given cell. Indeed, its south wall is actually the same as the cell on its south's north wall.

### Illustration

The following maze is a perfect maze of dimensions `3 * 4`
```
+---+---+---+---+
|       |       |
+---+   +   +---+
|       |   |   |
+   +   +   +   +
|   |           |
+---+---+---+---+
```

### Steps of the algorithm

```
Close all walls (every cell has 4 walls) and associate a unique value to each cell (the ID)
Pick a wall to break in a random way (once a wall is broken between two cells, the cells become connected)
Everytime we try to break a wall, we check that the potentially future cells currently have different IDS
  If the IDs are identical then it means that both cells are already connected somehow hence we can't break the wall
  If the IDs are different then it means we can break the wall and assign the ID of the first cell to all cells that currently contain the ID of the second cell
We can stop this process once the number of broken walls reached (m * n - 1) (i.e. the total number of cells minus 1)
```

