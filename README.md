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
# Understanding Binary Neural Network 
Reference https://neptune.ai/blog/binarized-neural-network-bnn-and-its-implementation-in-ml

Binarized Neural Network (BNN) comes from a paper by Courbariaux, Hubara, Soudry, El-Yaniv, and Bengio from 2016. It introduced a new method to train neural networks, where weights and activations are binarized at train time and then used to compute the gradients. This way, memory size is reduced, and bitwise operations improve power efficiency. GPUs consume huge amounts of power, making it difficult for neural networks to be trained on low-power devices. BNNs can reduce power consumption by more than 32 times.

The paper showed that a binary matrix multiplication could be used to reduce the train time, which made it possible to train BNN on MNIST 7 times faster, achieving near state-of-the-art results.

### Deterministic Function
![image](https://github.com/user-attachments/assets/af0d9f49-3acf-4674-89af-df84ad771271)

### Stochastic Function
![image](https://github.com/user-attachments/assets/53f07cec-0207-4d36-8502-c7a5b6d40cdd)
## Key Aspects of BNNs

### Real-valued weights for optimizers
For optimizers to work, you need real-valued weights, so they’re accumulated in real-valued variables. Even though we use binarized weights/activations, we use real-valued weights for optimization.

### Saturated Straight-Through Estimator (STE)
When using deterministic or stochastic functions for binarization, the derivative of these functions is zero, which makes the whole gradient zero. Saturated STE substitutes the derivative of the signum function with 1 when \( x \leq 1 \), effectively canceling out the gradient when \( x \) is too large.

### Shift-based Batch Normalization and AdaMax Optimization
BNNs use shift-based methods as alternatives to regular BatchNormalization and Adamax optimization to save time by using bitwise operations. The BNN paper claims no accuracy loss when replacing Batch Normalization and Adam optimizer with shift-based Batch Normalization and shift-based Adam optimizer.

### Speeding up the Training
The BNN paper introduced methods to speed up the GPU implementation of BNNs, increasing time efficiency even more than using cuBLAS. One such method is SWAR (Single Instruction, Multiple Data Within a Register), which concatenates 32-binary variables to 32-bit registers, allowing evaluation of these 32 connections in just 6 clock cycles on an Nvidia GPU. This results in a theoretical speed improvement of \( \frac{32}{6} = 5.3 \) times.

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

![image](https://github.com/user-attachments/assets/ad6e5c81-aa98-4b57-b015-b2eb2a324bc2)

![image](https://github.com/user-attachments/assets/5cac65e5-8930-4c1c-b95a-e39742d83a56)

![image](https://github.com/user-attachments/assets/1dbd254a-c510-48a2-87cf-0b22c2790948)



![image](https://github.com/user-attachments/assets/a6f72964-0668-4ffd-9b9f-6b2087f36c01)

![image](https://github.com/user-attachments/assets/e8aceef5-2ae5-4207-995d-a5f95f1a3629)
![image](https://github.com/user-attachments/assets/48d1fc98-46bf-45e1-942c-004ea3ad8348)
