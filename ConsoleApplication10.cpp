#include <iostream>
#include <thread>

using namespace std;
void threadF() {
    for (int i = 0; i < 10; ++i) {
        cout << "Semi stream: " << i << endl;
    }
}

int main() {
    thread t(threadF);
    for (int i = 0; i < 10; ++i) {
        cout << "Main stream: " << i << endl;
    }
    t.join(); 
    return 0;
}
