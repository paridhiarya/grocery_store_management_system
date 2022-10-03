#include <iostream>
#include <sqlite3.h>
#include <string.h>

using namespace std;

void table_inventory(sqlite3* DB);
void table_employees(sqlite3* DB);
void table_suppliers(sqlite3* DB);
void table_customer_logs(sqlite3* DB) {};
void restock() {};
void inventory() {};
void view_customer_logs() {};
void remove_goods() {};
void data_employees(sqlite3 *DB);
int emp_login(sqlite3* DB, string emp_id, string pass);

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char** argv)
{
    sqlite3* DB;
    char s[] = "C:\\Users\\Paridhi\\Dropbox\\PC\\Documents\\Notes\\Semester 3\\OOP\\project\\databases\\employees.db";
    int exit1 = 0, login_ch = 0;
    exit1 = sqlite3_open(s, &DB);

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

    cout << "Welcome User!" << endl;
    cout << "1. Employee login" << endl;
    cout << "2. Manager login" << endl;
    cout << "Enter your choice:" << endl;
    cin >> login_ch;
    if (login_ch == 1) {
        string emp_id, pass;
        cout << "Enter Employee ID: " << endl;
        cin >> emp_id;
        cout << "Enter employee password: " << endl;
        cin >> pass;
        emp_login(DB, emp_id, pass);
    }
    else if (login_ch == 2) {

    }
    else {
        cout << "Invalid Choice. Exitting." << endl;
    }


    int ch = 100;
    while (ch != 0) {
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
                inventory();
                break;
            case 2:
                restock();
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
        "ID             TEXT     PRIMARY KEY     NOT NULL, "
        "PRODUCT        TEXT    NOT NULL, "
        "QTY_IN_STOCK   INT     NOT NULL, "
        "UNIT_PRICE     INT     NOT NULL, "
        "QTY_SOLD       INT "
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

void data_employees(sqlite3 *DB) {
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

int emp_login(sqlite3* DB, string emp_id, string pass) {
    ///*char s1[] = "SELECT * FROM EMPLOYEES WHERE EMP_ID = \"";
    //strcat(s1, emp_id);
    //strcat(s1, "\";");
    //string sql(s1);
    //cout << sql;
    //strcat_s(sql, sql);*/
    //string idk = "hehe";
    //string sql("SELECT * FROM EMPLOYEES WHERE EMP_ID = \"");
    //errno_t strcat_s(idk, sizeof(idk), emp_id);

    string sql("SELECT * FROM EMPLOYEES WHERE EMP_ID = \"" + emp_id + "\";");

    int rc = sqlite3_exec(DB, sql.c_str(), callback, NULL, NULL);

    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else {
        cout << "Operation OK!" << endl;
    }
    return 0;
}