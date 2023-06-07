#include <bits/stdc++.h>


using namespace std;


int prime_checker(int p) {
    // Checks if the number entered is a prime number or not
    if (p < 1) {
        return -1;
    } else if (p > 1) {
        if (p == 2) {
            return 1;
        }
        for (int i = 2; i < p; i++) {
            if (p % i == 0) {
                return -1;
            }
            return 1;
        }
    }
    return 1;
}

int primitive_check(int g, int p, vector<int>& L) {
    // Checks if the entered number is a primitive root or not
    for (int i = 1; i < p; i++) {
        int result = static_cast<int>(pow(g, i));
        L.push_back(result % p);
    }
    for (int i = 1; i < p; i++) {
        if (count(L.begin(), L.end(), i) > 1) {
            L.clear();
            return -1;
        }
    }
    return 1;
}



int main() {
    vector<int> l;
    int P;

    while (true) {
        cout << "Enter P: ";
        cin >> P;

        if (prime_checker(P) == -1) {
            cout << "Number is not prime, please enter again!" << endl;
            continue;
        }
        break;
    }

    int G;

    while (true) {
        cout << "Enter the primitive root of " << P << ": ";
        cin >> G;

        if (primitive_check(G, P, l) == -1) {
            cout << "Number is not a primitive root of " << P << ", please try again!" << endl;
            continue;
        }
        break;
    }

    int x1, x2;

    while (true) {
        cout << "Enter the private key of User 1: ";
        cin >> x1;
        cout << "Enter the private key of User 2: ";
        cin >> x2;

        if (x1 >= P || x2 >= P) {
            cout << "Private key of both users should be less than " << P << "!" << endl;
            continue;
        }
        break;
    }

    int y1 = static_cast<int>(pow(G, x1)) % P;
    int y2 = static_cast<int>(pow(G, x2)) % P;

    int k1 = static_cast<int>(pow(y2, x1)) % P;
    int k2 = static_cast<int>(pow(y1, x2)) % P;

    cout << "\nSecret Key for User 1 is: " << k1 << endl;
    cout << "Secret Key for User 2 is: " << k2 << endl;

    if (k1 == k2) {
        cout << "Keys have been exchanged successfully." << endl;
    } else {
        cout << "Keys have not been exchanged successfully." << endl;
    }

    return 0;
}
