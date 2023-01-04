
# GeneticAlgorithm

This is an implementation of a Genetic Algorithm framework using the programming language C.

Our implementation is designed for single-objective optimization only.

It was created for the sake of learning.

This project was developed on MacOS and was not tested on other platforms.

---

# Notation and corresponding custom types

TODO

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

The executable file `main` is located in `GeneticAlgorithm > bin` after you have called `make compile`. You can run the program with the "-h" option (or "--help") to show the available command line arguments. The table below shows a list of the currently available arguments. Please note that, at the moment, these are just positional argument, which means that you have to specify the first 3 arguments even if you only want to change the mutation rate.

| Argument  | Default |
| ------------- | ------------- |
| Number of evolutions  | 1000  |
| Population size | 20  |
| Mutation rate | 0.1  |
| Elitism ratio | 0.2  |
| Active gene rate at initialization | 0.5  |
| Verbosity level | 0  |


---

# Creating your own `Environment_t`

You can define your own environment to be solved with the provided Genetic Algorithm framework by following the steps below:

At first, create a header file in `GeneticAlgorithm > include`. Try to use conventional naming, eg. EightQueens.h in camel case for the eight queens problem. You can copy the content of another environment header file, eg. the eightQueens.h, and replace the occurrence of "eightQueens" by the name of your problem.

Second, create a source file in `GeneticAlgorithm > src > Environments`. Try to use conventional naming, eg. EightQueens.c in camel case for the eight queens problem. Define the `Environment_t` that you declared in your header file at step 1. Therefore the following struct member variables have to be defined:

- `size_t individualSize` : The total number of booleans that encode a solution ("individual")
- `size_t geneLength` : The number of booleans that encode one gene of an individual

Furthermore the following struct member functions have to be defined:

- `void displayProblem (void)` : Display a short description of the problem at hand.
- `void displayIndividual (Individual_t individual)` : Display the interpretation of an individual in the context of your problem.
- `float individualFitness (Individual_t individual)` : Calculate a fitness score that states the quality of the solution regarding your problem. Important note : Fitness scores have to be non-negative !!
- `void populationFitness (Population_t population, FitnessScores_t fitnessScores)` : Calculate fitness scores that state the quality of every individual of the population. Important notes : Fitness score i has to corrspond to individual i of the population. Fitness scores have to be non-negative !!

In the file `GeneticAlgorithm > src > Main.c`: Import your header at the top and then look for the line where     `Environment_t env` is defined. Just assign your newly created `Environment_t` to env. For example, `Environment_t env = eightQueensProblem;` in case of the eight queens problem.

---

# Log files and Visualization

A cruicial part of this framework is the function `runGeneticAlgorithm`, which is running the Genetic Algorithm with given parameters, as the name already suggests. That function is constantly writing performance metrics to log files.

This project contains a small python script, `visualizeLogs.py`. It can be executed at the projects root folder to generate visualizations of the log files mentioned above.

---

# Limitations and Improvement Ideas

As stated above, this framework is restricted to single-objective optimization.

The code could be speed up by parallelization, using OpenMP for example. But this would require some extra work to maintain portability. This could be achieved using Docker.

---

## Project structure
According to [this post.](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)
