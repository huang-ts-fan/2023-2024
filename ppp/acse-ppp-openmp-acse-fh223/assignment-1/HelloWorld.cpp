#include <iostream>

// Include header file for OpenMP
#include <omp.h> 

int main(){
    // Set up parallel region
    #pragma omp parallel 
    {

        // int tid = omp_get_thread_num(); // Update this line to get the OpenMP thread ID

        // Use "ordered" to ensure that the threads write to the console in order
        #pragma omp for ordered
        for (int i = 0; i < omp_get_num_threads(); i++){
             
            // Use omp_get_thread_num() to get the thread ID
            #pragma omp ordered 
            {
                int tid = omp_get_thread_num();
                // Consider how to get the threads to write to the console in order.
                std::cout<<"hello from thread "<<tid<<std::endl;
            }
        }

    }
    
    return 0;

}
