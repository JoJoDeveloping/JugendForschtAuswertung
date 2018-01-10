#include "SensorData.h"

int ASAX = 175;
int ASAY = 176;
int ASAZ = 164;
inline int16_t mkshort(uint8_t high, uint8_t low)
{
    int16_t result = high;
    result = result << 8;
    result |= low;
    return result;
}

SensorData::SensorData(uint8_t *data, int iteration)
{
    id=iteration;
    time = iteration / 200.; //200 Hz
    temp = mkshort(data[6], data[7])/333.87 + 21.;
    accX = mkshort(data[0], data[1]) / 2048. * 9.80665; //2048 LSB/g, times g=9.80665 m/s²
    accY = mkshort(data[2], data[3]) / 2048. * 9.80665; //Y points towards Z
    accZ = mkshort(data[4], data[5]) / 2048. * 9.80665; //Z points towards -Y
    gyroX = mkshort(data[8], data[9]) / 16.4; //16.4 LSB/(°/s)
    gyroY = mkshort(data[10], data[11]) / 16.4;
    gyroZ = mkshort(data[12], data[13]) / 16.4;
    magReady = data[14] & 1;
    magOverflow = data[14] & 2;
    magOverload = data[21] & 8;
    magX = mkshort(data[16], data[15]) * 4192. / 32760. * (ASAX / 256. + 0.5);
    magY = mkshort(data[18], data[17]) * 4192. / 32760. * (ASAY / 256. + 0.5);
    magZ = mkshort(data[20], data[19]) * 4192. / 32760. * (ASAZ / 256. + 0.5);
    dataOverflow = data[21]==255; //marker for overflow
}

SensorData::~SensorData()
{
    //dtor
}
