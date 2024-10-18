#include <CL/cl.h>
#include <iostream>
#include <vector>

#define VECTOR_SIZE 1024

const char* kernelSource = R"(
__kernel void vec_add(__global const float* A, __global const float* B, __global float* C) {
    int id = get_global_id(0);
    C[id] = A[id] + B[id];
}
)";

int main() {
    // Initialize data
    std::vector<float> A(VECTOR_SIZE, 1.0f);
    std::vector<float> B(VECTOR_SIZE, 2.0f);
    std::vector<float> C(VECTOR_SIZE, 0.0f);

    // Get platform and device information
    cl_platform_id platform_id = nullptr;
    cl_device_id device_id = nullptr;
    cl_uint ret_num_devices;
    cl_uint ret_num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
    ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);

    // Create an OpenCL context
    cl_context context = clCreateContext(nullptr, 1, &device_id, nullptr, nullptr, &ret);

    // Create a command queue
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);

    // Create memory buffers on the device for each vector
    cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, VECTOR_SIZE * sizeof(float), nullptr, &ret);
    cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY, VECTOR_SIZE * sizeof(float), nullptr, &ret);
    cl_mem c_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY, VECTOR_SIZE * sizeof(float), nullptr, &ret);

    // Copy the lists A and B to their respective memory buffers
    ret = clEnqueueWriteBuffer(command_queue, a_mem_obj, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), A.data(), 0, nullptr, nullptr);
    ret = clEnqueueWriteBuffer(command_queue, b_mem_obj, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), B.data(), 0, nullptr, nullptr);

    // Create a program from the kernel source
    cl_program program = clCreateProgramWithSource(context, 1, &kernelSource, nullptr, &ret);

    // Build the program
    ret = clBuildProgram(program, 1, &device_id, nullptr, nullptr, nullptr);

    // Create the OpenCL kernel
    cl_kernel kernel = clCreateKernel(program, "vec_add", &ret);

    // Set the arguments of the kernel
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
    ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
    ret = clSetKernelArg(kernel, 2, sizeof(cl_mem), (void*)&c_mem_obj);

    // Execute the OpenCL kernel on the list
    size_t global_item_size = VECTOR_SIZE;
    size_t local_item_size = 64;
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, nullptr, &global_item_size, &local_item_size, 0, nullptr, nullptr);

    // Read the memory buffer C on the device to the local variable C
    ret = clEnqueueReadBuffer(command_queue, c_mem_obj, CL_TRUE, 0, VECTOR_SIZE * sizeof(float), C.data(), 0, nullptr, nullptr);

    // Display the result
    for (int i = 0; i < VECTOR_SIZE; i++)
        std::cout << C[i] << " ";
    std::cout << std::endl;

    // Clean up
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(a_mem_obj);
    ret = clReleaseMemObject(b_mem_obj);
    ret = clReleaseMemObject(c_mem_obj);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);

    return 0;
}

