#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <algorithm>
using namespace std;

// Function to convert string to uppercase for case-insensitive comparison
string toUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

// Function to get vehicle type with validation
char getVehicleType(double& dailyCharge) {
    char vehicleType;
    do {
        cout << "\nEnter vehicle type:\n";
        cout << "  S - Saloon (£22.50/day)\n";
        cout << "  H - High Performance (£28.00/day)\n";
        cout << "  V - Van (£35.00/day)\n";
        cout << "Choice: ";
        cin >> vehicleType;
        vehicleType = toupper(vehicleType);
        
        switch (vehicleType) {
            case 'S': dailyCharge = 22.50; return vehicleType;
            case 'H': dailyCharge = 28.00; return vehicleType;
            case 'V': dailyCharge = 35.00; return vehicleType;
            default: cout << "\nInvalid vehicle type. Please try again.\n";
        }
    } while (true);
}

// Function to get number of days with validation
int getDaysHired() {
    int daysHired;
    cout << "\nEnter the number of days for hire (1-10): ";
    cin >> daysHired;
    
    while (cin.fail() || daysHired < 1 || daysHired > 10) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Please enter a number between 1 and 10: ";
        cin >> daysHired;
    }
    return daysHired;
}

// Function to get yes/no response
bool getYesNoResponse(const string& prompt) {
    string response;
    do {
        cout << prompt;
        cin >> response;
        response = toUpper(response);
        
        if (response == "YES" || response == "Y") return true;
        if (response == "NO" || response == "N") return false;
        
        cout << "Invalid response. Please enter Yes or No.\n";
    } while (true);
}

// Function to get customer type
string getCustomerType() {
    string customerType;
    int attempts = 0;
    
    while (attempts < 3) {
        cout << "\nAre you a new or an existing customer? (New/Existing): ";
        cin >> customerType;
        customerType = toUpper(customerType);
        
        if (customerType == "NEW" || customerType == "EXISTING") {
            return customerType;
        }
        
        cout << "Invalid response. Must enter 'New' or 'Existing'.\n";
        attempts++;
    }
    
    cout << "\nToo many invalid attempts. Exiting program.\n";
    exit(1);
}

// Function to get loyalty card type
string getLoyaltyCard() {
    string loyaltyCard;
    do {
        cout << "\nEnter loyalty card type:\n";
        cout << "  Bronze - 5% additional discount\n";
        cout << "  Silver - 10% additional discount\n";
        cout << "  Gold - 15% additional discount + £18 off High Performance\n";
        cout << "Choice: ";
        cin >> loyaltyCard;
        loyaltyCard = toUpper(loyaltyCard);
        
        if (loyaltyCard == "BRONZE" || loyaltyCard == "SILVER" || loyaltyCard == "GOLD") {
            return loyaltyCard;
        }
        
        cout << "Invalid loyalty card type. Please try again.\n";
    } while (true);
}

// Function to calculate total cost
double calculateTotalCost(double dailyCharge, int daysHired, bool hasInsurance, 
                          const string& customerType, const string& loyaltyCard, char vehicleType) {
    const double INSURANCE_COST = 15.50;
    const double DEPOSIT = 50.0;
    const double GOLD_HP_DISCOUNT = 18.00;
    
    double subtotal = dailyCharge * daysHired;
    double discount = 0.0;
    
    // Multi-day discount (10% off for more than 7 days)
    if (daysHired > 7) {
        discount += subtotal * 0.1;
    }
    
    // Loyalty card discounts
    if (customerType == "EXISTING") {
        if (loyaltyCard == "BRONZE") {
            discount += subtotal * 0.05;
        } else if (loyaltyCard == "SILVER") {
            discount += subtotal * 0.10;
        } else if (loyaltyCard == "GOLD") {
            discount += subtotal * 0.15;
            if (vehicleType == 'H') {
                discount += GOLD_HP_DISCOUNT;
            }
        }
    }
    
    double totalCost = subtotal - discount;
    if (hasInsurance) totalCost += INSURANCE_COST;
    totalCost += DEPOSIT;
    
    return totalCost;
}

// Function to display summary
void displaySummary(char vehicleType, int daysHired, double dailyCharge, 
                   const string& customerType, const string& loyaltyCard, 
                   bool hasInsurance, double totalCost) {
    string vehicleName;
    switch(vehicleType) {
        case 'S': vehicleName = "Saloon"; break;
        case 'H': vehicleName = "High Performance"; break;
        case 'V': vehicleName = "Van"; break;
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << "         CAR HIRE QUOTE SUMMARY" << endl;
    cout << string(50, '=') << endl;
    cout << fixed << setprecision(2);
    cout << "Vehicle Type:        " << vehicleName << endl;
    cout << "Daily Charge:        £" << dailyCharge << endl;
    cout << "Days Hired:          " << daysHired << endl;
    cout << "Customer Type:       " << customerType << endl;
    cout << "Loyalty Card:        " << (loyaltyCard.empty() ? "None" : loyaltyCard) << endl;
    cout << "Insurance Cover:     " << (hasInsurance ? "Included (£15.50)" : "Not Included") << endl;
    cout << "Deposit:             £50.00" << endl;
    cout << string(50, '-') << endl;
    cout << "TOTAL COST:          £" << totalCost << endl;
    cout << string(50, '=') << endl;
}

int main() {
    cout << "\n**************************************" << endl;
    cout << "   WELCOME TO CAR HIRE SERVICES" << endl;
    cout << "**************************************" << endl;
    
    // Get vehicle type and daily charge
    double dailyCharge = 0.0;
    char vehicleType = getVehicleType(dailyCharge);
    
    // Get number of days
    int daysHired = getDaysHired();
    
    // Get insurance preference
    bool hasInsurance = getYesNoResponse("\nDo you need insurance cover? (Yes/No): ");
    
    // Get customer type
    string customerType = getCustomerType();
    
    // Get loyalty card if existing customer
    string loyaltyCard = "";
    if (customerType == "EXISTING") {
        loyaltyCard = getLoyaltyCard();
    }
    
    // Calculate total cost
    double totalCost = calculateTotalCost(dailyCharge, daysHired, hasInsurance, 
                                          customerType, loyaltyCard, vehicleType);
    
    // Display summary
    displaySummary(vehicleType, daysHired, dailyCharge, customerType, 
                   loyaltyCard, hasInsurance, totalCost);
    
    cout << "\nThank you for choosing our car hire service!\n" << endl;
    
    return 0;
}
