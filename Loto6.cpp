#include "Loto6.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "LayerManager.h"
#include "Loto6Data.h"
#include "TestData.h"
//#include "Adapter.h"

static  double COEF = 0.1;// äwèKó¶ 
LayerManager layerManager;

int main(int argc, char* argv[])
{
    int epoch = 100;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "-e") == 0) {
            ++i;
            if (i < argc) {
                epoch = atoi(argv[i]);
                continue;
            }
            else {
                std::cerr << "Argment error !!" << std::endl;
                return -1;
            }
        }
    }

    // äwèKÉfÅ[É^ÇÃì«Ç›çûÇ› 
    Loto6Data data;
    data.Load();

    layerManager.AddLayer(Loto7::dataKaigou * Loto7::dataNum); // ì¸óÕëw 
    layerManager.AddLayer(400);     // âBÇÍëw 
    layerManager.AddLayer(100);     // âBÇÍëw 
    layerManager.AddLayer(Loto7::dataNum / 2);      // èoóÕëw

    // èdÇ›èâä˙âª 
    layerManager.InitWeight();

    // äwèKÉfÅ[É^ï™ÅAäwèKÇçsÇ§
    std::cout << "Train Data Num : " << data.TrainDataNum << std::endl;
    std::cout << "Epoch Num : " << epoch << std::endl;
    std::ofstream ofs("result6.csv");
    ofs << "epoch,";
    for (int i = 0; i < (Loto7::dataNum / 2); ++i) {
        ofs << (i + 1) << ",";
    }
    ofs << std::endl;


    for (int e = 0; e < epoch; ++e) {
        std::cout << "Epoch : " << std::setw(4) << e << std::endl;
        double totalRatio = 0.0;
        long totalCount = 0;
        for (int i = Loto7::dataKaigou; i < data.TrainDataNum; ++i) {
            double InputData[(Loto7::dataKaigou * Loto7::dataNum)];
            double AnswerData[(Loto7::dataNum)];

            for (int j = 0; j < Loto7::dataKaigou; ++j) {
                int kaigou = i - Loto7::dataKaigou + j;
                for (int k = 0; k < Loto7::dataNum; ++k) {
                    InputData[(j * Loto7::dataNum) + k] =
                        static_cast<double>(data.Data[kaigou].tousen[k]);
                }
            }

            {
                int j = Loto7::dataKaigou;
                int kaigou = i - Loto7::dataKaigou + j;
                for (int k = 0; k < Loto7::dataNum; ++k) {
                    AnswerData[k] =
                        static_cast<double>(data.Data[kaigou].tousen[k]);
                }
            }

            layerManager.CalcOutput(InputData);
            layerManager.CalcError(AnswerData);
            double* softmax = layerManager.SoftMax();
            for (int j = 0; j < (Loto7::dataNum / 2); ++j) {
                // std::cerr << "softmax : " << softmax[j] << "  AnswerData : "<<  AnswerData[j];
                totalRatio += softmax[j] * AnswerData[j];
                // std::cerr << "  totalRatio : " << totalRatio << std::endl;
            }
            std::cout 
                << "\rcount : " << std::setw(4) << i 
                << "   ratio : " << std::fixed << std::setprecision(3) << (100.0 * totalRatio / (double)(++totalCount)) << "%   " << std::flush;

            layerManager.UpdateWeight(COEF);

            //if ((i % 10000) == 0) {
            //    // äwèKåãâ Çï€ë∂Ç∑ÇÈ
            //    layerManager.SaveWeight("weight.csv");
            //}
        }

        {
            int i = data.TrainDataNum;
            double InputData[(Loto7::dataKaigou * Loto7::dataNum)];

            for (int j = 0; j < Loto7::dataKaigou; ++j) {
                int kaigou = i - Loto7::dataKaigou + j;
                for (int k = 0; k < Loto7::dataNum; ++k) {
                    InputData[(j * Loto7::dataNum) + k] =
                        static_cast<double>(data.Data[kaigou].tousen[k]);
                }
            }

            layerManager.CalcOutput(InputData);
            std::cout 
                << "\rcount : " << std::setw(4) << i 
                << "   ratio : " << std::fixed << std::setprecision(3) << (100.0 * totalRatio / (double)totalCount) << "%   " << std::endl;

            ofs << e << ",";
            // std::cerr << e << ",";
            double* softmax = layerManager.SoftMax();
            for (int j = 0; j < (Loto7::dataNum / 2); ++j) {
                ofs << std::fixed << std::setprecision(3) << softmax[j] << ",";
                // std::cerr << std::fixed << std::setprecision(3) << softmax[j] << ",";
            }
            ofs << std::endl;
            // std::cerr << std::endl;
        }
    }

    layerManager.SaveWeight("weight.csv");
    return 0;
}

