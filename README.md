
# GeneticAlgorithm

This is an implementation of a Genetic Algorithm framework using the programming language C.

Our implementation is designed for single-objective optimization only.

It was created for the sake of learning.

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

# Log files and Visualization

A cruicial part of this framework is the function `runGeneticAlgorithm`, which is running the Genetic Algorithm with given parameters, as the name already suggests. That function is constantly writing performance metrics to log files.

This project contains a small python script, `visualizeLogs.py`. It can be executed at the projects root folder to generate visualizations of the log files mentioned above.

---

# Environment

You can define your own Environment to be solved with the proposed Genetic Algorithm framework.

The fitness function provided by an `Environment_t` can not yield positive values.

---

# Limitations and Improvement Ideas

As stated above, this framework is restricted to single-objective optimization.

The code could be speed up by parallelization, using OpenMP for example. But this would require some extra work to maintain portability. This could be achieved using Docker.

---

## Project structure
According to [this post.](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)
