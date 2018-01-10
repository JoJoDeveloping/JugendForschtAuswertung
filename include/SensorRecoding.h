#ifndef SENSORRECODING_H
#define SENSORRECODING_H
#include <vector>
#include <iostream>
#include <fstream>
#include "SensorData.h"

class SensorRecoding
{
    public:
        SensorRecoding(std::istream &in);
        virtual ~SensorRecoding();

        void streamDataOverFilter();
        void streamDatapointOverFilter(int datapoint);
        void setLiftoffTime(int index);

        std::vector<SensorData> data;
        int liftoffTime;

    protected:

    private:
};

#endif // SENSORRECODING_H
