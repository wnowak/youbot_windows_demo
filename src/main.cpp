// Copyright (c) 2014 Locomotec
//

#include "youbot_driver/youbot/YouBotBase.hpp"
#include "youbot_driver/youbot/YouBotManipulator.hpp"

using namespace youbot;

int main() {

	// configuration flags for different system configuration (e.g. base without arm)
	bool youBotHasBase = false;
	bool youBotHasArm = false;

	// define velocities
	double vLinear = 0.05; //meter_per_second
	double vRotate = 0.2; //radian_per_second

	// create handles for youBot base and manipulator (if available)
	YouBotBase* myYouBotBase = 0;
	YouBotManipulator* myYouBotManipulator = 0;

	try {
		myYouBotBase = new YouBotBase("youbot-base", YOUBOT_CONFIGURATIONS_DIR);
		myYouBotBase->doJointCommutation();

		youBotHasBase = true;
	} catch (std::exception& e) {
		LOG(warning) << e.what();
		youBotHasBase = false;
	}

	try {
		myYouBotManipulator = new YouBotManipulator("youbot-manipulator", YOUBOT_CONFIGURATIONS_DIR);
		myYouBotManipulator->doJointCommutation();
		myYouBotManipulator->calibrateManipulator();

		youBotHasArm = true;
	} catch (std::exception& e) {
		LOG(warning) << e.what();
		youBotHasArm = false;
	}

	try {
		/*
		 * Simple sequence of commands to the youBot:
		 */

		if (youBotHasBase) {
			// Variable for the base.
			// Here "boost units" is used to set values, that means you have to set a value and a unit.
			quantity<si::velocity> vx = 0 * meter_per_second;
			quantity<si::velocity> vy = 0 * meter_per_second;
			quantity<si::angular_velocity> va = 0 * radian_per_second;

			// forward
			vx = vLinear * meter_per_second;
			vy = 0 * meter_per_second;
			myYouBotBase->setBaseVelocity(vx, vy, va);
			LOG(info) << "drive forward";
			SLEEP_MILLISEC(2000);

			// backwards
			vx = -vLinear * meter_per_second;
			vy = 0 * meter_per_second;
			myYouBotBase->setBaseVelocity(vx, vy, va);
			LOG(info) << "drive backwards";
			SLEEP_MILLISEC(2000);

			// left
			vx = 0 * meter_per_second;
			vy = vLinear * meter_per_second;
			myYouBotBase->setBaseVelocity(vx, vy, va);
			LOG(info) << "drive left";
			SLEEP_MILLISEC(2000);

			// right 
			vx = 0 * meter_per_second;
			vy = -vLinear * meter_per_second;
			myYouBotBase->setBaseVelocity(vx, vy, va);
			LOG(info) << "drive right";
			SLEEP_MILLISEC(2000);

			// stop base 
			vx = 0 * meter_per_second;
			vy = 0 * meter_per_second;
			va = 0 * radian_per_second;
			myYouBotBase->setBaseVelocity(vx, vy, va);
			LOG(info) << "stop base";
		}

		if (youBotHasArm) {
			// Target position for one arm joint
			JointAngleSetpoint desiredJointAngle;

			// unfold arm 
			// all of the following constants are empirically determined to move the arm into the desired position 
			desiredJointAngle.angle = 2.56244 * radian;
			myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);

			desiredJointAngle.angle = 1.04883 * radian;
			myYouBotManipulator->getArmJoint(2).setData(desiredJointAngle);

			desiredJointAngle.angle = -2.43523 * radian;
			myYouBotManipulator->getArmJoint(3).setData(desiredJointAngle);

			desiredJointAngle.angle = 1.73184 * radian;
			myYouBotManipulator->getArmJoint(4).setData(desiredJointAngle);
			LOG(info) << "unfold arm";
			SLEEP_MILLISEC(4000);

			// fold arm (approx. home position) using empirically determined values for the positions
			desiredJointAngle.angle = 0.11 * radian;
			myYouBotManipulator->getArmJoint(1).setData(desiredJointAngle);

			desiredJointAngle.angle = 0.11 * radian;
			myYouBotManipulator->getArmJoint(2).setData(desiredJointAngle);

			desiredJointAngle.angle = -0.11 * radian;
			myYouBotManipulator->getArmJoint(3).setData(desiredJointAngle);

			desiredJointAngle.angle = 0.11 * radian;
			myYouBotManipulator->getArmJoint(4).setData(desiredJointAngle);

			LOG(info) << "fold arm";
			SLEEP_MILLISEC(4000);
		}

	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		std::cout << "unhandled exception" << std::endl;
	}

	// clean up
	if (myYouBotBase) {
		delete myYouBotBase;
		myYouBotBase = 0;
	}
	if (myYouBotManipulator) {
		delete myYouBotManipulator;
		myYouBotManipulator = 0;
	}

	LOG(info) << "Done.";

	return 0;
}

