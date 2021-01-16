#pragma once
#include <Data.h>

class Loto7;

class Loto7Data :
    public Data
{
    std::string Loto7Url;

public:
    Loto7* Data;

    Loto7Data();
    virtual ~Loto7Data();
    void Load() override;
};

