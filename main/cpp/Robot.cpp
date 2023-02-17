// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <frc/Timer.h>
#include <fmt/core.h>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  //m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  //m_chooser.AddOption(kAutoNameCustom1, kAutoNameCustom1);
  //frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    #if defined(__linux__) || defined(_WIN32)
  frc::CameraServer::StartAutomaticCapture();
  #else
    std::fputs("Vision only available on Linux or Windows.\n", stderr);
    std::fflush(stderr);
#endif
  //frc::CameraServer::SetSize	(	kSize640x480 );
  cs::CvSource frc::CameraServer::PutVideo	(	std::string_view 	DriveCam,
1280,
720
//Fix Camera
)		

    
     // The RestoreFactoryDefaults method can be used to reset the configuration parameters
     // in the SPARK MAX to their factory default state. If no argument is passed, these
     // parameters will not persist between power cycles
     //
  //m_leftLeadMotor.RestoreFactoryDefaults();
  //m_rightLeadMotor.RestoreFactoryDefaults();
  //m_leftFollowMotor.RestoreFactoryDefaults();
  //m_rightFollowMotor.RestoreFactoryDefaults();

   m_robotDrive.DriveCartesian (-m_driverController.GetLeftY(), -m_driverController.GetLeftX(),
                                -m_driverController.GetRightX());
  m_frontLeft.SetInverted(true);
  m_rearLeft.SetInverted(true);
  m_robotDrive.SetExpiration(100_ms);
  m_timer.Start();
}

/**
 * This function is called every 20 ms, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {

 frc::SmartDashboard::PutNumber("ia: ", ia);
 frc::SmartDashboard::PutNumber("it: ", it);

  frc::SmartDashboard::PutBoolean("LB : ", leftbumper);
  frc::SmartDashboard::PutBoolean("RB : ", rightbumper);

  frc::SmartDashboard::PutBoolean("LT : ", lefttriggeraxis);
  frc::SmartDashboard::PutBoolean("RT : ", righttriggeraxis);

  frc::SmartDashboard::PutBoolean("bA : ", bA);
  frc::SmartDashboard::PutBoolean("bB : ", bB);
  frc::SmartDashboard::PutBoolean("bX : ", bX);
  frc::SmartDashboard::PutBoolean("bY : ", bY);

  frc::SmartDashboard::PutNumber("left x : ", left_x);
  frc::SmartDashboard::PutNumber("left y : ", left_y);
  frc::SmartDashboard::PutNumber("right x : ", right_x);
  frc::SmartDashboard::PutNumber("right y : ", right_y); 

  frc::SmartDashboard::PutNumber("ai raw :", ai_raw);
  frc::SmartDashboard::PutNumber("ai voltage :", ai_voltage);

  frc::SmartDashboard::PutNumber("ultra raw :", ultra_raw);
  frc::SmartDashboard::PutNumber("ultra distance :", distance);

}


 
void Robot::AutonomousInit() {
  //m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  //fmt::print("Auto selected: {}\n", m_autoSelected);

  //if (m_autoSelected == kAutoNameCustom1) {
    // Custom Auto goes here
    
    m_timer.Reset();
    m_timer.Start();
    ia = 0;
  }
  //else {
    // Default Auto goes here
  



  
void Robot::AutonomousPeriodic() 
  //if (m_autoSelected == kAutoNameCustom1) {
    // Custom Auto goes here
    {
     if (m_timer.Get() < 2_s) {
      // Drive forwards quarter speed, make sure to turn input squaring off
      m_robotDrive.DriveCartesian(-0.25, 0.0, false);
    } else {
      // Stop robot
      m_robotDrive.DriveCartesian(0.0, 0.0, false);
    }
  //} else {
    // Default Auto goes here
  

  
  ia++;
}

void Robot::TeleopInit() {

  it = 0;
}

void Robot::TeleopPeriodic() {

  
  it++;

  left_y = m_driverController.frc::XboxController::GetLeftX(),
  right_y = m_driverController.frc::XboxController::GetRightX();

  left_x = m_driverController.frc::XboxController::GetLeftY(),
  right_x = m_driverController.frc::XboxController::GetRightY();

  leftbumper = m_driverController.frc::XboxController::GetLeftBumper();
  rightbumper = m_driverController.frc::XboxController::GetRightBumper();

  lefttriggeraxis = m_driverController.frc::XboxController::GetLeftTriggerAxis();
  righttriggeraxis = m_driverController.frc::XboxController::GetRightTriggerAxis();

  bA = m_driverController.GetAButton();
  bB = m_driverController.GetBButton();
  bX = m_driverController.GetXButton();
  bY = m_driverController.GetYButton();

  //limit_switch_value = limit_switch.Get();
  //knife_switch_value = knife_switch.Get();

  ai_raw = ai.GetValue();
  ai_voltage = ai.GetVoltage();

  ultra_raw = ultra.GetValue();
  distance = (double) ultra_raw * adc_to_mm ;

//Drive Cartesian
  m_robotDrive.DriveCartesian(-m_driverController.GetLeftX(), - -m_driverController.GetLeftY(),
                               - -m_driverController.GetRightTriggerAxis() + -m_driverController.GetLeftTriggerAxis());

// -m_driverController.GetRightX()
//When we calibrated XBox controller, Z-axis showed up on triggers so switched back to triggers but inverted...
//meaning I put the right first and left second to try next. We may need to set the Z axis to the triggers
//I DID IT -Carlos

//armextender lengthen using PWM Sparks paired
m_armextender.Set(0.05);
m_armextender.Set(leftbumper);
//armextender shorten
m_armextender.Set(-0.05);
m_armextender.Set(rightbumper);

//Pneumatics
//Arm up and down
m_updownarm.Set(frc::DoubleSolenoid::Value::kOff);
m_updownarm.Set(frc::DoubleSolenoid::Value::kForward);
m_updownarm.Set(frc::DoubleSolenoid::Value::kReverse);

//assign updownarm to X & Y buttons
//kReverse = X button; raises arm
//kForward = Y button; lowers arm

bX = m_driverController.GetXButton();
m_updownarm.Set(frc::DoubleSolenoid::kReverse);

bY = m_driverController.GetYButton();
m_updownarm.Set(frc::DoubleSolenoid::kForward);




//Grabber
// Initialize the DoubleSolenoid so it knows where to start.  Not required for single solenoids.
m_grabber.Set(frc::DoubleSolenoid::Value::kReverse);

if (m_driverController.GetBButtonPressed()) {
   m_grabber.Toggle();
   m_grabber.Toggle();
}

  //Claw
  //double rightTrigger = m_joystick.GetTriggerAxis(frc::GenericHID::kRightHand);
  // bool leftTrigger = m_joystick.GetTriggerAxis(frc::GenericHID::kLeftHand);
  //if (rightTrigger > 0.2)
  //{
  //m_claw.SetAngle(90);
    //}
    //if (leftTrigger > 0.2)
   // {
     // m_claw.SetAngle(0);
   // }

    //Claw Up
    //bool yButton = kjoystick.GetYButton();
    //bool aButton = kjoystick.GetAButton();
    //if (yButton == true)
    //{
      //m_clawUp.Set(DoubleSolenoid::Value::kForward);
    //}
    //if (aButton == true)
   // {
      //m_clawUp.Set(DoubleSolenoid::Value::kReverse);
    //}

    //Claw Forward
    //bool bButton = m_joystick.GetBButton();
    //bool xButton = m_joystick.GetXButton();

    //if (bButton == true)
    //{
      //m_clawExtend.Set(DoubleSolenoid::Value::kForward);
    //}
    //if (xButton == true)
    //{
     // m_clawExtend.Set(DoubleSolenoid::Value::kReverse);
    //}                               
}

void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}

void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}

void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif