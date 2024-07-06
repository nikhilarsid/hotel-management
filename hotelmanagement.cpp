#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// Room class
class Room {
public:
  int roomNumber;
  string roomType;
  bool isAvailable;
  int floorNumber;
  double price;

  Room(int number, string type, int floor, double price)
      : roomNumber(number), roomType(type), isAvailable(true),
        floorNumber(floor), price(price) {}
};

// Customer class
class Customer {
public:
  string name;
  string address;
  string phone;
  int roomNumber;
  double bill;

  Customer(string n, string a, string p, int r)
      : name(n), address(a), phone(p), roomNumber(r), bill(0.0) {}
};

// Staff class
class Staff {
public:
  string name;
  string position;
  double salary;

  Staff(string n, string p, double s) : name(n), position(p), salary(s) {}
};

// Inventory class
class Inventory {
public:
  string itemName;
  int quantity;

  Inventory() : itemName(""), quantity(0) {}
  Inventory(string name, int qty) : itemName(name), quantity(qty) {}
};

// Hotel class
class Hotel {
private:
  vector<Room> rooms;
  vector<Customer> customers;
  vector<Staff> staff;
  unordered_map<string, Inventory> inventory;
  map<int, double> floorPrices;

public:
  Hotel() {

    floorPrices[0] = 100.0;
    floorPrices[1] = 70.0;
    floorPrices[2] = 60.0;

    // Initialize some rooms
    addRoom(0, 101, "Single");
    addRoom(0, 102, "Double");
    addRoom(1, 201, "Single");
    addRoom(1, 202, "Double");
    addRoom(2, 301, "Single");
    addRoom(2, 302, "Suite");
  }

  void setFloorPrice(int floorNumber, double price) {
    floorPrices[floorNumber] = price;
    cout << "Set price for floor " << floorNumber << " to $" << price << endl;
  }

  void addRoom(int floorNumber, int roomNumber, string roomType) {
    double price = floorPrices[floorNumber];
    rooms.push_back(Room(roomNumber, roomType, floorNumber, price));
    cout << "Room " << roomNumber << " on floor " << floorNumber
         << " added successfully with price $" << price << "!" << endl;
  }

  void bookRoom(string name, string address, string phone, int roomNumber) {
    for (auto &room : rooms) {
      if (room.roomNumber == roomNumber && room.isAvailable) {
        room.isAvailable = false;
        customers.push_back(Customer(name, address, phone, roomNumber));
        cout << "Room " << roomNumber << " booked successfully!" << endl;
        return;
      }
    }
    cout << "Room " << roomNumber << " is not available." << endl;
  }

  void checkIn(int roomNumber) {
    for (auto &room : rooms) {
      if (room.roomNumber == roomNumber && !room.isAvailable) {
        cout << "Customer checked into room " << roomNumber << " successfully!"
             << endl;
        return;
      }
    }
    cout << "Room " << roomNumber << " is not booked." << endl;
  }

  void checkOut(int roomNumber) {
    for (auto &room : rooms) {
      if (room.roomNumber == roomNumber && !room.isAvailable) {
        room.isAvailable = true;
        for (auto it = customers.begin(); it != customers.end(); ++it) {
          if (it->roomNumber == roomNumber) {
            customers.erase(it);
            break;
          }
        }
        cout << "Customer checked out of room " << roomNumber
             << " successfully!" << endl;
        return;
      }
    }
    cout << "Room " << roomNumber << " is not occupied." << endl;
  }

  void showRooms() {
    for (const auto &room : rooms) {
      cout << "Room " << room.roomNumber << " (" << room.roomType
           << ") on floor " << room.floorNumber << " - "
           << (room.isAvailable ? "Available" : "Not Available") << ", Price: $"
           << room.price << endl;
    }
  }

  void showCustomers() {
    for (const auto &customer : customers) {
      cout << "Customer: " << customer.name << ", Address: " << customer.address
           << ", Phone: " << customer.phone << ", Room: " << customer.roomNumber
           << ", Bill: $" << customer.bill << endl;
    }
  }

  void addCharge(int roomNumber, double amount) {
    for (auto &customer : customers) {
      if (customer.roomNumber == roomNumber) {
        customer.bill += amount;
        cout << "Added charge of $" << amount << " to room " << roomNumber
             << endl;
        return;
      }
    }
    cout << "Room " << roomNumber << " not found." << endl;
  }

  void payBill(int roomNumber, string paymentMethod) {
    for (auto &customer : customers) {
      if (customer.roomNumber == roomNumber) {
        cout << "Bill of $" << customer.bill << " paid for room " << roomNumber
             << " using " << paymentMethod << endl;
        customer.bill = 0;
        return;
      }
    }
    cout << "Room " << roomNumber << " not found." << endl;
  }

  void addStaff(string name, string position, double salary) {
    staff.push_back(Staff(name, position, salary));
    cout << "Staff member " << name << " added." << endl;
  }

  void showStaff() {
    for (const auto &s : staff) {
      cout << "Staff: " << s.name << ", Position: " << s.position
           << ", Salary: $" << s.salary << endl;
    }
  }

  void addInventory(string itemName, int quantity) {
    if (inventory.find(itemName) != inventory.end()) {
      inventory[itemName].quantity += quantity;
    } else {
      inventory[itemName] = Inventory(itemName, quantity);
    }
    cout << "Added " << quantity << " of " << itemName << " to inventory."
         << endl;
  }

  void showInventory() {
    for (const auto &item : inventory) {
      cout << "Item: " << item.second.itemName
           << ", Quantity: " << item.second.quantity << endl;
    }
  }
};

int main() {
  Hotel myHotel;
  int choice;
  string name, address, phone, itemName, position, roomType, paymentMethod;
  int floorNumber, roomNumber, quantity;
  double amount, salary, price;

  while (true) {
    cout << "\nHotel Management System\n";
    cout << "1. Show Rooms\n";
    cout << "2. Book Room\n";
    cout << "3. Check In\n";
    cout << "4. Check Out\n";
    cout << "5. Show Customers\n";
    cout << "6. Add Charge\n";
    cout << "7. Pay Bill\n";
    cout << "8. Add Staff\n";
    cout << "9. Show Staff\n";
    cout << "10. Add Inventory\n";
    cout << "11. Show Inventory\n";
    cout << "12. Add Room\n";
    cout << "13. Set Floor Price\n";
    cout << "14. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (choice) {
    case 1:
      myHotel.showRooms();
      break;
    case 2:
      cout << "Enter name: ";
      getline(cin, name);
      cout << "Enter address: ";
      getline(cin, address);
      cout << "Enter phone: ";
      getline(cin, phone);
      cout << "Enter room number: ";
      cin >> roomNumber;
      myHotel.bookRoom(name, address, phone, roomNumber);
      break;
    case 3:
      cout << "Enter room number: ";
      cin >> roomNumber;
      myHotel.checkIn(roomNumber);
      break;
    case 4:
      cout << "Enter room number: ";
      cin >> roomNumber;
      myHotel.checkOut(roomNumber);
      break;
    case 5:
      myHotel.showCustomers();
      break;
    case 6:
      cout << "Enter room number: ";
      cin >> roomNumber;
      cout << "Enter amount: ";
      cin >> amount;
      myHotel.addCharge(roomNumber, amount);
      break;
    case 7:
      cout << "Enter room number: ";
      cin >> roomNumber;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter payment method (e.g., credit card, debit card): ";
      getline(cin, paymentMethod);
      myHotel.payBill(roomNumber, paymentMethod);
      break;
    case 8:
      cout << "Enter name: ";
      getline(cin, name);
      cout << "Enter position: ";
      getline(cin, position);
      cout << "Enter salary: ";
      cin >> salary;
      myHotel.addStaff(name, position, salary);
      break;
    case 9:
      myHotel.showStaff();
      break;
    case 10:
      cout << "Enter item name: ";
      getline(cin, itemName);
      cout << "Enter quantity: ";
      cin >> quantity;
      myHotel.addInventory(itemName, quantity);
      break;
    case 11:
      myHotel.showInventory();
      break;
    case 12:
      cout << "Enter floor number: ";
      cin >> floorNumber;
      cout << "Enter room number: ";
      cin >> roomNumber;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter room type: ";
      getline(cin, roomType);
      myHotel.addRoom(floorNumber, roomNumber, roomType);
      break;
    case 13:
      cout << "Enter floor number: ";
      cin >> floorNumber;
      cout << "Enter price: ";
      cin >> price;
      myHotel.setFloorPrice(floorNumber, price);
      break;
    case 14:
      return 0;
    default:
      cout << "Invalid choice!" << endl;
    }
  }

  return 0;
}