*This project has been created as part of the 42 curriculum by grhaddad.*
---

# Philosophers

### Description
Philosophers is a concurrency project from the 42 curriculum that explores the fundamentals of multithreading, synchronization, and shared resource management in C.

The project is based on the classic Dining Philosophers Problem, a well-known synchronization challenge in computer science.

A number of philosophers sit around a circular table.
Each philosopher alternates between:
- Eating
- Thinking
- Sleeping

To eat, a philosopher must pick up two forks — one on the left and one on the right.
Since forks are shared resources between neighbors, improper synchronization can lead to:

❌ Deadlocks

❌ Data races

❌ Starvation

The goal of this project is to design a robust, race-condition-free simulation where:
Each philosopher is implemented as a separate thread
Forks are protected using mutexes
No philosopher dies unless the simulation rules require it
Output logs are synchronized and formatted precisely
Memory is properly managed (no leaks)
No global variables are used
The simulation ends when:
A philosopher dies (fails to eat within time_to_die), or
All philosophers have eaten a required number of times (if specified)

🎯 Learning Objectives

Through this project, I developed a deeper understanding of:
Thread creation and lifecycle management (pthread_create, join, detach)
Mutexes and critical section protection
Avoiding deadlocks and starvation
Accurate time management using gettimeofday
Writing race-free concurrent programs
Designing monitor systems to detect philosopher death
Writing safe, leak-free C code under strict 42 Norm rules

---

# Instructions

### Compilation

The project must be compiled using cc with the required flags:
```shell
-Wall -Wextra -Werror
```

To compile the program:
```bash
make
```

This will generate the executable:
```bash
./philo
```

Available Makefile rules:
```bash
make		# Compile the project
make clean	# Remove object files
make fclean	# Remove object files and executable
make re		# Recompile everything
```
---

### Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philospher_must_eat]
```

### Arguments
- number_of_philosphers: Number of philosophers (also number of forks)
- time_to_die: Time (in ms) before a philosopher dies if they don't eat
- time_to_eat: Time (in ms) a philosopher spends eating
- time_to_sleep: Time (in ms) a philosopher spends sleeping
- number_of_times_each_philsopher_must_eat (optional): Simulation stops once all philosophers eat this many times

### Example

```bash
./philo 5 800 200 200
```
This means:
- 5 philosophers
- A philosopher dies if they don't eat withing 800ms
- Eating takes 200ms
- Sleeping takes 200ms
- simulation stops when one philosopher dies

Example with required meals:
```bash
./philo 5 800 200 200 7
```
The simulation stops once each philosopher has eaten at least 7 times

### Output format
The program logs state changes in the following format:
```bash
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
Where:
- timestamp_in_ms → time since simulation start (in ms)
- X → philosopher number
* Messages do not overlap
* Death is printed within 10ms of detection
* No data races
---

# Resources
### Learning materials used
- Dining philosophers explanation (Youtube)
<a href="https://www.youtube.com/watch?v=zOpzGHwJ3MU"></a>
- 42 Cursus guide - Philosopher
<a href="https://42-cursus.gitbook.io/guide/3-rank-03/philosophers"></a>
- Threads & Concurrency explanation (Youtube)
<a href="https://www.youtube.com/watch?v=uA8X5zNOGw8"></a>

### Official Documentation
- man pthread_create
- man pthread_join
- man pthread_mutex_init
- man pthread_mutex_lock
- man pthread_mutex_unlock
- man gettimeofday
- man usleep

### Concepts Reinforced
- Threads lifecycle management
- Mutex protetion of shared resources
- Deadlock prevention strategies
- Starvation detection
- Race condition avoidance
- Time-based monitoring in concurrent systems

### AI Usage
Ai tools were used responsibly to:
- Clarify concurrency concepts (deadlock, starvation, data races)
- Better understand pthread and mutex behavior
- Improve documentation clarity and structure
All synchronization logic, implementation decisions, debugging, and testing were done manually.
Every part of the project is fully understood and explainable during evaluation

