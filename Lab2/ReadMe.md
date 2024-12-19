# Kernel Module Project

This project demonstrates the creation of simple Linux kernel modules. Each module performs a specific task, such as printing messages to the kernel log, getting and setting values, and managing a linked list.

## Project Structure

The project consists of the following modules:

- **module1**
  - `helloKernel.c`
  - `Makefile`
  
- **module2**
  - `GetSetModule.c`
  - `Makefile`

- **module3**
  - `list.c`
  - `Makefile`

## Module 1: Hello Kernel Module (`helloKernel.c`)

This is a basic kernel module that prints a "Hello, Kernel!" message when loaded and a "Goodbye, Kernel!" message when unloaded. It demonstrates basic kernel module initialization and cleanup using `printk`, a function that logs messages to the kernel log.

### Key Concepts:
- **Initialization function (`hello_init`)**: This function is called when the module is loaded into the kernel.
- **Exit function (`hello_exit`)**: This function is called when the module is removed from the kernel.

## Module 2: Get and Set Data Module (`GetSetModule.c`)

This module demonstrates how to define a parameter that can be accessed when the module is loaded. It uses the `module_param` macro to define an integer parameter `value`, which is printed to the kernel log. This allows kernel parameters to be set at module load time and accessed during initialization.

### Key Concepts:
- **Parameter Definition**: The `value` parameter is defined with `module_param(value, int, S_IRUGO)` and is accessible when loading the module.
- **Kernel Log Output**: The value of the parameter is printed to the kernel log using `printk`.

## Module 3: Linked List Management Module (`list.c`)

This module demonstrates the creation and manipulation of a linked list in the Linux kernel. It initializes a list with 10 nodes, each containing an integer value. The list is traversed, and each node's value is printed to the kernel log. Upon unloading the module, the list is cleaned up by removing the nodes and freeing the memory.

### Key Concepts:
- **Linked List**: A simple linked list is created using `list_head` and is managed using kernel functions like `list_add_tail` and `list_for_each_entry`.
- **Memory Management**: The nodes are dynamically allocated using `kmalloc` and freed with `kfree` during module cleanup.

## Makefiles

Each module includes a `Makefile` that compiles the corresponding module. The Makefile specifies the kernel build directory and handles the compilation of `.c` files into kernel object files (`.ko`).

### Example `Makefile`:
The `Makefile` compiles the kernel module, using `make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules`, and provides a `clean` target to remove the generated object files.

## How to Build and Load the Modules

1. **Build the modules**:
   To build the modules, navigate to the respective module directory and run the following command:

   ```bash
   make

2. **Insert the modules**:
   To load a module into the kernel, use the `insmod` command:

    ```bash
    sudo insmod module1/helloKernel.ko
    sudo insmod module2/GetSetModule.ko
    sudo insmod module3/list.ko
    ```

3. **Check the kernel log**:
   After loading the modules, you can check the kernel log to see the output from the modules:

    ```bash
    dmesg
    ```

3. **Remove the modules**:
   To remove a module, use the `rmmod` command:

    ```bash
    sudo rmmod helloKernel
    sudo rmmod GetSetModule
    sudo rmmod list
    ```
# Conclusion
This project demonstrates the creation and management of basic kernel modules in Linux. The modules provide examples of simple tasks such as printing messages, getting/setting parameters, and managing a linked list. These modules serve as a foundation for more complex kernel module development.


