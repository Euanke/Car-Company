#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

string companyName = "CarWorld Ltd";

class Vehicle {
protected:
    string brand;
    string model;

public:
    static int count;

    Vehicle(string b, string m) {
        brand = b;
        model = m;
        count++;
    }

    virtual void displayInfo() {
        cout << "Brand: " << brand << ", Model: " << model << endl;
    }

    void updateModel(string newModel) {
        string tempModel = newModel;
        model = tempModel;
    }

    virtual string getData() {
        return brand + " " + model;
    }

    virtual ~Vehicle() {}
};

int Vehicle::count = 0;


class Car : public Vehicle {
private:
    int seats;

public:
    Car(string b, string m, int s) : Vehicle(b, m) {

        if (s < 0)
            throw invalid_argument("Invalid number of seats!");

        seats = s;
    }

    void displayInfo() override {
        cout << "Car -> Brand: " << brand
             << ", Model: " << model
             << ", Seats: " << seats << endl;
    }

    string getData() override {
        return "Car " + brand + " " + model + " " + to_string(seats);
    }
};


class Motorbike : public Vehicle {
private:
    int engineCapacity;

public:
    Motorbike(string b, string m, int e) : Vehicle(b, m) {

        if (e < 0)
            throw invalid_argument("Invalid engine capacity!");

        engineCapacity = e;
    }

    void displayInfo() override {
        cout << "Motorbike -> Brand: " << brand
             << ", Model: " << model
             << ", Engine Capacity: " << engineCapacity << "cc" << endl;
    }

    string getData() override {
        return "Motorbike " + brand + " " + model + " " + to_string(engineCapacity);
    }
};


int main() {

    cout << "Company Name: " << companyName << endl << endl;

    vector<Vehicle*> vehicles;

    try {

        Car* car1 = new Car("Ford", "Mustang", 4);
        Car* car2 = new Car("Porsche", "911", 4);

        Motorbike* bike1 = new Motorbike("BMW", "S1000RR", 999);
        Motorbike* bike2 = new Motorbike("Honda", "Gold Wing", 1832);

        vehicles.push_back(car1);
        vehicles.push_back(car2);
        vehicles.push_back(bike1);
        vehicles.push_back(bike2);

    }
    catch (exception &e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << "\nVehicle Information:\n";
    for (Vehicle* v : vehicles) {
        v->displayInfo();
    }

    cout << "\nTotal Vehicles Created: " << Vehicle::count << endl;


    ofstream file("vehicles.txt");

    for (Vehicle* v : vehicles) {
        file << v->getData() << endl;
    }

    file.close();


    cout << "\nReading from vehicles.txt:\n";

    ifstream readFile("vehicles.txt");
    string line;

    while (getline(readFile, line)) {
        cout << line << endl;
    }

    readFile.close();


    for (Vehicle* v : vehicles) {
        delete v;
    }

    return 0;
}
