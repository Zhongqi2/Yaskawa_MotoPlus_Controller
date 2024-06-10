#include <iostream>
#include <stdlib.h>

#include "robot_var.h"
#include "hardware_interface.h"

#define POS_CMD_PORT_ROBOT_A        11000
#define POS_STATE_PORT_ROBOT_A        11001 //port open for c++	

#define POS_CMD_PORT_ROBOT_B        11002
#define POS_STATE_PORT_ROBOT_B        11003 //port open for c++	

HardwareInterface::HardwareInterface()
{
	udp_send_robot_a = std::make_shared<udp::UDP_Interface>();
	udp_send_robot_a->ClientSetup(POS_CMD_PORT_ROBOT_A);

	udp_get_robot_a = std::make_shared<udp::UDP_Interface>();
	udp_get_robot_a->ServerSetup(POS_STATE_PORT_ROBOT_A);

	udp_send_robot_b = std::make_shared<udp::UDP_Interface>();
	udp_send_robot_b->ClientSetup(POS_CMD_PORT_ROBOT_B);

	udp_get_robot_b = std::make_shared<udp::UDP_Interface>();
	udp_get_robot_b->ServerSetup(POS_STATE_PORT_ROBOT_B);
}

HardwareInterface::~HardwareInterface()
{
	cout << "HardwareInterface is being deleted" << endl;
}

bool HardwareInterface::getJointPos(double *joint_pos, const int robot_index)
{
	float joint_pos_raw[6] = {0};
	if (robot_index == ROBOT_A)
	{
		udp_get_robot_a->GetJointPos(joint_pos_raw);
	}
	else if (robot_index == ROBOT_B)
	{
		udp_get_robot_b->GetJointPos(joint_pos_raw);
	}
	
	for (int i = 0; i < 6; i++)
	{
		joint_pos[i] = (double)joint_pos_raw[i];
	}
	// cout << "joint_pos:" << joint_pos[0] << " " << joint_pos[1] << " " << joint_pos[2] << " " << joint_pos[3] << " " << joint_pos[4] << " " << joint_pos[5] << endl;
	return true;
}

bool HardwareInterface::setJointPosCmd(const double *joint_pos_des, const int robot_index)
{
	float joint_pos[6] = {0};

	for (int i = 0; i < JOINT_NUM; i++)
	{
		joint_pos[i] = (float)joint_pos_des[i];
	}
	if (robot_index == ROBOT_A)
	{
		udp_send_robot_a->SendJointPos(joint_pos);
	}
	else if (robot_index == ROBOT_B)
	{
		udp_send_robot_b->SendJointPos(joint_pos);
	}
	
	return true;
}