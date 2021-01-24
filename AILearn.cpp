#include <cstdio>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "LayerManager.h"
#include "TrainData.h"
#include "TestData.h"
#include "Sigmoid.h"
#include "ReLU.h"
//#include "Adapter.h"

static  double COEF = 0.1;// 学習率 
LayerManager layerManager;
double Test(int testNum, TrainData& data);

int main(int argc,char* argv[])
{
    // 学習データの読み込み 
    TrainData data;
    data.Load();

    layerManager.AddLayer(28 * 28,&sigmoid); // 入力層 
    layerManager.AddLayer(400, &sigmoid);     // 隠れ層 
    layerManager.AddLayer(100, &sigmoid);     // 隠れ層 
    layerManager.AddLayer(10, &sigmoid);      // 出力層

    // 重み初期化 
    layerManager.InitWeight();
 
    // 学習データ分、学習を行う
    std::cout << "Train Data Num : " << data.TrainDataNum << std::endl;
    for (int epoch = 0; epoch < 1; ++epoch) {
        std::cout << "Epoch : " << epoch << std::endl;
        for (int i = 0; i < data.TrainDataNum; i++) {
            layerManager.CalcOutput(data.Images[i]);
            layerManager.CalcError(data.Answers[i]);
            layerManager.UpdateWeight(COEF);

                // 100回毎に精度をチェックしてグラフ表示
            if ((i % 100) == 0) {
                double score = Test(100, data);
                std::cout
                    << "Epoch : " << std::setw(3) << epoch
                    << "   Count : " << std::setw(6) << i
                    << "   Ratio : " << std::setw(7) << std::fixed << std::setprecision(3) << (score * 100) << "%"
                    << std::endl;
            }
            if ((i % 10000) == 0) {
                // 学習結果を保存する
                layerManager.SaveWeight("weight.csv");
            }
        }
    }

    // 最終的な精度をチェック 
    double last_score = Test(100, data);
    last_score *= 100;
    std::cout << std::fixed << std::setprecision(3)  << last_score << "%"<< std::endl;
    // 学習結果を保存する
    layerManager.SaveWeight("weight.csv");
    return 0;
}

// 精度をチェックする
double Test(int testNum, TrainData& data) {
    int correctCnt = 0; // 正解数 
    for (int i = 0; i < testNum; i++) {
        layerManager.CalcOutput(data.Images[data.TrainDataNum + i]);
        //std::cerr << "Max : " << layerManager.GetMaxIndex() << "   Label : " << (size_t)data.AnsNumber[data.TrainDataNum + i] << std::endl;
        if (layerManager.GetMaxIndex() == (size_t)data.AnsNumber[data.TrainDataNum + i]) {
                correctCnt++;
        }
    }
    return ((double)correctCnt / (double)testNum);
}


