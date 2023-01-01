
# GeneticAlgorithm

An implementation of a Genetic Algorithm framework using the programming language C.

Written for the sake of learning.

---

# Getting Started

Download this repository and make sure that you do not change the project structure.

Make sure that you have installed the build automation tool `make`.

Start the terminal of your maschine and navigate to the root folder of this project.


The following make instructions are available..

- `make compile` : Compiling the source code of the project.
- `make exec` : Running the Main file. Therefore compiling the source code of the project, if not already compiled.

- `make clean` : Deleting all intermediate files of the compile step. Not deleting executable binaries and program execution logs.
- `make reset` : Resetting the whole project folder to its initial state after download.

- `make compileTests` : Compiling the code that can be executed afterwards to run some test cases.
- `make test` : Running the compiled tests. Therefore compiling test cases, if not already compiled.

---

# Environment

The fitness function provided by an `Environment_t` can not yield positive values.

---

The code could be speed up by parallelization, using OpenMP for example. But this would require some extra work to maintain portability. This could be achieved using Docker.

---

## Project structure
According to [this post.](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)
