#include <iostream>
#include <string>
using namespace std;

// ─── Appointment Class ───────────────────────────────────────────
class Appointment {
private:
    int appointmentID;
    int petID;
    string date;
    string reason;
    string status;

public:
    void setAppointment(int aID, int pID, string d, string r) {
        appointmentID = aID;
        petID = pID;
        date = d;
        reason = r;
        status = "Scheduled";
    }

    void getAppointment() {
        cout << "Appointment ID : " << appointmentID << endl;
        cout << "Pet ID         : " << petID << endl;
        cout << "Date           : " << date << endl;
        cout << "Reason         : " << reason << endl;
        cout << "Status         : " << status << endl;
    }

    void cancelAppointment() {
        status = "Cancelled";
        cout << "Appointment " << appointmentID << " has been cancelled." << endl;
    }
};

// ─── Pet Class (Base class — Abstraction + Encapsulation) ────────
class Pet {
private:
    int petID;
    string name;
    string species;
    int age;
    int ownerID;

public:
    void setDetails(int pID, string n, string sp, int a, int oID) {
        petID = pID;
        name = n;
        species = sp;
        age = a;
        ownerID = oID;
    }

    void getDetails() {
        cout << "Pet ID   : " << petID << endl;
        cout << "Name     : " << name << endl;
        cout << "Species  : " << species << endl;
        cout << "Age      : " << age << " years" << endl;
        cout << "Owner ID : " << ownerID << endl;
    }

    // Overridden by Dog and Cat
    void displayInfo() {
        cout << "--- Pet Info ---" << endl;
        getDetails();
    }
};

// ─── Dog Class (Inherits Pet) ─────────────────────────────────────
class Dog : public Pet {
private:
    string breed;
    bool isVaccinated;

public:
    void setDogDetails(string b, bool v) {
        breed = b;
        isVaccinated = v;
    }

    string fetchBreed() {
        return breed;
    }

    void displayInfo() {
        cout << "--- Dog Info ---" << endl;
        Pet::getDetails();
        cout << "Breed       : " << breed << endl;
        cout << "Vaccinated  : " << (isVaccinated ? "Yes" : "No") << endl;
    }

    void bark() {
        cout << "Woof! Woof!" << endl;
    }
};

// ─── Cat Class (Inherits Pet) ─────────────────────────────────────
class Cat : public Pet {
private:
    bool isIndoor;
    string furColor;

public:
    void setCatDetails(bool indoor, string color) {
        isIndoor = indoor;
        furColor = color;
    }

    string getFurColor() {
        return furColor;
    }

    void displayInfo() {
        cout << "--- Cat Info ---" << endl;
        Pet::getDetails();
        cout << "Indoor    : " << (isIndoor ? "Yes" : "No") << endl;
        cout << "Fur Color : " << furColor << endl;
    }

    void meow() {
        cout << "Meow! Meow!" << endl;
    }
};

// ─── Owner Class ──────────────────────────────────────────────────
class Owner {
private:
    int ownerID;
    string name;
    string phone;
    string email;

public:
    void setDetails(int oID, string n, string p, string e) {
        ownerID = oID;
        name = n;
        phone = p;
        email = e;
    }

    void getDetails() {
        cout << "Owner ID : " << ownerID << endl;
        cout << "Name     : " << name << endl;
        cout << "Phone    : " << phone << endl;
        cout << "Email    : " << email << endl;
    }

    void addPet(string petName) {
        cout << "Pet '" << petName << "' added under owner: " << name << endl;
    }
};

// ─── Main Function ────────────────────────────────────────────────
int main() {
    // Create Owner
    Owner o1;
    o1.setDetails(101, "Ravi Kumar", "9876543210", "ravi@gmail.com");
    cout << "=== Owner Details ===" << endl;
    o1.getDetails();
    o1.addPet("Bruno");

    cout << endl;

    // Create Dog object
    Dog d1;
    d1.setDetails(201, "Bruno", "Dog", 3, 101);
    d1.setDogDetails("Labrador", true);
    d1.displayInfo();
    d1.bark();

    cout << endl;

    // Create Cat object
    Cat c1;
    c1.setDetails(202, "Whiskers", "Cat", 2, 101);
    c1.setCatDetails(true, "White");
    c1.displayInfo();
    c1.meow();

    cout << endl;

    // Create Appointment for the dog
    Appointment a1;
    a1.setAppointment(301, 201, "2025-04-20", "Annual Vaccination");
    cout << "=== Appointment Details ===" << endl;
    a1.getAppointment();

    cout << endl;
    a1.cancelAppointment();

    return 0;
}