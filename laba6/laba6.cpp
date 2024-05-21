void sleepSort(const string& word) {
    this_thread::sleep_for(chrono::milliseconds(word.length() * 100)); 
    std::cout << word << endl;
}

void main() {
    vector<string> words;
    cout << "Enter the number of valid lines: ";
    int a;
    cin >> a;
    for (int i = 0; i < a; i++) {
        string word;
        cin >> word;
        words.push_back(word);
    }

    vector<thread> threads;
    for (const string& word : words) {
        threads.emplace_back(sleepSort, word);
    }

    for (thread& th : threads) {
        th.join();
    }
}