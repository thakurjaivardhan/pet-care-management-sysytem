#include <iostream>
#include <string>
#include <vector>
#include <algorithm>   // for sort() and find_if()
#include <stdexcept>   // for runtime_error
using namespace std;

// ─── Pet (Base Class) ─────────────────────────────────────────────────────────
// Base class for all pet types.
// Uses 'protected' so derived classes (Dog, Cat) can access these fields directly.

class Pet {
protected:
    int    petID;
    string name;
    int    age;
    string species;

public:
    // Default constructor — initializes numeric fields to safe defaults
    Pet() : petID(0), age(0) {}

    // --- Setters ---
    void setPetID(int id)     { petID    = id; }
    void setName(string n)    { name     = n;  }
    void setAge(int a)        { age      = a;  }
    void setSpecies(string s) { species  = s;  }

    // --- Getters ---
    int    getPetID()   { return petID;   }
    string getName()    { return name;    }
    int    getAge()     { return age;     }
    string getSpecies() { return species; }

    // Prints the common pet fields shared by all pet types
    void displayPet() {
        cout << "  Pet ID  : " << petID              << endl;
        cout << "  Name    : " << name               << endl;
        cout << "  Age     : " << age << " year(s)"  << endl;
        cout << "  Species : " << species             << endl;
    }

    // Virtual display — overridden by Dog and Cat to show their extra fields
    virtual void display() { displayPet(); }

    // Virtual destructor ensures proper cleanup when deleting via base pointer
    virtual ~Pet() {}
};

// ─── Dog (Derived from Pet) ───────────────────────────────────────────────────
// Inherits common pet data from Pet and adds dog-specific fields.

class Dog : public Pet {
private:
    string breed;
    bool   isVaccinated;

public:
    // Default constructor — vaccination defaults to false
    Dog() : isVaccinated(false) {}

    // --- Setters ---
    void setBreed(string b)    { breed        = b; }
    void setVaccinated(bool v) { isVaccinated = v; }

    // --- Getters ---
    string getBreed()      { return breed;        }
    bool   getVaccinated() { return isVaccinated; }

    // Overrides Pet::display() to also show breed and vaccination status
    void display() override {
        displayPet();
        cout << "  Breed       : " << breed                          << endl;
        cout << "  Vaccinated  : " << (isVaccinated ? "Yes" : "No") << endl;
    }

    // Dog-specific behaviour
    void bark() {
        cout << "  " << name << " says: Woof! Woof!" << endl;
    }
};

// ─── Cat (Derived from Pet) ───────────────────────────────────────────────────
// Inherits common pet data from Pet and adds cat-specific fields.

class Cat : public Pet {
private:
    string furColor;
    bool   isIndoor;

public:
    // Default constructor — isIndoor defaults to false
    Cat() : isIndoor(false) {}

    // --- Setters ---
    void setFurColor(string c) { furColor = c; }
    void setIndoor(bool i)     { isIndoor  = i; }

    // --- Getters ---
    string getFurColor() { return furColor; }
    bool   getIndoor()   { return isIndoor; }

    // Overrides Pet::display() to also show fur color and indoor status
    void display() override {
        displayPet();
        cout << "  Fur Color   : " << furColor                  << endl;
        cout << "  Indoor      : " << (isIndoor ? "Yes" : "No") << endl;
    }

    // Cat-specific behaviour
    void meow() {
        cout << "  " << name << " says: Meow! Meow!" << endl;
    }
};

// ─── Owner ────────────────────────────────────────────────────────────────────
// Represents a pet owner with contact information.
// Not linked to a Pet object here — kept simple for this system.

class Owner {
private:
    int    ownerID;
    string name, phone, email;

public:
    // Default constructor — ownerID starts at 0
    Owner() : ownerID(0) {}

    // --- Setters ---
    void setOwnerID(int id)  { ownerID = id; }
    void setName(string n)   { name    = n;  }
    void setPhone(string p)  { phone   = p;  }
    void setEmail(string e)  { email   = e;  }

    // --- Getters ---
    int    getOwnerID() { return ownerID; }
    string getName()    { return name;    }
    string getPhone()   { return phone;   }
    string getEmail()   { return email;   }

    // Prints all owner details
    void displayOwner() {
        cout << "  Owner ID : " << ownerID << endl;
        cout << "  Name     : " << name    << endl;
        cout << "  Phone    : " << phone   << endl;
        cout << "  Email    : " << email   << endl;
    }
};

// ─── Appointment ──────────────────────────────────────────────────────────────
// Represents a vet appointment linked to a pet via petID.
// Status defaults to "Scheduled" and can be cancelled.

class Appointment {
private:
    int    appointmentID, petID;
    string date, purpose, status;

public:
    // Default constructor — status starts as "Scheduled"
    Appointment() : appointmentID(0), petID(0), status("Scheduled") {}

    // --- Setters ---
    void setAppointmentID(int id) { appointmentID = id;  }
    void setPetID(int pid)        { petID         = pid; }
    void setDate(string d)        { date          = d;   }
    void setPurpose(string p)     { purpose       = p;   }
    void setStatus(string s)      { status        = s;   }

    // --- Getters ---
    int    getAppointmentID() { return appointmentID; }
    int    getPetID()         { return petID;         }
    string getDate()          { return date;          }
    string getPurpose()       { return purpose;       }
    string getStatus()        { return status;        }

    // Changes status to "Cancelled" and confirms to the user
    void cancel() {
        status = "Cancelled";
        cout << "  Appointment " << appointmentID << " has been cancelled." << endl;
    }

    // Prints all appointment details
    void displayAppointment() {
        cout << "  Appt. ID : " << appointmentID << endl;
        cout << "  Pet ID   : " << petID         << endl;
        cout << "  Date     : " << date          << endl;
        cout << "  Purpose  : " << purpose       << endl;
        cout << "  Status   : " << status        << endl;
    }
};

// ─── Helpers ──────────────────────────────────────────────────────────────────

// Prints a horizontal divider line between records
void printLine() {
    cout << "  ----------------------------------------" << endl;
}

// Displays the main menu options to the user
void showMenu() {
    cout << endl;
    cout << "  ========================================" << endl;
    cout << "      PET CARE MANAGEMENT SYSTEM         " << endl;
    cout << "  ========================================" << endl;
    cout << "  1. Add Pet (Dog)"            << endl;
    cout << "  2. Display All Pets"         << endl;
    cout << "  3. Add Owner"                << endl;
    cout << "  4. Display All Owners"       << endl;
    cout << "  5. Add Appointment"          << endl;
    cout << "  6. Display All Appointments" << endl;
    cout << "  7. Exit"                     << endl;
    cout << "  ----------------------------------------" << endl;
    cout << "  Enter your choice: ";
}

// Comparator used by sort() to order pets alphabetically by name
bool comparePetByName(Pet* a, Pet* b) {
    return a->getName() < b->getName();
}

// Generic duplicate ID checker used with find_if()
// T    — the type stored in the vector (Pet*, Owner, Appointment)
// GetID — a callable (lambda) that extracts the ID from each element
template <typename T, typename GetID>
bool idExists(vector<T>& vec, int id, GetID getId) {
    return find_if(vec.begin(), vec.end(),
        [&](T& item) { return getId(item) == id; }
    ) != vec.end();
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {

    // Vectors to store all records at runtime (no file/database used)
    vector<Pet*>        pets;          // Stores pointers (polymorphism — Dog/Cat via Pet*)
    vector<Owner>       owners;
    vector<Appointment> appointments;

    // Reusable input variables
    int    choice;
    int    id, age, petRef;
    string name, breed, phone, email, date, purpose;
    char   vacChar;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();   // Clears the newline left in the buffer after cin >>

        switch (choice) {

            // ── Case 1: Add a new Dog ─────────────────────────────────────────
            case 1: {
                cout << endl << "  --- Add New Dog ---" << endl;
                cout << "  Enter Pet ID   : "; cin >> id; cin.ignore();

                try {
                    // Prevent duplicate Pet IDs using find_if
                    if (idExists(pets, id, [](Pet* p){ return p->getPetID(); }))
                        throw runtime_error("Pet ID already exists!");

                    Dog* d = new Dog();   // Heap-allocated so it can be stored as Pet*
                    d->setPetID(id);

                    cout << "  Enter Name     : "; getline(cin, name);
                    d->setName(name);

                    cout << "  Enter Age      : "; cin >> age; cin.ignore();
                    d->setAge(age);
                    d->setSpecies("Dog");

                    cout << "  Enter Breed    : "; getline(cin, breed);
                    d->setBreed(breed);

                    cout << "  Vaccinated? (y/n): "; cin >> vacChar; cin.ignore();
                    d->setVaccinated(vacChar == 'y' || vacChar == 'Y');

                    pets.push_back(d);   // Stored as Pet* — polymorphism in action
                    cout << "  [+] Dog added successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            // ── Case 2: Display all Pets ──────────────────────────────────────
            case 2: {
                cout << endl << "  --- All Pets (Dogs) ---" << endl;

                if (pets.empty()) { cout << "  No pets added yet." << endl; break; }

                // Sort the pets vector alphabetically by name before displaying
                sort(pets.begin(), pets.end(), comparePetByName);
                cout << "  (Sorted alphabetically by name)" << endl;

                int count = 1;
                for (vector<Pet*>::iterator it = pets.begin(); it != pets.end(); ++it) {
                    printLine();
                    cout << "  Pet #" << count++ << endl;

                    // Calls the overridden display() of Dog or Cat via virtual dispatch
                    (*it)->display();

                    // dynamic_cast checks if this Pet* is actually a Dog — safe downcast
                    Dog* dogPtr = dynamic_cast<Dog*>(*it);
                    if (dogPtr != nullptr) dogPtr->bark();
                }
                printLine();
                break;
            }

            // ── Case 3: Add a new Owner ───────────────────────────────────────
            case 3: {
                cout << endl << "  --- Add New Owner ---" << endl;
                cout << "  Enter Owner ID : "; cin >> id; cin.ignore();

                try {
                    // Prevent duplicate Owner IDs
                    if (idExists(owners, id, [](Owner& o){ return o.getOwnerID(); }))
                        throw runtime_error("Owner ID already exists!");

                    Owner o;
                    o.setOwnerID(id);

                    // Read and set name, phone, email in sequence
                    cout << "  Enter Name     : "; getline(cin, name);  o.setName(name);
                    cout << "  Enter Phone    : "; getline(cin, phone); o.setPhone(phone);
                    cout << "  Enter Email    : "; getline(cin, email); o.setEmail(email);

                    owners.push_back(o);
                    cout << "  [+] Owner added successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            // ── Case 4: Display all Owners ────────────────────────────────────
            case 4: {
                cout << endl << "  --- All Owners ---" << endl;

                if (owners.empty()) { cout << "  No owners added yet." << endl; break; }

                int count = 1;
                for (vector<Owner>::iterator it = owners.begin(); it != owners.end(); ++it) {
                    printLine();
                    cout << "  Owner #" << count++ << endl;
                    it->displayOwner();
                }
                printLine();
                break;
            }

            // ── Case 5: Add a new Appointment ─────────────────────────────────
            case 5: {
                cout << endl << "  --- Add New Appointment ---" << endl;
                cout << "  Enter Appointment ID : "; cin >> id; cin.ignore();

                try {
                    // Prevent duplicate Appointment IDs
                    if (idExists(appointments, id, [](Appointment& a){ return a.getAppointmentID(); }))
                        throw runtime_error("Appointment ID already exists!");

                    Appointment a;
                    a.setAppointmentID(id);

                    cout << "  Enter Pet ID         : "; cin >> petRef; cin.ignore();
                    a.setPetID(petRef);   // Links appointment to a pet by ID

                    cout << "  Enter Date (DD/MM/YYYY): "; getline(cin, date);
                    a.setDate(date);

                    cout << "  Enter Purpose        : "; getline(cin, purpose);
                    a.setPurpose(purpose);

                    a.setStatus("Scheduled");   // Default status on creation
                    appointments.push_back(a);
                    cout << "  [+] Appointment scheduled successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            // ── Case 6: Display all Appointments ──────────────────────────────
            case 6: {
                cout << endl << "  --- All Appointments ---" << endl;

                if (appointments.empty()) { cout << "  No appointments added yet." << endl; break; }

                int count = 1;
                for (vector<Appointment>::iterator it = appointments.begin(); it != appointments.end(); ++it) {
                    printLine();
                    cout << "  Appointment #" << count++ << endl;
                    it->displayAppointment();
                }
                printLine();
                break;
            }

            // ── Case 7: Exit ──────────────────────────────────────────────────
            case 7: {
                // Free all heap-allocated Pet objects to prevent memory leaks
                for (vector<Pet*>::iterator it = pets.begin(); it != pets.end(); ++it)
                    delete *it;
                pets.clear();

                cout << endl;
                cout << "  Thank you for using Pet Care Management System!" << endl;
                cout << "  Goodbye!" << endl << endl;
                break;
            }

            default:
                cout << "  [!] Invalid choice. Please enter 1-7." << endl;
                break;
        }

    } while (choice != 7);

    return 0;
}