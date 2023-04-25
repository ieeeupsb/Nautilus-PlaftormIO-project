#include <Arduino.h>
#include "proj_types.h"
#include "robot.h"
#include "IRLine.h"

extern IRLine_t IRLine;

void control(robot_t& robot)
{
    robot.tis = millis() - robot.tes;

    //robot.setState(4);

    // Rules for the state evolution
     if(robot.state == 0 && robot.tof_dist > 0.10 && robot.prev_tof_dist < 0.05 && robot.tis > 3000) {
      robot.rel_s = 0;
      robot.setState(1);

    } else if (robot.state == 1 && robot.tof_dist < 0.04) {
      robot.setState(2);

    } else if(robot.state == 2 && robot.tis > 400) {
      robot.rel_s = 0;
      robot.setState(3);

    } else if(robot.state == 3 && robot.rel_s < -0.1) {
      robot.rel_theta = 0;
      robot.setState(4);

    } else if(robot.state == 4 && robot.rel_theta > radians(170) && IRLine.total > 1500) {
      IRLine.crosses = 0;
      robot.setState(5);

    } else if(robot.state == 5 && IRLine.crosses >= 5) {
      robot.rel_s = 0;
      robot.rel_theta = 0;
      robot.setState(6);

    } else if(robot.state == 6 && robot.rel_theta < radians(-70) && IRLine.total > 1500) {
      robot.setState(7);

    } else if(robot.state == 7 && robot.tis > 2000) {
      IRLine.crosses = 0;
      robot.setState(8);

    } else if (robot.state == 202 && robot.tis > robot.T1) {
      robot.setState(200);

    } else if(robot.state == 20 && robot.LastTouchSwitch && !robot.TouchSwitch) {
      robot.rel_s = 0;
      robot.setState(21);

    } else if(robot.state == 21 && robot.TouchSwitch) {
      robot.setState(22);

    } else if(robot.state == 22 && robot.TouchSwitch) {
      //robot.setState(1);

    } else if(robot.state == 25) {
      //robot.setState(1);

    }

    // Actions in each state
    if (robot.state == 0) {         // Robot Stoped            
      robot.solenoid_state = 0;
      robot.setRobotVW(0, 0);
    
    } else if (robot.state == 1) {  // Go: Get first box
      robot.solenoid_state = 0;
      robot.followLineLeft(IRLine, robot.follow_v, robot.follow_k);

    } else if (robot.state == 2) { // Turn Solenoid On and Get the Box
      robot.solenoid_state = 1;
      robot.followLineLeft(IRLine, robot.follow_v, robot.follow_k);
    
    } else if (robot.state == 3) {  // Go back with the box
      robot.solenoid_state = 1;
      robot.setRobotVW(-0.2, 0);
      
    } else if (robot.state == 4) {  // Turn 180 degrees
      robot.solenoid_state = 1;
      robot.setRobotVW(0, 2);
      
    } else if (robot.state == 5) {  // long travel to the box final destination
      robot.solenoid_state = 1;
      //followLineRight(80 - 40 * (IRLine.crosses >= 5), -2.0);
      robot.followLineRight(IRLine, robot.follow_v, robot.follow_k);
      
    } else if (robot.state == 6) {  // Advance a little then turn to place the box
      robot.solenoid_state = 1;
      robot.setRobotVW(0.05, -2);
      
    } else if (robot.state == 7) {  
      robot.solenoid_state = 1;
      robot.followLineRight(IRLine, robot.follow_v, robot.follow_k); 

    } else if (robot.state == 8) { // Drop the box and go back
      robot.solenoid_state = 0;
      if (robot.tis < 2000) robot.setRobotVW(-0.1, 0);
      else robot.setRobotVW(0, 0);
    
    } else if (robot.state == 20) {
      robot.v_req = 0;
      robot.w_req = 0;

    } else if (robot.state == 21) {
      robot.v_req = 0.1;
      robot.w_req = 0;
    
    } else if (robot.state == 22) {
      robot.v_req = 0.1;
      robot.w_req = 0;
      robot.solenoid_state = 1;
    
    } else if (robot.state == 25) {
      robot.v_req = 0;
      robot.w_req = 0;
      robot.solenoid_state = 1;
    
    }
    
    
      else if (robot.state == 10) { //Test
      robot.setRobotVW(0.1, 0);      

    } else if (robot.state == 100) {
      robot.v_req = 0.2;
      robot.w_req = 0;

    } else if (robot.state == 101) {
      robot.v_req = 0;
      robot.w_req = 2;

    } else if (robot.state == 200) {
      robot.PWM_1 = 0;
      robot.PWM_2 = 0;

    } else if (robot.state == 201) {
      robot.PWM_1 = robot.PWM_1_req;
      robot.PWM_2 = robot.PWM_2_req;
    
    } else if (robot.state == 202) {
      robot.PWM_1 = robot.PWM_1_req;
      robot.PWM_2 = robot.PWM_2_req;      
    }
  
}
