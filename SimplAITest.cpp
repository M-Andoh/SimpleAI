#include <cstdio>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "LayerManager.h"
#include "TrainData.h"
#include "TestData.h"

LayerManager layerManager;
double Test(int testNum, TrainData& data);

int main(int argc,char* argv[])
{
    // テストデータの読み込み 
    TestData data;
    data.Load();

    // 学習結果を復元する
    std::cout << realpath("weight.csv", NULL) << std::endl;
    layerManager.LoadWeight("weight.csv");

    // 精度をチェック 
    int correctCnt = 0; // 正解数 
    for (int i = 0; i < data.TestDataNum; ++i) {
        layerManager.CalcOutput(data.Images[i]);
        if (layerManager.GetMaxIndex() == (size_t)data.AnsNumber[i]) {
            correctCnt++;
        }
        if (i % 100 == 0) {
            std::cerr 
                << "Count : " << i 
                << "   Correct : " << correctCnt 
                << "   Ratio : " << (100.0 * correctCnt / i) << "%"
                << std::endl;
        }
    }

    std::cout << (100.0 * correctCnt / data.TestDataNum) << "%" << std::endl;
    return 0;
}


