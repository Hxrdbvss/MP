#include <iostream>
#include <pthread.h>
#include <vector>
#include <string>
#include <unistd.h>

using namespace std;

struct ThreadParams {
    int id;
    vector<string> messages;
};

void* threadFunction(void* arg) {
    ThreadParams* params = (ThreadParams*)arg;
    int id = params->id;
    vector<string> messages = params->messages;

    cout << "Thread " << id << ":\n";
    for (const string& message : messages) {
        cout << message << endl;
        usleep(100000); 
    }
    pthread_exit(NULL);
}

int main() {
    vector<vector<string>> allMessages = {
        {"Message 1 from Thread 1", "Message 2 from Thread 1", "Message 3 from Thread 1"},
        {"Message 1 from Thread 2", "Message 2 from Thread 2", "Message 3 from Thread 2"},
        {"Message 1 from Thread 3", "Message 2 from Thread 3", "Message 3 from Thread 3"},
        {"Message 1 from Thread 4", "Message 2 from Thread 4", "Message 3 from Thread 4"}
    };

    pthread_t threads[4];

    for (int i = 0; i < 4; ++i) {
        ThreadParams params;
        params.id = i + 1;
        params.messages = allMessages[i];

        if (pthread_create(&threads[i], NULL, threadFunction, (void*)&params) != 0) {
            cerr << "Error: Couldn't create Thread " << i + 1 << endl;
            return 1;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            cerr << "Error joining Thread " << i + 1 << endl;
            return 1;
        }
    }

    return 0;
}

