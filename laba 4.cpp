#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* ThreadF(void*) {
    cout << "Semi stream started..." << endl;
    sleep(5); 
    cout << "Semi stream is finishing." << endl;
    pthread_exit(NULL);
}

int main() {
    pthread_t t;

    if (pthread_create(&t, NULL, ThreadF, NULL)) {
        cerr << "Error: Failed to create thread." << endl;
        return 1;
    }

    sleep(2); 

    if (pthread_cancel(t)) {
        cerr << "Error: Failed to cancel thread." << endl;
        return 1;
    }

    cout << "Semi stream terminated by Main." << endl;

    if (pthread_join(t, NULL)) {
        cerr << "Error: Failed to join thread." << endl;
        return 1;
    }

    cout << " Main stream started." << endl;
    return 0;
}
