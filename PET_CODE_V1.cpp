/*
 * ============================================================
 *  PET CARE MANAGEMENT SYSTEM  — STL UPGRADED VERSION
 *  Subject : 21CSC101T - Object Oriented Design and Programming
 * ============================================================
 *
 *  UNIT 1-4 OOP Concepts (unchanged):
 *  1. CLASSES & OBJECTS   - Pet, Dog, Cat, Owner, Appointment
 *  2. ENCAPSULATION       - private data + public getters/setters
 *  3. ABSTRACTION         - data accessed only via methods
 *  4. INHERITANCE         - Dog and Cat derived from Pet
 *  5. POLYMORPHISM        - virtual display() in base class Pet
 *  6. FUNCTION OVERLOAD   - displayInfo() overloaded in Dog/Cat
 *  7. EXCEPTION HANDLING  - try/catch for duplicate ID check
 *
 *  UNIT 5 STL Concepts (NEW additions):
 *  A. vector<Pet*>        - replaces Dog array (polymorphic store)
 *  B. vector<Owner>       - replaces Owner array
 *  C. vector<Appointment> - replaces Appointment array
 *  D. ITERATORS           - explicit iterator loops used
 *  E. find_if()           - STL algorithm for searching by ID
 *  F. sort()              - STL algorithm to sort pets by name
 * ============================================================
 */

#include <iostream>
#include <string>
#include <vector>      // STL [A] vector container
#include <algorithm>   // STL [E,F] find_if(), sort()
#include <stdexcept>   // for runtime_error (exception handling)
using namespace std;

// ================================================================
//  CLASS 1 : Pet  (Base Class)
//  OOP — ENCAPSULATION : all attributes are private
//  OOP — ABSTRACTION   : data accessed only through public methods
//  OOP — POLYMORPHISM  : virtual display() for runtime binding
// ================================================================
class Pet {
private:
    int    petID;
    string name;
    int    age;
    string species;

public:
    // ---------- Constructor (used when creating Dog/Cat objects) ----------
    Pet() : petID(0), age(0) {}   // default constructor

    // ---------- Setters (mutators) ----------
    void setPetID(int id)      { petID   = id; }
    void setName(string n)     { name    = n;  }
    void setAge(int a)         { age     = a;  }
    void setSpecies(string s)  { species = s;  }

    // ---------- Getters (accessors) ----------
    int    getPetID()    { return petID;   }
    string getName()     { return name;    }
    int    getAge()      { return age;     }
    string getSpecies()  { return species; }

    // ---------- Base display ----------
    void displayPet() {
        cout << "  Pet ID  : " << petID   << endl;
        cout << "  Name    : " << name    << endl;
        cout << "  Age     : " << age << " year(s)" << endl;
        cout << "  Species : " << species << endl;
    }

    // OOP — POLYMORPHISM : virtual function overridden in Dog and Cat
    virtual void display() {
        displayPet();
    }

    // Virtual destructor — good practice with polymorphism + pointers
    virtual ~Pet() {}
};

// ================================================================
//  CLASS 2 : Dog  (Derived — INHERITANCE from Pet)
//  OOP — FUNCTION OVERLOADING : display() overrides Pet::display()
// ================================================================
class Dog : public Pet {
private:
    string breed;
    bool   isVaccinated;

public:
    Dog() : isVaccinated(false) {}

    // ---------- Setters ----------
    void setBreed(string b)      { breed        = b; }
    void setVaccinated(bool v)   { isVaccinated = v; }

    // ---------- Getters ----------
    string getBreed()      { return breed;        }
    bool   getVaccinated() { return isVaccinated; }

    // OOP — POLYMORPHISM : overrides Pet::display() at runtime
    void display() override {
        Pet::displayPet();
        cout << "  Breed       : " << breed << endl;
        cout << "  Vaccinated  : " << (isVaccinated ? "Yes" : "No") << endl;
    }

    void bark() {
        cout << "  " << Pet::getName() << " says: Woof! Woof!" << endl;
    }
};

// ================================================================
//  CLASS 3 : Cat  (Derived — INHERITANCE from Pet)
//  New class added to demonstrate Cat along with Dog
// ================================================================
class Cat : public Pet {
private:
    string furColor;
    bool   isIndoor;

public:
    Cat() : isIndoor(false) {}

    // ---------- Setters ----------
    void setFurColor(string c)  { furColor = c; }
    void setIndoor(bool i)      { isIndoor  = i; }

    // ---------- Getters ----------
    string getFurColor()  { return furColor; }
    bool   getIndoor()    { return isIndoor; }

    // OOP — POLYMORPHISM : overrides Pet::display() at runtime
    void display() override {
        Pet::displayPet();
        cout << "  Fur Color   : " << furColor << endl;
        cout << "  Indoor      : " << (isIndoor ? "Yes" : "No") << endl;
    }

    void meow() {
        cout << "  " << Pet::getName() << " says: Meow! Meow!" << endl;
    }
};

// ================================================================
//  CLASS 4 : Owner
//  OOP — ENCAPSULATION : ownerID, name, phone, email are private
// ================================================================
class Owner {
private:
    int    ownerID;
    string name;
    string phone;
    string email;

public:
    Owner() : ownerID(0) {}

    // ---------- Setters ----------
    void setOwnerID(int id)   { ownerID = id; }
    void setName(string n)    { name    = n;  }
    void setPhone(string p)   { phone   = p;  }
    void setEmail(string e)   { email   = e;  }

    // ---------- Getters ----------
    int    getOwnerID()  { return ownerID; }
    string getName()     { return name;    }
    string getPhone()    { return phone;   }
    string getEmail()    { return email;   }

    // ---------- Display ----------
    void displayOwner() {
        cout << "  Owner ID : " << ownerID << endl;
        cout << "  Name     : " << name    << endl;
        cout << "  Phone    : " << phone   << endl;
        cout << "  Email    : " << email   << endl;
    }
};

// ================================================================
//  CLASS 5 : Appointment
//  OOP — ENCAPSULATION : all fields are private
// ================================================================
class Appointment {
private:
    int    appointmentID;
    int    petID;
    string date;
    string purpose;
    string status;

public:
    Appointment() : appointmentID(0), petID(0), status("Scheduled") {}

    // ---------- Setters ----------
    void setAppointmentID(int id)  { appointmentID = id;          }
    void setPetID(int pid)         { petID         = pid;         }
    void setDate(string d)         { date          = d;           }
    void setPurpose(string p)      { purpose       = p;           }
    void setStatus(string s)       { status        = s;           }

    // ---------- Getters ----------
    int    getAppointmentID()  { return appointmentID; }
    int    getPetID()          { return petID;         }
    string getDate()           { return date;          }
    string getPurpose()        { return purpose;       }
    string getStatus()         { return status;        }

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

// ================================================================
//  HELPER : Print separator line
// ================================================================
void printLine() {
    cout << "  ----------------------------------------" << endl;
}

// ================================================================
//  HELPER : Print the main menu  (UNCHANGED from original)
// ================================================================
void showMenu() {
    cout << endl;
    cout << "  ========================================" << endl;
    cout << "      PET CARE MANAGEMENT SYSTEM         " << endl;
    cout << "  ========================================" << endl;
    cout << "  1. Add Pet (Dog)" << endl;
    cout << "  2. Display All Pets" << endl;
    cout << "  3. Add Owner" << endl;
    cout << "  4. Display All Owners" << endl;
    cout << "  5. Add Appointment" << endl;
    cout << "  6. Display All Appointments" << endl;
    cout << "  7. Exit" << endl;
    cout << "  ----------------------------------------" << endl;
    cout << "  Enter your choice: ";
}

// ================================================================
//  STL [E] — find_if() HELPER PREDICATES
//  These are simple functions used by find_if() to search by ID.
//  A predicate returns true when the element matches.
// ================================================================

// Checks if a Pet pointer has the given petID
struct MatchPetID {
    int targetID;
    MatchPetID(int id) : targetID(id) {}
    bool operator()(Pet* p) {
        return p->getPetID() == targetID;
    }
};

// Checks if an Owner has the given ownerID
struct MatchOwnerID {
    int targetID;
    MatchOwnerID(int id) : targetID(id) {}
    bool operator()(const Owner& o) {
        return const_cast<Owner&>(o).getOwnerID() == targetID;
    }
};

// Checks if an Appointment has the given appointmentID
struct MatchApptID {
    int targetID;
    MatchApptID(int id) : targetID(id) {}
    bool operator()(const Appointment& a) {
        return const_cast<Appointment&>(a).getAppointmentID() == targetID;
    }
};

// ================================================================
//  STL [F] — sort() COMPARATOR
//  Used to sort pets alphabetically by name before displaying.
// ================================================================
bool comparePetByName(Pet* a, Pet* b) {
    return a->getName() < b->getName();
}

// ================================================================
//  MAIN FUNCTION — Menu-driven program using switch-case
//  FLOW is IDENTICAL to original; only storage changed to STL.
// ================================================================
int main() {

    // ── STL [A] vector<Pet*> replaces Dog dogs[MAX] ──────────────
    // Pet* allows storing Dog AND Cat objects (polymorphism)
    vector<Pet*> pets;          // STL CONTAINER — stores pointers to Pet objects

    // ── STL [B] vector<Owner> replaces Owner owners[MAX] ─────────
    vector<Owner> owners;       // STL CONTAINER — stores Owner objects

    // ── STL [C] vector<Appointment> replaces Appointment arr[] ───
    vector<Appointment> appointments;  // STL CONTAINER

    int choice;
    int    id, age, petRef;
    string name, breed, phone, email, date, purpose;
    char   vacChar;

    // ── Main program loop ──────────────────────────────────────────
    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {

            // ────────────────────────────────────────────────────
            // OPTION 1 : Add a Pet (Dog)
            //  OOP — Uses Dog (derived class) and polymorphism
            //  STL — push_back() adds Dog* to vector<Pet*>
            //  OOP — EXCEPTION HANDLING: duplicate ID check
            // ────────────────────────────────────────────────────
            case 1: {
                cout << endl << "  --- Add New Dog ---" << endl;

                cout << "  Enter Pet ID   : "; cin >> id;  cin.ignore();

                // OOP — EXCEPTION HANDLING : check for duplicate Pet ID
                // STL [E] — find_if() searches vector using MatchPetID predicate
                vector<Pet*>::iterator dupIt = find_if(
                    pets.begin(), pets.end(), MatchPetID(id)
                );

                try {
                    if (dupIt != pets.end()) {
                        // ID already exists — throw exception
                        throw runtime_error("Pet ID already exists!");
                    }

                    // Create new Dog on heap (needed for polymorphism with Pet*)
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

                    // STL [A] — push_back() adds Dog* into vector<Pet*>
                    pets.push_back(d);
                    cout << "  [+] Dog added successfully!" << endl;
                }
                catch (runtime_error& e) {
                    // OOP — EXCEPTION HANDLING : catch and report error
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            // ────────────────────────────────────────────────────
            // OPTION 2 : Display All Pets
            //  STL [F] — sort() sorts pets by name before display
            //  STL [D] — explicit iterator loop used here
            //  OOP — POLYMORPHISM : d->display() calls Dog::display()
            // ────────────────────────────────────────────────────
            case 2: {
                cout << endl << "  --- All Pets (Dogs) ---" << endl;

                if (pets.empty()) {    // vector method: empty()
                    cout << "  No pets added yet." << endl;
                    break;
                }

                // STL [F] — sort() algorithm: sorts pets alphabetically by name
                sort(pets.begin(), pets.end(), comparePetByName);
                cout << "  (Sorted alphabetically by name)" << endl;

                // STL [D] — EXPLICIT ITERATOR LOOP (required in syllabus)
                // vector<Pet*>::iterator traverses the vector one by one
                int count = 1;
                for (vector<Pet*>::iterator it = pets.begin();
                     it != pets.end(); ++it) {

                    printLine();
                    cout << "  Pet #" << count++ << endl;

                    // OOP — POLYMORPHISM : (*it) is Pet*, but calls Dog::display()
                    (*it)->display();

                    // Cast to Dog* to call bark() — safe since we only add Dogs here
                    Dog* dogPtr = dynamic_cast<Dog*>(*it);
                    if (dogPtr != nullptr) {
                        dogPtr->bark();
                    }
                }
                printLine();
                break;
            }

            // ────────────────────────────────────────────────────
            // OPTION 3 : Add an Owner
            //  STL [B] — push_back() adds Owner into vector<Owner>
            //  OOP — EXCEPTION HANDLING: duplicate owner ID check
            //  STL [E] — find_if() used to detect duplicate ID
            // ────────────────────────────────────────────────────
            case 3: {
                cout << endl << "  --- Add New Owner ---" << endl;

                cout << "  Enter Owner ID : "; cin >> id; cin.ignore();

                // STL [E] — find_if() searches owners vector for duplicate ID
                vector<Owner>::iterator dupOwner = find_if(
                    owners.begin(), owners.end(), MatchOwnerID(id)
                );

                try {
                    if (dupOwner != owners.end()) {
                        throw runtime_error("Owner ID already exists!");
                    }

                    Owner o;
                    o.setOwnerID(id);

                    cout << "  Enter Name     : "; getline(cin, name);
                    o.setName(name);

                    cout << "  Enter Phone    : "; getline(cin, phone);
                    o.setPhone(phone);

                    cout << "  Enter Email    : "; getline(cin, email);
                    o.setEmail(email);

                    // STL [B] — push_back() grows vector automatically (no MAX limit)
                    owners.push_back(o);
                    cout << "  [+] Owner added successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            // ────────────────────────────────────────────────────
            // OPTION 4 : Display All Owners
            //  STL [D] — explicit iterator loop used here
            // ────────────────────────────────────────────────────
            case 4: {
                cout << endl << "  --- All Owners ---" << endl;

                if (owners.empty()) {
                    cout << "  No owners added yet." << endl;
                    break;
                }

                // STL [D] — EXPLICIT ITERATOR LOOP over vector<Owner>
                int count = 1;
                for (vector<Owner>::iterator it = owners.begin();
                     it != owners.end(); ++it) {

                    printLine();
                    cout << "  Owner #" << count++ << endl;
                    it->displayOwner();   // it->  is same as (*it).
                }
                printLine();
                break;
            }

            // ────────────────────────────────────────────────────
            // OPTION 5 : Add an Appointment
            //  STL [C] — push_back() into vector<Appointment>
            //  STL [E] — find_if() checks duplicate appointment ID
            //  OOP — EXCEPTION HANDLING for duplicate ID
            // ────────────────────────────────────────────────────
            case 5: {
                cout << endl << "  --- Add New Appointment ---" << endl;

                cout << "  Enter Appointment ID : "; cin >> id;     cin.ignore();

                // STL [E] — find_if() checks for duplicate appointment ID
                vector<Appointment>::iterator dupAppt = find_if(
                    appointments.begin(), appointments.end(), MatchApptID(id)
                );

                try {
                    if (dupAppt != appointments.end()) {
                        throw runtime_error("Appointment ID already exists!");
                    }

                    Appointment a;
                    a.setAppointmentID(id);

                    cout << "  Enter Pet ID         : "; cin >> petRef; cin.ignore();
                    a.setPetID(petRef);

                    cout << "  Enter Date (DD/MM/YYYY): "; getline(cin, date);
                    a.setDate(date);

                    cout << "  Enter Purpose        : "; getline(cin, purpose);
                    a.setPurpose(purpose);

                    a.setStatus("Scheduled");

                    // STL [C] — push_back() adds Appointment into vector
                    appointments.push_back(a);
                    cout << "  [+] Appointment scheduled successfully!" << endl;
                }
                catch (runtime_error& e) {
                    cout << "  [!] Error: " << e.what() << endl;
                }
                break;
            }

            // ────────────────────────────────────────────────────
            // OPTION 6 : Display All Appointments
            //  STL [D] — explicit iterator loop used here
            // ────────────────────────────────────────────────────
            case 6: {
                cout << endl << "  --- All Appointments ---" << endl;

                if (appointments.empty()) {
                    cout << "  No appointments added yet." << endl;
                    break;
                }

                // STL [D] — EXPLICIT ITERATOR LOOP over vector<Appointment>
                int count = 1;
                for (vector<Appointment>::iterator it = appointments.begin();
                     it != appointments.end(); ++it) {

                    printLine();
                    cout << "  Appointment #" << count++ << endl;
                    it->displayAppointment();
                }
                printLine();
                break;
            }

            // ────────────────────────────────────────────────────
            // OPTION 7 : Exit
            //  Free all heap memory (Dog/Cat objects created with new)
            // ────────────────────────────────────────────────────
            case 7: {
                // Free memory: each Pet* was allocated with new Dog()
                for (vector<Pet*>::iterator it = pets.begin();
                     it != pets.end(); ++it) {
                    delete *it;   // call destructor for each Dog/Cat
                }
                pets.clear();

                cout << endl;
                cout << "  Thank you for using Pet Care Management System!" << endl;
                cout << "  Goodbye!" << endl << endl;
                break;
            }

            // ────────────────────────────────────────────────────
            // DEFAULT : Invalid input
            // ────────────────────────────────────────────────────
            default:
                cout << "  [!] Invalid choice. Please enter 1-7." << endl;
                break;
        }

    } while (choice != 7);

    return 0;
}

