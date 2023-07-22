#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <sstream>
#include <iomanip>

using namespace std;

class employees {
protected:
    string emp_id;
    string FIRST_NAME;
    string LAST_NAME;
    char GENDER;
    int AGE;
    string DESIGNATION;
    int SALARY;
    int YEAR_OF_JOINING;
    string EMAIL;
    int PHONE_NO;
    string  PASSWORD1;
    string  PASSWORD2;

public:
    void view_inventory(sqlite3* DB);
    void inventory_restock(sqlite3* DB);
    void remove_from_inventory(sqlite3* DB);
    void view_customer_logs(sqlite3* DB);

};

class inventory {
public:
    string ID;
    string S_NO;
    string PRODUCT;
    string QTY_IN_STOCK;
    int UNIT_PRICE;
    string QTY_SOLD;
    string SALES_VALUE;
};

class suppliers {
    string phone;
    string email;
public:
    string S_ID;
    string name;
    string years_of_business;
    string last_purchase;
};

class manager : public employees {
public:
    void view_suppliers(sqlite3* db);
    void add_suppliers(sqlite3* db);
    void delete_suppliers(sqlite3* db);
    void view_employees(sqlite3* db);
    void promote_employee(sqlite3* db);
    void update_emp_salary(sqlite3* db);
};

void table_inventory(sqlite3* DB);
void table_employees(sqlite3* DB);
void table_suppliers(sqlite3* DB);
void data_employees(sqlite3* DB);
void data_inventory(sqlite3* DB);
void data_suppliers(sqlite3* DB);
int emp_login(sqlite3* DB, string emp_id);
int m_login(sqlite3* DB, string m_id);

int qty_updated_restock = 0;
int qty_removed = 0;
int new_sales = 0, qty_sold = 0;
int no_emp = 0;

int main(int argc, char** argv)
{
    sqlite3* DB;
    char s[] = "C:\\Users\\Paridhi\\Dropbox\\PC\\Documents\\Notes\\Semester 3\\OOP\\project\\databases\\employees.db";
    int exit1 = 0, login_ch = 0;
    exit1 = sqlite3_open(s, &DB);
    int interface1 = 0, interface2 = 0, interface1_flag = 0, interface2_flag = 0;

    if (exit1) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        return (-1);
    }

    /*
    table_inventory(DB);
    table_employees(DB);
    table_suppliers(DB);

    data_employees(DB);
    data_inventory(DB);
    data_suppliers(DB);
    char* messageError;
    string sql("DROP TABLE SUPPLIERS;");
    sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    */

    employees emp;
    manager mngr;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\tFRESHLY GROCERY STORE\n";
    cout << "\t\t\t\t\t\t\t\t   GROCERY STORE MANAGEMENT SYSTEM\n";
    cout << "\t\t\t\t\t\t\t\t\t   OOP Project 2022\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\tEmployee Interface\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\tWelcome User!" << endl;
    cout << "\t\t\t\t\t\t\t\t\t LOGIN PORTAL" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t1. Employee login" << endl;
    cout << "\t\t\t\t\t\t\t\t\t2. Manager login" << endl;
    cout << "\t\t\t\t\t\t\t\t\tEnter your choice: ";
    cin >> login_ch;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    if (login_ch == 1) {
        string emp_id;
        cout << "Enter Employee ID: " << endl;
        cin >> emp_id;
        interface1 = emp_login(DB, emp_id);
        if (interface1 == 1) interface1_flag = 1;
        else cout << "Exitting.";
    }
    else if (login_ch == 2) {
        string m_id;
        cout << "Enter Employee ID: " << endl;
        cin >> m_id;
        interface2 = m_login(DB, m_id);
        if (interface2 == 1) interface2_flag = 1;
        else cout << "Exitting.";
    }
    else {
        cout << "Invalid Choice. Exitting." << endl;
    }


    int ch = 100;
    while ((ch != 0) && (interface1_flag == 1)) {
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "Welcome to Employee Interface" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "1. View Inventory" << endl;
        cout << "2. Restock Items" << endl;
        cout << "3. Remove Damaged goods" << endl;
        cout << "4. View Customer logs" << endl;
        cout << "! Press 0 to exit !" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "Enter your choice:" << endl;
        cin >> ch;
        switch (ch) {
        case 1:
            emp.view_inventory(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 2:
            emp.inventory_restock(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 3:
            emp.remove_from_inventory(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 4:
            emp.view_customer_logs(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 0:
            exit(-1);
            break;
        }

    }

    while ((ch != 0) && (interface2_flag == 1)) {
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "Welcome to Manager Interface" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "1. View Suppliers List" << endl;
        cout << "2. Add Suppliers" << endl;
        cout << "3. Remove Suppliers" << endl;
        cout << "4. View Employee Details" << endl;
        cout << "5. Promote an Employee" << endl;
        cout << "6. Update Salary of Employee" << endl;
        cout << "! Press 0 to exit !" << endl;
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "Enter your choice:" << endl;
        cin >> ch;
        switch (ch) {
        case 1:
            mngr.view_suppliers(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 2:
            mngr.add_suppliers(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 3:
            mngr.delete_suppliers(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 4:
            mngr.view_employees(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 5:
            mngr.promote_employee(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 6:
            mngr.update_emp_salary(DB);
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            break;
        case 0:
            exit(-1);
            break;
        }

    }
    sqlite3_close(DB);

    return (0);
}

static int callback(void* data, int argc, char** argv, char** azColName)
{
    static int j;
    int i;
    if (j == 0) {
        for (i = 0; i < argc; i++) {
            printf("%s\t", azColName[i]);
        }
        printf("\n");
        j++;
    }

    for (i = 0; i < argc; i++) {
        printf("%s\t  ", argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

static int callback_custlog(void* data, int argc, char** argv, char** azColName)
{
    static int j;
    int i, n = 10;
    if (j == 0) {
        for (i = 0; i < (argc / 7); i++) {
            cout << setw(20) << azColName[i];
            cout << setw(12) << azColName[i + 1];
            cout << setw(10) << azColName[i + 2];
            cout << setw(15) << azColName[i + 3];
            cout << setw(15) << azColName[i + 4];
            cout << setw(15) << azColName[i + 5];
            cout << setw(8) << azColName[i + 6];
        }
        printf("\n");
        j++;
    }

    for (i = 0; i < (argc / 6); i = i + 7) {
        cout << setw(20) << argv[i] ? argv[i] : "NULL";
        cout << setw(12) << argv[i + 1] ? argv[i + 1] : "NULL";
        cout << setw(10) << argv[i + 2] ? argv[i + 2] : "NULL";
        cout << setw(15) << argv[i + 3] ? argv[i + 3] : "NULL";
        cout << setw(15) << argv[i + 4] ? argv[i + 4] : "NULL";
        cout << setw(15) << argv[i + 5] ? argv[i + 5] : "NULL";
        cout << setw(8) << argv[i + 6] ? argv[i + 6] : "NULL";
    }

    printf("\n");
    return 0;
}

static int callback_suppliers(void* data, int argc, char** argv, char** azColName)
{
    static int j;
    int i, n = 10;
    if (j == 0) {
        for (i = 0; i < (argc / 6); i++) {
            cout << setw(10) << azColName[i];
            cout << setw(30) << azColName[i + 1];
            cout << setw(15) << azColName[i + 2];
            cout << setw(40) << azColName[i + 3];
            cout << setw(15) << azColName[i + 4];
            cout << setw(20) << azColName[i + 5];
        }
        printf("\n");
        j++;
    }

    for (i = 0; i < (argc / 6); i = i + 6) {
        cout << setw(10) << argv[i] ? argv[i] : "NULL";
        cout << setw(30) << argv[i + 1] ? argv[i + 1] : "NULL";
        cout << setw(15) << argv[i + 2] ? argv[i + 2] : "NULL";
        cout << setw(40) << argv[i + 3] ? argv[i + 3] : "NULL";
        cout << setw(15) << argv[i + 4] ? argv[i + 4] : "NULL";
        cout << setw(5) << argv[i + 5] ? argv[i + 5] : "NULL";
    }

    printf("\n");
    return 0;
}

static int callback_employees(void* data, int argc, char** argv, char** azColName)
{

    static int j;
    int i;

    if (j == 0) {
        i = 0;
        cout << setw(10) << azColName[i];
        cout << setw(12) << azColName[i + 1];
        cout << setw(10) << azColName[i + 2];
        cout << setw(7) << azColName[i + 3];
        cout << setw(4) << azColName[i + 4];
        cout << setw(15) << azColName[i + 5];
        cout << setw(8) << azColName[i + 6];
        cout << setw(16) << azColName[i + 7];
        cout << setw(25) << azColName[i + 8];
        cout << setw(12) << azColName[i + 9];
        cout << setw(15) << azColName[i + 10];
        cout << setw(10) << azColName[i + 11];
        printf("\n");
        j++;
    }

    for (i = 0; i < (argc / 12); i = i + 12) {
        cout << setw(10) << argv[i] ? argv[i] : "NULL";
        cout << setw(12) << argv[i + 1] ? argv[i + 1] : "NULL";
        cout << setw(10) << argv[i + 2] ? argv[i + 2] : "NULL";
        cout << setw(7) << argv[i + 3] ? argv[i + 3] : "NULL";
        cout << setw(4) << argv[i + 4] ? argv[i + 4] : "NULL";
        cout << setw(15) << argv[i + 5] ? argv[i + 5] : "NULL";
        cout << setw(8) << argv[i + 6] ? argv[i + 6] : "NULL";
        cout << setw(16) << argv[i + 7] ? argv[i + 7] : "NULL";
        cout << setw(25) << argv[i + 8] ? argv[i + 8] : "NULL";
        cout << setw(12) << argv[i + 9] ? argv[i + 9] : "NULL";
        //cout << setw(15) << argv[i + 10] ? argv[i + 10] : "NULL";
        //cout << setw(10) << argv[i + 11] ? argv[i + 11] : "NULL";
    }

    /*
    for (i = 0; i < argc; i++) {
        printf("%s\t  ", argv[i] ? argv[i] : "sus");
    }*/


    printf("\n");
    return 0;
}


static int callback_inventory(void* data, int argc, char** argv, char** azColName)
{
    static int j;
    int i, n = 20;
    if (j == 0) {
        for (i = 0; i < argc; i++) {
            cout << setw(n) << azColName[i];
        }
        printf("\n");
        j++;
    }

    for (i = 0; i < argc; i++) {
        cout << setw(n) << argv[i] ? argv[i] : "NULL";
    }

    printf("\n");
    return 0;
}

static int callback_empcheck(void* data, int argc, char** argv, char** azColName)
{
    char zero[] = "0";
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], zero) == 0) {
            no_emp = 1;
        }
    }

    printf("\n");
    return 0;
}

static int callback_pass(void* data, int argc, char** argv, char** azColName)
{
    if (argc == 0) {
        no_emp = 1;
        return 1;
    }
    int i, flag = -1;
    char pass[20];
    cout << "Enter password: ";
    cin >> pass;

    for (i = 0; i < argc; i++) {
        if (strcmp(argv[0], pass) == 0) {
            cout << "Password matches." << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            flag = 0;
        }
        else {
            flag = 1;
        }
    }

    printf("\n");
    return flag;
}

static int callback_restock(void* data, int argc, char** argv, char** azColName)
{
    string flag;
    int n;
    flag = argv[0];
    stringstream obj;
    obj << flag;
    obj >> qty_updated_restock;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Enter how many items to be added: ";
    cin >> n;
    qty_updated_restock = qty_updated_restock + n;
    printf("\n");
    return 0;
}

static int callback_remove(void* data, int argc, char** argv, char** azColName)
{
    string flag, flag2, flag3, flag4;
    char ch;
    int unit_price = 0;
    flag = argv[3];
    stringstream obj, obj1, obj2, obj3;
    obj << flag;
    obj >> qty_updated_restock;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Enter how many items to be removed: ";
    cin >> qty_removed;
    qty_updated_restock = qty_updated_restock - qty_removed;
    //cout << "Flag is: " << flag << endl;
    //cout << "Flag is: " << qty_updated_restock << endl;
    flag2 = argv[4];
    flag3 = argv[5];
    flag4 = argv[6];
    /*cout << flag2 << endl;
    cout << flag3 << endl;
    cout << flag4 << endl;
    */
    obj1 << flag2;
    obj1 >> unit_price;
    obj2 << flag3;
    obj2 >> qty_sold;

    //cout << "New qty sold: " << qty_sold << endl;
    obj3 << flag4;
    obj3 >> new_sales;

    //cout << "New sales: " << new_sales << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Were the items damaged or sold?\nEnter 'd' for damaged and 's' for sold: " << endl;
    cin >> ch;
    if ((ch == 's') || (ch == 'S')) {
        qty_sold = qty_sold + qty_removed;
        new_sales = new_sales + unit_price * qty_removed;
        cout << "Items removed." << endl;

    }
    else if ((ch == 'd') || (ch == 'D')) {
        cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
        cout << "Items removed." << endl;
    }
    else {
        cout << "Invalid choice. Default choice (damaged) has been chosen." << endl;
    }
    printf("\n");
    return 0;
}

void table_inventory(sqlite3* DB) {
    string sql = "CREATE TABLE IF NOT EXISTS INVENTORY("
        "ID             TEXT    NOT NULL, "
        "S_NO           INT     PRIMARY KEY     NOT NULL, "
        "PRODUCT        TEXT    NOT NULL, "
        "QTY_IN_STOCK   INT     NOT NULL, "
        "UNIT_PRICE     INT     NOT NULL, "
        "QTY_SOLD       INT, "
        "SALES_VALUE    INT );";

    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Table created Successfully" << endl;
}

void table_suppliers(sqlite3* DB) {
    string sql = "CREATE TABLE IF NOT EXISTS SUPPLIERS("
        "S_ID           TEXT     PRIMARY KEY     NOT NULL, "
        "NAME           TEXT    NOT NULL, "
        "PHONE_NO       INT     NOT NULL, "
        "EMAIL          TEXT     NOT NULL, "
        "LAST_PURCHASE  DATE, "
        "YEARS_OF_BUSINESS  INT );";

    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Table created Successfully" << endl;
}
void table_employees(sqlite3* DB) {
    string sql = "CREATE TABLE IF NOT EXISTS EMPLOYEES("
        "EMP_ID             TEXT     PRIMARY KEY     NOT NULL, "
        "FIRST_NAME         TEXT     NOT NULL, "
        "LAST_NAME          TEXT     NOT NULL,"
        "GENDER             CHAR     NOT NULL, "
        "AGE                INT      NOT NULL,"
        "DESIGNATION        TEXT     NOT NULL,"
        "SALARY             INT      NOT NULL,"
        "YEAR_OF_JOINING    INT      NOT NULL,"
        "EMAIL              TEXT,"
        "PHONE_NO           INT,"
        "PASSWORD1          TEXT,"
        "PASSWORD2          TEXT );";

    int exit = 0;
    char* messageError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Table created Successfully" << endl;
}

void data_employees(sqlite3* DB) {
    int exit = 0;
    char* messageError;
    string query = "SELECT * FROM EMPLOYEES;";
    string sql("INSERT INTO EMPLOYEES VALUES('S182221', 'STEVE', 'GATES', 'M', 27, 'CASHIER', 20000, 2021, 'stevegates@gmail.com', 9621043526, 'meowcat77', NULL);"
        "INSERT INTO EMPLOYEES VALUES('S182222', 'JOLIE', 'RIVERS', 'F', 24, 'CASHIER', 22000, 2020, 'jolierivers99@gmail.com', 9643797653, 'dogwoof23', NULL);"
        "INSERT INTO EMPLOYEES VALUES('S182223', 'MARK', 'RONSON', 'M', 32, 'SWEEPER', 10000, 2016, 'mark1989@yahoo.com', 896532543, NULL , NULL);"
        "INSERT INTO EMPLOYEES VALUES('S182224', 'RICK', 'JOHNSON', 'M', 34, 'STAFF', 23500, 2018, 'rickkkjohn@gmail.com', 9354281437, 'bluesun', NULL);"
        "INSERT INTO EMPLOYEES VALUES('S182225', 'MORTY', 'EDWARDS', 'M', 28, 'STAFF', 21000, 2022, 'edwardsmorty@yahoo.com', 8459652986, 'alien23', NULL);"
        "INSERT INTO EMPLOYEES VALUES('S182226', 'CAMILA', 'RIVERA', 'F', 32, 'MANAGER', 45000, 2020, 'camila1999@gmail.com', 7652364972, 'greenhoney21', 'oswald1999');");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    cout << "STATE OF TABLE AFTER INSERT" << endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
}

int emp_login(sqlite3* DB, string emp_id) {
    int chk;
    string sql("SELECT PASSWORD1 FROM EMPLOYEES WHERE EMP_ID = \"" + emp_id + "\";");
    string sql2("SELECT COUNT(*) FROM EMPLOYEES WHERE EMP_ID = \"" + emp_id + "\";");
    int rc = sqlite3_exec(DB, sql2.c_str(), callback_empcheck, NULL, NULL);

    if (no_emp == 0) {
        rc = sqlite3_exec(DB, sql.c_str(), callback_pass, NULL, NULL);

        if (rc != SQLITE_OK) {
            cerr << "Access denied." << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            chk = 0;
        }
        else {
            cout << "Access granted." << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            chk = 1;
        }
    }
    else {
        cerr << "No such emplotee ID exists." << endl;
        chk = 0;
        no_emp = 0;
    }
    return chk;
}

int m_login(sqlite3* DB, string m_id) {
    int chk;
    string sql("SELECT PASSWORD2 FROM EMPLOYEES WHERE EMP_ID = \"" + m_id + "\";");
    string sql2("SELECT COUNT(*) FROM EMPLOYEES WHERE EMP_ID = \"" + m_id + "\";");
    int rc = sqlite3_exec(DB, sql2.c_str(), callback_empcheck, NULL, NULL);

    if (no_emp == 0) {
        rc = sqlite3_exec(DB, sql.c_str(), callback_pass, NULL, NULL);

        if (rc != SQLITE_OK) {
            cerr << "Access denied." << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            chk = 0;
        }
        else {
            cout << "Access granted." << endl;
            cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
            chk = 1;
        }
    }
    else {
        cerr << "No such emplotee ID exists." << endl;
        chk = 0;
        no_emp = 0;
    }
    return chk;
}

void data_inventory(sqlite3* DB) {
    int exit = 0;
    char* messageError;
    string query = "SELECT * FROM INVENTORY;";
    string sql("INSERT INTO INVENTORY VALUES('IC326', 1, 'Chicken (1kg)', 50, 275, 12, 3300);"
        "INSERT INTO INVENTORY VALUES('IUT2678', 2, 'Canned Fish (100g)', 75, 100, 27, 2700);"
        "INSERT INTO INVENTORY VALUES('PF2618', 3, 'Yogurt (100g)', 28, 120, 6, 720);"
        "INSERT INTO INVENTORY VALUES('WT23434', 4, 'Tofu (200g)', 35, 70, 7, 245);"
        "INSERT INTO INVENTORY VALUES('PO2356', 5, 'Cheese (100g)', 30, 125, 7, 875);"
        "INSERT INTO INVENTORY VALUES('FGI4326', 6, 'Butter (100g)', 26, 55, 6, 330);"
        "INSERT INTO INVENTORY VALUES('FDTE445', 7, 'Almonds (500g)', 40, 650, 5, 3250);"
        "INSERT INTO INVENTORY VALUES('OFSI345', 8, 'Walnuts (500g)', 35, 350, 4, 1400);"
        "INSERT INTO INVENTORY VALUES('FPSI474', 9, 'Mustard Oil (1L)', 45, 130, 12, 1560);"
        "INSERT INTO INVENTORY VALUES('IFKS3345', 10, 'Olive Oil (200mL)', 43, 250, 9, 2250);"
        "INSERT INTO INVENTORY VALUES('SB7532', 11, 'Sugar (1 kg)', 57, 70, 23, 0);"
        "INSERT INTO INVENTORY VALUES('PO0998', 12, 'Rice (1 kg)', 67, 200, 12, 2400);"
        "INSERT INTO INVENTORY VALUES('GPR8533', 13, 'Wheat Flour (1 kg)', 120, 32, 56, 1792);"
        "INSERT INTO INVENTORY VALUES('GPK8648', 14, 'Flour (500g)', 80, 30, 39, 1170);"
        "INSERT INTO INVENTORY VALUES('CFP351', 15, 'Coffee (100g)', 113, 200, 29, 5800);"
        "INSERT INTO INVENTORY VALUES('O82FGJ', 16, 'Tea leaves (100g)', 230, 65, 57, 3705);"
        "INSERT INTO INVENTORY VALUES('UR6221', 17, 'Multigrain bread', 30, 55, 8, 440);"
        "INSERT INTO INVENTORY VALUES('P08621', 18, 'Watermelon (1 kg)', 20, 30, 3, 90);"
        "INSERT INTO INVENTORY VALUES('AX2581', 19, 'Bananas (1 dozen)', 12, 35, 1, 35);"
        "INSERT INTO INVENTORY VALUES('DIRH43', 20, 'Apples (1 kg)', 12, 140, 4, 560);"
        "INSERT INTO INVENTORY VALUES('RI2734', 21, 'Pineapples (1 kg)', 8, 40, 1, 40);"
        "INSERT INTO INVENTORY VALUES('FI6392', 22, 'Muskmelon (1 kg)', 8, 30, 2, 60);"
        "INSERT INTO INVENTORY VALUES('PSIE273', 23, 'Grapes (1 kg)', 17, 95, 3, 285);"
        "INSERT INTO INVENTORY VALUES('AXT3844', 24, 'Orange (1 kg)', 23, 85, 8, 680);"
        "INSERT INTO INVENTORY VALUES('AGETE43', 25, 'Papaya (1 kg)', 13, 28, 2, 56);"
        "INSERT INTO INVENTORY VALUES('P796593', 26, 'Pomegranate (1 kg)', 7, 175, 1, 275);"
        "INSERT INTO INVENTORY VALUES('PKHF470', 27, 'Guava (1 kg)', 6, 50, 2, 100);"
        "INSERT INTO INVENTORY VALUES('SY7621', 28, 'Pears (1 kg)', 8, 115, 2, 230);"
        "INSERT INTO INVENTORY VALUES('FJ28472', 29, 'Potato (1 kg)', 40, 40, 12, 480);"
        "INSERT INTO INVENTORY VALUES('EK16384', 30, 'Tomato (1 kg)', 43, 45, 16, 720);"
        "INSERT INTO INVENTORY VALUES('PKFW673', 31, 'Onion (1 kg)', 34, 35, 9, 315);"
        "INSERT INTO INVENTORY VALUES('PL7777', 32, 'Cabbage (1 kg)', 4, 30, 1, 30);"
        "INSERT INTO INVENTORY VALUES('FH4971', 33, 'Carrot (1 kg)', 8, 72, 3, 216);"
        "INSERT INTO INVENTORY VALUES('PLFE00', 34, 'Cucumbers (1 kg)', 23, 30, 5, 150);"
        "INSERT INTO INVENTORY VALUES('QFWJ63', 35, 'Capsicum (1 kg)', 7, 55, 2, 110);"
        "INSERT INTO INVENTORY VALUES('FREO66', 36, 'Cauliflower (1 kg)', 4, 55, 0, 0);"
        "INSERT INTO INVENTORY VALUES('WRIG621', 37, 'Eggplant (1 kg)', 5, 24, 1, 24);"
        "INSERT INTO INVENTORY VALUES('ARE547', 38, 'Garlic (1 kg)', 5, 60, 1, 60);"
        "INSERT INTO INVENTORY VALUES('GN2945', 39, 'Ginger (1 kg)', 5, 50, 1, 50);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    cout << "STATE OF TABLE AFTER INSERT" << endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
};

void data_suppliers(sqlite3* DB) {
    int exit = 0;
    char* messageError;
    string query = "SELECT * FROM SUPPLIERS;";
    string sql("INSERT INTO SUPPLIERS VALUES('SP791', 'Farm Naturals', 8355926419, 'farmnaturalsco@gmail.com', '2022-03-04', 4);"
        "INSERT INTO SUPPLIERS VALUES('SP792', 'Farm and Fruits', 9543827542, 'farmnandfruitscompany@gmail.com', '2022-07-02', 5);"
        "INSERT INTO SUPPLIERS VALUES('SP793', 'Organic Suppliers', 9498765325, 'organicsuppliersindia@yahoo.co.in', '2022-01-07', 2);"
        "INSERT INTO SUPPLIERS VALUES('SP794', 'Raj Groceries', 8353618099, 'rajgroceries@gmail.com', '2021-12-11', 1);"
        "INSERT INTO SUPPLIERS VALUES('SP795', 'Bala Akashaya Products', 8192837465, 'akashayabala@gmail.com', '2022-09-23', 11);"
        "INSERT INTO SUPPLIERS VALUES('SP796', 'Prem Wholesale and retailers', 9222348717, 'premretail@yahoo.com', '2022-04-05', 6);"
        "INSERT INTO SUPPLIERS VALUES('SP797', 'Organic Farming Retails', 8356781990, 'ofretails@gmail.com', '2022-01-17', 7);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    cout << "STATE OF TABLE AFTER INSERT" << endl;

    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
}

void employees::view_inventory(sqlite3* DB) {
    string query = "SELECT * FROM INVENTORY;";
    cout << "INVENTORY\n" << endl;
    sqlite3_exec(DB, query.c_str(), callback_inventory, NULL, NULL);
}

void employees::inventory_restock(sqlite3* DB) {
    inventory obj1;
    //string sno, qty_updated_restock_str;
    view_inventory(DB);
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Enter the 's_no' of the item you want to restock: " << endl;
    cin >> obj1.S_NO;
    string sql("SELECT QTY_IN_STOCK FROM INVENTORY WHERE S_NO=" + obj1.S_NO + ";");
    sqlite3_exec(DB, sql.c_str(), callback_restock, NULL, NULL);
    stringstream obj;
    obj << qty_updated_restock;
    obj >> obj1.QTY_IN_STOCK;
    //cout << obj1.QTY_IN_STOCK;
    string query("UPDATE INVENTORY SET QTY_IN_STOCK=" + obj1.QTY_IN_STOCK + " WHERE S_NO=" + obj1.S_NO + ";");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    if (rc != SQLITE_OK) {
        cerr << "Not updated." << endl;
    }
    else {
        cout << "Updated." << endl;
    }
}

void employees::remove_from_inventory(sqlite3* DB) {
    //char ch;
    inventory obj1;
    //string sno, qty_updated_restock_str;
    view_inventory(DB);
    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Enter the 's_no' of the item you want to remove: " << endl;
    cin >> obj1.S_NO;
    string sql("SELECT * FROM INVENTORY WHERE S_NO=" + obj1.S_NO + ";");
    sqlite3_exec(DB, sql.c_str(), callback_remove, NULL, NULL);
    stringstream obj, obj2, obj3;
    obj << qty_updated_restock;
    obj >> obj1.QTY_IN_STOCK;
    obj2 << qty_sold;
    obj2 >> obj1.QTY_SOLD;
    obj3 << new_sales;
    obj3 >> obj1.SALES_VALUE;
    string query("UPDATE INVENTORY SET QTY_IN_STOCK=" + obj1.QTY_IN_STOCK + ", QTY_SOLD=" + obj1.QTY_SOLD + ", SALES_VALUE=" + obj1.SALES_VALUE + " WHERE S_NO = " + obj1.S_NO + "; ");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    if (rc != SQLITE_OK) {
        cerr << "Not updated." << endl;
    }
    else {
        cout << "Updated." << endl;
    }
}

void manager::view_suppliers(sqlite3* DB) {
    string query = "SELECT * FROM SUPPLIERS;";
    cout << "SUPPLIERS\n" << endl;
    sqlite3_exec(DB, query.c_str(), callback_suppliers, NULL, NULL);
}

void manager::view_employees(sqlite3* DB) {
    string query = "SELECT * FROM EMPLOYEES;";
    cout << "EMPLOYEES\n" << endl;
    sqlite3_exec(DB, query.c_str(), callback_employees, NULL, NULL);
}

void manager::delete_suppliers(sqlite3* DB) {
    string id;
    manager obj;
    obj.view_suppliers(DB);
    cout << "Enter 'S_ID' of supplier to be removed: " << endl;
    cin >> obj.emp_id;
    string query("DELETE FROM SUPPLIERS WHERE S_ID=\"" + obj.emp_id + "\";");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    if (rc != SQLITE_OK) {
        cout << "Unable to delete supplier." << endl;
    }
    else {
        cout << "Deleted." << endl;
    }
}

void manager::promote_employee(sqlite3* DB) {
    manager obj;
    obj.view_employees(DB);
    cout << "Enter ID of employee to be promoted: " << endl;
    cin >> obj.emp_id;
    cout << "Enter new designation of employee: " << endl;
    cin >> obj.DESIGNATION;
    if ((obj.DESIGNATION == "MANAGER") || (obj.DESIGNATION == "Manager") || (obj.DESIGNATION == "manager")) {
        cout << "Enter new manager password for said employee: " << endl;
        cin >> obj.PASSWORD2;
    }
    else {
        obj.PASSWORD2 = "NULL";
    }

    cout << "Enter new salary: " << endl;
    cin >> obj.SALARY;
    stringstream obj1;
    obj1 << obj.SALARY;
    string salary_str;
    obj1 >> salary_str;
    string query("UPDATE EMPLOYEES SET DESIGNATION=\"" + obj.DESIGNATION + "\", PASSWORD2=\"" + obj.PASSWORD2 + "\", SALARY=" + salary_str + " WHERE EMP_ID =\"" + obj.emp_id + "\";");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    if (rc == SQLITE_OK) {
        cout << "Promoted." << endl;
    }
    else {
        cout << "Unable to promote." << endl;
    }
}

void manager::update_emp_salary(sqlite3* DB) {
    manager obj;
    obj.view_employees(DB);
    cout << "Enter ID of employee whose salary is to be modified: " << endl;
    cin >> obj.emp_id;
    cout << "Enter new salary: " << endl;
    cin >> obj.SALARY;
    stringstream obj1;
    obj1 << obj.SALARY;
    string salary_str;
    obj1 >> salary_str;
    string query("UPDATE EMPLOYEES SET SALARY=" + salary_str + " WHERE EMP_ID =\"" + obj.emp_id + "\";");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    if (rc == SQLITE_OK) {
        cout << "Salary updated." << endl;
    }
    else {
        cout << "Unable to update." << endl;
    }
}

void manager::add_suppliers(sqlite3* DB) {
    string id, email, phone;
    manager obj;
    suppliers sup;
    cout << "Enter details of new supplier" << endl;
    cout << "Enter Supplier ID: ";
    cin >> sup.S_ID;
    cout << "Enter name of supplier: ";
    cin >> sup.name;
    cout << "Enter phone number of supplier: ";
    cin >> phone;
    cout << "Enter email of supplier: ";
    cin >> email;
    cout << "Enter last purchase date of supplier (in format YYYY-MM-DD): ";
    cin >> sup.last_purchase;
    cout << "Enter years of business with supplier: ";
    cin >> sup.years_of_business;

    string query("INSERT INTO SUPPLIERS VALUES('" + sup.S_ID + "', '" + sup.name + "', " + phone + ", '" + email + "', '" + sup.last_purchase + "', " + sup.years_of_business + ");");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    if (rc != SQLITE_OK) {
        cout << "Unable to add supplier." << endl;
    }
    else {
        cout << "Added." << endl;
    }
}

void employees::view_customer_logs(sqlite3* DB) {
    string query = "SELECT * FROM CLOG;";
    cout << "CUSTOMER LOG\n" << endl;
    sqlite3_exec(DB, query.c_str(), callback_custlog, NULL, NULL);
}