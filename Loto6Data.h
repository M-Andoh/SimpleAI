#pragma once
#include <Data.h>

struct Loto7;

class Loto6Data :
    public Data
{
    std::string Loto6Url;

public:
    Loto7* Data;

    Loto6Data();
    virtual ~Loto6Data();
    void Load() override;
};

