#include "TRandom.h"

Int_t task_4()
{
    Int_t N = 1000000;
    Double_t x_lower_boundary = -30., x_upper_boundary = 30.;

    TRandom* distributor = new TRandom();
    distributor->SetSeed();

    TF1* our_function = new TF1("our_function", "exp(-abs(x)*5)/(x*x+100)", x_lower_boundary, x_upper_boundary);

    Double_t M = our_function->GetMaximum(x_lower_boundary, x_upper_boundary);

    TH1D* result = new TH1D("result", "result", sqrt(N), x_lower_boundary, x_upper_boundary);
    for(int i = 0; i < N - 1; i++)
    {   
        Double_t rand_x = distributor->Uniform(x_lower_boundary, x_upper_boundary), rand_y = distributor->Uniform(0, M);
        if(rand_y <= our_function->Eval(rand_x)) result->Fill(rand_x);
    }

    result->Draw("hist");
    result->SetFillColor(kBlue);

    return 0; 
}