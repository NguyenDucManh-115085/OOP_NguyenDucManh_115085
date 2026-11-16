#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
bool nhap_gia_tri(const string& loi_nhac, T& gia_tri) {
    while (true) {
        cout << loi_nhac;
        if (cin >> gia_tri) return true;
        if (cin.eof()) return false;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Du lieu khong hop le, vui long nhap lai.\n";
    }
}

class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;

public:
    Vehicle();
    Vehicle(int id, const string& type, int time, int duration);

    int getVehicleID() const;
    string getVehicleType() const;
    int getEntryTime() const;
    int getParkingDuration() const;
    double getParkingFee() const;
    void setVehicleID(int id);
    void setVehicleType(const string& type);
    void setEntryTime(int time);
    void setParkingDuration(int duration);
    void setParkingFee(double fee);
    double calculateFee() const;
    void display() const;
};

Vehicle::Vehicle()
    : vehicleID(0), vehicleType(""), entryTime(0), parkingDuration(0), parkingFee(0.0) {}

Vehicle::Vehicle(int id, const string& type, int time, int duration)
    : vehicleID(id), vehicleType(type), entryTime(time),
      parkingDuration(duration), parkingFee(0.0) {
    parkingFee = calculateFee();
}

int Vehicle::getVehicleID() const { return vehicleID; }
string Vehicle::getVehicleType() const { return vehicleType; }
int Vehicle::getEntryTime() const { return entryTime; }
int Vehicle::getParkingDuration() const { return parkingDuration; }
double Vehicle::getParkingFee() const { return parkingFee; }

void Vehicle::setVehicleID(int id) { vehicleID = id; }

void Vehicle::setVehicleType(const string& type) {
    vehicleType = type;
    parkingFee = calculateFee();
}

void Vehicle::setEntryTime(int time) {
    entryTime = time;
    parkingFee = calculateFee();
}

void Vehicle::setParkingDuration(int duration) {
    parkingDuration = duration;
    parkingFee = calculateFee();
}

void Vehicle::setParkingFee(double fee) { parkingFee = fee; }

double Vehicle::calculateFee() const {
    double rate = (vehicleType == "Car") ? 6.0
                : (vehicleType == "Motorcycle") ? 4.0 : 2.0;
    bool peakHour = (entryTime >= 6 && entryTime <= 9)
                 || (entryTime >= 15 && entryTime <= 18);
    double total = 0.0;
    for (int hour = 0; hour < parkingDuration; ++hour) {
        total += rate * (hour < 2 ? (peakHour ? 1.30 : 0.95) : 0.90);
    }
    return total;
}

void Vehicle::display() const {
    cout << "  ID: " << vehicleID << " | " << vehicleType
         << " | " << entryTime << "h | " << parkingDuration << "h"
         << " | Phi: $" << fixed << setprecision(2) << parkingFee << "\n";
}

class ParkingLot {
private:
    static const int MAX_VEHICLES = 3;
    int parkID;
    char size;
    Vehicle vehicles[MAX_VEHICLES];
    int currentVehicleCount;

    int getCapacity() const;

public:
    ParkingLot();
    ParkingLot(int id, char lotSize);

    int getParkID() const;
    int getCurrentVehicleCount() const;
    bool isFull() const;
    bool addVehicle(const Vehicle& vehicle);
    bool removeVehicle(int vehicleID);
    int findVehicleIndex(int vehicleID) const;
    const Vehicle& getVehicle(int index) const;
    void displayLotInfo() const;
};

ParkingLot::ParkingLot()
    : parkID(0), size('S'), currentVehicleCount(0) {}

ParkingLot::ParkingLot(int id, char lotSize)
    : parkID(id), size(lotSize), currentVehicleCount(0) {}

int ParkingLot::getParkID() const { return parkID; }
int ParkingLot::getCurrentVehicleCount() const { return currentVehicleCount; }

int ParkingLot::getCapacity() const {
    return (size == 'S') ? 1 : (size == 'M') ? 2 : MAX_VEHICLES;
}

bool ParkingLot::isFull() const {
    return currentVehicleCount >= getCapacity();
}

bool ParkingLot::addVehicle(const Vehicle& vehicle) {
    if (isFull()) return false;
    vehicles[currentVehicleCount] = vehicle;
    ++currentVehicleCount;
    return true;
}

bool ParkingLot::removeVehicle(int vehicleID) {
    int index = findVehicleIndex(vehicleID);
    if (index == -1) return false;

    for (int i = index; i < currentVehicleCount - 1; ++i) {
        vehicles[i] = vehicles[i + 1];
    }
    --currentVehicleCount;
    return true;
}

int ParkingLot::findVehicleIndex(int vehicleID) const {
    for (int i = 0; i < currentVehicleCount; ++i) {
        if (vehicles[i].getVehicleID() == vehicleID) return i;
    }
    return -1;
}

const Vehicle& ParkingLot::getVehicle(int index) const {
    return vehicles[index];
}

void ParkingLot::displayLotInfo() const {
    cout << "Bai " << parkID << " [" << size << "] "
         << currentVehicleCount << "/" << getCapacity() << " xe\n";
    for (int i = 0; i < currentVehicleCount; ++i) {
        vehicles[i].display();
    }
}

class SystemInterface {
private:
    static const int MAX_LOTS = 10;
    ParkingLot parkingLots[MAX_LOTS];
    int currentLotCount;

    int findLotIndex(int parkID) const;
    void displayAverageFees() const;

public:
    SystemInterface();
    void runMenu();
    bool isParkIDExists(int parkID) const;
    bool isVehicleIDExists(int vehicleID) const;
    int generateRandomID() const;
};

SystemInterface::SystemInterface() : currentLotCount(0) {
    srand(static_cast<unsigned int>(time(0)));
}

int SystemInterface::findLotIndex(int parkID) const {
    for (int i = 0; i < currentLotCount; ++i) {
        if (parkingLots[i].getParkID() == parkID) return i;
    }
    return -1;
}

bool SystemInterface::isParkIDExists(int parkID) const {
    return findLotIndex(parkID) != -1;
}

bool SystemInterface::isVehicleIDExists(int vehicleID) const {
    for (int i = 0; i < currentLotCount; ++i) {
        if (parkingLots[i].findVehicleIndex(vehicleID) != -1) return true;
    }
    return false;
}

int SystemInterface::generateRandomID() const {
    int id;
    do {
        id = 10000 + rand() % 90000;
    } while (isParkIDExists(id) || isVehicleIDExists(id));
    return id;
}

void SystemInterface::displayAverageFees() const {
    const string vehicleTypes[3] = {"Car", "Motorcycle", "Bicycle"};

    for (int typeIndex = 0; typeIndex < 3; ++typeIndex) {
        int totalCount = 0;
        double totalFee = 0.0;
        for (int lotIndex = 0; lotIndex < currentLotCount; ++lotIndex) {
            for (int vehicleIndex = 0;
                 vehicleIndex < parkingLots[lotIndex].getCurrentVehicleCount();
                 ++vehicleIndex) {
                const Vehicle& vehicle = parkingLots[lotIndex].getVehicle(vehicleIndex);
                if (vehicle.getVehicleType() == vehicleTypes[typeIndex]) {
                    ++totalCount;
                    totalFee += vehicle.getParkingFee();
                }
            }
        }

        cout << vehicleTypes[typeIndex] << " - Toan he thong: ";
        if (totalCount == 0) cout << "khong co xe\n";
        else cout << totalCount << " xe | TB: $" << fixed << setprecision(2)
                  << totalFee / totalCount << "\n";

        for (int lotIndex = 0; lotIndex < currentLotCount; ++lotIndex) {
            int lotCount = 0;
            double lotFee = 0.0;
            for (int vehicleIndex = 0;
                 vehicleIndex < parkingLots[lotIndex].getCurrentVehicleCount();
                 ++vehicleIndex) {
                const Vehicle& vehicle = parkingLots[lotIndex].getVehicle(vehicleIndex);
                if (vehicle.getVehicleType() == vehicleTypes[typeIndex]) {
                    ++lotCount;
                    lotFee += vehicle.getParkingFee();
                }
            }
            cout << "  Bai " << parkingLots[lotIndex].getParkID() << ": ";
            if (lotCount == 0) cout << "khong co xe\n";
            else cout << lotCount << " xe | TB: $" << fixed << setprecision(2)
                      << lotFee / lotCount << "\n";
        }
    }
}

void SystemInterface::runMenu() {
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";

        int choice;
        if (!nhap_gia_tri("Chon: ", choice)) return;

        switch (choice) {
            case 1: {
                if (currentLotCount >= MAX_LOTS) {
                    cout << "Danh sach bai do da day (toi da 10 bai)!\n";
                    break;
                }

                int parkID;
                char lotSize;
                if (!nhap_gia_tri("Ma bai: ", parkID)) return;
                if (isParkIDExists(parkID)) {
                    cout << "Ma bai bi trung, tu dong gan ma moi.\n";
                    parkID = generateRandomID();
                }
                while (true) {
                    if (!nhap_gia_tri("Kich thuoc (S/M/L): ", lotSize)) return;
                    if (lotSize == 'S' || lotSize == 'M' || lotSize == 'L') break;
                    cout << "Kich thuoc khong hop le, vui long nhap S, M hoac L.\n";
                }

                parkingLots[currentLotCount] = ParkingLot(parkID, lotSize);
                ++currentLotCount;
                cout << "Da tao bai " << parkID << "\n";
                break;
            }
            case 2: {
                int vehicleID, entryTime, duration;
                string vehicleType;
                if (!nhap_gia_tri("Ma xe: ", vehicleID)) return;
                if (isVehicleIDExists(vehicleID)) {
                    cout << "Ma xe bi trung, tu dong gan ma moi.\n";
                    vehicleID = generateRandomID();
                }
                if (!nhap_gia_tri("Loai (Car/Motorcycle/Bicycle): ", vehicleType)) return;
                while (true) {
                    if (!nhap_gia_tri("Gio vao (0-23): ", entryTime)) return;
                    if (entryTime >= 0 && entryTime <= 23) break;
                    cout << "Gio vao phai nam trong khoang 0-23.\n";
                }
                while (true) {
                    if (!nhap_gia_tri("Thoi luong (1-23): ", duration)) return;
                    if (duration >= 1 && duration <= 23) break;
                    cout << "Thoi luong phai nam trong khoang 1-23.\n";
                }

                Vehicle vehicle(vehicleID, vehicleType, entryTime, duration);
                bool added = false;
                for (int i = 0; i < currentLotCount && !added; ++i) {
                    if (!parkingLots[i].isFull()) {
                        added = parkingLots[i].addVehicle(vehicle);
                    }
                }
                if (added) {
                    cout << "Da them xe " << vehicleID << " | Phi: $"
                         << fixed << setprecision(2) << vehicle.getParkingFee() << "\n";
                } else {
                    cout << "Khong co bai do con cho trong!\n";
                }
                break;
            }
            case 3: {
                int parkID;
                if (!nhap_gia_tri("Ma bai can xoa: ", parkID)) return;
                int index = findLotIndex(parkID);
                if (index == -1) {
                    cout << "Khong tim thay ma bai\n";
                    break;
                }
                for (int i = index; i < currentLotCount - 1; ++i) {
                    parkingLots[i] = parkingLots[i + 1];
                }
                --currentLotCount;
                cout << "Da xoa bai " << parkID << "\n";
                break;
            }
            case 4: {
                int vehicleID;
                if (!nhap_gia_tri("Ma xe can lay ra: ", vehicleID)) return;
                bool removed = false;
                for (int i = 0; i < currentLotCount && !removed; ++i) {
                    removed = parkingLots[i].removeVehicle(vehicleID);
                }
                cout << (removed ? "Da lay xe ra\n" : "Khong tim thay xe\n");
                break;
            }
            case 5: {
                if (currentLotCount == 0) cout << "Chua co bai do nao.\n";
                for (int i = 0; i < currentLotCount; ++i) {
                    parkingLots[i].displayLotInfo();
                }
                break;
            }
            case 6: {
                int parkID;
                if (!nhap_gia_tri("Ma bai: ", parkID)) return;
                int index = findLotIndex(parkID);
                if (index == -1) cout << "Khong tim thay thong tin\n";
                else parkingLots[index].displayLotInfo();
                break;
            }
            case 7: {
                string vehicleType;
                if (!nhap_gia_tri("Loai xe: ", vehicleType)) return;
                bool found = false;
                for (int lotIndex = 0; lotIndex < currentLotCount; ++lotIndex) {
                    bool lotHasType = false;
                    for (int vehicleIndex = 0;
                         vehicleIndex < parkingLots[lotIndex].getCurrentVehicleCount();
                         ++vehicleIndex) {
                        const Vehicle& vehicle = parkingLots[lotIndex].getVehicle(vehicleIndex);
                        if (vehicle.getVehicleType() == vehicleType) {
                            if (!lotHasType) {
                                cout << "Bai " << parkingLots[lotIndex].getParkID() << ":\n";
                                lotHasType = true;
                            }
                            vehicle.display();
                            found = true;
                        }
                    }
                }
                if (!found) cout << "Khong co xe thuoc loai nay.\n";
                break;
            }
            case 8:
                displayAverageFees();
                break;
            case 9:
                return;
            default:
                cout << "Lua chon khong hop le!\n";
                break;
        }
    }
}

int main() {
    SystemInterface system;
    system.runMenu();
    return 0;
}
