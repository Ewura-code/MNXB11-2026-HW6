#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <iostream>
#include "MovingObject.h"

void read() {
    // 1. Open tree_file.root in READ mode and check if it opened successfully
    TFile *file = new TFile("tree_file.root", "READ");
    if (!file || file->IsZombie()) {
        std::cerr << "Error: Could not open tree_file.root!" << std::endl;
        return;
    }

    // 2. Retrieve the tree named "tree" and check that it exists
    TTree *tree = nullptr;
    file->GetObject("tree", tree);
    if (!tree) {
        std::cerr << "Error: Could not find 'tree' in the file!" << std::endl;
        file->Close();
        return;
    }

    // 3. Pointer must start as nullptr for ROOT object branches
    MovingObject *obj = nullptr;
    tree->SetBranchAddress("object", &obj);

    // 4. Obtain the number of entries using Long64_t
    Long64_t nEntries = tree->GetEntries();
    std::cout << "Total entries in tree: " << nEntries << std::endl;

    // 5. Create a TH2D histogram for v_y versus v_x
    TCanvas *c1 = new TCanvas("c1", "Velocity Components Canvas", 800, 600);
    TH2D *h2_comp = new TH2D("h2_comp", "Velocity Components;v_{x} (m/s);v_{y} (m/s)", 100, -1.5, 1.5, 100, -1.5, 1.5);

    // 6. Loop over the entries using Long64_t 
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i); // Unpacks data into 'obj'

        if (obj) {
            // Fill 2D histogram using your public getter functions
            h2_comp->Fill(obj->Vx(), obj->Vy());
            
            // Print the first few values to verify they are non-zero
            if (i < 5) {
                std::cout << "DEBUG: Entry " << i << " -> Vx: " << obj->Vx() << ", Vy: " << obj->Vy() << std::endl;
            }
        } else {
            if (i < 5) {
                std::cout << "DEBUG: Entry " << i << " -> obj is null!" << std::endl;
            }
        }
    }

    // Print total entries registered in the histogram after the loop
    std::cout << "Total entries successfully filled into histogram: " << h2_comp->GetEntries() << std::endl;

    // 7. Draw explicitly on the canvas
    c1->cd();                 
    h2_comp->Draw("COLZ");    
    c1->Modified();           
    c1->Update();             
    c1->SaveAs("velocity_components.pdf");

    // 8. For the scatter plot using TTree::Draw
    TCanvas *c2 = new TCanvas("c2", "Speed Scatter Plot", 800, 600);
    c2->cd();
    tree->Draw("object.HorizontalSpeed():object.Vz()", "object.Speed() > 0.50");
    TObject *obj_temp = gPad->GetPrimitive("htemp");
    if (obj_temp) {
        TH2 *htemp = dynamic_cast<TH2*>(obj_temp);
        if (htemp) {
            htemp->SetTitle("Horizontal Speed vs Vertical Component;v_{z} (m/s);v_{xy} (m/s)");
        }
    }
    
    c2->Modified();
    c2->Update();
    c2->SaveAs("velocity_scatter.pdf");

    // 9. Cleanup file resources
    file->Close();
    delete file;
}