# Retail Management System (RMS)

## Overview

The Retail Management System (RMS) is a command-line application designed to manage daily trading and reporting for a retail business. It supports functionalities such as product selection, sales tracking, payment handling (cash, UPI, and due payments), and generating daily reports. The RMS allows businesses to efficiently manage inventory, track sales, and process payments.

## Features

- **Product Selection**: Add products to the cart and calculate the total amount.
- **Payment Methods**: Handle payments through cash, UPI, or on credit.
- **Sales Tracking**: Store sales data in a CSV file.
- **Inventory Management**: Subtract sold units from the inventory.
- **Daily Reports**: Generate reports for total sales, due payments, account balances, and current inventory.
- **Due Management**: Update and display due payments.

## Requirements

- C++ Compiler (e.g., g++, clang++)
- Standard C++ Library

## Installation

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/Saishhhhhh/Retail-Management-System.git
    ```

2. **Navigate to the Project Directory:**

    ```bash
    cd Retail-Management-System
    ```

3. **Compile the Code:**

    Use the following command to compile the project using `g++`:

    ```bash
    g++ -o rms main.cpp
    ```

    Replace `main.cpp` with the name of your C++ source file if it differs.

4. **Run the Program:**

    Execute the compiled program:

    ```bash
    ./rms
    ```

## Usage

### Main Menu

- **Daily Trade**: Manage product selection and process payments.
- **Daily Report**: Generate reports for sales, due payments, account balances, and inventory.

### Daily Trade

1. Display a list of products.
2. Enter the product ID and number of units to purchase.
3. Choose a payment method to finalize the transaction.

### Daily Report

1. View total sales for the day.
2. View due payments and update records.
3. Check account balances (Cash, UPI, Due).
4. Display current inventory.

## File Descriptions

- **Product_List.txt**: Contains the list of products available in the system.
- **products.txt**: Stores details of products including ID, name, and price.
- **Inventory.txt**: Maintains the current stock levels of products.
- **Sales_Data.csv**: Records sales data including product name, units sold, and total price.
- **DueAmounts.txt**: Lists customer phone numbers and their due amounts.
- **Cash.txt**: Records the current cash balance.
- **UPI.txt**: Records the current UPI balance.
- **Due.txt**: Records the current due balance.

## Contact

For any inquiries or support, please contact Saishhhhhh.
