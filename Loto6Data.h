#pragma once
#include <Data.h>

struct Loto6;

class Loto6Data :
    public Data
{
    std::string Loto6Url;

public:
    Loto6* Data;

    Loto6Data();
    virtual ~Loto6Data();
    void Load() override;
};

