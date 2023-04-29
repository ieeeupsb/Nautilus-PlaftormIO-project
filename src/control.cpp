#include <Arduino.h>
#include "proj_types.h"
#include "robot.h"
#include "IRLine.h"

extern IRLine_t IRLine;

void control(robot_t &robot)
{
    robot.tis = millis() - robot.tes;
    switch (robot.state)
    {
    case START:
        robot.solenoid_state = 0;
        robot.setRobotVW(0,0);
        break;
    case SETUP:
        break;
    case STOP:
        IRLine.crosses = 0;
        robot.rel_theta = 0;
        break;
    case FLINE:
        robot.rel_theta = 0;
        robot.followLine(IRLine);
        if (IRLine.crosses >= 1)
        {
            IRLine.crosses = 0;
            robot.rel_theta = 0;
            robot.setState(STOP);
        }
        break;
    case TLEFT:
        robot.setRobotVW(0.04,1.5);
        if (robot.rel_theta > radians(80))
        {
            IRLine.crosses = 0;
            robot.setState(STOP);
        }
        break;
    case TRIGHT:
        robot.setRobotVW(0.04,-1.5);
        if (robot.rel_theta > radians(-80))
        {
            IRLine.crosses = 0;
            robot.setState(STOP);
        }
        break;
    case PICKB:
        robot.followLine(IRLine);
        if (robot.tof_dist < 0.04)
            robot.setState(11);
        break;
    case 11:
        robot.solenoid_state = 1;
        robot.followLine(IRLine);
        if(robot.tis > 1000) {
            robot.rel_s = 0;
            robot.setState(12);
        }
        break;
    case 12:
        robot.setRobotVW(-0.12,0);
        if(robot.rel_s < -0.08) {
            robot.rel_theta = 0;
            robot.setState(13);
        }
        break;
    case 13:
        robot.setRobotVW(0,-2.5);
        if(robot.rel_theta < radians(-160)) {
            robot.rel_theta = 0;
            IRLine.crosses = 0;
            robot.setState(STOP);
        }
        break;
    case DROPB:
        robot.followLine(IRLine);
        if(robot.tis > 1000) {
            robot.rel_s = 0;
            robot.rel_theta = 0;
            robot.setState(21);
        }
        break;
    case 21:
        robot.solenoid_state = 0;
        robot.setRobotVW(-0.1,0);
        if(robot.rel_s < -0.08) {
            robot.rel_theta = 0;
            robot.setState(21);
        }
        break;
    case 22:
        robot.setRobotVW(0,-2.5);
        if(robot.rel_theta < radians(-160)) {
            IRLine.crosses = 0;
            robot.rel_theta = 0;
            robot.setState(STOP);
        }
        break;
    case DROPG:
        robot.followLine(IRLine);
        if(robot.tis > 1500) {
            robot.rel_s = 0;
            robot.rel_theta = 0;
            robot.setState(31);
        }
        break;
    case 31:
        robot.solenoid_state = 0;
        robot.setRobotVW(-0.1,0);
        if(robot.rel_s < -0.22) {
            robot.rel_theta = 0;
            robot.setState(32);
        }
    case 32:
        robot.setRobotVW(0,-2.5);
        if(robot.rel_theta < radians(-160)) {
            IRLine.crosses = 0;
            robot.rel_theta = 0;
            robot.setState(STOP);
        }

    // STATES FOR TESTING THE ROBOT
    case 100:
    case 101:
        robot.v_req = 0;
        robot.w_req = 0;
        break;
    case 200:
        robot.PWM_1 = 0;
        robot.PWM_2 = 0;
        break;
    case 201:
    case 202:
        robot.PWM_1 = robot.PWM_1_req;
        robot.PWM_2 = robot.PWM_2_req;
        break;
        
    }
}
