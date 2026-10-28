#include "MovingObject.h"
#include <cmath> // Needed for std::sqrt

// Required ROOT macro for implementation mapping
ClassImp(MovingObject);

// 1. Default Constructor (initializes components to 0)
MovingObject::MovingObject() : TObject(), fVx(0.0), fVy(0.0), fVz(0.0) {}

// 2. Parameterized Constructor
MovingObject::MovingObject(Double_t vx, Double_t vy, Double_t vz) 
    : TObject(), fVx(vx), fVy(vy), fVz(vz) {}

// 3. Destructor
MovingObject::~MovingObject() {}

// 4. Getters
Double_t MovingObject::Vx() const { return fVx; }
Double_t MovingObject::Vy() const { return fVy; }
Double_t MovingObject::Vz() const { return fVz; }

// 5. Speed calculation: v = sqrt(v_x^2 + v_y^2 + v_z^2)
Double_t MovingObject::Speed() const {
    return std::sqrt(fVx * fVx + fVy * fVy + fVz * fVz);
}

// 6. Horizontal speed calculation: v_xy = sqrt(v_x^2 + v_y^2)
Double_t MovingObject::HorizontalSpeed() const {
    return std::sqrt(fVx * fVx + fVy * fVy);
}

// 7. Setter
void MovingObject::SetVelocity(Double_t vx, Double_t vy, Double_t vz) {
    fVx = vx;
    fVy = vy;
    fVz = vz;
}