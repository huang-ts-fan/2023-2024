#include <iostream>
// Include header file for OpenMP

int main(){
    // Set up parallel region
    int tid = 0; // Update this line to get the OpenMP thread ID

    // Consider how to get the threads to write to the console in order.
    std::cout<<"hello from thread "<<tid<<std::endl;

    return 0;
}
