#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <limits>

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

using namespace std;

void clearScreen()
{
    system(CLEAR_SCREEN);
}

void displayMenu(int msg)
{
    clearScreen();

    switch (msg)
    {
        case 0:
            cout << "Welcome to Text Editor" << endl << endl;
            break;
        case 1:
            cout << "File Created Successfully" << endl << endl;
            break;
        case 2:
            cout << "File Updated Successfully" << endl << endl;
            break;
        case 4:
            cout << "File Emptied Successfully" << endl << endl;
            break;
        case 5:
            cout << "File Deleted Successfully" << endl << endl;
            break;
        case 55:
            cout << "File Not Found" << endl << endl;
            break;
        case 6:
            cout << "File Copied Successfully" << endl << endl;
            break;
        default:
            break;
    }

    cout << "Main Menu" << endl;
    cout << "-------------" << endl;
    cout << "1. Create File" << endl;
    cout << "2. Add to File" << endl;
    cout << "3. Read from File" << endl;
    cout << "4. Empty File" << endl;
    cout << "5. Delete File" << endl;
    cout << "6. Copy File" << endl;
    cout << "7. Exit" << endl << endl;
}

void createFile()
{
    string filename;
    cout << endl << "Enter name of the file: ";
    cin.ignore();
    getline(cin, filename);

    ofstream myfile(filename + ".txt");
    myfile.close();

    displayMenu(1);
}

void addToFile()
{
    string filename;
    cout << endl << "Enter name of the file: ";
    cin >> filename;

    string text;
    cout << endl << "Enter text to write to file (Enter END to complete):" << endl;

    cin.ignore();
    while (true)
    {
        string line;
        getline(cin, line);

        if (line == "END")
        {
            break;
        }

        text += line + "\n";
    }

    ofstream myfile;
    myfile.open((filename + ".txt").c_str(), ios::app);
    if (!myfile)
    {
        cout << "Error opening file." << endl;
        displayMenu(0);
        return;
    }
    myfile << text;
    myfile.close();

    displayMenu(2);
}

void readFile()
{
    string filename;
    cout << endl << "Enter name of the file: ";
    cin >> filename;

    ifstream myfile(filename + ".txt");
    if (myfile.is_open())
    {
        string line;
        while (getline(myfile, line))
        {
            cout << line << endl;
        }

        myfile.close();
    }
    else
    {
        displayMenu(55);
    }

    cout << endl << "End of File. Press any key to return to the main menu: ";
    cin.ignore();
    cin.get();

    displayMenu(3);
}

void emptyFile()
{
    string filename;
    cout << endl << "Enter name of the file: ";
    cin >> filename;

    ofstream myfile(filename + ".txt");
    myfile.close();

    displayMenu(4);
}

void deleteFile()
{
    string filename;
    cout << endl << "Enter name of the file: ";
    cin >> filename;

    if (remove((filename + ".txt").c_str()) == 0)
    {
        displayMenu(5);
    }
    else
    {
        displayMenu(55);
    }
}

void copyFile()
{
    string sourceFilename;
    cout << endl << "Enter name of the file to copy from: ";
    cin.ignore();
    getline(cin, sourceFilename);

    ifstream sourceFile(sourceFilename + ".txt");
    if (!sourceFile.is_open())
    {
        displayMenu(55);
        return;
    }

    string destinationFilename;
    cout << endl << "Enter name of the file to copy to: ";
    getline(cin, destinationFilename);

    ofstream destinationFile(destinationFilename + ".txt", ios::app);
    if (!destinationFile)
    {
        cout << "Error opening destination file." << endl;
        sourceFile.close();
        displayMenu(0);
        return;
    }

    string line;
    while (getline(sourceFile, line))
    {
        destinationFile << line << endl;
    }

    sourceFile.close();
    destinationFile.close();

    displayMenu(6);
}

void runMenu() {
    int choice = 0;

    while (choice != 7)
    {
        displayMenu(0);

        cout << endl << "Enter Choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please enter a valid option. Press enter to continue." << endl;
            cin.ignore();
            continue;
        }

        switch (choice)
        {
            case 1:
                createFile();
                break;
            case 2:
                addToFile();
                break;
            case 3:
                readFile();
                break;
            case 4:
                emptyFile();
                break;
            case 5:
                deleteFile();
                break;
            case 6:
                copyFile();
                break;
            default:
                cout << "Invalid choice. Please enter a valid option. Press enter to continue." << endl;
                cin.ignore();
                break;
        }
    }
}

int main()
{
    runMenu();
    return 0;
}
