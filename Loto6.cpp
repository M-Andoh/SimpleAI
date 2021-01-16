#include "Loto6.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "LayerManager.h"
#include "Loto6Data.h"
#include "TestData.h"
//#include "Adapter.h"

static  double COEF = 0.1;// ŠwK—¦ 
LayerManager layerManager;

int main(int argc, char* argv[])
{
    // ŠwKƒf[ƒ^‚Ì“Ç‚İ‚İ 
    Loto6Data data;
    data.Load();

    layerManager.AddLayer(Loto6::dataKaigou * Loto6::dataNum); // “ü—Í‘w 
    layerManager.AddLayer(400);     // ‰B‚ê‘w 
    layerManager.AddLayer(100);     // ‰B‚ê‘w 
    layerManager.AddLayer(Loto6::dataNum / 2);      // o—Í‘w

    // d‚İ‰Šú‰» 
    layerManager.InitWeight();

    // ŠwKƒf[ƒ^•ªAŠwK‚ğs‚¤
    std::cout << "Train Data Num : " << data.TrainDataNum << std::endl;
    std::ofstream ofs("result.csv");
    ofs << "epoch,";
    for (int i = 0; i < (Loto6::dataNum / 2); ++i) {
        ofs << (i + 1) << ",";
    }
    ofs << std::endl;


    for (int epoch = 0; epoch < 100; ++epoch) {
        std::cout << "Epoch : " << std::setw(4) << epoch << std::endl;
        double totalRatio = 0.0;
        long totalCount = 0;
        for (int i = Loto6::dataKaigou; i < data.TrainDataNum; ++i) {
            double InputData[(Loto6::dataKaigou * Loto6::dataNum)];
            double AnswerData[(Loto6::dataNum)];

            for (int j = 0; j < Loto6::dataKaigou; ++j) {
                int kaigou = i - Loto6::dataKaigou + j;
                for (int k = 0; k < Loto6::dataNum; ++k) {
                    InputData[(j * Loto6::dataNum) + k] =
                        static_cast<double>(data.Data[kaigou].tousen[k]);
                }
            }

            {
                int j = Loto6::dataKaigou;
                int kaigou = i - Loto6::dataKaigou + j;
                for (int k = 0; k < Loto6::dataNum; ++k) {
                    AnswerData[k] =
                        static_cast<double>(data.Data[kaigou].tousen[k]);
                }
            }

            layerManager.CalcOutput(InputData);
            layerManager.CalcError(AnswerData);
            double* softmax = layerManager.SoftMax();
            for (int j = 0; j < (Loto6::dataNum / 2); ++j) {
                // std::cerr << "softmax : " << softmax[j] << "  AnswerData : "<<  AnswerData[j];
                totalRatio += softmax[j] * AnswerData[j];
                // std::cerr << "  totalRatio : " << totalRatio << std::endl;
            }
            std::cout 
                << "\rcount : " << std::setw(4) << i 
                << "   ratio : " << std::fixed << std::setprecision(3) << (100.0 * totalRatio / (double)(++totalCount)) << "%" << std::flush;

            layerManager.UpdateWeight(COEF);

            //if ((i % 10000) == 0) {
            //    // ŠwKŒ‹‰Ê‚ğ•Û‘¶‚·‚é
            //    layerManager.SaveWeight("weight.csv");
            //}
        }

        {
            int i = data.TrainDataNum;
            double InputData[(Loto6::dataKaigou * Loto6::dataNum)];

            for (int j = 0; j < Loto6::dataKaigou; ++j) {
                int kaigou = i - Loto6::dataKaigou + j;
                for (int k = 0; k < Loto6::dataNum; ++k) {
                    InputData[(j * Loto6::dataNum) + k] =
                        static_cast<double>(data.Data[kaigou].tousen[k]);
                }
            }

            layerManager.CalcOutput(InputData);
            std::cout 
                << "\rcount : " << std::setw(4) << i 
                << "   ratio : " << std::fixed << std::setprecision(3) << (100.0 * totalRatio / (double)totalCount) << "%" << std::endl;

            ofs << epoch;
            double* softmax = layerManager.SoftMax();
            for (int j = 0; j < (Loto6::dataNum / 2); ++j) {
                ofs << std::fixed << std::setprecision(3) << softmax[j] << ",";
            }
            ofs << std::endl;
        }
    }

    layerManager.SaveWeight("weight.csv");
    return 0;
}

