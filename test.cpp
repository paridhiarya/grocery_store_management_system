#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>

using namespace std;

class inventory
{
public:
    string ID;
    string S_NO;
    string PRODUCT;
    string QTY_IN_STOCK;
    int UNIT_PRICE;
    string QTY_SOLD;
    string SALES_VALUE;

    void add_Data(string a, string b, string c, string d, string e, string f, string g)
    {
        stringstream obj;
        int int_e;
        ID = a;
        S_NO = b;
        PRODUCT = c;
        QTY_IN_STOCK = d;
        obj << e;
        obj >> int_e;
        UNIT_PRICE = int_e;
        QTY_SOLD = f;
        SALES_VALUE = g;
    }

    void insert_intable((sqlite3* DB)
    {
        string query("INSERT INTO INVENTORY VALUES('" + ID + "', " + S_NO + ", '" + PRODUCT + "', " + QTY_IN_STOCK + ", " + UNIT_PRICE + ", " + QTY_SOLD + ", " + SALES_VALUE ");");
        int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

        if (rc != SQLITE_OK)
        {
            cout << "Unable to delete supplier." << endl;
        }
        else
        {
            cout << "Deleted." << endl;
        }
    }
};

int main()
{
    char ch;
    const char* fileName = "inventory.csv";

    // declare object
    ifstream file;
    string str, word;
    inventory item;

    sqlite3* DB;
    char s[] = "C:\\Users\\Paridhi\\Dropbox\\PC\\Documents\\Notes\\Semester 3\\OOP\\project\\databases\\employees.db";
    int exit1 = 0, login_ch = 0;
    exit1 = sqlite3_open(s, &DB);
    int interface1 = 0, interface2 = 0, interface1_flag = 0, interface2_flag = 0;

    if (exit1) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        return (-1);
    }
    else
        cout << "Opened Database Successfully!" << endl;


    // open file
    file.open(fileName, ios::in);
    if (!file)
    {
        cout << "Error in opening file!!!" << endl;
        return -1; // return from main
    }

    // // read and print file content
    // while (!file.eof())
    // {
    //     getline(file, str, ',');
    //     cout << str << " ";
    // }
    // // close the file

    // while (!file.eof())
    // {
    //     getline(file, str);
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.ID;
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.S_NO;
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.PRODUCT;
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.ID;
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.UNIT_PRICE;
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.QTY_SOLD;
    //     getline(str, word, ',');
    //     cout << word << " ";
    //     cin >> item.SALES_VALUE;
    //}

    vector<string> v;

    while (!file.eof())
    {
        getline(file, str);
        stringstream ss(str);
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            v.push_back(substr);
        }

        for (size_t i = 0; i < v.size(); i++)
            cout << v[i] << endl;
        item.add_Data(v[0], v[1], v[2], v[3], v[4], v[5], v[6]);
        item.insert_intable();
    }

    file.close();
    return 0;
}
