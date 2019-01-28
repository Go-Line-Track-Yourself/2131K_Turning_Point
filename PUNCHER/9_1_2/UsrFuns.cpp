
void ManualIntake(){
  if(Controller1.ButtonR1.pressing()){
    IntakeSMS(100);
  }
  else if(Controller1.ButtonR2.pressing()){
    IntakeSMS(-100);
  }
  else
  IntakeSMS(0);
}
bool autointakeenabled = false;
int bottomlightvalue;
int toplightvalue;
int bottomballinmax = 60;
int topballinmax = 60;

bool IntakeEnabledBtnPressed = false;
bool IntakeEnabledInverted = false;
bool ballinbottom;
bool ballintop;
bool autoindexfiring;

void setIntakePower(int power){
  IntakeMotor.spin(vex::directionType::fwd,power,vex::pct);
}

void auto_intake( ) {
  bottomlightvalue = FeedSen1.value(vex::percentUnits::pct);
  toplightvalue = PuncSen.value(vex::percentUnits::pct);

  if (bottomlightvalue < bottomballinmax) ballinbottom = true;
  else ballinbottom = false;
  if (toplightvalue  < topballinmax) ballintop = true;
  else ballintop = false;

  if(!ballintop)  setIntakePower(100);
  else{
    if(!ballinbottom) setIntakePower(60);
    else              setIntakePower(0);
  }
}

void AutoFeed()  {
  // Brain.Screen.print(IntakeEnabledInverted);
  if (Controller1.ButtonA.pressing() && IntakeEnabledBtnPressed == false)  {
    IntakeEnabledBtnPressed = true;
    IntakeEnabledInverted = !IntakeEnabledInverted;
    }
    else if (!Controller1.ButtonA.pressing() && IntakeEnabledBtnPressed == true)  {
      IntakeEnabledBtnPressed = false;
    }
    if (IntakeEnabledInverted)
    {
      auto_intake();
    }
    if (!IntakeEnabledInverted)
    {
      autointakeenabled = false;
      ManualIntake();
    }
}

void PuncherChargeControl(){
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
        L1Pressed=true;
        vex::task CompRumerTask(ComRumerFun);
        if(Charged){//if charged && the puncherPos is not spining  && !PuncherPosSTS
            PuncherDeg+=80;
            PuncherSpinToControlRunEnabled=true;//enable puncherspinto
            Charged=false;
        }
        else if(!Charged){
            PuncherDeg+=280;
            PuncherSpinToControlRunEnabled=true;//enable puncherspinto
            Charged=true;
        }
    }
    else if(!Controller1.ButtonL1.pressing() && L1Pressed)  L1Pressed=false;

    PuncherSpinTo(PuncherDeg,true);//spin motor to puncherDeg && set motor to spin
}
void NewPunch()  {
  if(Controller1.ButtonL2.pressing()  && !L2Pressed){
  L2Pressed=true;
  PuncherDeg=360;
  vex::task::sleep(150);
  PuncherPosDeg=90;
  vex::task::sleep(150);
  PuncherDeg=360;
  vex::task::sleep(150);
  PuncherPosDeg=0;
}
else if(!Controller1.ButtonL2.pressing() && L2Pressed)  L2Pressed=false;

  }

void PuncherPosRoter(){
    if(PuncherPos==PuncherPositions::ShortTop)      PuncherPos=PuncherPositions::ShortMid;
    else if(PuncherPos==PuncherPositions::ShortMid) PuncherPos=PuncherPositions::ShortTop;
}
void PuncherPosControl(){
  if(Controller1.ButtonUp.pressing() && !UpPressed){
    UpPressed=true;
    PuncherPosDeg=90;
    PuncherPosSpinToControlRunEnabled=true;
  }
  else if(!Controller1.ButtonUp.pressing() &&UpPressed)          UpPressed=false;

  else if(Controller1.ButtonDown.pressing() && !DownPressed){
    DownPressed=true;
    PuncherPosDeg=0;
    PuncherPosSpinToControlRunEnabled=true;
  }
  else if(!Controller1.ButtonDown.pressing() &&DownPressed)          DownPressed=false;

  PuncherPosSpinTo(PuncherPosDeg);
}

void PuncherControl(){
    PuncherPosControl();
    PuncherChargeControl();
}

/*void FlipperControll(){//fliper control
     if(Controller1.ButtonY.pressing() && !YPressed){
       YPressed=true;
       if (FliperRequested==0) FliperRequested=300;
       else if (FliperRequested==300) FliperRequested=0;
     FlipMotor.startRotateTo(FliperRequested,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
     }
     else if(!Controller1.ButtonY.pressing() && YPressed)     YPressed=false;
}
void LiftControl(){
    if(Controller1.ButtonRight.pressing()) {
    FlipMotor.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
  }
    else if(Controller1.ButtonLeft.pressing())  {
    FlipMotor.spin(vex::directionType::rev,100,vex::velocityUnits::pct);
    }
    else
      FliperSMS(0);
}
void CapFlip(){
  if(Controller1.ButtonX.pressing())  {
    FlipMotor.startRotateTo(400,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
  }
}*/
void FlipperControll(){//fliper control
    if(Controller1.ButtonLeft.pressing()) {
        FlipMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        manualOverride = true;
    }
    else if(Controller1.ButtonRight.pressing()) {
        FlipMotor.spin(vex::directionType::rev, 100, vex::velocityUnits::pct);
        manualOverride = true;
    }
    else if(Controller1.ButtonX.pressing() && FliperMotorConBtnPressed==false){
        FliperMotorConBtnPressed=true;
        FlipMotor.startRotateFor(FliperMotorInverted ? -300 : 300,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
        FliperMotorInverted=!FliperMotorInverted;
        manualOverride = false;
    }
    else if (manualOverride) {
        FlipMotor.stop(vex::brakeType::brake);
    }
}

//------------------Drive voids----------------------//
void setMechLFPower(int pct){
    if(pct==0)   FLDriveMotor.stop();
    else{
        FLDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
    }
}
void setMechLBPower(int pct){
    if(pct==0)   BLDriveMotor.stop();
    else{
        BLDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
    }
}
void setMechRFPower(int pct){
    if(pct==0)   FRDriveMotor.stop();
    else{
        FRDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
    }
}
void setMechRBPower(int pct){
    if(pct==0)   BRDriveMotor.stop();
    else{
        BRDriveMotor.spin(vex::directionType::fwd,pct,vex::velocityUnits::pct);
    }
}
void setMechDrivePower(int LF,int LB,int RF,int RB){
    setMechLFPower(LF);
    setMechLBPower(LB);
    setMechRFPower(RF);
    setMechRBPower(RB);
}
void DriveMechPowerSend(int j1,int j2,int j3=0,int j4=0){//left,right,side1,side2
    int LF=j1;//left
    int RF=j2;//right
    int SD=(j3+j4)/2;//side

    setMechDrivePower(//left go apart && right go into when going right
        LF+SD,
        LF-SD,
        RF-SD,
        RF+SD);
}
void setDrivePower(int left, int right){
    setMechLFPower(left);
    setMechLBPower(left);
    setMechRFPower(right);
    setMechRBPower(right);
}

//------Manual Drive Mech Controll------------//
void ManualMechDriveCont(){
    int LeftVirtJoy=Controller1.Axis3.value();
    int RightVirtJoy=Controller1.Axis2.value();
    int LeftHorJoy=Controller1.Axis4.value();
    int RightHorJoy=Controller1.Axis1.value();

    if(std::abs(LeftVirtJoy)<5)    LeftVirtJoy=0;
    if(std::abs(RightVirtJoy)<5)    RightVirtJoy=0;
    if(std::abs(LeftHorJoy)<15)  LeftHorJoy=0;
    if(std::abs(RightHorJoy)<15)  RightHorJoy=0;

    if(LeftVirtJoy!=0 || RightVirtJoy!=0 || LeftHorJoy!=0 || RightHorJoy!=0){
      //  DriveMechPowerSend(LeftVirtJoy,RightVirtJoy,LeftHorJoy,RightHorJoy);
      DriveArcadeSMS(LeftVirtJoy, LeftHorJoy, RightHorJoy);
    }
    else{
        setMechDrivePower(0,0,0,0);//Last loop before disableing; used to release drivemanualcontrol
    }
}

/*void driveLock(){
    stopDriveHold();
}*/
bool DriveLockInverted;
bool DriveLockConBtnPressed;
void DriveCont_LockCont(){
    if(Controller1.ButtonB.pressing() && DriveLockConBtnPressed==false){
        DriveLockConBtnPressed=true;
        DriveLockInverted=!DriveLockInverted;
    }
    if(!Controller1.ButtonB.pressing() && DriveLockConBtnPressed==true){
        DriveLockConBtnPressed=false;
    }

    if(DriveLockInverted){
      BLDriveMotor.stop(vex::brakeType::hold);
      BRDriveMotor.stop(vex::brakeType::hold);
      FLDriveMotor.stop(vex::brakeType::hold);
      FRDriveMotor.stop(vex::brakeType::hold);
    }
    else if(!DriveLockInverted) {
      BLDriveMotor.setStopping(vex::brakeType::coast);
      BRDriveMotor.setStopping(vex::brakeType::coast);
      FLDriveMotor.setStopping(vex::brakeType::coast);
      FRDriveMotor.setStopping(vex::brakeType::coast);
      ManualMechDriveCont();

    }
}
