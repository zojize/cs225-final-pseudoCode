#include "Airport.h"

Airport::Airport(){
    id_ = 0;
    name_ = "";
    city_ = "";
    latitude_ = 0.0;
    longitude_ = 0.0;

}
//copy constructor
Airport::Airport(int id, std::string name, std::string city, std::string country, double latitude, double longitude) {
    id_ = id;
    name_ = name;
    city_ = city;
    country_ = country;
    latitude_ = latitude;
    longitude_ = longitude;
}

Airport::Airport(const Airport& other){
    id_ = other.id_;
    name_ = other.name_;
    city_ = other.city_;
    latitude_ = other.latitude_;
    longitude_ = other.longitude_;
}

bool Airport::operator==(const Airport & other) const{
    if(id_ == other.id_ && name_ == other.name_ && city_ == other.city_ && latitude_ == other.latitude_ && longitude_ == other.longitude_) {
      return true;
    }
    return false;

}

Airport Airport::operator=(const Airport & other) {
    id_ = other.id_;
    name_ = other.name_;
    city_ = other.city_;
    latitude_ = other.latitude_;
    longitude_ = other.longitude_;
    return *this;
}

int Airport::getID() {
    return id_;
}

std::string Airport::getName() {
    return name_;
}
