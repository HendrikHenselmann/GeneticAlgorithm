
# GeneticAlgorithm

This is an implementation of a Genetic Algorithm framework using the programming language C.

Our implementation is designed for single-objective optimization only.

It was created for the sake of learning.

This project was developed on MacOS and was not tested on other platforms.

---

# Notation and custom types

## Individual

One solution instance of a problem is encoded as a vector of booleans and is called an individual, also known as a chromosome. If you want to encode numbers you have to use multiple booleans to do so. Such a set of booleans, encoding one piece of information (eg. one number), is called a gene. All your genes have to be of the same size, eg. an individual can consist of 3 genes of length 2 each. This individual is of size 3\*2 = 6 because it consists of 6 booleans in total.

Implementation:
```
typedef bool *Individual_t;
```

## Population

The set of individuals at timestep t is called the population. The population size does not change during the execution of the Genetic Algorithm. A population at timestep t is also called a generation. All the individuals of a population have to be of the same size, the same amount of genes and those genes have to be of same size too.

Implementation:
```
typedef struct Population_ {
    size_t populationSize;
    size_t individualSize;
    Individual_t *array;
} *Population_t;
```

---

# Getting Started

Download this repository and make sure that you do not change the project structure.

Make sure that you have installed the build automation tool `make`.

Start the terminal of your machine and navigate to the root folder of this project.


The following make instructions are available..

- `make compile` : Compiling the source code of the project.
- `make exec` : Running the Main file. Therefore compiling the source code of the project, if not already compiled.

- `make clean` : Deleting all intermediate files of the compile step. Not deleting executable binaries and program execution logs.
- `make reset` : Resetting the whole project folder to its initial state after download.

- `make compileTests` : Compiling the code that can be executed afterwards to run some test cases.
- `make test` : Running the compiled tests. Therefore compiling test cases, if not already compiled.

The executable file `main` is located in `GeneticAlgorithm > bin` after you have called `make compile`. You can run the program with the "-h" option (or "--help") to show the available command line arguments. The table below shows a list of the currently available arguments. Please note that, at the moment, these are just positional arguments, which means that you have to specify the first 3 arguments even if you only want to change the mutation rate.

| Argument  | Default | Description |
| ------------- | ------------- | ------------- |
| Number of evolutions  | 1000  | How many times the evolution step is applied (Selection, Crossover, Mutation) |
| Population size | 20  | How many individuals are part of the population. Not changing with evolution. |
| Mutation rate | 0.1  | How likely it is that one bool of an individual is flipped. |
| Elitism ratio | 0.2  | Elitism ratio is the percentage of individuals that will be copied to the next generation without being manipulated. |
| Active gene rate | 0.5  | The probability of true booleans at random initialization of individuals. |
| Verbosity level | 0 | The amount of text that is displayed at execution. 0: Progress bar only 1: Additionally, the fitness of fittest individual 1: Additionally, the average fitness of elitists |


---

# Creating your own `Environment_t`

You can define your own environment to be solved with the provided Genetic Algorithm framework by following the steps below:

First, create a header file in `GeneticAlgorithm > include`. Try to use conventional naming, eg. EightQueens.h in camel case for the eight queens problem. You can copy the content of another environment header file, eg. the eightQueens.h, and replace the occurrence of "eightQueens" with the name of your problem.

Second, create a source file in `GeneticAlgorithm > src > Environments`. Try to use conventional naming, eg. EightQueens.c in camel case for the eight queens problem. Define the `Environment_t` that you declared in your header file at step 1. Therefore the following struct member variables have to be defined:

- `size_t individualSize` : The total number of booleans that encode a solution ("individual")
- `size_t geneLength` : The number of booleans that encode one gene of an individual

Furthermore, the following struct member functions have to be defined:

- `void displayProblem (void)` : Display a short description of the problem at hand.
- `void displayIndividual (Individual_t individual)` : Display the interpretation of an individual in the context of your problem.
- `float individualFitness (Individual_t individual)` : Calculate a fitness score that states the quality of the solution regarding your problem. Important note : Fitness scores have to be non-negative !!
- `void populationFitness (Population_t population, FitnessScores_t fitnessScores)` : Calculate fitness scores that state the quality of every individual in the population. Important notes : Fitness score i has to correspond to the individual i of the population. Fitness scores have to be non-negative !!

In the file `GeneticAlgorithm > src > Main.c`: Import your header at the top and then look for the line where     `Environment_t env` is defined. Just assign your newly created `Environment_t` to env. For example, `Environment_t env = eightQueensProblem;` in the case of the eight queens problem.

---

# Log files and Visualization

A crucial part of this framework is the function `runGeneticAlgorithm`, which runs the Genetic Algorithm with given parameters, as the name already suggests. That function is constantly writing performance metrics to log files.

This project contains a small python script, `visualizeLogs.py`. It can be executed in the project's root folder to generate visualizations of the log files mentioned above.

---

# Limitations and Improvement Ideas

As stated above, this framework is restricted to single-objective optimization.

Individual solutions are implemented as boolean vector. That is inefficient because a boolean is at least the size of one byte and to encode a gene with more than one boolean you have to use much more space than needed. A better way to implement this would be to use integers instead and work with the bits of the integer.

An `Environment_t` represents a problem instance as opposed to a class of problems.

The execution speed could be improved by parallelization, using OpenMP for example. But this would require some extra work to maintain portability. This could be achieved using Docker.

---

## Project structure
According to [this post.](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/)
