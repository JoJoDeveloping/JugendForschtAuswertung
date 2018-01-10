#include <iostream>
#include "SensorData.h"
#include "SensorRecoding.h"
#include <fstream>
#include <string>
#include <cstring>


SensorRecoding* read(std::string file)
{
    std::ifstream input(file, std::ios::binary);
    SensorRecoding *sr = new SensorRecoding(input);
    input.close();
    std::cout << "Got "<<sr->data.size()<<" data sets"<<std::endl;
    std::ofstream output(file+".csva");
    output << "sep=:"<<std::fixed<<std::endl;
    output << "time:temp:ax:ay:az:gx:gy:gz:mx:my:mz:flags"<<std::endl;
    for(auto iter = sr->data.begin(); iter != sr->data.end(); ++iter){
        SensorData data = *iter;
        output << data.time << ":";
        output << data.temp << ":";
        output << data.accX << ":";
        output << data.accY << ":";
        output << data.accZ << ":";
        output << data.gyroX << ":";
        output << data.gyroY << ":";
        output << data.gyroZ << ":";
        output << data.magX << ":";
        output << data.magY << ":";
        output << data.magZ << ":";
        if(data.dataOverflow)output << "O";
        if(data.magReady)output << "r";
        if(data.magOverflow)output << "o";
        if(data.magOverload)output << "h";
        output << std::endl;
    }
    output.close();
    return sr;
}

void mkFilename(unsigned int i, char* result){
  strcpy(result, ("JF00000"));
  for(int c = 6; i > 0; i/= 10, c--){
    result[c] = '0'+(i%10);
  }
}

int main(int argc, char* argv[])
{
    std::string fn = "G:\\Schule\\JuFo\\JUFO\\JF00013.BIN";
    SensorRecoding* sr=read(fn);
    std::cout << "Read file "<<fn<<std::endl;

    std::cout << "Abhebeindex?"<<std::endl;
    int index; //7540
    std::cin >> index;
    sr->setLiftoffTime(index);
    sr->streamDataOverFilter();
    auto output = std::ofstream(fn+"-filtered.csv");
    output << "sep=:"<<std::fixed<<std::endl;
    output << "time:temp:wax:way:waz:qw:qx:qy:qz:flags"<<std::endl;
    double vx=0, vy=0, vz=0, sx=0, sy=0, sz=0;
    for(auto iter = sr->data.begin(); iter != sr->data.end(); ++iter){
        SensorData data = *iter;
        if(data.id < index-400) continue;
        output << data.time << ":";
        output << data.temp << ":";
        output << data.waX << ":";
        output << data.waY << ":";
        output << (data.waZ-9.80665) << ":";
        output << data.q.w() << ":";
        output << data.q.x() << ":";
        output << data.q.y() << ":";
        output << data.q.z() << ":";
        if(data.dataOverflow)output << "O";
        if(data.magReady)output << "r";
        if(data.magOverflow)output << "o";
        if(data.magOverload)output << "h";
        output << std::endl;
    }

}
