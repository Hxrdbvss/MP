#include <iostream>
#include <cmath>
#include <vector>
#include <future>
#include <iomanip>
#include <csignal>
#include <atomic>

using namespace std;

atomic<bool> keepRunning(true);

void signalHandler(int signum)
{
    if (signum == SIGINT)
    {
        keepRunning = false;
        cout << " Received SIGINT. Exiting..." << endl;
    }
}

long double picalculation(int start, int end)
{
    long double sum = 0;
    for (int i = start; i <= end; i++) {
        sum += ((pow(-1, i)) / (2 * i + 1));
    }
    return sum;
}

void Calculation()
{
    int threadcount;
    cin >> threadcount;
    int iteration = 1000000000 / threadcount;
    long double pi = 0;
    vector<future<long double>> futures(threadcount); 
    for (int i = 0; i < threadcount; i++) {
        int start = i * iteration;
        int end = (i == threadcount - 1) ? 1000000000 - 1 : start + iteration - 1;
        futures[i] = async(launch::async, picalculation, start, end);
    }

    for (auto& future : futures) {
        long double result = future.get();
        pi = pi + result;
    }
    pi = pi * 4;
    cout << setprecision(10) << pi << endl;
}

int main()
{
    signal(SIGINT, signalHandler);
    while (keepRunning) {
        Calculation();
    }

    return 0;
}