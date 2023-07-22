#include <iostream>
#include <sqlite3.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

int qty_updated_restock = 0, qty_removed=0;
int qty_sold = 0, new_sales = 0;
int tot_qty = 0;
float bill = 0;

void table_customer_logs(sqlite3* DB);

class inventory {
public:
    string ID;
    string S_NO;
    string PRODUCT;
    string QTY_IN_STOCK;
    int UNIT_PRICE;
    string QTY_SOLD;
    string SALES_VALUE;

public:
    void view_inventory(sqlite3* DB);
};

class customer_log {
    string name;
    string dop;
    string top;
    string phone;

public: 
    int items_bought;
    int total_qty;
    float bill;

    customer_log() {
        items_bought = 0;
        total_qty = 0;
        bill = 0;
        phone = "0000000000";
    }

    void view_inventory(sqlite3* DB){};
    void purchase(sqlite3* DB);
    void getData();
    void Date();
    string display();
    void tax();
    void insertion_to_clog(sqlite3* DB, string phone);
};

int main(int argc, char** argv)
{
    sqlite3* DB;
    char s[] = "C:\\Users\\Paridhi\\Dropbox\\PC\\Documents\\Notes\\Semester 3\\OOP\\project\\databases\\employees.db";
    int exit1 = 0;
    exit1 = sqlite3_open(s, &DB);

    inventory inv;
    customer_log cust;
    string ph;

    if (exit1) {
        cerr << "Error open DB " << sqlite3_errmsg(DB) << endl;
        return (-1);
    }
    /*else
        cout << "Opened Database Successfully!" << endl;
    */
    //table_customer_logs(DB);
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\tFRESHLY GROCERIES CO.\n\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------";    
    cout << "\t\t\t\t\t\t\t\t\t\t\t         Welcome to Self-Checkout System!" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    cust.getData();
    cust.Date();
    inv.view_inventory(DB);

    char ch = 'y';
    while ((ch == 'y') || (ch == 'Y')) {
        cust.purchase(DB);
        cout << "Do you want to purchase more items?" << endl;
        cout << "Press 'y' or 'Y' for yes, else, press any other key." << endl;
        cin >> ch;
    }

    cust.bill = bill;
    cust.total_qty = tot_qty;
    cout << "\n\n----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\t\tINVOICE" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    ph = cust.display();
    cout << "Total cost: " << cust.bill << " Rs." << endl;
    cout << "GST: 5%" << endl;
    cust.tax();
    cout << "Amount to be paid: " << cust.bill << " Rs. " << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t      THANK YOU FOR SHOPPING WITH US" << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cust.insertion_to_clog(DB, ph);

    return 0;
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
        printf("%s\t\t", argv[i] ? argv[i] : "NULL");
    }

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
static int callback_remove(void* data, int argc, char** argv, char** azColName)
{
    string flag, flag2, flag3, flag4;
    int unit_price = 0;
    flag = argv[3];
    stringstream obj, obj1, obj2, obj3;


    obj << flag;
    obj >> qty_updated_restock;

    cout << "Enter quantity: ";
    cin >> qty_removed;
    
    tot_qty = tot_qty + qty_removed;
    qty_updated_restock = qty_updated_restock - qty_removed;
    flag2 = argv[4];
    flag3 = argv[5];
    flag4 = argv[6];
    obj1 << flag2;
    obj1 >> unit_price;
    obj2 << flag3;
    obj2 >> qty_sold;

    obj3 << flag4;
    obj3 >> new_sales;
    qty_sold = qty_sold + qty_removed;
    new_sales = new_sales + unit_price * qty_removed;
    bill = bill + float(unit_price * qty_removed);

    printf("\n");
    return 0;
}

void table_customer_logs(sqlite3* DB) {
    string sql = "CREATE TABLE IF NOT EXISTS CLOG("
        "NAME           TEXT     NOT NULL, "
        "DATE           DATE     NOT NULL, "
        "TIME           TEXT     NOT NULL, "
        "PHONE          INT      NOT NULL, "
        "ITEMS_BOUGHT   INT      NOT NULL, "
        "TOTAL_QTY      INT      NOT NULL, "
        "BILL           INT      NOT NULL);";

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

void customer_log::insertion_to_clog(sqlite3* DB, string phone) {
    int exit = 0;
    char* messageError;
    stringstream obj, obj2, obj3;
    string tmp, tmp2, tmp3, tmp4;

    obj << items_bought;
    obj >> tmp2;
    obj2 << total_qty;
    obj2 >> tmp3;
    obj3 << bill;
    obj3 >> tmp;

    string sql("INSERT INTO CLOG VALUES('" + name + "', '" + dop + "', '" + top + "', " + phone + ", " + tmp2 + ", " + tmp3 + ", " + tmp + ");");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messageError);
    }
    /*else
        std::cout << "Records added to customer logs successfully!" << std::endl;


    string query = "SELECT * FROM CLOG;";
    cout << "STATE OF TABLE AFTER INSERT" << endl;
    sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
    */
};

void inventory::view_inventory(sqlite3* DB) {
    string query = "SELECT S_NO, PRODUCT, uNIT_PRICE FROM INVENTORY;";
    cout << "INVENTORY\n" << endl;
    sqlite3_exec(DB, query.c_str(), callback_inventory, NULL, NULL);
}

void customer_log::purchase(sqlite3* DB) {
    items_bought++;
    stringstream obj, obj2, obj3;
    inventory obj1;
    view_inventory(DB);

    cout << "Enter the 's_no' of the item you want to purchase: " << endl;
    cin >> obj1.S_NO;

    string sql("SELECT * FROM INVENTORY WHERE S_NO=" + obj1.S_NO + ";");
    sqlite3_exec(DB, sql.c_str(), callback_remove, NULL, NULL);

    obj << qty_updated_restock;
    obj >> obj1.QTY_IN_STOCK;
    obj2 << qty_sold;
    obj2 >> obj1.QTY_SOLD;
    obj3 << new_sales;
    obj3 >> obj1.SALES_VALUE;

    string query("UPDATE INVENTORY SET QTY_IN_STOCK=" + obj1.QTY_IN_STOCK + ", QTY_SOLD=" + obj1.QTY_SOLD + ", SALES_VALUE=" + obj1.SALES_VALUE + " WHERE S_NO = " + obj1.S_NO + "; ");
    int rc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

    if (rc != SQLITE_OK) {
        cerr << "Unable to process. Checkout System out of service." << endl;
        exit(-1);
    }
    else {
        cout << "Purchased." << endl;
    }
}

void customer_log::getData() {
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter phone number: ";
    cin >> phone;

}

void customer_log::Date() {
    char dateString1[100];
    stringstream ss, ss2;
    string s, s2;

    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    int month = 1 + newtime.tm_mon;
    int day = newtime.tm_mday;
    int year = 1900 + newtime.tm_year;

    
    ss << year << "/" << month << "/" << day;
    s = ss.str();

    cout << s << endl;
    dop = s;

    int h = newtime.tm_hour;
    int m = newtime.tm_min;
    int sec = newtime.tm_sec;

    ss2 << h << ":" << m << ":" << sec;
    s2 = ss2.str();

    cout << s2 << endl;
    top = s2;
}

void customer_log::tax() {
    bill = 1.05 * bill;
}

string customer_log::display() {
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Date: " << dop << endl;
    cout << "Time: " << top << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Customer Name: " << name << endl;
    cout << "Phone number: " << phone << endl;
    cout << "Number of items bought: " << items_bought << endl;
    cout << "Total quantity: " << total_qty << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    return phone;
}