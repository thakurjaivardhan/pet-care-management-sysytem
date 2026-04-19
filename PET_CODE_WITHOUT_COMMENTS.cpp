#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;


const int MAX_OWNERS       = 50;
const int MAX_PETS         = 50;
const int MAX_APPOINTMENTS = 50;

class Owner {
private:
    int    ownerID;
    string name;
    string phone;

public:

    Owner() : ownerID(0), name("Unknown"), phone("N/A") {}


    Owner(int id, string n, string p) : ownerID(id), name(n), phone(p) {}


    Owner(const Owner& other)
        : ownerID(other.ownerID), name(other.name), phone(other.phone) {
        cout << "  [Copy Constructor] Owner \"" << name << "\" was copied.\n";
    }


    ~Owner() {
        
    }

    int    getOwnerID() const { return ownerID; }
    string getName()    const { return name; }
    string getPhone()   const { return phone; }

    void display() const {
        cout << "  Owner ID : " << ownerID << "\n"
             << "  Name     : " << name    << "\n"
             << "  Phone    : " << phone   << "\n";
    }
};


class Pet {
protected:
    int    petID;
    string petName;
    int    ownerID;  
    string species;  

public:
    Pet() : petID(0), petName("Unknown"), ownerID(0), species("Unknown") {}

    
    Pet(int pid, string pname, int oid, string spec)
        : petID(pid), petName(pname), ownerID(oid), species(spec) {}

    int    getPetID()   const { return petID; }
    string getPetName() const { return petName; }
    int    getOwnerID() const { return ownerID; }
    string getSpecies() const { return species; }

    virtual void display() const = 0;

    virtual ~Pet() {
        cout << "  [Destructor] Pet \"" << petName << "\" removed from memory.\n";
    }
};


class Dog : public Pet {
private:
    string breed;

public:
    Dog() : Pet(), breed("Unknown") {}

    Dog(int pid, string pname, int oid, string b)
        : Pet(pid, pname, oid, "Dog"), breed(b) {}


    void display() const override {
        cout << "  Pet ID   : " << petID   << "\n"
             << "  Name     : " << petName << "\n"
             << "  Species  : " << species << "\n"
             << "  Owner ID : " << ownerID << "\n"
             << "  Breed    : " << breed   << "\n";
    }
};

class Cat : public Pet {
private:
    bool isIndoor;

public:
    Cat() : Pet(), isIndoor(true) {}

    Cat(int pid, string pname, int oid, bool indoor)
        : Pet(pid, pname, oid, "Cat"), isIndoor(indoor) {}

    void display() const override {
        cout << "  Pet ID   : " << petID   << "\n"
             << "  Name     : " << petName << "\n"
             << "  Species  : " << species << "\n"
             << "  Owner ID : " << ownerID << "\n"
             << "  Type     : " << (isIndoor ? "Indoor" : "Outdoor") << "\n";
    }
};


class Appointment {
private:
    int    apptID;
    int    petID;
    string date;    
    string reason;

public:
    static int apptCounter;   

    Appointment() : apptID(0), petID(0), date("N/A"), reason("N/A") {}

    Appointment(int pid, string d, string r)
        : apptID(++apptCounter), petID(pid), date(d), reason(r) {}

    void display() const {
        cout << "  Appt ID  : " << apptID << "\n"
             << "  Pet ID   : " << petID  << "\n"
             << "  Date     : " << date   << "\n"
             << "  Reason   : " << reason << "\n";
    }
};

int Appointment::apptCounter = 0;

template <typename T>
void printSectionHeader(T title) {
    cout << "\n========================================\n";
    cout << "  " << title << "\n";
    cout << "========================================\n";
}

class PetCareSystem {
private:
   
    Owner       owners[MAX_OWNERS];               
    Pet*        pets[MAX_PETS];                  
    Appointment appointments[MAX_APPOINTMENTS];   


    int ownerCount = 0;
    int petCount   = 0;
    int apptCount  = 0;

    int ownerCounter = 0;
    int petCounter   = 0;

    void initPets() {
        for (int i = 0; i < MAX_PETS; i++)
            pets[i] = nullptr;
    }

    bool ownerExists(int id) {

        for (int i = 0; i < ownerCount; i++)
            if (owners[i].getOwnerID() == id) return true;
        return false;
    }


    bool petExists(int id) {
        for (int i = 0; i < petCount; i++)
            if (pets[i]->getPetID() == id) return true;
        return false;
    }

public:
    
    PetCareSystem() {
        initPets();
    }

    ~PetCareSystem() {
        for (int i = 0; i < petCount; i++) {
            delete pets[i];     
            pets[i] = nullptr;   
        }
        cout << "\n[Destructor] PetCareSystem shut down. All pet records cleared from memory.\n";
    }

    void registerOwner() {
        string name, phone;

        cout << "\n--- Register Owner ---\n";
        cout << "Enter Owner Name  : "; cin.ignore(); getline(cin, name);
        cout << "Enter Phone Number: "; getline(cin, phone);

    
        try {
            if (name.empty() || phone.empty())
                throw invalid_argument("Name and phone cannot be empty.");

     
            if (ownerCount >= MAX_OWNERS)
                throw runtime_error("Owner list is full. Cannot add more owners.");

            int id = ++ownerCounter;

            owners[ownerCount] = Owner(id, name, phone);
            ownerCount++;

            cout << "  Owner registered successfully! Owner ID: " << id << "\n";
        }
        catch (const exception& e) {
            cout << "  Error: " << e.what() << "\n";
            --ownerCounter;
        }
    }

    void registerPet() {
        int ownerID, petType;
        string petName;

        cout << "\n--- Register Pet ---\n";
        cout << "Enter Owner ID (pet belongs to): "; cin >> ownerID;

        try {
            if (!ownerExists(ownerID))
                throw runtime_error("Owner ID " + to_string(ownerID) + " not found. Register the owner first.");

            if (petCount >= MAX_PETS)
                throw runtime_error("Pet list is full. Cannot add more pets.");

            cout << "Enter Pet Name  : "; cin.ignore(); getline(cin, petName);
            if (petName.empty()) throw invalid_argument("Pet name cannot be empty.");

            cout << "Select Species  : 1) Dog  2) Cat\nChoice: "; cin >> petType;

            int pid = ++petCounter;

            if (petType == 1) {
                string breed;
                cout << "Enter Breed     : "; cin.ignore(); getline(cin, breed);
                pets[petCount] = new Dog(pid, petName, ownerID, breed);
            }
            else if (petType == 2) {
                char indoorChar;
                cout << "Indoor cat? (y/n): "; cin >> indoorChar;
                bool indoor = (indoorChar == 'y' || indoorChar == 'Y');
                pets[petCount] = new Cat(pid, petName, ownerID, indoor);
            }
            else {
                throw invalid_argument("Invalid species choice.");
            }

            petCount++;
            cout << "  Pet registered successfully! Pet ID: " << pid << "\n";
        }
        catch (const exception& e) {
            cout << "  Error: " << e.what() << "\n";
            --petCounter;
        }
    }

    void bookAppointment() {
        int petID;
        string date, reason;

        cout << "\n--- Book Appointment ---\n";
        cout << "Enter Pet ID : "; cin >> petID;

        try {
            if (!petExists(petID))
                throw runtime_error("Pet ID " + to_string(petID) + " not found.");

            if (apptCount >= MAX_APPOINTMENTS)
                throw runtime_error("Appointment list is full.");

            cout << "Enter Date (DD/MM/YYYY): "; cin.ignore(); getline(cin, date);
            cout << "Enter Reason           : "; getline(cin, reason);

            if (date.empty() || reason.empty())
                throw invalid_argument("Date and reason cannot be empty.");


            appointments[apptCount] = Appointment(petID, date, reason);
            apptCount++;

            cout << "  Appointment booked successfully!\n";
        }
        catch (const exception& e) {
            cout << "  Error: " << e.what() << "\n";
        }
    }

    void searchPet(int id) {

        cout << "\n--- Search Result (by ID: " << id << ") ---\n";
        bool found = false;
        for (int i = 0; i < petCount; i++) {
            if (pets[i]->getPetID() == id) {
                pets[i]->display();
                found = true;
                break;
            }
        }
        if (!found) cout << "  No pet found with ID " << id << ".\n";
    }

    void searchPet(const string& name) {

        cout << "\n--- Search Result (by Name: \"" << name << "\") ---\n";
        bool found = false;
        for (int i = 0; i < petCount; i++) {
            string pName = pets[i]->getPetName();
            string qName = name;
            for (int c = 0; c < (int)pName.size(); c++) pName[c] = tolower(pName[c]);
            for (int c = 0; c < (int)qName.size(); c++) qName[c] = tolower(qName[c]);
            if (pName == qName) {
                pets[i]->display();
                cout << "  ----------\n";
                found = true;
            }
        }
        if (!found) cout << "  No pet found with name \"" << name << "\".\n";
    }

    void searchMenu() {
        int choice;
        cout << "\n--- Search Pet ---\n";
        cout << "1) Search by ID\n2) Search by Name\nChoice: ";
        cin >> choice;

        try {
            if (choice == 1) {
                int id;
                cout << "Enter Pet ID  : "; cin >> id;
                searchPet(id);          
            }
            else if (choice == 2) {
                string name;
                cout << "Enter Pet Name: "; cin.ignore(); getline(cin, name);
                searchPet(name);      
            }
            else {
                throw invalid_argument("Invalid search option.");
            }
        }
        catch (const exception& e) {
            cout << "  Error: " << e.what() << "\n";
        }
    }

    void displayAllRecords() {
        printSectionHeader(string("ALL OWNERS"));
        if (ownerCount == 0) cout << "  No owners registered yet.\n";
        for (int i = 0; i < ownerCount; i++) {
            owners[i].display();
            cout << "  --------\n";
        }

        printSectionHeader(string("ALL PETS"));
        if (petCount == 0) cout << "  No pets registered yet.\n";
        for (int i = 0; i < petCount; i++) {
            pets[i]->display(); 
            cout << "  --------\n";
        }

        printSectionHeader(string("ALL APPOINTMENTS"));
        if (apptCount == 0) cout << "  No appointments booked yet.\n";
        for (int i = 0; i < apptCount; i++) {
            appointments[i].display();
            cout << "  --------\n";
        }
    }

    void run() {
        cout << "\n============================================\n";
        cout << "   Welcome to Paws & Claws Management     \n";
        cout << "============================================\n";

        int choice;
        do {
            cout << "\n--- Phase 1: Setup ---\n";
            cout << "  1. Register Owner\n";
            cout << "  2. Register Pet\n";
            cout << "--- Phase 2: Operations ---\n";
            cout << "  3. Book Appointment\n";
            cout << "  4. Search Pet (by ID or Name)\n";
            cout << "--- Phase 3: Management ---\n";
            cout << "  5. Display All Records\n";
            cout << "  6. Exit\n";
            cout << "Enter choice: ";
            cin  >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "  Please enter a valid number.\n";
                continue;
            }

            switch (choice) {
                case 1: registerOwner();     break;
                case 2: registerPet();       break;
                case 3: bookAppointment();   break;
                case 4: searchMenu();        break;
                case 5: displayAllRecords(); break;
                case 6: cout << "\nGoodbye! Keep your pets happy!\n"; break;
                default: cout << "  Invalid option. Try again.\n";
            }

        } while (choice != 6);
    }
};
int main() {
    PetCareSystem system;
    system.run();
    return 0;
}