#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <sstream>

using namespace std;

void table_inventory(sqlite3* DB);
void table_employees(sqlite3* DB);
void table_suppliers(sqlite3* DB);
void table_customer_logs(sqlite3* DB) {};
void restock(sqlite3* DB);
void inventory(sqlite3* DB);
void view_customer_logs() {};
void remove_goods() {};
void data_employees(sqlite3* DB);
void data_inventory(sqlite3* DB);
int emp_login(sqlite3* DB, string emp_id);
int m_login(sqlite3* DB, string m_id);

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
        printf("%s\t\t", argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

static int callback_pass(void* data, int argc, char** argv, char** azColName)
{
    int i, flag;
    char pass[20];
    cout << "Enter password: ";
    cin >> pass;

    for (i = 0; i < argc; i++) {
        if (strcmp(argv[0], pass) == 0) {
            cout << "Password matches." << endl;
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
    int flag_int;
    string flag;
    flag = argv[0];
    stringstream obj;
    obj << flag;
    obj >> flag_int;
    cout << "Flag is: " << flag << endl;
    cout << "Flag is: " << flag_int << endl;
    printf("\n");
    return 0;
}

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
    else
        cout << "Opened Database Successfully!" << endl;

    table_inventory(DB);
    table_employees(DB);
    table_suppliers(DB);
    //table_customer_logs(DB);
    //data_employees(DB);
    //data_inventory(DB);

    cout << "Welcome User!" << endl;
    cout << "1. Employee login" << endl;
    cout << "2. Manager login" << endl;
    cout << "Enter your choice:" << endl;
    cin >> login_ch;
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
        cout << "Welcome to Employee Interface" << endl;
        cout << "1. View Inventory" << endl;
        cout << "2. Restock Items" << endl;
        cout << "3. Remove Damaged goods" << endl;
        cout << "4. View Customer logs" << endl;
        cout << "! Press 0 to exit !" << endl;
        cout << "Enter your choice:" << endl;
        cin >> ch;
        switch (ch) {
        case 1:
            inventory(DB);
            break;
        case 2:
            restock(DB);
            break;
        case 3:
            remove_goods();
            break;
        case 4:
            view_customer_logs();
            break;
        case 0:
            exit(-1);
            break;
        }

    }

    while ((ch != 0) && (interface2_flag == 1)) {
        cout << "Welcome to Manager Interface" << endl;
        cout << "1. View Inventory" << endl;
        cout << "2. Restock Items" << endl;
        cout << "3. Remove Damaged goods" << endl;
        cout << "4. View Customer logs" << endl;
        cout << "! Press 0 to exit !" << endl;
        cout << "Enter your choice:" << endl;
        cin >> ch;
        switch (ch) {
        case 1:
            inventory(DB);
            break;
        case 2:
            restock(DB);
            break;
        case 3:
            remove_goods();
            break;
        case 4:
            view_customer_logs();
            break;
        case 0:
            exit(-1);
            break;
        }

    }
    sqlite3_close(DB);

    return (0);
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
        "LAST_PURCHASE  DATE "
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
        "INSERT INTO EMPLOYEES VALUES('S182226', 'CAMILA', 'RIVERA', 'F', 32, 'MANAGER', 45000, 2020, 'riveracamila1999@gmail.com', 7652364972, 'greenhoney21', 'oswald1999');");

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

    int rc = sqlite3_exec(DB, sql.c_str(), callback_pass, NULL, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Access denied." << endl;
        chk = 0;
    }
    else {
        cout << "Access granted." << endl;
        chk = 1;
    }
    return chk;
}

int m_login(sqlite3* DB, string m_id) {
    int chk;
    string sql("SELECT PASSWORD2 FROM EMPLOYEES WHERE EMP_ID = \"" + m_id + "\";");

    int rc = sqlite3_exec(DB, sql.c_str(), callback_pass, NULL, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Access denied." << endl;
        chk = 0;
    }
    else {
        cout << "Access granted." << endl;
        chk = 1;
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

void inventory(sqlite3* DB) {
    string query = "SELECT * FROM INVENTORY;";
    cout << "INVENTORY\n" << endl;
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

}

void restock(sqlite3* DB) {
    string sno;
    inventory(DB);
    cout << "Enter the 's_no' of the item you want to restock: " << endl;
    cin >> sno;
    string sql("SELECT QTY_IN_STOCK FROM INVENTORY WHERE S_NO=" + sno + ";");
    sqlite3_exec(DB, sql.c_str(), callback_restock, NULL, NULL);
}