#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

// ─── Pet (Base) ───────────────────────────────────────────────────────────────

class Pet {
protected:
    int    petID;
    string name;
    int    age;
    string species;

public:
    Pet() : petID(0), age(0) {}

    void setPetID(int id)     { petID    = id; }
    void setName(string n)    { name     = n;  }
    void setAge(int a)        { age      = a;  }
    void setSpecies(string s) { species  = s;  }

    int    getPetID()   { return petID;   }
    string getName()    { return name;    }
    int    getAge()     { return age;     }
    string getSpecies() { return species; }

    void displayPet() {
        cout << "  Pet ID  : " << petID   << endl;
        cout << "  Name    : " << name    << endl;
        cout << "  Age     : " << age << " year(s)" << endl;
        cout << "  Species : " << species << endl;
    }

    virtual void display() { displayPet(); }
    virtual ~Pet() {}
};

// ─── Dog ──────────────────────────────────────────────────────────────────────

class Dog : public Pet {
private:
    string breed;
    bool   isVaccinated;

public:
    Dog() : isVaccinated(false) {}

    void setBreed(string b)    { breed        = b; }
    void setVaccinated(bool v) { isVaccinated = v; }

    string getBreed()      { return breed;        }
    bool   getVaccinated() { return isVaccinated; }

    void display() override {
        displayPet();
        cout << "  Breed       : " << breed << endl;
        cout << "  Vaccinated  : " << (isVaccinated ? "Yes" : "No") << endl;
    }

    void bark() {
        cout << "  " << name << " says: Woof! Woof!" << endl;
    }
};

// ─── Owner ────────────────────────────────────────────────────────────────────

class Owner {
private:
    int    ownerID;
    string name, phone, email;

public:
    Owner() : ownerID(0) {}

    void setOwnerID(int id)  { ownerID = id; }
    void setName(string n)   { name    = n;  }
    void setPhone(string p)  { phone   = p;  }
    void setEmail(string e)  { email   = e;  }

    int    getOwnerID() { return ownerID; }
    string getName()    { return name;    }
    string getPhone()   { return phone;   }
    string getEmail()   { return email;   }

    void displayOwner() {
        cout << "  Owner ID : " << ownerID << endl;
        cout << "  Name     : " << name    << endl;
        cout << "  Phone    : " << phone   << endl;
        cout << "  Email    : " << email   << endl;
    }
};

// ─── Appointment ──────────────────────────────────────────────────────────────

class Appointment {
private:
    int    appointmentID, petID;
    string date, purpose, status;

public:
    Appointment() : appointmentID(0), petID(0), status("Scheduled") {}

    void setAppointmentID(int id) { appointmentID = id;  }
    void setPetID(int pid)        { petID         = pid; }
    void setDate(string d)        { date          = d;   }
    void setPurpose(string p)     { purpose       = p;   }
    void setStatus(string s)      { status        = s;   }

    int    getAppointmentID() { return appointmentID; }
    int    getPetID()         { return petID;         }
    string getDate()          { return date;          }
    string getPurpose()       { return purpose;       }
    string getStatus()        { return status;        }

    void cancel() {
        status = "Cancelled";
        cout << "  Appointment " << appointmentID << " has been cancelled." << endl;
    }

    void displayAppointment() {
        cout << "  Appt. ID : " << appointmentID << endl;
        cout << "  Pet ID   : " << petID         << endl;
        cout << "  Date     : " << date          << endl;
        cout << "  Purpose  : " << purpose       << endl;
        cout << "  Status   : " << status        << endl;
    }
};

// ─── Helpers ──────────────────────────────────────────────────────────────────

void printLine() {
    cout << "  ----------------------------------------" << endl;
}

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

bool comparePetByName(Pet* a, Pet* b) {
    return a->getName() < b->getName();
}

// Generic ID-duplicate checker using a lambda-friendly approach with find_if
template <typename T, typename GetID>
bool idExists(vector<T>& vec, int id, GetID getId) {
    return find_if(vec.begin(), vec.end(),
        [&](T& item) { return getId(item) == id; }
    ) != vec.end();
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {

    vector<Pet*>        pets;
    vector<Owner>       owners;
    vector<Appointment> appointments;

    int    choice;
    int    id, age, petRef;
    string name, breed, phone, email, date, purpose;
    char   vacChar;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {

            case 1: {
                cout << endl << "  --- Add New Dog ---" << endl;
                cout << "  Enter Pet ID   : ";
                 cin >> id; 
                 cin.ignore();

                try {
                    if (idExists(pets, id, [](Pet* p){ return p->getPetID(); }))
                        throw runtime_error("Pet ID already exists!");

                    Dog* d = new Dog();
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

                    pets.push_back(d);
                    cout << "  [+] Dog added successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            case 2: {
                cout << endl << "  --- All Pets (Dogs) ---" << endl;

                if (pets.empty()) { cout << "  No pets added yet." << endl; break; }

                sort(pets.begin(), pets.end(), comparePetByName);
                cout << "  (Sorted alphabetically by name)" << endl;

                int count = 1;
                for (vector<Pet*>::iterator it = pets.begin(); it != pets.end(); ++it) {
                    printLine();
                    cout << "  Pet #" << count++ << endl;
                    (*it)->display();
                }
                printLine();
                break;
            }

            case 3: {
                cout << endl << "  --- Add New Owner ---" << endl;
                cout << "  Enter Owner ID : "; cin >> id; cin.ignore();

                try {
                    if (idExists(owners, id, [](Owner& o){ return o.getOwnerID(); }))
                        throw runtime_error("Owner ID already exists!");

                    Owner o;
                    o.setOwnerID(id);

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

            case 5: {
                cout << endl << "  --- Add New Appointment ---" << endl;
                cout << "  Enter Appointment ID : "; cin >> id; cin.ignore();

                try {
                    if (idExists(appointments, id, [](Appointment& a){ return a.getAppointmentID(); }))
                        throw runtime_error("Appointment ID already exists!");

                    Appointment a;
                    a.setAppointmentID(id);

                    cout << "  Enter Pet ID         : "; cin >> petRef; cin.ignore();
                    a.setPetID(petRef);

                    cout << "  Enter Date (DD/MM/YYYY): "; getline(cin, date);
                    a.setDate(date);

                    cout << "  Enter Purpose        : "; getline(cin, purpose);
                    a.setPurpose(purpose);

                    a.setStatus("Scheduled");
                    appointments.push_back(a);
                    cout << "  [+] Appointment scheduled successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

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

            case 7: {
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