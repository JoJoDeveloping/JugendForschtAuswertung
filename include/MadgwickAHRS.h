//=====================================================================================================
// MadgwickAHRS.h
//=====================================================================================================
//
// Implementation of Madgwick's IMU and AHRS algorithms.
// See: http://www.x-io.co.uk/node/8#open_source_ahrs_and_imu_algorithms
//
// Date			Author          Notes
// 29/09/2011	SOH Madgwick    Initial release
// 02/10/2011	SOH Madgwick	Optimised for reduced CPU load
//
//=====================================================================================================
#ifndef MadgwickAHRS_h
#define MadgwickAHRS_h
#ifdef __cplusplus
extern "C"
{
#endif
//----------------------------------------------------------------------------------------------------
// Variable declaration

extern volatile double beta;				// algorithm gain
extern volatile double zeta;				// algorithm gain
extern volatile double q0, q1, q2, q3;	// quaternion of sensor frame relative to auxiliary frame
extern volatile double w_bx, w_by, w_bz; // estimate gyroscope biases error
//---------------------------------------------------------------------------------------------------
// Function declarations
void MadgwickAHRSupdate(double gx, double gy, double gz, double ax, double ay, double az, double mx, double my, double mz);
void MadgwickAHRSupdateIMU(double gx, double gy, double gz, double ax, double ay, double az);
void MadgwickAHRSupdateMAG(double gx, double gy, double gz, double mx, double my, double mz);
void setQ(double qq0, double qq1, double qq2, double qq3);

#ifdef __cplusplus
}
#endif

#endif
//=====================================================================================================
// End of file
//=====================================================================================================
