#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// It ask user to enter how many miles they have travelled and returns the value as a double. It will keep asking until a valid non negative number is entered in the console. 
double getDistance() {
    double miles;
    while (true) {
        cout << "Enter distance travelled (miles): ";
        if (cin >> miles && miles >= 0) return miles;
        cout << "Please enter a valid, non-negative distance.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// It take input fuel type
int getFuelType() {
    int fuel;
    while (true) {
        cout << "Select fuel type (1 = Petrol, 2 = Diesel): ";
        if (cin >> fuel && (fuel == 1 || fuel == 2)) return fuel;
        cout << "Please enter 1 or 2.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

}

double calculateEmissions(double miles, int fuelType) {
    const double litresPer100Miles = 9.66;
    const double kgPerLitre = (fuelType == 1) ? 2.31 : 2.68;
    return (miles / 100.0) * litresPer100Miles * kgPerLitre;
}

int main() {
    cout << "=== CO2 Calculator ===\n";
    double distance = getDistance();
    int fuel = getFuelType();
    double emissions = calculateEmissions(distance, fuel);
    cout << fixed << setprecision(2);
    cout << "Fuel: " << (fuel == 1 ? "Petrol" : "Diesel") << '\n';
    cout << "Estimated CO2 emissions: " << emissions << " kg\n";
    return 0;
}
