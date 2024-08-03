#include<bits/stdc++.h>
using namespace std;

// Declaration of the main menu function
void Main_Menu();
int total_amt = 0;

// Function to allow user choice for returning to the main menu or exiting
void Choice(){

    char choice;
        cout << endl << "Enter '1' for Main Menu \nEnter anything for exit: ";
        cin >> choice;

        if(choice == '1'){
            Main_Menu();
        }else{
            exit(0); //Ecit the program
        }

}

// Function to display the list of products from a file
void Display_Products(){

    ifstream read("Product_List.txt");
    string red;

    while(getline(read,red)){
        cout<<red <<"\n";
    };

    cout << endl;

    read.close();

}

// Structure to represent a product
struct Product {

    int id;
    string name;
    float mrp;

};

// Function to get a product's details by its ID
Product getProductById(const string& filename, int productId) {

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file." << endl;
        exit(EXIT_FAILURE);
    }
    
    string line;
    Product product = {-1, "", 0.0}; // Default values indicating not found
    
    while (getline(file, line)) {
        istringstream iss(line);
        Product tempProduct;
        
        if (iss >> tempProduct.id >> ws) {
            getline(iss, tempProduct.name, ' ');
            iss >> tempProduct.mrp;
            
            if (tempProduct.id == productId) {
                product = tempProduct;
                break;
            }
        }
    }
    
    file.close();
    return product;

}

// Function to update due amounts in the due file
void updateDueAmounts(const string& dueFile, const string& phoneNumber, int dueAmount) {
    
    unordered_map<string, int> dueMap;

    ifstream dueInfile(dueFile);
    if (dueInfile.is_open()) {
        string line;
        while (getline(dueInfile, line)) {
            stringstream lineStream(line);
            string phone;
            int amount;
            if (getline(lineStream, phone, ',') && lineStream >> amount) {
                dueMap[phone] = amount;
            }
        }
        dueInfile.close();
    } else {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    if (dueMap.find(phoneNumber) != dueMap.end()) {
        
        dueMap[phoneNumber] += dueAmount;

    } else {

        dueMap[phoneNumber] = dueAmount;
    }

    ofstream dueOutfile(dueFile);
    if (!dueOutfile.is_open()) {

        cerr << "Error opening file for writing." << endl;

        return;
    }

    for (const auto& entry : dueMap) {

        dueOutfile << entry.first << ',' << entry.second << endl;

    }

    dueOutfile.close();

    cout << endl;
    cout << "============================================" << endl;
    cout << "    Due Amount Updated Successfully          " << endl;
    cout << "--------------------------------------------" << endl;
    cout << "    Phone Number: " << phoneNumber << endl;
    cout << "============================================" << endl << endl;

}

// Function to read an amount from a file
int readAmount(const string& fileName) {

    ifstream file(fileName);
    int amount = 0;

    if (file.is_open()) {

        file >> amount;
        file.close();

    } else {

        cerr << "Error opening file for reading: " << fileName << endl;
        
    }

    return amount;

}

// Function to write an amount to a file
void writeAmount(const string& fileName, int amount) {

    ofstream file(fileName);
    
    if (file.is_open()) {

        file << amount;
        file.close();

    } else {

        cerr << "Error opening file for writing: " << fileName << endl;

    }

}

// Function to handle cash payments
void Cash_Method(int total_amount) {

    int currentAmount = readAmount("Cash.txt");
    currentAmount += total_amount;
    writeAmount("Cash.txt", currentAmount);
    const int amountWidth = 15;  // Width for the total amount

    cout << endl;
    cout << "============================================" << endl;
    cout << "              CASH RECEIVED                 " << endl;
    cout << "--------------------------------------------" << endl;
    cout << right << setw(amountWidth) << fixed << setprecision(2) << total_amount
         << "   Cash Received" << endl;
    cout << "============================================" << endl << endl;

}

// Function to handle UPI payments
void UPI_Method(int total_amount) {

    int currentAmount = readAmount("UPI.txt");
    currentAmount += total_amount;
    writeAmount("UPI.txt", currentAmount);
    const int amountWidth = 15;  // Width for the total amount

    cout << endl;
    cout << "============================================" << endl;
    cout << "              UPI PAYMENT RECEIVED          " << endl;
    cout << "--------------------------------------------" << endl;
    cout << right << setw(amountWidth) << fixed << setprecision(2) << total_amount
         << "   UPI Payment Received" << endl;
    cout << "============================================" << endl << endl;

}

// Function to handle due payments
void Due_Payment(int total_amount){

    string phoneNumber ;

    cout << "Enter the customer phone number: ";
    cin >> phoneNumber;

    int currentAmount = readAmount("Due.txt");
    currentAmount += total_amount;
    writeAmount("Due.txt", currentAmount);
    
    updateDueAmounts("DueAmounts.txt", phoneNumber, total_amount);
    
}

// Function to process cash-in based on user choice
void Cash_In(int total_amount){

    char choice;

    cout << endl;
    cout << "============================================" << endl;
    cout << "    Total Amount to be Paid: " << fixed << setprecision(2) << total_amount << endl;
    cout << "============================================" << endl << endl;

    cout << "Choose Payment Method:" << endl;
    cout << "1) Cash" << endl;
    cout << "2) UPI" << endl;
    cout << "3) Due" << endl << endl;

    cout << "Enter your choice (1-3): ";
    cin >> choice;
    
    if(choice == '1'){

        Cash_Method(total_amount);

    }else if(choice == '2'){

        UPI_Method(total_amount);

    }else if(choice == '3'){

        Due_Payment(total_amount);

    }else{

        cout << "Wrong input";
        Cash_In(total_amount);  // Retry on invalid input

    }

}

// Function to store sales data into a file
void Store_Sales_Data(const string& name, int unit, int t_price) {

    ofstream MyFile("Sales_Data.csv", ios::app);

    if (!MyFile.is_open()) {

        cerr << "Error: Could not open file for writing." << endl;
        return;

    }

    MyFile << name << ',' << unit << ',' << t_price << '\n';

    MyFile.close();

}

// Function to subtract units of a product from the inventory
void subtractUnits(const string& filename, int productId, int unitsToSubtract) {

    ifstream infile(filename);

    if (!infile.is_open()) {

        cerr << "Error opening file for updating units" << endl;
        return;

    }

    vector<string> lines;
    string line;
    bool updated = false;

    while (getline(infile, line)) {

        stringstream lineStream(line);
        string idStr, name, unitsStr;
        
        if (getline(lineStream, idStr, ',') && getline(lineStream, name, ',') && getline(lineStream, unitsStr)) {

            int id = stoi(idStr);
            int units = stoi(unitsStr);

            if (id == productId) {

                units -= unitsToSubtract;
                if (units < 0) {

                    units = 0;

                }
                unitsStr = to_string(units);
                updated = true;

            }

            line = idStr + ',' + name + ',' + unitsStr;

        }

        lines.push_back(line);
    }

    infile.close();

    if (!updated) {

        cout << "Product ID not found." << endl;
        return;

    }

    ofstream outfile(filename);

    if (!outfile.is_open()) {

        cerr << "Error opening file for updating units." << endl;
        return;

    }

    for (const auto& updatedLine : lines) {

        outfile << updatedLine << endl;

    }
    outfile.close();

}

// Function to handle product selection and calculation
void Product_Selection(){

    char choice ;
    int total_per_item = 0;

    Display_Products();

    string filename = "products.txt";
    int searchId;

    cout << "Enter product ID: ";
    cin >> searchId;

    Product product = getProductById(filename, searchId);

    string product_name = product.name;
    float mrp = product.mrp;
    int units;

    cout << "Enter number of units: ";
    cin >> units;

    cout << endl;

    total_per_item = mrp * units;
    total_amt = total_amt + total_per_item;

    Store_Sales_Data(product_name, units, total_per_item);
    subtractUnits("Inventory.txt", product.id, units);
    
    cout << endl;
    cout << "============================================" << endl;
    cout << "        Total Amount to be Paid: " << setw(10) << fixed << setprecision(2) << total_amt << endl;
    cout << "============================================" << endl << endl;

    cout << "Please choose an option:" << endl;
    cout << "1) Add more products" << endl;
    cout << "2) Cash in" << endl << endl;

    cout << "Enter a number: ";
    cin >> choice;

    if(choice == '1'){

        Product_Selection();

    }else if(choice == '2'){

        Cash_In(total_amt);

    }else{

        cout << "Wrong input...";
        return ;

    }

    total_amt = 0; // Reset total amount
    Choice(); // Return to choice menu

}

// Function to handle daily trade
void Daily_Trade(){

    Product_Selection();
    
}

// Function to display sales data from a CSV file
void displaySalesData(const string& fileName) {

    ifstream file(fileName);

    if (!file.is_open()) {

        cerr << "Error: Could not open file for reading." << endl;
        return;

    }

    string line;

    // Print header
    cout << left << setw(20) << "Product Name"
         << setw(10) << "Units"
         << setw(12) << "Total Price" << endl;
    cout << string(42, '-') << endl;

    // Read and display data
    while (getline(file, line)) {

        istringstream iss(line);
        string name;
        int unit;
        int t_price;

        // Extract product name, units, and total price
        getline(iss, name, ','); 
        iss >> unit;
        iss.ignore(); 
        iss >> t_price;

        // Print the formatted output
        cout << left << setw(20) << name
             << setw(10) << unit
             << setw(12) << t_price << endl;

    }

    file.close();

}

// Function to display due payments
void displayDuePayments(const string& fileName) {

    ifstream file(fileName);

    if (!file.is_open()) {

        cerr << "Error: Could not open file for reading." << endl;
        return;

    }

    string line;

    // Print header
    cout << left << setw(15) << "Phone Number"
         << setw(10) << "Due Amount" << endl;
    cout << string(25, '-') << endl;

    // Read and display data
    while (getline(file, line)) {

        istringstream iss(line);
        string phoneNumber;
        int dueAmount;

        // Extract phone number and due amount
        getline(iss, phoneNumber, ','); // Read until the comma
        iss >> dueAmount;

        // Print the formatted output
        cout << left << setw(15) << phoneNumber
             << setw(10) << dueAmount << endl;

    }

    file.close();
}

// Function to display account balance
void Display_Balance(const string& file, const string& title) {

    ifstream MyReadFile(file);

    if (!MyReadFile.is_open()) {

        cerr << "Error: Could not open file " << file << endl;
        return;

    }

    string myText;

    if (getline(MyReadFile, myText)) {

        // Display the title with the balance amount
        cout << left << setw(20) << title
             << right << setw(10) << myText << endl;

    }

    MyReadFile.close();


    MyReadFile.close();
}

// Function to display inventory
void Display_Inventory(const string& file) {
    
    ifstream MyReadFile(file);

    if (!MyReadFile.is_open()) {
        cerr << "Error: Could not open file " << file << endl;
        return;

    }

    string line;
    // Print the header
    cout << left << setw(10) << "Product Id"
         << setw(20) << "Product Name"
         << setw(10) << "Units" << endl;
    cout << "---------------------------------------------" << endl;

    while (getline(MyReadFile, line)) {

        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {

            string productId = line.substr(0, pos1);
            string productName = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string units = line.substr(pos2 + 1);
            
            cout << left << setw(10) << productId
                 << setw(20) << productName
                 << setw(10) << units << endl;

        }
    }

    MyReadFile.close();
}

// Function to generate and display daily report
void Daily_Report(){

    char choice;

    cout << endl;
    cout << "==========================================" << endl;
    cout << "            DAILY REPORT MENU            " << endl;
    cout << "==========================================" << endl << endl;

    cout << "1) Today's Total Sales" << endl;
    cout << "2) Today's Due Payments" << endl;
    cout << "3) Account Balance" << endl;
    cout << "4) Inventory" << endl << endl;

    cout << "Enter a number: ";
    cin >> choice;

    cout << endl;

    if(choice == '1'){

        displaySalesData("Sales_Data.csv");

        Choice();

    }else if(choice == '2'){

        displayDuePayments("DueAmounts.txt");

        Choice();

    }else if(choice == '3'){

        cout << left << setw(20) << "Method" << setw(15) << "Amount" << endl;
        cout << "----------------------------------------" << endl;

        Display_Balance("Cash.txt","Cash Balance: ");

        Display_Balance("UPI.txt", "UPI Balance: ");

        Display_Balance("Due.txt","Due Balance: ");

        Choice();

    }else if(choice == '4'){

        Display_Inventory("Inventory.txt");

        Choice();

    }else{

        cout<<"Wrong input, try again...";
        Daily_Report();

    } 
}

// Main menu function
void Main_Menu(){

cout << endl;
    cout << "========================================" << endl;
    cout << "||         MAIN MENU OPTIONS          ||" << endl;
    cout << "========================================" << endl << endl;

    char choice;

    cout << "1) Daily Trade" << endl;
    cout << "2) Daily Report" << endl << endl;

    cout << "Enter a number: ";
    cin >> choice;

    if (choice == '1') {

        cout << endl << "You have selected Daily Trade." << endl;
         Daily_Trade();

    } else if (choice == '2') {

        cout << endl << "You have selected Daily Report." << endl;
         Daily_Report();

    } else {

        cout << endl << "Invalid input. Please try again." << endl;
        Main_Menu();

    }
}

// Main function
int main(){
 
cout << endl;
    cout << "****************************************" << endl;
    cout << "*         WELCOME TO THE RMS           *" << endl;
    cout << "*      Retail Management System        *" << endl;
    cout << "*                                      *" << endl;
    cout << "*  Your one-stop solution for daily    *" << endl;
    cout << "*    trading and reporting needs.      *" << endl;
    cout << "*                                      *" << endl;
    cout << "****************************************" << endl << endl;

Main_Menu(); // Start the main menu

return 0;

}