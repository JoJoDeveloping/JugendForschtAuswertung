#ifndef MATHUTILS_H
#define MATHUTILS_H
#include <math.h>
#include <iostream>
class Quaternion
{
public:
    Quaternion(double w, double x, double y, double z);
    Quaternion(double x, double y, double z);
    Quaternion(Quaternion const& other);
    Quaternion();
    ~Quaternion() = default;

    double w();
    double w() const;
    double x();
    double x() const;
    double y();
    double y() const;
    double z();
    double z() const;
    void print()
    {
        std::cout << mw << " " << mx << " " << my << " " << mz << std::endl;
    }

    Quaternion hamiltonBy(Quaternion const&) const;

    Quaternion conjugate() const;

private:
    double mw,mx,my,mz;
};

#endif // MATHUTILS_H
