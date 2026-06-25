#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class shopping {
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu() {
    int choice;
    string email;
    string password;

    while (true) {
        cout << "\n\t\t\tSUPERMARKET MAIN MENU\n";
        cout << "\t\t\t1) Administrator\n";
        cout << "\t\t\t2) Customer\n";
        cout << "\t\t\t3) Exit\n";
        cout << "\t\t\tPlease select an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\t\t\tPlease login\n";
                cout << "\t\t\tEnter email: ";
                cin >> email;
                cout << "\t\t\tPassword: ";
                cin >> password;

                if (email == "supermarketuser@gmail.com" && password == "super#234") {
                    administrator();
                } else {
                    cout << "Incorrect email/password.\n";
                }
                break;

            case 2:
                buyer();
                break;

            case 3:
                cout << "Exiting program.\n";
                exit(0);

            default:
                cout << "Please select a valid option.\n";
        }
    }
}

void shopping::administrator() {
    int choice;

    while (true) {
        cout << "\n\t\t\tAdministrator Menu\n";
        cout << "\t\t\t1) Add the product\n";
        cout << "\t\t\t2) Modify the product\n";
        cout << "\t\t\t3) Delete the product\n";
        cout << "\t\t\t4) Back to main menu\n";
        cout << "\t\t\tPlease enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;

            case 2:
                edit();
                break;

            case 3:
                rem();
                break;

            case 4:
                return;

            default:
                cout << "Invalid choice.\n";
        }
    }
}

void shopping::buyer() {
    int choice;

    while (true) {
        cout << "\n\t\t\tBuyer\n";
        cout << "\t\t\t1) Buy product\n";
        cout << "\t\t\t2) Go back\n";
        cout << "\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                receipt();
                break;

            case 2:
                return;

            default:
                cout << "Invalid choice.\n";
        }
    }
}

void shopping::add() {
    fstream data;
    int c;
    float p, d;
    string n;

    cout << "\n\n\t\tAdd new product\n";
    cout << "\tProduct code: ";
    cin >> pcode;
    cout << "\tProduct name: ";
    cin >> pname;
    cout << "\tProduct price: ";
    cin >> price;
    cout << "\tProduct discount: ";
    cin >> dis;

    data.open("database.txt", ios::in);
    if (data) {
        while (data >> c >> n >> p >> d) {
            if (c == pcode) {
                cout << "Product recorded \n";
                data.close();
                return;
            }
        }
        data.close();
    }

    data.open("database.txt", ios::app | ios::out);
    data << pcode << " " << pname << " " << price << " " << dis << "\n";
    data.close();
    cout << "Record inserted.\n";
}

void shopping::edit() {
    fstream data, data1;
    int pkey, token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\t\tModify the record\n";
    cout << "\tProduct code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist.\n";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    while (data >> pcode >> pname >> price >> dis) {
        if (pkey == pcode) {
            cout << "\tNew product code: ";
            cin >> c;
            cout << "\tProduct name: ";
            cin >> n;
            cout << "\tPrice: ";
            cin >> p;
            cout << "\tDiscount: ";
            cin >> d;
            data1 << c << " " << n << " " << p << " " << d << "\n";
            cout << "Record edited.\n";
            token++;
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
    }

    data.close();
    data1.close();
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
        cout << "Record not found.\n";
    }
}

void shopping::rem() {
    fstream data, data1;
    int pkey, token = 0;

    cout << "\n\t\tDelete product\n";
    cout << "\tProduct code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist.\n";
        return;
    }

    data1.open("database1.txt", ios::app | ios::out);
    while (data >> pcode >> pname >> price >> dis) {
        if (pkey == pcode) {
            cout << "Product deleted successfully.\n";
            token++;
        } else {
            data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
        }
    }

    data.close();
    data1.close();
    remove("database.txt");
    rename("database1.txt", "database.txt");

    if (token == 0) {
        cout << "Record not found.\n";
    }
}

void shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Database not found!\n";
        return;
    }

    cout << "\n\nProduct Code\tName\tPrice\n";
    while (data >> pcode >> pname >> price >> dis) {
        cout << pcode << "\t\t" << pname << "\t" << price << "\n";
    }
    data.close();
}

void shopping::receipt() {
    fstream data;
    int arrc[100], arrq[100], c = 0;
    char choice;
    float amount, total = 0;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "Database is empty.\n";
        return;
    }

    list();
    cout << "\nPlease place the order.\n";

    do {
        cout << "\nEnter product code: ";
        cin >> arrc[c];
        cout << "Enter the quantity: ";
        cin >> arrq[c];
        c++;
        cout << "Do you want to buy another product? (y/n): ";
        cin >> choice;
    } while (choice == 'y');

    cout << "\n\nRECEIPT\n";
    cout << "Product No\tName\tQuantity\tPrice\tAmount with Discount\n";

    for (int i = 0; i < c; i++) {
        data.clear();  // clear eof state
        data.seekg(0); // go back to the start
        while (data >> pcode >> pname >> price >> dis) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                total += amount - (amount * dis / 100);
                cout << pcode << "\t" << pname << "\t" << arrq[i] << "\t\t" << price << "\t" << amount - (amount * dis / 100) << "\n";
                break;
            }
        }
    }
    data.close();

    cout << "\nTotal Amount: " << total << "\n";
}

int main() {
    shopping s;
    s.menu();
}

