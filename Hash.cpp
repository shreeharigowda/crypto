#include <iostream>
#include <random>

using namespace std;

unsigned int custom_hash(const string& message) {
    hash<string> hasher;
    unsigned int hash_value = hasher(message);
    return hash_value;
}

int main() {
    string message;
    
    cout << "Enter the message: ";
    getline(cin, message);

    unsigned int hash_value = custom_hash(message);

    cout << "Original Message: " << message << endl;
    cout << "Hash value: " << hash_value << endl;

    // Simulate receiver computing the hash again
    string received_message;
    cout << "Enter the received message: ";
    getline(cin, received_message);
    unsigned int received_hash_value = custom_hash(received_message);

    cout << "Received Message: " << received_message << endl;
    cout << "Received Hash value: " << received_hash_value << endl;

    // Verify integrity
    if (received_hash_value == hash_value) {
        cout << "Integrity: The message has not been modified." << endl;
    } else {
        cout << "Integrity: The message has been modified." << endl;
    }

    return 0;
}
