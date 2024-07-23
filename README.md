# VSD_SQUADRON_MINI_RISCV_RESEARCH_INTERNSHIP

![image](https://github.com/user-attachments/assets/0f0091ae-8a07-4903-ac24-8c1342084913)

# TASK 1: Installing the required programmes for this internship, such as Ubuntu on VMBox, Visual C++, and writing an example of C code along with evaluating RISC assembly code for the sample C code, are the tasks at hand.

![image](https://github.com/user-attachments/assets/c86b50ba-21c3-4b82-bd27-182e47afad11)

## Step 1: Setting Up Ubuntu within VMBox

1. Install Ubuntu on VMBox.
2. Launch Ubuntu's terminal.

## Step 2: Install Leafpad

```bash
$ sudo apt install leafpad
```
Navigate to the home directory:
```
$ cd
```
```
$ leafpad filename.c &
```

![image](https://github.com/user-attachments/assets/49f80e9e-9e0f-4c55-a526-99c0c40f35d7)

## Step 3: Compile and Run the C Code
Compile the C code:

```

$ gcc filename.c

```
Run the compiled program:
```
$ ./a.out
```
![image](https://github.com/user-attachments/assets/e029df5f-f931-4cc4-9b87-7df94b100aa5)


![image](https://github.com/user-attachments/assets/6eff5a0a-2866-4957-9e52-5e87ac542cee)

## Step 4: Compile C Code with RISC-V Compiler
Compile the C code using the RISC-V compiler:

```
$ riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o filename.o filename.c
```
List the compiled object file:

```
$ ls -ltr filename.o
```

![image](https://github.com/user-attachments/assets/8c8e3183-c3b2-4148-a11c-9c2a3f9c8cdd)

## Step 5: Display Assembly Code


Display the optimized assembly code for the main function:

```
$ riscv64-unknown-elf-objdump -d filename.o | less
```

![image](https://github.com/user-attachments/assets/1f6443e6-c0cb-43b0-8a76-5777b7b6f82c)


![image](https://github.com/user-attachments/assets/ad6e5c81-aa98-4b57-b015-b2eb2a324bc2)

![image](https://github.com/user-attachments/assets/5cac65e5-8930-4c1c-b95a-e39742d83a56)

![image](https://github.com/user-attachments/assets/1dbd254a-c510-48a2-87cf-0b22c2790948)



![image](https://github.com/user-attachments/assets/a6f72964-0668-4ffd-9b9f-6b2087f36c01)

![image](https://github.com/user-attachments/assets/e8aceef5-2ae5-4207-995d-a5f95f1a3629)
![image](https://github.com/user-attachments/assets/48d1fc98-46bf-45e1-942c-004ea3ad8348)
