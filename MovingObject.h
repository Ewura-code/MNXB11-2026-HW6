#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H

#include <TObject.h>

class MovingObject : public TObject {
public:
    // Constructors and Destructor
    MovingObject();
    MovingObject(Double_t vx, Double_t vy, Double_t vz);
    ~MovingObject() override;

    // Getters for velocity components
    Double_t Vx() const;
    Double_t Vy() const;
    Double_t Vz() const;

    // Physics calculations
    Double_t Speed() const;
    Double_t HorizontalSpeed() const;

    // Setter
    void SetVelocity(Double_t vx, Double_t vy, Double_t vz);

private:
    Double_t fVx;
    Double_t fVy;
    Double_t fVz;

    ClassDef(MovingObject, 1);
};

#endif