#ifndef SENSORDATA_H
#define SENSORDATA_H

#include "MathUtils.h"
#include <cstdint>


/*FIFO data packet layout (22 bytes):
0:  [Accel X H] [Accel X L]
2:  [Accel Y H] [Accel Y L]
4:  [Accel Z H] [Accel Z L]
6:  [Temp H] [Temp L]
8:  [Gyro X H] [Gyro X L]
10: [Gyro Y H] [Gyro Y L]
12: [Gyro Z H] [Gyro Z L]
14: [Mag Status 1]
15: [Mag X L] [Mag X H]
17: [Mag Y L] [Mag Y H]
19: [Mag Z L] [Mag Z H]
21: [Mag Status 2]
*/


class SensorData
{
    public:
        SensorData(uint8_t *data, int iteration);
        virtual ~SensorData();

    double time, temp, accX, accY, accZ, gyroX, gyroY, gyroZ, magX, magY, magZ;
    bool magReady, magOverload, magOverflow, dataOverflow;
    int id;

    double waX, waY, waZ;
    Quaternion q;

    protected:

    private:
};

#endif // SENSORDATA_H
