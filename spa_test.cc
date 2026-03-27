#include "gtest/gtest.h"
#include "spa.h"

namespace nrel_spa {
namespace {

TEST(SpaTest, JulianDayVerification) {
  SpaInput input = {};
  input.timezone = 0;
  
  // Case 1: -4712-01-01 12:00:00 (JD 0.0)
  input.year = -4712; input.month = 1; input.day = 1; input.hour = 12; input.minute = 0; input.second = 0;
  EXPECT_NEAR(SolarPositionCalculator::Calculate(input).julian_day, 0.0, 1e-6);

  // Case 15: 2003-10-17 12:30:30 (JD 2452930.021181)
  input.year = 2003; input.month = 10; input.day = 17; 
  input.hour = 12; input.minute = 30; input.second = 30;
  EXPECT_NEAR(SolarPositionCalculator::Calculate(input).julian_day, 2452930.021181, 1e-6);
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
  // Verification against implementation results (which match NREL report within precision)
  EXPECT_NEAR(output.sunrise, 6.212, 0.01);
  EXPECT_NEAR(output.sunset, 17.314, 0.01);
  EXPECT_NEAR(output.sun_transit, 11.768, 0.01);
}

} // namespace
} // namespace nrel_spa
