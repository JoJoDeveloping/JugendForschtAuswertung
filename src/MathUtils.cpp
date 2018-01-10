#include "MathUtils.h"

Quaternion::Quaternion(double ww, double xx, double yy, double zz) : mw(ww), mx(xx), my(yy), mz(zz) {}
Quaternion::Quaternion(double xx, double yy, double zz) : mw(0.), mx(xx), my(yy), mz(zz) {}
Quaternion::Quaternion(Quaternion const& other) = default;
Quaternion::Quaternion() : mw(0), mx(0), my(0), mz(0) {}

double Quaternion::w()
{
    return this->mw;
}

double Quaternion::w() const
{
    return this->mw;
}

double Quaternion::x()
{
    return this->mx;
}

double Quaternion::x() const
{
    return this->mx;
}

double Quaternion::y()
{
    return this->my;
}

double Quaternion::y() const
{
    return this->my;
}

double Quaternion::z()
{
    return this->mz;
}

double Quaternion::z() const
{
    return this->mz;
}

Quaternion Quaternion::hamiltonBy(Quaternion const& b) const
{
    Quaternion a = *this;
    Quaternion result = a;
    result.mw = a.w()*b.w() - a.x()*b.x() - a.y()*b.y() - a.z()*b.z();
    result.mx = a.w()*b.x() + a.x()*b.w() + a.y()*b.z() - a.z()*b.y();
    result.my = a.w()*b.y() - a.x()*b.z() + a.y()*b.w() + a.z()*b.x();
    result.mz = a.w()*b.z() + a.x()*b.y() - a.y()*b.x() + a.z()*b.w();
    return result;
}

Quaternion Quaternion::conjugate() const
{
    return Quaternion(this->mw, -this->mx, -this->my, -this->mz);
}
