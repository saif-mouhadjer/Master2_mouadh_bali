# Producer-Consumer Problem with Shared Memory and Semaphores

This project demonstrates the Producer-Consumer problem using shared memory and semaphores in C. The program creates multiple producer and consumer threads that interact with a shared buffer, coordinating access with semaphores and a mutex to prevent race conditions.

## Project Structure

- **main.c**: Contains the main program logic, including producer and consumer functions.
- **shared.c**: Contains helper functions for setting up and cleaning up shared memory, printing the buffer, and initializing semaphores and the mutex.
- **shared.h**: Header file with shared constants, variables, and function declarations.

## Compilation and Execution

To compile and run the project, use the following steps:

### 1. Compile the code

```bash
gcc main.c shared.c -o main -lpthread
```
### 2. Run the program
```bash
./main
```
## Files and Code Structure

### main.c

- Defines the `producer` and `consumer` functions, which interact with the shared buffer.
- Creates multiple producer and consumer threads.
- Each producer generates items and adds them to the buffer.
- Each consumer removes items from the buffer and prints the current state.

### shared.c

- Implements helper functions for:
  - **setup_shared_memory**: Sets up shared memory segments, semaphores, and the mutex.
  - **cleanup_shared_memory**: Cleans up shared memory and destroys semaphores and the mutex.
  - **print_buffer**: Prints the current state of the buffer.

### shared.h

- Contains:
  - Shared memory identifiers and semaphore names.
  - Global variables for buffer, count, semaphores, and the mutex.
  - Declarations for `setup_shared_memory`, `cleanup_shared_memory`, and `print_buffer`.

## Example Output

```text
Producer 2 
Buffer =>  [ 86 _ _ _ ]

Producer 5 
Buffer =>  [ 86 93 _ _ ]

Producer 4 
Buffer =>  [ 86 93 77 _ ]

Consumer 1 => 
Buffer =>  [ 93 77 _ _ ]

Producer 3 
Buffer =>  [ 93 77 15 _ ]

Consumer 3 => 
Buffer =>  [ 77 15 _ _ ]

Consumer 4 => 
Buffer =>  [ 15 _ _ _ ]

Consumer 5 => 
Buffer =>  [ _ _ _ _ ]
