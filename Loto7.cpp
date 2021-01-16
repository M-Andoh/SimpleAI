#include "Loto7.h"
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "LayerManager.h"
#include "Loto7Data.h"
#include "TestData.h"
//#include "Adapter.h"

static  double COEF = 0.1;// �w�K�� 
LayerManager layerManager;

int main(int argc, char* argv[])
{
    // �w�K�f�[�^�̓ǂݍ��� 
    Loto7Data data;
    data.Load();

    layerManager.AddLayer(Loto7::dataKaigou * Loto7::dataNum); // ���͑w 
    layerManager.AddLayer(400);     // �B��w 
    layerManager.AddLayer(100);     // �B��w 
    layerManager.AddLayer(Loto7::dataNum / 2);      // �o�͑w

    // �d�ݏ����� 
    layerManager.InitWeight();

    // �w�K�f�[�^���A�w�K���s��
    std::cout << "Train Data Num : " << data.TrainDataNum << std::endl;
    std::ofstream ofs("result7.csv");
    ofs << "epoch,";
    for (int i = 0; i < (Loto7::dataNum / 2); ++i) {
        ofs << (i + 1) << ",";
    }
    ofs << std::endl;


    for (int epoch = 0; epoch < 100; ++epoch) {
        std::cout << "Epoch : " << std::setw(4) << epoch << std::endl;
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
                << "   ratio : " << std::fixed << std::setprecision(3) << (100.0 * totalRatio / (double)(++totalCount)) << "%" << std::flush;

            layerManager.UpdateWeight(COEF);

            //if ((i % 10000) == 0) {
            //    // �w�K���ʂ�ۑ�����
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
                << "   ratio : " << std::fixed << std::setprecision(3) << (100.0 * totalRatio / (double)totalCount) << "%" << std::endl;

            ofs << epoch << ",";
            // std::cerr << epoch << ",";
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
