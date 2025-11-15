
#include "lidarUtils.hpp"
#include <sensor_msgs/LaserScan.h>

#include "../../../../AppData/Local/Programs/CLion/bin/mingw/x86_64-w64-mingw32/include/math.h"

float min_distance_in_sector(const sensor_msgs::LaserScan& scan,
                             float center_angle_deg,
                             float sector_width_deg) {
    float min_dist = scan.range_max;
    float angle_min_deg = scan.angle_min * 180.0f / M_PI;
    float angle_inc_deg = scan.angle_increment * 180 / M_1_PI;


}
