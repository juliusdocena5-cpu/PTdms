#include <iostream>
#include <string>
#include <filesystem>
#include <dirent.h>  
using namespace std;
namespace fs = std::filesystem;

void listFiles() {
    int choice;
    cout << "1. List All Files\n2. List Files by Extension\n3. List Files by Pattern\nEnter choice: ";
    cin >> choice;
    
   
    if (choice == 1) {
        cout << "Files in current directory:\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (fs::is_regular_file(entry.status())) {
                cout << "- " << entry.path().filename().string() << endl;
            }
        }
    }
   
    else if (choice == 2) {
        string extension;
        cout << "Enter file extension (e.g., .txt): ";
        cin >> extension;
        cout << "Files with " << extension << " extension in current directory:\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (fs::is_regular_file(entry.status()) && entry.path().extension() == extension) {
                cout << "- " << entry.path().filename().string() << endl;
            }
        }
    }

    else if (choice == 3) {
        string pattern;
        cout << "Enter file pattern (e.g., 'moha*.*'): ";
        cin >> pattern;
        cout << "Files matching pattern '" << pattern << "' in current directory:\n";
        for (const auto& entry : fs::directory_iterator(fs::current_path())) {
            if (fs::is_regular_file(entry.status())) {
                string filename = entry.path().filename().string();
                if (filename.find(pattern) != string::npos) {
                    cout << "- " << filename << endl;
                }
            }
        }
    }
}


void createDirectory() {
    string dirName;
    cout << "Enter directory name: ";
    cin >> dirName;
    
    if (fs::exists(dirName)) {
        cout << "Error: Directory \"" << dirName << "\" already exists!" << endl;
    } else {
        fs::create_directory(dirName);
        cout << "Directory \"" << dirName << "\" created successfully." << endl;
    }
}


void changeDirectory() {
    int choice;
    cout << "1. Move to Parent Directory\n2. Move to Root Directory\n3. Enter Custom Path\nEnter choice: ";
    cin >> choice;
    
    string path;
    
    switch (choice) {
        case 1:
           
            path = fs::current_path().parent_path().string();
            break;
        case 2:
           
            #ifdef _WIN32
               
                path = "C:\\";
            #else
               
                path = "/";
            #endif
            break;
        case 3:
           
            cout << "Enter path: ";
            cin >> path;
            break;
        default:
            cout << "Invalid choice!" << endl;
            return;
    }
    
    if (fs::exists(path) && fs::is_directory(path)) {
        fs::current_path(path);
        cout << "Current directory changed to: " << fs::current_path() << endl;
    } else {
        cout << "Error: Directory \"" << path << "\" not found!" << endl;
    }
}


void mainMenu() {
    int choice;
    do {
        cout << "\nMain Menu:\n";
        cout << "[1] List Files\n[2] Create Directory\n[3] Change Directory\n[4] Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                listFiles();
                break;
            case 2:
                createDirectory();
                break;
            case 3:
                changeDirectory();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 4);
}

int main() {
    
    mainMenu();
    return 0;
}
    