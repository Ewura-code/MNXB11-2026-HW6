#include <TFile.h>
#include <TTree.h>
#include <TRandom.h>
#include "MovingObject.h"

void write() {
    // 1. Create tree_file.root in RECREATE mode
    TFile *file = new TFile("tree_file.root", "RECREATE");

    // 2. Create a TTree named "tree"
    TTree *tree = new TTree("tree", "Tree of moving object measurements");

    // 3. Create one MovingObject instance to keep alive throughout the loop
    MovingObject *obj = new MovingObject();

    // 4. Create an object branch named "object" for your class
    // Syntax: Branch(branchName, className, addressOfPointer)
    tree->Branch("object", "MovingObject", &obj);

    // 5. Set a fixed random seed for reproducibility
    gRandom->SetSeed(12345);

    // 6. Loop to generate 10,000 independent measurements[cite: 6]
    const Int_t nMeasurements = 10000;
    for (Int_t i = 0; i < nMeasurements; ++i) {
        // Generate components: Gaussian distribution (mean = 0.0, sigma = 0.30)[cite: 6]
        Double_t vx = gRandom->Gaus(0.0, 0.30);
        Double_t vy = gRandom->Gaus(0.0, 0.30);
        Double_t vz = gRandom->Gaus(0.0, 0.30);

        // Update the existing object's velocity[cite: 7]
        obj->SetVelocity(vx, vy, vz);

        // Fill the tree with the current state of the object
        tree->Fill();
    }

    // 7. Write the tree/file and close it[cite: 6]
    tree->Write();
    file->Close();

    // 8. Release dynamically allocated resources to avoid memory leaks
    delete obj;
    delete file;
}