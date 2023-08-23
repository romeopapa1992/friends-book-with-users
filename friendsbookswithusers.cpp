#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

struct User 
{
    int id = 0;
    string username = "", password = "";
};

struct Friend 
{
    int id = 0;
    int userId = 0;
    string firstName = "", lastName = "", phoneNumber = "", email = "", address = "";
};

string readLine()
{
    string input;
    getline(cin, input);
    return input;
}

void printMainMenu()
{
    cout << "MAIN MENU" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Quit the program" << endl;
}

void printAddressBookMenu()
{
    cout << "----- ADDRESS BOOK -----" << endl;
    cout << "1. Add a friend" << endl;
    cout << "2. Search by first name" << endl;
    cout << "3. Search by last name" << endl;
    cout << "4. Display all friends" << endl;
    cout << "5. Delete friend" << endl;
    cout << "6. Edit friend" << endl;
    cout << "7. Change password" << endl;
    cout << "8. Logout" << endl;
    cout << "Choice: ";
}

void saveUserData(const vector<User>& userList) 
{
    ofstream file("Users.txt");
    if (file.is_open()) 
    {

        for (const User& user : userList) 
        {
            file << user.id << '|'
                 << user.username << '|'
                 << user.password << '|' << endl;
        }

        file.close();
    } 
    else 
    {
        cout << "Cannot open the file." << endl;
    }
}

void addUser(vector<User>& userList) 
{
    User newUser;

    cout << "Enter a username: ";
    cin >> newUser.username;

    for (const User& user : userList) 
    {
        if (user.username == newUser.username) 
        {
            cout << "Username already exists. Choose a different username." << endl;
            return;
        }
    }

    cout << "Enter a password: ";
    cin >> newUser.password;

    newUser.id = userList.size() + 1; 
    userList.push_back(newUser);

    saveUserData(userList);

    cout << "User registration successful." << endl;
}

void readUserData(vector<User>& userList)
{
    ifstream file("Users.txt");
    if (file.good())
    {
        string line;
        while (getline(file, line))
        {
            User newUser;
            stringstream ss(line);
            string field;

            getline(ss, field, '|');
            if (isdigit(field[0]))
            {
                newUser.id = stoi(field);
            }

            getline(ss, newUser.username, '|');
            getline(ss, newUser.password, '|');

            userList.push_back(newUser);
        }

        file.close();
    }
    else
    {
        cout << "File doesn't exist. Starting with an empty user list." << endl;
    }
}

bool loginUser(vector<User>& userList, int& loggedUserId) 
{
    string username, password;
    cout << "Enter username: ";
    cin.ignore();
    username = readLine();
    cout << "Enter password: ";
    password = readLine();

    for (const User& user : userList) 
    {
        if (user.username == username && user.password == password) 
        {
            loggedUserId = user.id;
            return true;
        }
    }

    return false;
}

void saveFriendData(const vector<Friend>& friendList) 
{
    ofstream file("Friends.txt");  
    if (file.is_open()) 
    {
        for (const Friend& friendObj : friendList) 
        {
            file << friendObj.id << '|'
                 << friendObj.userId << '|'
                 << friendObj.firstName << '|'
                 << friendObj.lastName << '|'
                 << friendObj.phoneNumber << '|'
                 << friendObj.email << '|'
                 << friendObj.address << '|' << endl;
        }
        file.close();
    } 
    else 
    {
        cout << "Cannot open the file." << endl;
    }
}

void printFriendDetails(const Friend& friendObj) 
{
    cout << "ID: " << friendObj.id << endl;
    cout << "First Name: " << friendObj.firstName << endl;
    cout << "Last Name: " << friendObj.lastName << endl;
    cout << "Phone Number: " << friendObj.phoneNumber << endl;
    cout << "Email: " << friendObj.email << endl;
    cout << "Address: " << friendObj.address << endl;
    cout << endl;
}

void addFriend(vector<Friend>& friendList, int userId) 
{
    Friend newFriend;

    cout << "Enter first name: ";
    cin.ignore();
    newFriend.firstName = readLine();
    cout << "Enter last name: ";
    newFriend.lastName = readLine();
    cout << "Enter phone number: ";
    newFriend.phoneNumber = readLine();
    cout << "Enter email: ";
    newFriend.email = readLine();
    cout << "Enter address: ";
    newFriend.address = readLine();

    newFriend.id = friendList.empty() ? 1 : friendList.back().id + 1;

    newFriend.userId = userId;

    friendList.push_back(newFriend);

    saveFriendData(friendList);
    cout << "Added a new friend." << endl;
}

void readFriendData(vector<Friend>& friendList) 
{
    ifstream file("Friends.txt");
    if (file.good()) {
        string line;
        while (getline(file, line)) 
        {
            Friend newFriend;
            stringstream ss(line);
            string field;

            getline(ss, field, '|');
            if (isdigit(field[0])) 
            {
                newFriend.id = stoi(field);
            }

            getline(ss, field, '|');
            if (isdigit(field[0])) 
            {
                newFriend.userId = stoi(field);
            }

            getline(ss, newFriend.firstName, '|');
            getline(ss, newFriend.lastName, '|');
            getline(ss, newFriend.phoneNumber, '|');
            getline(ss, newFriend.email, '|');
            getline(ss, newFriend.address, '|');

            friendList.push_back(newFriend);
        }
        file.close();
    } 
    else 
    {
        cout << "File doesn't exist. Starting with an empty friend list." << endl;
    }
}

void searchByFirstName(const vector<Friend>& friendList, const string& firstName) 
{
    bool found = false;

    for (const Friend& friendObj : friendList) 
    {
        if (friendObj.firstName == firstName) 
        {
            printFriendDetails(friendObj);
            found = true;
        }
    }

    if (!found) 
    {
        cout << "No friend found with the given first name." << endl;
    }
}

void searchByLastName(const vector<Friend>& friendList, const string& lastName) 
{
    bool found = false;

    for (const Friend& friendObj : friendList) 
    {
        if (friendObj.lastName == lastName) 
        {
            printFriendDetails(friendObj);
            found = true;
        }
    }

    if (!found) 
    {
        cout << "No friend found with the given last name." << endl;
    }
}

void displayAllFriends(const vector<Friend>& friendList, int userId) 
{
    if (friendList.empty()) 
    {
        cout << "No friends saved." << endl;
    } 
    else 
    {
        for (const Friend& friendObj : friendList) 
        {
            if (friendObj.userId == userId) 
            {
                printFriendDetails(friendObj);
            }
        }
    }
}

void deleteFriend(vector<Friend>& friendList, int userId) 
{
    int id;
    cout << "Enter the ID of the friend to delete: ";
    cin >> id;

    auto it = friendList.begin();
    while (it != friendList.end()) 
    {
        if (it->id == id && it->userId == userId) 
        {
            cout << "Are you sure you want to delete this friend? (Press 't' to confirm): ";
            char confirm;
            cin >> confirm;

            if (confirm == 't' || confirm == 'T') 
            {
                it = friendList.erase(it);
                cout << "Friend with ID " << id << " has been deleted." << endl;
                saveFriendData(friendList);
            } 
            else 
            {
                cout << "Deletion canceled." << endl;
                ++it;
            }
            return;
        } 
        else 
        {
            ++it;
        }
    }
    
    cout << "No friend found with the given ID." << endl;
}

void editFriend(vector<Friend>& friendList, int userId) 
{
    int id;
    cout << "Enter the ID of the friend to edit: ";
    cin >> id;
    bool found = false;

    for (Friend& friendObj : friendList) 
    {
        if (friendObj.id == id && friendObj.userId == userId) 
        {
            cout << "Select the field to edit:" << endl;
            cout << "1 - First Name" << endl;
            cout << "2 - Last Name" << endl;
            cout << "3 - Phone Number" << endl;
            cout << "4 - Email" << endl;
            cout << "5 - Address" << endl;
            cout << "6 - Go back to the menu" << endl;
            cout << "Choice: ";

            int choice;
            cin >> choice;

            switch (choice) 
            {
                case 1:
                    cout << "Enter new first name: ";
                    friendObj.firstName = readLine();
                    break;
                case 2:
                    cout << "Enter new last name: ";
                    friendObj.lastName = readLine();
                    break;
                case 3:
                    cout << "Enter new phone number: ";
                    friendObj.phoneNumber = readLine();
                    break;
                case 4:
                    cout << "Enter new email: ";
                    friendObj.email = readLine();
                    break;
                case 5:
                    cout << "Enter new address: ";
                    friendObj.address = readLine();
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
            found = true;
            break;
        }
    }

    if (!found) 
    {
        cout << "No friend found with the given ID." << endl;
    }
    saveFriendData(friendList);
}

void changePassword(vector<User>& userList, int userId) 
{
    string newPassword;
    cout << "Enter a new password: ";
    cin >> newPassword;

    for (User& user : userList) 
    {
        if (user.id == userId) 
        {
            user.password = newPassword;
            saveUserData(userList); 
            cout << "Password changed successfully." << endl;
            return;
        }
    }
    cout << "User not found." << endl;
}

int main() 
{
    vector<User> userList;
    readUserData(userList);

    vector<Friend> friendList;
    readFriendData(friendList);

    int choice = 0;
    int loggedUserId = -1;

    while (true) 
    {
        if (loggedUserId == -1) 
        {
            printMainMenu();
            cin >> choice;

            switch (choice) 
            {
                case 1:
                    if (loginUser(userList, loggedUserId)) 
                    {
                        cout << "Login successful." << endl;
                    } 
                    else 
                    {
                        cout << "Login failed." << endl;
                    }
                    break;
                case 2:
                    addUser(userList);
                    break;
                case 3:
                    cout << "Goodbye!" << endl;
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        } 
        else 
        {
            printAddressBookMenu();
            cin >> choice;

            switch (choice) 
            {
                case 1:
                    addFriend(friendList, loggedUserId);
                    break;
                case 2: 
                    cout << "Enter first name to search: ";
                    cin.ignore(); 
                    searchByFirstName(friendList, readLine());
                    break;
                case 3:
                    cout << "Enter last name to search: ";
                    cin.ignore(); 
                    searchByLastName(friendList, readLine());
                    break;
                case 4:
                    displayAllFriends(friendList, loggedUserId);
                    break;
                case 5:
                    deleteFriend(friendList, loggedUserId);
                    break;
                case 6:
                    editFriend(friendList, loggedUserId);
                    break;
                case 7:
                    changePassword(userList, loggedUserId);
                    cout << "Logged out." << endl;
                    loggedUserId = -1;
                    saveFriendData(friendList);
                    break;
                case 8:
                    cout << "Logged out." << endl;
                    loggedUserId = -1;
                    saveFriendData(friendList);
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }
        }
    }

    return 0;
} 