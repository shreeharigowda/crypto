#include <bits/stdc++.h>


using namespace std;

string generate_salt(int length = 8) {
    string salt_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-=_+";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, salt_characters.size() - 1);

    string salt;
    for (int i = 0; i < length; ++i) {
        salt += salt_characters[dis(gen)];
    }
    return salt;
}

string hash_password(const string& password, const string& salt) {
    string salted_password = password + salt;
    stringstream ss;
    for (size_t i = 0; i < salted_password.size(); ++i) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(salted_password[i]);
    }
    string hashed_password = ss.str();
    return hashed_password;
}

bool check_password(const string& password, const string& hashed_password, const string& salt) {
    string salted_password = password + salt;
    stringstream ss;
    for (size_t i = 0; i < salted_password.size(); ++i) {
        ss << hex << setw(2) << setfill('0') << static_cast<int>(salted_password[i]);
    }
    string hashed_input_password = ss.str();
    return hashed_password == hashed_input_password;
}

int main() {
    // Generate a password file based on user input
    int num_users;
    cout << "Enter the number of users: ";
    cin >> num_users;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    ofstream password_file("hashed_passwords.txt");
    if (!password_file) {
        cerr << "Failed to open the password file." << endl;
        return 1;
    }

    for (int i = 0; i < num_users; ++i) {
        string username, password;
        cout << "Enter the username for User" << i + 1 << ": ";
        getline(cin, username);
        cout << "Enter the password for User" << i + 1 << ": ";
        getline(cin, password);

        string salt = generate_salt();
        string hashed_password = hash_password(password, salt);

        password_file << username << ":" << hashed_password << ":" << salt << endl;
    }
    password_file.close();

    // Simulate user login
    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    getline(cin, password);

    ifstream hashed_password_file("hashed_passwords.txt");
    if (!hashed_password_file) {
        cerr << "Failed to open the password file." << endl;
        return 1;
    }

    string stored_username, stored_hashed_password, stored_salt;
    bool found = false;
    while (getline(hashed_password_file, stored_username, ':') &&
           getline(hashed_password_file, stored_hashed_password, ':') &&
           getline(hashed_password_file, stored_salt)) {
        if (stored_username == username) {
            found = true;
            break;
        }
    }
    hashed_password_file.close();

    if (found) {
        if (check_password(password, stored_hashed_password, stored_salt)) {
            cout << "Login successful." << endl;
        } else {
            cout << "Login failed. Invalid username or password." << endl;
        }
    } else {
        cout << "Login failed. Invalid username or password." << endl;
    }

    return 0;
}
