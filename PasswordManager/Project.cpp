#include <iostream>
#include <fstream>
#include <string>
#include<vector>

using namespace std;

class PasswordManager {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~PasswordManager() {}

    // Pure virtual function for logging in
    virtual bool Login(const string& username, const string& password) = 0;

    // Pure virtual function for signing up
    virtual bool SignUp(const string& username, const string& password) = 0;

    virtual string SeePassword(const string& username) = 0;


    // Pure virtual function for updating the password
    virtual bool UpdatePassword(const string& username, const string& oldPassword, const string& newPassword) = 0;
};

class Staff : public PasswordManager {
public:
    // Destructor
    ~Staff() override {}

    // Implementation of pure virtual functions

    bool Login(const string& username, const string& password) override {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);
                string filePassword = line.substr(pos + 2); // Skip the two spaces

                if (fileUsername == username && filePassword == password) {
                    cout << "Login successful" << endl;
                    file.close();
                    return true;
                }
            }
        }

        file.close();
        cerr << "Error: Invalid login credentials" << endl;
        return false;
    }

    bool SignUp(const string& username, const string& password) override {
        if (UserExists(username)) {
            cerr << "Error: User already exists" << endl;
            return false;
        }

        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << username << "  " << password << endl; // Write username and password with two spaces between
            file.close();
            cout << "SignUp successful" << endl;
            return true;
        }
        else {
            cerr << "Error: Unable to open file for signing up" << endl;
            return false;
        }
    }

    // Logic for SeePassword function
    string SeePassword(const string& username) override {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);
                string filePassword = line.substr(pos + 2); // Skip the two spaces

                if (fileUsername == username) {
                    file.close();
                    return filePassword;
                    
                }
            }
        }

        file.close();
        return "User not found";
    }

    bool UpdatePassword(const string& username, const string& oldPassword, const string& newPassword) override
    {
        ifstream file(filename);
        string line;
        vector<string> fileContents;

        while (getline(file, line))
        {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);
                string filePassword = line.substr(pos + 2); // Skip the two spaces

                if (fileUsername == username) {
                    if (filePassword == oldPassword) {
                        fileContents.push_back(fileUsername + "  " + newPassword);
                        cout << "Password updated successfully" << endl;
                    }
                    else {
                        cerr << "Error: Incorrect old password" << endl;
                        fileContents.push_back(line);
                    }
                }
                else {
                    fileContents.push_back(line);
                }
            }
        }

        file.close();

        ofstream outFile(filename);
        for (const auto& content : fileContents) {
            outFile << content << endl;
        }
        outFile.close();

        return false;
    }

private:
    const string filename = "./staffData.txt"; // Adjust the path as needed

    // Helper function to check if user already exists
    bool UserExists(const string& username) {
        ifstream file(filename);
        if (!file) {
            // File does not exist yet, so user does not exist
            return false;
        }

        string line;
        while (getline(file, line)) {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);

                if (fileUsername == username) {
                    file.close();
                    return true;
                }
            }
        }

        file.close();
        return false;
    }
};

class User : public PasswordManager {
public:
    // Destructor
    ~User() {}

    // Implementation of pure virtual functions
    bool Login(const string& username, const string& password) override {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);
                string filePassword = line.substr(pos + 2); // Skip the two spaces

                if (fileUsername == username && filePassword == password) {
                    cout << "Login successful" << endl;
                    file.close();
                    return true;
                }
            }
        }

        file.close();
        cerr << "Error: Invalid login credentials" << endl;
        return false;
    }

    bool SignUp(const string& username, const string& password) override {
        if (UserExists(username)) {
            cerr << "Error: User already exists" << endl;
            return false;
        }

        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << username << "  " << password << endl; // Write username and password with two spaces between
            file.close();
            cout << "SignUp successful" << endl;
            return true;
        }
        else {
            cerr << "Error: Unable to open file for signing up" << endl;
            return false;
        }
    }

    // Logic for SeePassword function
    string SeePassword(const string& username) override {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);
                string filePassword = line.substr(pos + 2); // Skip the two spaces

                if (fileUsername == username) {
                    file.close();
                    return filePassword;

                }
            }
        }

        file.close();
        return "User not found";
    }

    bool UpdatePassword(const string& username, const string& oldPassword, const string& newPassword) override
    {
        ifstream file(filename);
        string line;
        vector<string> fileContents;

        while (getline(file, line))
        {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);
                string filePassword = line.substr(pos + 2); // Skip the two spaces

                if (fileUsername == username) {
                    if (filePassword == oldPassword) {
                        fileContents.push_back(fileUsername + "  " + newPassword);
                        cout << "Password updated successfully" << endl;
                    }
                    else {
                        cerr << "Error: Incorrect old password" << endl;
                        fileContents.push_back(line);
                    }
                }
                else {
                    fileContents.push_back(line);
                }
            }
        }

        file.close();

        ofstream outFile(filename);
        for (const auto& content : fileContents) {
            outFile << content << endl;
        }
        outFile.close();

        return false;
    }

private:
    const string filename = "./userData.txt"; // Adjust the path as needed

    // Helper function to check if user already exists
    bool UserExists(const string& username) {
        ifstream file(filename);
        if (!file) {
            // File does not exist yet, so user does not exist
            return false;
        }

        string line;
        while (getline(file, line)) {
            size_t pos = line.find("  "); // Two spaces between username and password
            if (pos != string::npos) {
                string fileUsername = line.substr(0, pos);

                if (fileUsername == username) {
                    file.close();
                    return true;
                }
            }
        }

        file.close();
        return false;
    }
    
};


int main()
{
    Staff staffMember;
    User userMember;

    while (true)
    {
        cout << "Welcome to the futuristic Secure Password Manager!" << endl;
        cout << "Kindly Select One Option Below" << endl;
        cout << "1. Login as User" << endl;
        cout << "2. Login as Staff" << endl;
        cout << "3. Signup as User" << endl;
        cout << "4. Signup as Staff" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        string username, password, oldPassword, newPassword;

        switch (choice)
        {
        case 1: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (userMember.Login(username, password)) {
                int userChoice;
                do {
                    cout << "1. Update Password" << endl;
                    cout << "2. See Password" << endl;
                    cout << "3. Exit" << endl;
                    cin >> userChoice;

                    switch (userChoice) {
                    case 1:
                        cout << "Enter old password: ";
                        cin >> oldPassword;
                        cout << "Enter new password: ";
                        cin >> newPassword;
                        userMember.UpdatePassword(username, oldPassword, newPassword);
                        break;
                    case 2:
                        cout << "Password: " << userMember.SeePassword(username) << endl;
                        break;
                    case 3:
                        cout << "Exiting..." << endl;
                        break;
                    default:
                        cout << "Invalid option. Please choose again." << endl;
                    }
                } while (userChoice != 3);
            }
            break;
        }
        case 2: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (staffMember.Login(username, password)) {
                int staffChoice;
                do {
                    cout << "1. Update Password" << endl;
                    cout << "2. See Password" << endl;
                    cout << "3. Exit" << endl;
                    cin >> staffChoice;

                    switch (staffChoice) {
                    case 1:
                        cout << "Enter old password: ";
                        cin >> oldPassword;
                        cout << "Enter new password: ";
                        cin >> newPassword;
                        staffMember.UpdatePassword(username, oldPassword, newPassword);
                        break;
                    case 2:
                        cout << "Password: " << staffMember.SeePassword(username) << endl;
                        break;
                    case 3:
                        cout << "Exiting..." << endl;
                        break;
                    default:
                        cout << "Invalid option. Please choose again." << endl;
                    }
                } while (staffChoice != 3);
            }
            break;
        }
        case 3: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            userMember.SignUp(username, password);
            break;
        }
        case 4: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            staffMember.SignUp(username, password);
            break;
        }
        case 5: {
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        }
        default: {
            cout << "Invalid option. Please choose again." << endl;
            break;
        }
        }
    }

    return 0;
}
