#include <CL/cl.h>
#include <iostream>
#include <vector>

void printDeviceInfo(cl_device_id device) {
    char buffer[1024];
    cl_uint buf_uint;
    cl_ulong buf_ulong;

    // Print device name
    clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(buffer), buffer, nullptr);
    std::cout << "Device: " << buffer << std::endl;

    // Print device vendor
    clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(buffer), buffer, nullptr);
    std::cout << "Vendor: " << buffer << std::endl;

    // Print hardware version
    clGetDeviceInfo(device, CL_DEVICE_VERSION, sizeof(buffer), buffer, nullptr);
    std::cout << "Hardware version: " << buffer << std::endl;

    // Print software driver version
    clGetDeviceInfo(device, CL_DRIVER_VERSION, sizeof(buffer), buffer, nullptr);
    std::cout << "Software version: " << buffer << std::endl;

    // Print OpenCL C version supported by this device
    clGetDeviceInfo(device, CL_DEVICE_OPENCL_C_VERSION, sizeof(buffer), buffer, nullptr);
    std::cout << "OpenCL C version: " << buffer << std::endl;

    // Print max compute units
    clGetDeviceInfo(device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(buf_uint), &buf_uint, nullptr);
    std::cout << "Max compute units: " << buf_uint << std::endl;

    // Print max work group size
    clGetDeviceInfo(device, CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(buf_ulong), &buf_ulong, nullptr);
    std::cout << "Max work group size: " << buf_ulong << std::endl;

    std::cout << std::endl;
}

int main() {
    cl_uint ret_num_platforms;
    cl_uint ret_num_devices;
    cl_int ret;

    // Get Platform IDs
    ret = clGetPlatformIDs(0, nullptr, &ret_num_platforms);
    std::vector<cl_platform_id> platforms(ret_num_platforms);
    ret = clGetPlatformIDs(ret_num_platforms, platforms.data(), nullptr);

    for (cl_uint i = 0; i < ret_num_platforms; ++i) {
        char buffer[1024];
        std::cout << "Platform " << i + 1 << ":" << std::endl;

        // Get platform name
        clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, sizeof(buffer), buffer, nullptr);
        std::cout << "Name: " << buffer << std::endl;

        // Get platform vendor
        clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, sizeof(buffer), buffer, nullptr);
        std::cout << "Vendor: " << buffer << std::endl;

        // Get devices associated with the platform
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &ret_num_devices);
        std::vector<cl_device_id> devices(ret_num_devices);
        ret = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_ALL, ret_num_devices, devices.data(), nullptr);

        for (cl_uint j = 0; j < ret_num_devices; ++j) {
            printDeviceInfo(devices[j]);
        }
    }

    return 0;
}
