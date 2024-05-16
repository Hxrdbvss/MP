#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

void* semiStream(void*) {
    for (int i = 0; i < 10; i++) {
        cout << "Semi stream " << i + 1 << endl;
        usleep(100000);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t thread;

    // Создание потока
    if (pthread_create(&thread, NULL, semiStream, NULL) != 0) {
        cerr << "Error" << endl;
        return 1;
    }

    if (pthread_join(thread, NULL) != 0) {
        cerr << "Error" << endl;
        return 1;
    }

    cout << "Main: After Semi" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "Main stream " << i + 1 << endl;
        usleep(100000);
    }
    return 0;
}