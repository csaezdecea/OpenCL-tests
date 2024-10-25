# About this repository

This `.md` file provides a concise explanation of the repository, along with instructions on how to compile the code. This repository consists of two codes designed to test if OpenCL is working and utilizing your GPU.

## `check_gpu.cpp`
This C++ program uses the OpenCL API to query and display information about all available OpenCL platforms and their associated devices on the system. It first retrieves the number of platforms, then iterates through each platform to gather details like platform name and vendor. For each platform, the program lists all devices (such as CPUs or GPUs), printing key information about each device, including its name, vendor, hardware and software versions, OpenCL C version, maximum compute units, and maximum work group size. The result is a detailed overview of the system's OpenCL capabilities.

## `vector_addition.cpp`
This C++ program performs vector addition using OpenCL to parallelize the computation on a GPU. It defines a simple kernel (`vec_add`) to add two vectors element-wise. In the main function, the program first initializes two input vectors `A` and `B` with sizes of 1024 and a result vector `C`. It then sets up the OpenCL environment by retrieving the platform and GPU device, creating a context and command queue, and allocating memory buffers on the device for the vectors. The kernel is compiled from source, and its arguments are set to reference the memory buffers. The kernel is then executed in parallel on the GPU using `clEnqueueNDRangeKernel`. After execution, the result is copied from the device to host memory and printed. Finally, the program releases all OpenCL resources, including memory buffers, the kernel, and the command queue. The result of this program should be an array of replicated `3`s.

## To compile the codes:
```bash
mkdir build
cd build
cmake ..
make
```


