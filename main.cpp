#include <bits/stdc++.h>
#define int long long
#define print(a) cout << a << "\n";
#define ret return;
using namespace std;
/**

 THE CODE I HAVE WRITTEN IS EXTENSIBLE FOR MULTIPLE PARKING LOTS WITH MULTIPLE
 SPACES, BUT FOR NOW I HAVE IMPLEMENTED FOR ONLY ONE PARKING LOT AS BASED ON THE
 INPUT.TXT

*/
class vehicle { // vehicle class
private:
  string regNo = "";
  int driverAge = -1;
  int parked_in = -1;
  int parkingLotNo = -1;

public:
  void setDetails(string reg_no, int age, int idx, int row) {
    regNo = reg_no;
    driverAge = age;
    parked_in = idx;
    parkingLotNo = row;
  }
  pair<int, string> getDetails() { return {driverAge, regNo}; }
  int get_parkedIn() { return parked_in; }
  int getParkingLotNo() { return parkingLotNo; }
  int getAge() { return driverAge; }
  string getRegNo() { return regNo; }
};
class parkingLot { // parking lot class
private:
  int _id = 0, MAX_SIZE = -1, load = 0;
  set<int> inActive_slots; // slots that are free
  map<int, vehicle>
      slot_details; // map of slots having details of vehicle parked
  map<string, int>
      where_; // map storing the slot number where a vehicle is parked
  string current_status() { // returning a status string that can be parsed and
                            // used for various uses
    if (MAX_SIZE == -1) {
      return "INVALID";
    }
    if (MAX_SIZE == load) {
      return "FULL";
    }
    if (MAX_SIZE - load > 0) {
      return "FREE_SPACE #" + to_string(MAX_SIZE - load);
    } else {
      return "FULL";
    }
  }

public:
  parkingLot(int n, int id) {
    MAX_SIZE = n;
    for (int i = 1; i <= n; i++) {
      inActive_slots.insert(i);
    }
    _id = id;
  }
  string get_status() { return current_status(); }
  int get_id() { return _id; }
  int whereIsVehicleParked(string regNo) { return where_[regNo]; }
  int park(int age, string regno) {
    int free_slot =
        (*inActive_slots.begin()); // get the first slot that is free
    where_[regno] = free_slot;
    vehicle vh;
    vh.setDetails(regno, age, free_slot, this->_id);
    slot_details[free_slot] = vh;
    inActive_slots.erase(inActive_slots.begin());
    load++;
    return free_slot;
  }
  vector<int> get_slot_numbers_of_age(int age) {
    vector<int> v;
    return v;
  }
  vector<int> get_slot_numbers_of_regNo(string regNo) {
    vector<int> v;
    return v;
  }
  pair<int, string> vacate(int slotNo) {

    string status = current_status();
    if (status == "INVALID") { // parking lot not created
      return {2, ""};
    }
    if (inActive_slots.find(slotNo) != inActive_slots.end()) {
      return {0, ""}; // slot is empty already
    }
    auto details = slot_details[slotNo].getDetails();
    auto it1 = where_.find(details.second);
    where_.erase(it1);
    auto it = slot_details.find(slotNo);
    slot_details.erase(it);
    inActive_slots.insert(slotNo);
    load--;
    return {1, details.second};
  }
  vector<int> get_registration_numbers_of_age(int age) {
    vector<int> v;
    return v;
  }
};
class globalHandler { // global class that handles multiple parking lots with
                      // spaces
public:
  int parkinglots = -1, curr_parking_lot = -1;
  vector<parkingLot> parkingLots;
  unordered_map<string, vehicle> allVehicles;
  void create_parking_lot(int n) { // create a new parking lot
    parkinglots++;
    curr_parking_lot = parkinglots; // based on the input arguments always the
                                    // current parking lot is to be reffered
    parkingLot new_parking_lot = parkingLot(n, curr_parking_lot);
    parkingLots.push_back(new_parking_lot);
    cout << "Created parking of " << n << " slots\n";
  }
  string
  make_To_String(vector<string> v) { // helper function to combine strings
    string str = "";
    for (auto &s : v) {
      str += s + " ";
    }
    return str;
  }
  void park(int age, string regNo) {
    if (allVehicles.count(regNo)) { // if the vehicle is already parked no need
                                    // to park it again
      auto details = allVehicles[regNo].getDetails();
      print("Sorry car with registration number already parked in parking lot "
            << allVehicles[regNo].get_parkedIn() << " in slot number "
            << parkingLots[curr_parking_lot].whereIsVehicleParked(regNo));
      return;
    }
    if (curr_parking_lot ==
        -1) { // if no parking lot is created, have to create a parking lot
      cout << "Sorry no Parking Lot created\n";
      return;
    }
    string status = parkingLots[curr_parking_lot].get_status();
    // cout<<"status = "<<status<<"\n" ;
    if (status == "INVALID") {
      cout << "Sorry Parking Lot not created";
    } else if (parkingLots[curr_parking_lot].get_status() != "FULL") { //
      int parkedin = parkingLots[curr_parking_lot].park(age, regNo);
      vehicle vh;
      vh.setDetails(regNo, age, parkedin, curr_parking_lot);
      allVehicles[regNo] = vh;
      print(make_To_String(
          {"Car with vehicle registration number", ("\"" + regNo + "\""),
           "has been parked at slot number " + to_string(parkedin)}));
    } else { // if status is full
      print("Sorry parking lot FULL");
    }
  }
  void get_slot_numbers_of_age(int age) {
    vector<int> v;
    for (auto &e : allVehicles) { // get all the vehicles slot where driver age
                                  // == given age
      if (e.second.getAge() == age) {
        v.push_back(e.second.get_parkedIn());
      }
    }
    sort(begin(v), end(v));
    if (v.size() == 0) {
      print("Sorry no vehicle parked with the given age") ret
    }
    for (auto &e : v) {
      cout << e << " ";
    }
    cout << "\n";
  }
  void get_slot_numbers_of_regNo(string regNo) {
    vector<int> v;
    for (auto &e : allVehicles) { // get all the vehicles slot where
                                  // registration No.  == given registration No.
      if (e.second.getRegNo() == regNo) {
        v.push_back(e.second.get_parkedIn());
      }
    }
    sort(begin(v), end(v));
    if (v.size() == 0) {
      print("Sorry no vehicle parked with the given registration number") ret
    }
    for (auto &e : v) {
      cout << e << " ";
    }
    cout << "\n";
  }
  void vacate(int n) {
    if (curr_parking_lot == -1) { // no parking lot created ;
      print("Sorry No parking lot created");
      ret;
    }
    auto p = parkingLots[curr_parking_lot].vacate(n);
    if (!p.first) { // when the slot is already empty
      cout << "Sorry no vehicle parked in slot number " << n << "\n";
      return;
    }
    if (p.first) {
      auto details = allVehicles[p.second].getDetails();
      auto it = allVehicles.find(p.second);
      allVehicles.erase(it);
      print(make_To_String({"Slot no", to_string(n),
                            "vacated, the car with vehicle registration no",
                            "\"" + details.second + "\"",
                            "left the space, the driver of the car was of age",
                            to_string(details.first)}));
    } else if (p.first == 2) { // parking lot not created
      print("Sorry parking lot is not created");
    } else {
      print("Sorry parking lot is already empty");
    }
  }
  void get_registration_numbers_of_age(int age) {
    vector<string> v;
    for (auto &e : allVehicles) { // get all the vehicles registration No. where
                                  // driver age  == given age
      if (e.second.getAge() == age) {
        v.push_back(e.second.getRegNo());
      }
    }
    sort(begin(v), end(v));
    if (v.size() == 0) {
      print("Sorry no vehicle found with the given age") ret
    }
    for (auto &e : v) {
      cout << e << " ";
    }
    cout << "\n";
  }
};

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cout << fixed;
  cout << setprecision(15);
  globalHandler engine;
  string cmd = "";
  // cout<<"type EXIT to exit the engine\n\n" ;
  freopen("input.txt", "r", stdin);

  while (cin >> cmd) {
    // cin>>cmd ;
    bool done = 0;
    if (cmd == "EXIT") {
      break;
    }
    if (cmd == "Create_parking_lot") {
      int n;
      cin >> n;
      engine.create_parking_lot(n);
      done = 1;
    }
    if (cmd == "Park") {
      string regNo, temp;
      int age;
      cin >> regNo;
      cin >> temp;
      cin >> age;
      if (temp != "driver_age") {
        print("Sorry INVALID command");
        continue;
      }
      engine.park(age, regNo);
      done = 1;
    }
    if (cmd == "Leave") {
      int n;
      cin >> n;
      engine.vacate(n);
      done = 1;
    }
    if (cmd == "Vehicle_registration_number_for_driver_of_age") {
      int age;
      cin >> age;
      engine.get_registration_numbers_of_age(age);
      done = 1;
    }
    if (cmd == "Slot_number_for_car_with_number") {
      string regNo;
      cin >> regNo;
      engine.get_slot_numbers_of_regNo(regNo);
      done = 1;
    }
    if (cmd == "Slot_numbers_for_driver_of_age") {
      int age;
      cin >> age;
      engine.get_slot_numbers_of_age(age);
      done = 1;
    }
    if (!done) {
      print("Sorry INVALID command");
    }
  }

  return 0;
}
