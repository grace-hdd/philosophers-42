*This project has been created as part of the 42 curriculum by grhaddad.*

# Philosophers

This project is an implementation of the **Dining Philosophers** problem, a classic synchronization problem in computer science.  
It focuses on managing **concurrency**, **shared resources**, and **time-sensitive state changes**, while avoiding **deadlocks**, **data races**, and **starvation**.

The project is implemented **exclusively using threads and mutexes**, in accordance with the mandatory requirements of the 42 curriculum.

---

## Project Overview

A number of philosophers are sitting at a round table. In the center of the table is a large bowl of spaghetti.  
Between each pair of philosophers lies exactly **one fork**.

Rules of the simulation:

- Each philosopher alternates between **eating**, **sleeping**, and **thinking**
- To eat, a philosopher must hold **two forks** (left and right)
- Philosophers do **not communicate** with each other
- Philosophers do **not know** if another philosopher is about to die
- The simulation stops:
  - When a philosopher dies  
  - Or, optionally, when all philosophers have eaten a required number of times

The goal is to ensure:
- No philosopher starves
- Forks are never shared simultaneously
- Logs are printed consistently and without overlap

---

## Concurrency Model

### Philosophers

- Each philosopher is represented by a **pthread**
- Each philosopher runs the same routine in a loop:
  1. Take forks
  2. Eat
  3. Sleep
  4. Think

### Forks

- Each fork is represented by a **mutex**
- Forks are shared resources and must be locked before use
- Mutexes prevent simultaneous access to the same fork

---

## Synchronization Strategy

- Fork mutexes protect fork access
- A dedicated print mutex prevents output overlap
- Meal times and counters are protected against race conditions
- A shared simulation state is used to stop all threads safely

Deadlocks are avoided by enforcing a **consistent fork-locking strategy**  
(e.g. ordered locking or odd/even philosopher behavior).

---

## Usage

### Program Execution

```shell
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

### Examples
```shell
./philo 5 800 200 200
```
