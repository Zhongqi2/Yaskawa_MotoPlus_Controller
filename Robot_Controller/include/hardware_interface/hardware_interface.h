#ifndef __HARDWARE_INTERFACE_H_
#define __HARDWARE_INTERFACE_H_

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <vector>

#include "udp_Interface.h"
#include "robot_var.h"

using namespace std;

class HardwareInterface{
	public:
		HardwareInterface();
		~HardwareInterface();

		bool getJointPos(double* joint_pos, const int robot_index);
		bool setJointPosCmd(const double* joint_pos_des, const int robot_index);
	
		udp::UDP_Interface::Ptr udp_get_robot_a;
		udp::UDP_Interface::Ptr udp_send_robot_a;
		udp::UDP_Interface::Ptr udp_get_robot_b;
		udp::UDP_Interface::Ptr udp_send_robot_b;

	private:
		unsigned int actuator_count;
		const char* robot_name;
		double motor_pos_precision;
		double motor_spd_precision;
		double motor_trq_fbk_precision;
		double motor_trq_cmd_precision;
		double motor_abs_zero[JOINT_NUM];
		double trq_static_offset[JOINT_NUM]; //define torque sensor static offset
		double trq_dym_offset[JOINT_NUM];
		double joint_range[JOINT_NUM];
		double joint_max_spd[JOINT_NUM];
		double joint_max_trq[JOINT_NUM];
		
		int motor_dir[JOINT_NUM];   		//define transform from motor coordinate to joint coordinate
		int axis_enable[JOINT_NUM];
		int first_enter[JOINT_NUM];

};

#endif
