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

    // result->Draw("hist");
    result->SetFillColor(kBlue);

    //task 2
    TGraph* rms_error = new TGraph();
    TGraph* mean_error = new TGraph();
    for(int j = 0; j < 100; j++)
    {
        N += 1000;
        TH1D* temp = new TH1D("temp", "temp", sqrt(N), x_lower_boundary, x_upper_boundary);
        for(int i = 0; i < N - 1; i++)
        {   
            Double_t rand_x = distributor->Uniform(x_lower_boundary, x_upper_boundary), rand_y = distributor->Uniform(0, M);
            if(rand_y <= our_function->Eval(rand_x)) temp->Fill(rand_x);
        }
        rms_error->SetPoint(j, N, temp->GetRMSError());
        mean_error->SetPoint(j, N, temp->GetMeanError());

        delete temp;
    }

    // rms_error->Draw("AP");
    // rms_error->SetMarkerStyle(1);
    // rms_error->SetMarkerColor(kBlue);
    // rms_error->SetMarkerSize(4);

    mean_error->Draw("AP");
    mean_error->SetMarkerStyle(1);
    mean_error->SetMarkerColor(kBlue);
    mean_error->SetMarkerSize(4);

    return 0; 
}