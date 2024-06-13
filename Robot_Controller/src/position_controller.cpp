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
    int robot_index_a = 0;
    int robot_index_b = 1;
    double joint_pos_cmd[6] = {0};
    int flange[6] = {0};
    joint_pos_cmd[4] = -1.57;
    while(brobot_ok)
    {
        robot_hw.getJointPos(joint_pos_fbk, robot_index_a);
        robot_hw.getJointPos(joint_pos_fbk, robot_index_b);
        if (flange[0] == 0)
        {
            joint_pos_cmd[0] = joint_pos_cmd[0] + 0.002;
        }
        else if(flange[0] == 1)
        {
            joint_pos_cmd[0] = joint_pos_cmd[0] - 0.002;
        }

        if (joint_pos_cmd[0] >= 0.57)
        {
            flange[0] = 1;
        }
        else if (joint_pos_cmd[0] <= -0.57)
        {
            flange[0] = 0;
        }

        // for (int i =0; i<6; i++)
        // {
        //     if (flange[i] == 0)
        //     {
        //         joint_pos_cmd[i] = joint_pos_cmd[i] + 0.002;
        //     }
        //     else if(flange[i] == 1)
        //     {
        //         joint_pos_cmd[i] = joint_pos_cmd[i] - 0.002;
        //     }

        //     if (joint_pos_cmd[i] >= 0.57)
        //     {
        //         flange[i] = 1;
        //     }
        //     else if (joint_pos_cmd[i] <= -0.57)
        //     {
        //         flange[i] = 0;
        //     }
        // }
        robot_hw.setJointPosCmd(joint_pos_cmd, robot_index_a);
        robot_hw.setJointPosCmd(joint_pos_cmd, robot_index_b);

        usleep(4000);
    }
    
    printf("the code is finished");
    return true;
}