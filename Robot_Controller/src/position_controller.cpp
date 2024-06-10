#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>
#include <vector>
#include <Eigen/Dense>

#include "hardware_interface.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*my code*/
    HardwareInterface robot_hw;

    double joint_pos_fbk[6] = {0};
    static int brobot_ok = true;
    int robot_index = 0;
    while(brobot_ok)
    {
        robot_hw.getJointPos(joint_pos_fbk, robot_index);

        usleep(4000);
    }
    
    printf("the code is finished");
    return true;
}