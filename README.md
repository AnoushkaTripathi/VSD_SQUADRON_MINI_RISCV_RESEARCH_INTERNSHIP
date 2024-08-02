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
# TASK 2
# Understanding Binary Neural Network 
Reference https://neptune.ai/blog/binarized-neural-network-bnn-and-its-implementation-in-ml
## Binarized Neural Network (BNN)

Binarized Neural Networks (BNNs) were introduced in a 2016 paper by Courbariaux, Hubara, Soudry, El-Yaniv, and Bengio. This innovative approach involves training neural networks with binarized weights and activations.

### Key Points of BNNs:

1. **Binarization of Weights and Activations:**
   - During training, weights and activations are binarized to either -1 or 1. This reduces the memory needed to store these values compared to floating-point numbers.
   
2. **Efficiency Improvements:**
   - The binarized values enable the use of bitwise operations instead of complex arithmetic operations. Bitwise operations are much faster and consume less power.
   - This results in improved power efficiency, essential for training neural networks on low-power devices like mobile phones and embedded systems. BNNs can reduce power consumption by over 32 times compared to traditional neural networks.

3. **Faster Training:**
   - The paper demonstrated that binary matrix multiplication can significantly speed up the training process. For instance, training a BNN on the MNIST dataset was shown to be 7 times faster than traditional methods while still achieving near state-of-the-art results.

### Benefits of BNNs:

- **Reduced Memory Usage:** Using binary values significantly reduces the neural network's memory footprint.
- **Increased Speed:** Simpler binary operations enable faster computation.
- **Lower Power Consumption:** Bitwise operations lead to lower power usage, making BNNs suitable for low-power devices.

### Deterministic Function
![image](https://github.com/user-attachments/assets/af0d9f49-3acf-4674-89af-df84ad771271)

### Stochastic Function
![image](https://github.com/user-attachments/assets/53f07cec-0207-4d36-8502-c7a5b6d40cdd)
## Key Aspects of BNNs

### Real-valued Weights for Optimizers
Although BNNs use binarized weights and activations during training, real-valued weights are still necessary for optimizers to function effectively. These real-valued weights are accumulated in real-valued variables, enabling the optimization process.

### Saturated Straight-Through Estimator (STE)
When using deterministic or stochastic functions for binarization, their derivatives are zero, resulting in zero gradients. To address this, the Saturated STE substitutes the derivative of the signum function with 1 when \( x \leq 1 \), effectively preventing the gradient from vanishing when \( x \) is too large.

### Shift-based Batch Normalization and AdaMax Optimization
BNNs utilize shift-based methods as alternatives to conventional Batch Normalization and AdaMax optimization. These methods leverage bitwise operations to save time. The BNN paper asserts that replacing Batch Normalization and the Adam optimizer with shift-based Batch Normalization and shift-based Adam optimizer does not result in accuracy loss.

### Speeding Up the Training
The BNN paper introduced techniques to further accelerate GPU implementations of BNNs, achieving greater efficiency than using cuBLAS. One notable technique is SWAR (Single Instruction, Multiple Data Within a Register), which concatenates 32 binary variables into 32-bit registers. This allows 32 connections to be evaluated in just 6 clock cycles on an Nvidia GPU, resulting in a theoretical speed improvement of \( \frac{32}{6} = 5.3 \) times.


## Performance Stats
![image](https://github.com/user-attachments/assets/e24eb032-c586-41cf-9f13-090c0e2fcc62)


**Figure 1:** A binary weight filter from the 1st convolutional layer of BNN | [Source](https://arxiv.org/pdf/1602.02830)
![image](https://github.com/user-attachments/assets/9dd83f86-ebae-4eef-b524-527ac2dd5c8d)


**Figure 2:** Comparison between Baseline kernel, cuBLAS, and the XNOR kernel for time and accuracy | [Source](https://arxiv.org/pdf/1602.02830)

As shown in Figure 2:
- The accuracy for all three methods (unoptimized baseline kernel, cuBLAS library, and paper’s XNOR kernel) are the same in the third section of the graph.
- In the first section, matrix multiplication time is compared, with an 8192 x 8192 x 8192 matrix.
- In the second section, full test data in MNIST is inferred on a multi-layered perceptron. The XNOR kernel performs better, being 23 times faster than the baseline kernel and 3.4 times faster than the cuBLAS kernel in the case of matrix multiplication.

 ## Summary
- BNNs binarize weights and activations to reduce memory size and improve power efficiency.
- Deterministic and stochastic functions are used for binarization.
- Real-valued weights are used for optimization.
- Saturated STE is used to address zero gradients in backpropagation.
- Shift-based methods are employed for BatchNormalization and AdaMax optimization.
- SWAR is used to speed up calculations by performing parallel operations within a register.
- The XNOR kernel provides significant speed improvements compared to baseline and cuBLAS kernels.


# Binary Neural Network in C
![image](https://github.com/user-attachments/assets/06fec611-7f1c-49eb-ac26-f5c0976c7e89)

## Code Explanation

### Function Definitions

- **`f(double a, double b)`**: The function to be learned by the neural network. In this example, it returns the absolute difference of `a` and `b`.

- **`rnd()`**: Generates a uniform random number between 0.0 and 1.0.

- **`nrnd()`**: Generates a normal random number with a standard deviation of 1.0.

- **`sigmoid(double x)`**: The sigmoid activation function.

- **`sigmoid_g(double y)`**: The gradient of the sigmoid function.

### Layer Structure

A layer in the network is represented by the `Layer` structure, which includes:

- **`lid`**: Layer ID.
- **`lprev`**: Pointer to the previous layer.
- **`lnext`**: Pointer to the next layer.
- **`nnodes`**: Number of nodes in the layer.
- **`outputs`**: Array of node outputs.
- **`gradients`**: Array of node gradients.
- **`errors`**: Array of node errors.
- **`nbiases`**: Number of biases.
- **`biases`**: Array of biases.
- **`u_biases`**: Array of bias updates.
- **`nweights`**: Number of weights.
- **`weights`**: Array of weights.
- **`u_weights`**: Array of weight updates.

### Layer Functions

- **`Layer_create(Layer* lprev, int nnodes)`**: Creates a new layer with the specified number of nodes and connects it to the previous layer if provided.

- **`Layer_destroy(Layer* self)`**: Releases the memory allocated for the layer.

- **`Layer_dump(const Layer* self, FILE* fp)`**: Outputs the layer's details for debugging purposes.

- **`Layer_feedForw(Layer* self)`**: Performs the feedforward operation for the layer.

- **`Layer_feedBack(Layer* self)`**: Performs the backpropagation operation for the layer.

- **`Layer_setInputs(Layer* self, const double* values)`**: Sets the input values for the input layer and starts the feedforward process.

- **`Layer_getOutputs(const Layer* self, double* outputs)`**: Retrieves the output values from the layer.

- **`Layer_getErrorTotal(const Layer* self)`**: Calculates the total error for the layer.

- **`Layer_learnOutputs(Layer* self, const double* values)`**: Learns the target output values by calculating the errors and initiating the backpropagation process.

- **`Layer_update(Layer* self, double rate)`**: Updates the weights and biases based on the learning rate.

### Main Function

The `main` function initializes the layers, runs the training loop for a specified number of epochs, and updates the weights after each epoch.

```c
int main(int argc, char* argv[])
{
    srand(0); // Use a fixed random seed for debugging.

    // Initialize layers.
    Layer* linput = Layer_create(NULL, 2);
    Layer* lhidden = Layer_create(linput, 3);
    Layer* loutput = Layer_create(lhidden, 1);
    Layer_dump(linput, stderr);
    Layer_dump(lhidden, stderr);
    Layer_dump(loutput, stderr);

    // Run the network.
    double rate = 1.0;
    int nepochs = 10000;
    for (int i = 0; i < nepochs; i++) {
        double x[2];
        double y[1];
        double t[1];
        x[0] = rnd();
        x[1] = rnd();
        t[0] = f(x[0], x[1]);
        Layer_setInputs(linput, x);
        Layer_getOutputs(loutput, y);
        Layer_learnOutputs(loutput, t);
        double etotal = Layer_getErrorTotal(loutput);
        fprintf(stderr, "i=%d, x=[%.4f, %.4f], y=[%.4f], t=[%.4f], etotal=%.4f\n",
                i, x[0], x[1], y[0], t[0], etotal);
        Layer_update(loutput, rate);
    }

    // Dump the finished network.
    Layer_dump(linput, stdout);
    Layer_dump(lhidden, stdout);
    Layer_dump(loutput, stdout);

    // Free the memory.
    Layer_destroy(linput);
    Layer_destroy(lhidden);
    Layer_destroy(loutput);
    return 0;
}
```
![image](https://github.com/user-attachments/assets/4b4ac4ad-6e43-48a9-a1a1-1d0c1e68ae05)

![image](https://github.com/user-attachments/assets/faf45b2b-988e-4c3e-bccc-5a6b9d80b909)

![image](https://github.com/user-attachments/assets/ac528eb5-21c4-4e68-bc16-4320206bf7c9)

# TASK 3 :  RISC V Instruction Types
![image](https://github.com/user-attachments/assets/f63f8c64-e8d8-417d-a962-03f09df16fe9)


As a part of this Internship I completed this course offered by Kunal Ghosh sir, VLSI SYSTEM DESIGN.

### RISC V OPERANDS

![image](https://github.com/user-attachments/assets/6e1c1788-6c29-4811-b469-521e9be1346a)



Operands are essential components in any instruction. For example, consider the operation `a = b + c`, where `a`, `b`, and `c` are operands. In this case, `b` and `c` are the source operands, and `a` is the destination operand. These operands need to be stored physically somewhere within the computer, and we typically have three options:
![image](https://github.com/user-attachments/assets/2cddc2cf-975d-4a5a-83c6-7f4d3f61747f)

![image](https://github.com/user-attachments/assets/3d7e38dc-576c-48ff-9ea3-49d817b18586)
1. **Registers**
2. **Memory**
3. **Constants**

### Registers
Registers are small, fast storage locations within the CPU, typically built from flip-flops or a register file. They provide quick access to data compared to memory. Memory, which is often built from SRAM or DRAM, has a larger capacity but slower access times. Constants, or immediates, are values embedded directly within the instructions themselves.

### RISC-V Registers
RISC-V, a popular open-source instruction set architecture, has 32 registers, each 32 bits wide. These registers provide much faster data access than memory. The RISC-V architecture is known as a 32-bit architecture because it primarily operates on 32-bit data. There is also a 64-bit version of RISC-V where registers are 64 bits wide, allowing for 64-bit data operations.

**Design Principle 3: Smaller is Faster**
The design philosophy behind RISC-V includes having a small number of registers (32) to ensure the system is not limited by register access time, thus enabling faster computation. The number of registers is chosen carefully to balance speed and storage capacity.

### Register Naming in RISC-V
The 32 registers in RISC-V are named `x0` to `x31`. However, they are often referred to by more descriptive names to indicate their typical usage:

- **x0 (zero)**: Always holds the constant value 0.
- **x1 (ra)**: Return Address, used to store the return address after a function call.
- **x2 (sp)**: Stack Pointer, points to the top of the stack in memory.
- **x3 (gp)**: Global Pointer.
- **x4 (tp)**: Thread Pointer.

### Saved, Temporary, and Argument Registers
The remaining registers are categorized as saved registers (`s`), temporary registers (`t`), and argument registers (`a`):

- **Saved Registers (s0-s11)**: Used to store variables that must retain their values across function calls. (x8, x9, x18-x27)
- **Temporary Registers (t0-t6)**: Used for intermediate calculations and temporary data.
- **Argument Registers (a0-a7)**: Used for passing arguments to functions and storing return values.


![image](https://github.com/user-attachments/assets/af936f03-ded7-4d6a-9e4b-38cf37695620)



### ABI : Application Binary Interface



## "Decoding RISC-V Instructions: A Visual Guide"
### "Understanding I-Type, S-Type, B-Type, U-Type, and J-Type Instructions"

  ## Introduction Section:


RISC-V (Reduced Instruction Set Computer - V) is an open standard instruction set architecture (ISA) based on established reduced instruction set computing principles. Unlike proprietary ISAs, RISC-V is free and open, enabling unrestricted academic and commercial use without licensing fees. This has made RISC-V an attractive option for research, education, and industry applications, fostering innovation and development across various domains.

### Importance of Understanding Instruction Formats

Understanding instruction formats is crucial for several reasons:

1. **Instruction Decoding**: Knowing the structure of different instruction formats enables the correct decoding of instructions, which is essential for the CPU to execute them correctly.

2. **Pipeline Design**: Instruction formats impact the design of the CPU pipeline. Proper handling of instruction formats ensures efficient instruction fetch, decode, execution, memory access, and write-back stages.

3. **Compiler Design**: Compilers generate machine code that adheres to the ISA's instruction formats. A deep understanding of these formats helps in optimizing code generation, leading to better performance and efficiency.

4. **Debugging and Verification**: Understanding instruction formats aids in debugging and verifying hardware and software. It helps in identifying issues related to incorrect instruction execution or pipeline hazards.

5. **Extensibility and Customization**: RISC-V's modular and extensible nature allows for custom extensions. Understanding the base instruction formats is essential for creating and integrating custom instructions tailored to specific applications or performance needs.

# BASICS

 ## Instruction Types and Fields

The RISC-V instructions are categorized into types based on their field organization. Each type has specific fields like opcode, func3, func7, immediate values, and register numbers. The types include:

- **R-type**: Register type
- **I-type**: Immediate type
- **S-type**: Store type
- **B-type**: Branch type
- **U-type**: Upper immediate type
- **J-type**: Jump type

## Opcode and Function Fields

- **Opcode**: Determines the type of instruction.
- **func3** and **func7**: Further specify the operation within the instruction type.
  - Example: In R-type instructions, func3 and func7 differentiate between operations like addition and subtraction.

## Immediate Values and Registers

- **Immediate Values**: Encoded in specific fields within the instruction.
  - Example: I-type instructions use a 12-bit immediate value field along with source and destination registers.
- **Registers**: Specified in fields such as rd (destination register), rs1 (source register 1), and rs2 (source register 2).

## Assembly to Machine Code Translation

### Assembly Language Statement

An assembly statement like `add x1, x2, x3` specifies an operation (add) and operands (x1, x2, x3).

### Encoding Process

This statement is translated into machine code by encoding the operation into the opcode, func3, and func7 fields, and the operands into the register fields.

### Machine Code Execution

When the machine encounters this instruction, it decodes the fields to perform the specified operation, using the specified registers and immediate values.

## Instruction Set Encoding

### Usage Template Column

The usage template column links the parameters in assembly language instructions to their encoded fields in machine language.
- Example: In U-type instructions, the immediate value from the assembly code is placed in the instruction’s immediate field.

### Example - U-Type Instruction

Consider the `lui` (Load Upper Immediate) instruction:

- **Assembly**: `lui x5, 0x12345`
- **Encoding**: The immediate value `0x12345` is placed in the instruction’s immediate field, and the destination register `x5` is specified in the rd field.
- **Machine Execution**: The machine loads the upper 20 bits of the immediate value into the upper 20 bits of register `x5`.

   ## Arithmetic Instructions

- **ADD**: Adds values in two registers and stores the result in a third register.
  - Example: `ADD rd, rs1, rs2` (rd = rs1 + rs2)
- **ADDI**: Adds a register and an immediate value (constant) and stores the result.
  - Example: `ADDI rd, rs1, imm` (rd = rs1 + imm)

## Logical Instructions

- **AND, OR, XOR**: Perform bitwise operations.
  - Example: `AND rd, rs1, rs2` (rd = rs1 & rs2)

## Branch Instructions

- **BEQ**: Branch if equal.
  - Example: `BEQ rs1, rs2, offset` (if rs1 == rs2, PC = PC + offset)
- **BNE**: Branch if not equal.
  - Example: `BNE rs1, rs2, offset` (if rs1 != rs2, PC = PC + offset)

## Load and Store Instructions

- **LW**: Load word from memory.
  - Example: `LW rd, offset(rs1)` (rd = memory[rs1 + offset])
- **SW**: Store word to memory.
  - Example: `SW rs1, offset(rs2)` (memory[rs2 + offset] = rs1)

## Special Instructions

- **AUIPC**: Add upper immediate to PC.
  - Example: `AUIPC rd, imm` (rd = PC + imm << 12)

## Execution Cycle

A CPU executes instructions in a cycle:

1. **Fetch**: Retrieve the instruction from memory.
2. **Decode**: Determine the operation and operands.
3. **Execute**: Perform the operation.
4. **Write-back**: Store the result in the destination register.
5. **Update PC**: Move to the next instruction.

## Branch and Jump Instructions

- **Jump (J)**: Unconditional branch to a specified address.
- **Branch (B)**: Conditional branch based on a comparison.

## RV32I Extensions

RISC-V allows optional extensions for additional functionality:

- **M**: Integer multiplication and division.
- **A**: Atomic instructions.
- **F, D, Q**: Floating-point operations (32-bit, 64-bit, 128-bit).
- **C**: Compressed instructions.


### RISC-V R-Type Instructions

R-type instructions are used for operations that involve only registers. These instructions typically perform arithmetic, logical, and shift operations.

#### Format: 
![image](https://github.com/user-attachments/assets/e01d8bbe-710e-4927-8fec-51f162d384ca)


- **opcode**: Specifies the operation (e.g., 0110011 for integer register-register operations).
- **rd**: Destination register.
- **funct3**: Further specifies the operation.
- **rs1**: First source register.
- **rs2**: Second source register.
- **funct7**: Further specifies the operation.



### I-Type Instructions
I-Type instructions cover various operations, including immediate arithmetic, load operations, and certain control flow instructions.

### Extracting Immediate Value

- The immediate value spans bits [31:20].
- To extract this value:
  - Mask the instruction to isolate the relevant bits.
  - Perform a right shift to align the immediate value to the least significant bits (LSBs).
- **Example**: If the instruction value is `0x12345678`, the immediate value is extracted as follows:
  ```cpp
  uint32_t imm_i = (instruction & 0xFFF00000) >> 20;

![image](https://github.com/user-attachments/assets/3d035720-dc62-45d5-9a2c-2a6b263ade74)

**Example: ADDI rd, rs1, imm**
- **opcode**: 0010011 (for immediate arithmetic operations)
- **funct3**: 000 (for ADDI)
- **imm**: Immediate value
- **rs1**: Source register 1
- **rd**: Destination register

### S-Type Instructions

![image](https://github.com/user-attachments/assets/eb224238-c0ef-42ca-82d0-c42ed8293320)

**Example: SW rs2, imm(rs1)**
- **opcode**: 0100011 (for store operations)
- **funct3**: 010 (for SW)
- **imm**: Immediate value (split into imm[11:5] and imm[4:0])
- **rs1**: Base address register
- **rs2**: Source register to be stored

### B-Type Instructions

![image](https://github.com/user-attachments/assets/7f138e24-cb0c-4506-9875-c4b3b14a2670)

**Example: BEQ rs1, rs2, imm**
- **opcode**: 1100011 (for branch operations)
- **funct3**: 000 (for BEQ)
- **imm**: Immediate value (split into imm[12], imm[10:5], imm[4:1], imm[11])
- **rs1**: Source register 1
- **rs2**: Source register 2

### U-Type Instructions
U-Type instructions are used for operations like loading upper immediate (LUI) and adding upper immediate to PC (AUIPC).

### Extracting Immediate Value

- The immediate value in U-type instructions spans bits [31:12].
- To extract this value, you can mask the instruction with `0xFFFFF000`.
- **Example**: If the instruction value is `0x12345000`, applying the mask will yield `0x12345000`.

### Encoding and Usage

- The immediate value extracted directly forms part of the U-type instruction.
  - For **LUI**, this value is loaded into the destination register.
  - For **AUIPC**, this value is added to the current PC.


![image](https://github.com/user-attachments/assets/d6269585-d85a-4675-b13f-4ae4ed1ea05a)

**Example: LUI rd, imm**
- **opcode**: 0110111 (for LUI)
- **imm**: Upper 20 bits of the immediate value
- **rd**: Destination register

### J-Type Instructions


![image](https://github.com/user-attachments/assets/9b35cad7-8fd8-41da-be46-aec4cf712657)

**Example: JAL rd, imm**
- **opcode**: 1101111 (for JAL)
- **imm**: Immediate value (split into imm[20], imm[10:1], imm[11], imm[19:12])
- **rd**: Destination register (stores the return address)





## Acknowledgements

 - [Kunal Ghosh,Co-Founder at VLSI System Design](https://www.linkedin.com/in/kunal-ghosh-vlsisystemdesign-com-28084836/)
 - [Yusuke Shinyama](https://github.com/euske)
 - [RISC-V](https://www.linkedin.com/company/risc-v-international/posts/?feedView=all)


