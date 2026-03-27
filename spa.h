#ifndef NREL_SPA_SPA_H_
#define NREL_SPA_SPA_H_

#include <cmath>

namespace nrel_spa {

/**
 * @brief Input parameters for the NREL Solar Position Algorithm (SPA).
 * Based on NREL/TP-560-34302 (Revised January 2008).
 */
struct SpaInput {
  int year;           ///< Year: -2000 to 6000
  int month;          ///< Month: 1 to 12
  int day;            ///< Day: 1 to 31
  int hour;           ///< Hour: 0 to 24
  int minute;         ///< Minute: 0 to 59
  double second;      ///< Second: 0 to 59.999
  double timezone;    ///< Timezone: -18 to 18 hours (negative for West)
  double delta_t;     ///< Difference between Earth rotation and atomic time (sec)
  double longitude;   ///< Longitude: -180 to 180 degrees (positive for East)
  double latitude;    ///< Latitude: -90 to 90 degrees (positive for North)
  double elevation;   ///< Elevation above mean sea level (meters)
  double pressure;    ///< Annual average local pressure (millibars)
  double temperature; ///< Annual average local temperature (Celsius)
  double slope;       ///< Surface slope (degrees from horizontal)
  double azm_rotation; ///< Surface azimuth rotation (degrees from South, positive Eastward)
  double atmos_refract; ///< Atmospheric refraction at sunrise/sunset (degrees)
};

/**
 * @brief Output results from the NREL Solar Position Algorithm (SPA).
 */
struct SpaOutput {
  double zenith;           ///< Topocentric zenith angle (degrees)
  double azimuth;          ///< Topocentric azimuth angle (Eastward from North, 0 to 360)
  double incidence;        ///< Surface incidence angle (degrees)
  double sunrise;          ///< Sunrise time (fractional hours local time)
  double sunset;           ///< Sunset time (fractional hours local time)
  double sun_transit;      ///< Sun transit time (fractional hours local time)
  double julian_day;       ///< Julian Day
};

/**
 * @brief Calculator for high-precision solar position.
 */
class SolarPositionCalculator {
 public:
  /**
   * @brief Calculate solar position based on SPA algorithm.
   * @param input Input parameters including time and location.
   * @return Calculated solar positions and related event times.
   */
  static SpaOutput Calculate(const SpaInput& input);

 private:
  // Internal mathematical steps (to be implemented in spa.cc)
  static double CalculateJulianDay(const SpaInput& input);
  // ... and other steps from the plan
};

} // namespace nrel_spa

#endif  // NREL_SPA_SPA_H_
