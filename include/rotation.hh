#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>

float xzrot(const std::vector<std::vector<float>>& xz){
    
    float zdist = xz[1][2] - xz[0][2];
    float xdist = xz[1][0] - xz[0][0];
    float rotation = atan(xdist/zdist);
    
    return rotation;
}

float xyrot(const std::vector<std::vector<float>>& xy){
    
    float ydist = xy[2][1] - xy[0][1];
    float xdist = xy[2][0] - xy[0][0];
    float rotation = atan(ydist/xdist);
    
    return rotation;
}
std::vector<float> findcenter(const std::vector<std::vector<float>>& corners){
    float centerx = corners[1][0]+corners[2][0] / 2;
    float centery = corners[1][1]+corners[2][1] /2;
    float centerz = corners[1][2]+corners[2][2] /2;
    std::vector<float> center = {centerx,centery,centerz};
    return center;
}
