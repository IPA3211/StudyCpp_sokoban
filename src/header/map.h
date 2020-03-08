#pragma once

#include "transform.h"

typedef int** data;

class map
{
private:
    data map_data = nullptr;
    transform map_size;
public:
    map();
    map(const transform &_ms);

    void freeMapData();

    void resizeMap(const transform &_ms);

    void swap(const transform &index, const transform &index2);

    ~map();
};