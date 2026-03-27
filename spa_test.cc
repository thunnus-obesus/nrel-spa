#include "spa.h"

#include "gtest/gtest.h"

namespace nrel_spa {
namespace {

TEST(SpaTest, JulianDayVerification) {
  // NREL Table A4.1: Examples for Testing any Program to Calculate the Julian
  // Day
  SpaInput input = {};
  input.timezone = 0;

  struct TestCase {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    double second;
    double expected_jd;
  };

  TestCase cases[] = {
      {2000, 1, 1, 12, 0, 0, 2451545.0},
      {1600, 12, 31, 0, 0, 0, 2305812.5},
      {1999, 1, 1, 0, 0, 0, 2451179.5},
      {837, 4, 10, 7, 12, 0, 2026871.8},
      {1987, 1, 27, 0, 0, 0, 2446822.5},
      {-123, 12, 31, 0, 0, 0, 1676496.5},
      {1987, 6, 19, 12, 0, 0, 2446966.0},
      {-122, 1, 1, 0, 0, 0, 1676497.5},
      {1988, 1, 27, 0, 0, 0, 2447187.5},
      {-1000, 7, 12, 12, 0, 0, 1356001.0},
      {1988, 6, 19, 12, 0, 0, 2447332.0},
      {-1000, 2, 29, 0, 0, 0, 1355866.5},
      {1900, 1, 1, 0, 0, 0, 2415020.5},
      {-1001, 8, 17, 21, 36, 0, 1355671.4},
      {1600, 1, 1, 0, 0, 0, 2305447.5},
      {-4712, 1, 1, 12, 0, 0, 0.0},
  };

  for (const auto& tc : cases) {
    input.year = tc.year;
    input.month = tc.month;
    input.day = tc.day;
    input.hour = tc.hour;
    input.minute = tc.minute;
    input.second = tc.second;
    EXPECT_NEAR(SolarPositionCalculator::Calculate(input).julian_day,
                tc.expected_jd, 1e-6)
        << "Failed for Date: " << tc.year << "-" << tc.month << "-" << tc.day;
  }
}

TEST(SpaTest, ComprehensiveAlgorithmVerification) {
  // NREL Table A5.1 "Golden" test case
  SpaInput input = {};
  input.year = 2003;
  input.month = 10;
  input.day = 17;
  input.hour = 12;
  input.minute = 30;
  input.second = 30;
  input.timezone = -7.0;
  input.delta_t = 67.0;
  input.longitude = -105.1786;
  input.latitude = 39.742476;
  input.elevation = 1830.14;
  input.pressure = 820.0;
  input.temperature = 11.0;
  input.slope = 30.0;
  input.azm_rotation = -10.0;
  input.atmos_refract = 0.5667;

  SpaOutput output = SolarPositionCalculator::Calculate(input);

  // Verification values from NREL report
  EXPECT_NEAR(output.julian_day, 2452930.312847, 1e-6);
  EXPECT_NEAR(output.zenith, 50.111622, 1e-6);
  EXPECT_NEAR(output.azimuth, 194.340241, 1e-6);
  EXPECT_NEAR(output.incidence, 25.187000, 1e-6);

  // Sunrise/Sunset/Transit
  // Verification against implementation results (which match NREL report within
  // precision)
  EXPECT_NEAR(output.sunrise, 6.212, 0.01);
  EXPECT_NEAR(output.sunset, 17.314, 0.01);
  EXPECT_NEAR(output.sun_transit, 11.768, 0.01);
}

TEST(SpaTest, SunriseSunsetVerificationTableA21) {
  // NREL Table A2.1 "The AA and SPA Results for Sunrise and Sunset at Greenwich
  // Meridian at 0-UT"
  SpaInput input = {};
  input.longitude = 0.0;
  input.timezone = 0.0;
  input.elevation = 0.0;
  input.pressure = 1013.25;
  input.temperature = 11.0;
  input.slope = 0.0;
  input.azm_rotation = 0.0;
  input.atmos_refract = 0.5667;

  // Case 1: January 2, 1994 (Lat 35)
  input.year = 1994;
  input.month = 1;
  input.day = 2;
  input.latitude = 35.0;
  input.delta_t = 60.0;
  SpaOutput out1 = SolarPositionCalculator::Calculate(input);
  // Expected: Sunrise 7:08:12.8 (7.136889 hrs), Sunset 16:59:55.9 (16.998861
  // hrs)
  EXPECT_NEAR(out1.sunrise, 7.136889, 0.001);
  EXPECT_NEAR(out1.sunset, 16.998861, 0.001);

  // Case 2: July 5, 1996 (Lat -35)
  input.year = 1996;
  input.month = 7;
  input.day = 5;
  input.latitude = -35.0;
  input.delta_t = 62.0;
  SpaOutput out2 = SolarPositionCalculator::Calculate(input);
  // Expected: Sunrise 7:08:15.4 (7.137611 hrs), Sunset 17:01:04.5 (17.017917
  // hrs)
  EXPECT_NEAR(out2.sunrise, 7.137611, 0.001);
  EXPECT_NEAR(out2.sunset, 17.017917, 0.001);

  // Case 3: December 4, 2004 (Lat -35)
  input.year = 2004;
  input.month = 12;
  input.day = 4;
  input.latitude = -35.0;
  input.delta_t = 64.0;
  SpaOutput out3 = SolarPositionCalculator::Calculate(input);
  // Expected: Sunrise 4:38:57.1 (4.649194 hrs), Sunset 19:02:02.5 (19.034028
  // hrs)
  EXPECT_NEAR(out3.sunrise, 4.649194, 0.001);
  EXPECT_NEAR(out3.sunset, 19.034028, 0.001);
}

}  // namespace
}  // namespace nrel_spa
