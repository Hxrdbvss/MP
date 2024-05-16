#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void cleanup(void*) {
    cout << "Semi stream: Finishing work..." << endl;
}

void* ThreadF(void*) {
    cout << "Semi stream: Started..." << endl;
    pthread_cleanup_push(cleanup, NULL);
    sleep(5); 
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}

int main() {
    pthread_t t;
    if (pthread_create(&t, NULL, ThreadF, NULL)) {
        cerr << "Error creating thread." << endl;
        return 1;
    }

    sleep(2); 

    if (pthread_cancel(t)) {
        cerr << "Error cancelling thread." << endl;
        return 1;
    }

    cout << "Semi stream terminated by Main." << endl;

    if (pthread_join(t, NULL)) {
        cerr << "Error joining thread." << endl;
        return 1;
    }

    cout << "Main stream started." << endl;

    return 0;
}
