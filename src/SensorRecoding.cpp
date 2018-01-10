#include "SensorRecoding.h"
#include <string>
#include "MadgwickAHRS.h"
#include "MathUtils.h"
#include <thread>
#include <unistd.h>
SensorRecoding::SensorRecoding(std::istream &in)
{
    uint8_t dataa[22];
    int i = 0;
    while(in.good()){
        in.read(dataa, 22);
        if(in.gcount() != 22){
            if(in.gcount() != 0) std::cout << "Error at dataset "<<i<<", only read "<<in.gcount()<<" bytes instead of 22"<<std::endl;
            break;
        }
        //std::cout << base64_encode(data, 22)<<std::endl;
        SensorData sd = SensorData(dataa, i++);
        this->data.push_back(sd);
        if(i%1000==0)
            std::cout << "Got "<<i<<std::endl;
    }
}

SensorRecoding::~SensorRecoding()
{
    //dtor
}

void SensorRecoding::setLiftoffTime(int i)
{
    this->liftoffTime = i;
        std::cout << this->data.size() << std::endl;
}

#define NUM_THREADS 1
static double pi180 = 0.01745329251994329576924d;

volatile int progress[NUM_THREADS];

void streamDatapointsThread(SensorRecoding* thiz, int init)
{
    for(int i = init; i < thiz->data.size(); i+=NUM_THREADS)
    {
        thiz->streamDatapointOverFilter(i);
        progress[init]++;
    }
}

void SensorRecoding::streamDataOverFilter()
{
    std::thread thread[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; i++)
    {
        progress[i]=0;
        thread[i] = std::thread(streamDatapointsThread, this, i);
    }
    for(int total = 0; total < this->data.size();)
    {
        total = progress[0];
        for(int i = 1; i < NUM_THREADS; i++)
        {
            total += progress[i];
        }
        std::cout << "At "<<total<<std::endl;
        //usleep(500);
    }
    for(int i = 0; i < NUM_THREADS; i++)
    {
        thread[i].join();
    }
}

double aq0, aq1, aq2, aq3;
void setQ(double qq0, double qq1, double qq2, double qq3)
{
    aq0=qq0;
    aq1=qq1;
    aq2=qq2;
    aq3=qq3;
}

void SensorRecoding::streamDatapointOverFilter(int i)
{
    SensorData& sd = this->data[i];
    if(i < this->liftoffTime)
    {
        MadgwickAHRSupdate(sd.gyroX*pi180, sd.gyroY*pi180, sd.gyroZ*pi180, sd.accX, sd.accY, sd.accZ, sd.magY, sd.magX, sd.magZ);
        //MadgwickAHRSupdateIMU(sd.gyroX*pi180, sd.gyroY*pi180, sd.gyroZ*pi180, sd.accX, sd.accY, sd.accZ);
    }
    else
    {
        MadgwickAHRSupdateMAG(sd.gyroX*pi180, sd.gyroY*pi180, sd.gyroZ*pi180, sd.magY, sd.magX, sd.magZ);
    }
    sd.q = Quaternion(aq0, aq1, aq2, aq3); //values from MadgwickAHRS
    Quaternion accel = Quaternion(sd.accX, sd.accY, sd.accZ);
    accel = sd.q.hamiltonBy(accel).hamiltonBy(sd.q.conjugate());
    sd.waX = accel.x();
    sd.waY = accel.y();
    sd.waZ = accel.z();
    this->data[i]=sd;
}
