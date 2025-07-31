# 🍽️ Philosophers

A C implementation of the classic Dining Philosophers Problem, featuring both thread-based and process-based solutions. Demonstrates advanced concurrent programming concepts including deadlock prevention, starvation avoidance, and precise timing control.

## 📖 Overview

The Dining Philosophers Problem illustrates synchronization issues and techniques for resolving them in concurrent programming. Five philosophers sit around a circular table with five forks. Each philosopher alternates between thinking and eating, but needs two forks to eat. The challenge is to design a solution that prevents deadlock and starvation.

## 🚀 Features

- 🔒 **Deadlock Prevention**: Address-based mutex ordering eliminates circular wait conditions
- ⚡ **Starvation Avoidance**: Anti-starvation mechanisms ensure fair resource access
- 🎯 **Precise Timing**: Millisecond-precision death detection using monotonic clocks
- 🧵 **Dual Implementation**: Thread-based (`philo`) and process-based (`philo_bonus`) versions
- 🛡️ **Robust Error Handling**: Comprehensive input validation and graceful failure recovery
- 📊 **Memory Safe**: Zero memory leaks with proper resource cleanup
- ⚙️ **Optimized Performance**: Efficient CPU usage with smart sleep mechanisms

## 🏗️ Architecture

### philo (Mandatory - Threads)
- **Synchronization**: pthread mutexes
- **Communication**: Shared memory between threads
- **Monitoring**: Centralized death detection thread
- **Benefits**: Lower overhead, faster context switching

### philo_bonus (Bonus - Processes)
- **Synchronization**: POSIX semaphores
- **Communication**: Inter-process communication
- **Monitoring**: Individual monitor thread per process
- **Benefits**: True isolation, crash resilience

## 🛠️ Installation

```bash
# Clone the repository
git clone https://github.com/ElieBalaa/Philosophers.git
cd Philosophers

# Compile mandatory part (threads)
make

# Compile bonus part (processes)
make bonus

# Clean object files
make clean

# Full clean (remove executables)
make fclean

# Recompile everything
make re
```

## 📋 Usage

```bash
# Basic syntax
./philo [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: meals_required]
./philo_bonus [num_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: meals_required]

# Examples
./philo 5 800 200 200          # 5 philosophers, basic simulation
./philo 4 310 200 100          # Edge case testing
./philo 5 800 200 200 7        # Stop after 7 meals per philosopher
./philo 1 800 200 200          # Single philosopher (should die)

# Process-based version
./philo_bonus 5 800 200 200    # Same parameters, different implementation
```

### Parameters

- `num_philosophers`: Number of philosophers (and forks)
- `time_to_die`: Time in milliseconds before a philosopher dies of starvation
- `time_to_eat`: Time in milliseconds a philosopher takes to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping
- `meals_required`: (Optional) Simulation stops when all philosophers have eaten this many times

## 🧪 Testing

The project has been thoroughly tested with:

- **LazyPhilosophersTester**: Community-standard test suite
- **Custom automated tests**: Regression testing for edge cases
- **Memory analysis**: Valgrind-verified memory safety
- **Performance testing**: Stress testing with 200+ philosophers

### Test Results
✅ All death detection tests pass (±1-2ms precision)  
✅ Starvation prevention in edge cases  
✅ Resource cleanup verification  
✅ High-load stress testing  
✅ Error handling validation  

## 🔧 Technical Implementation

### Key Algorithms
- **Address-Based Fork Ordering**: Prevents deadlock by consistent resource acquisition order
- **Monotonic Timing**: Uses `clock_gettime(CLOCK_MONOTONIC)` for reliable time measurements
- **Smart Sleep Mechanisms**: Efficient waiting with minimal CPU usage
- **Race Condition Prevention**: Careful mutex/semaphore usage to avoid data races

### Code Quality
- **42 Norminette Compliant**: Passes all coding standard checks
- **Clean Architecture**: Modular design with clear separation of concerns
- **Comprehensive Error Handling**: Robust initialization and cleanup

## 📊 Performance

- **Scalability**: Successfully handles 200+ philosophers
- **Efficiency**: Minimal CPU usage with smart waiting
- **Reliability**: Zero deadlocks, consistent timing
- **Precision**: Death detection within millisecond accuracy

## 🎓 Learning Outcomes

This project demonstrates mastery of:

- **Concurrent Programming**: Thread and process synchronization
- **Deadlock Prevention**: Resource ordering and timing strategies
- **System Programming**: POSIX APIs, memory management, error handling
- **Performance Optimization**: Efficient algorithms and resource usage
- **Code Quality**: Clean, maintainable, and standard-compliant code

## 🔧 Technical Stack

- **Language**: C
- **Standards**: POSIX, 42 Norminette
- **Synchronization**: pthread mutexes, POSIX semaphores
- **Timing**: Monotonic clocks, precise sleep mechanisms
- **Testing**: Automated test suites, memory analysis tools

## 📁 Project Structure

```
.
├── philo/
│   ├── includes/
│   │   └── philo.h
│   ├── src/
│   │   ├── main.c
│   │   ├── init.c
│   │   ├── philosopher.c
│   │   ├── monitor.c
│   │   ├── utils.c
│   │   └── cleanup.c
│   └── Makefile
├── philo_bonus/
│   ├── includes/
│   │   └── philo_bonus.h
│   ├── src/
│   │   ├── main_bonus.c
│   │   ├── init_bonus.c
│   │   ├── philosopher_bonus.c
│   │   ├── monitor_bonus.c
│   │   ├── utils_bonus.c
│   │   └── cleanup_bonus.c
│   └── Makefile
└── README.md
```

## ⚠️ Common Pitfalls Avoided

- **Deadlock**: Solved with address-based mutex ordering
- **Starvation**: Prevented with fair scheduling and micro-delays
- **Data Races**: Eliminated with proper synchronization
- **Memory Leaks**: Prevented with comprehensive cleanup
- **Timing Issues**: Resolved with monotonic clocks and precise monitoring

## 🏆 Achievements

- ✅ 100% test suite compliance
- ✅ Zero memory leaks (Valgrind verified)
- ✅ Deadlock-free under all test conditions
- ✅ Norminette compliant (42 coding standards)
- ✅ High performance (supports 200+ philosophers)

---

*This project was developed as part of the 42 School curriculum, focusing on advanced systems programming and concurrent computing concepts.* 