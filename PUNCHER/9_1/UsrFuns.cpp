/*Need to
add enum class for charging fire or not moving
*/
/*Change Log
BtnX->BtnR1 Puncher Control && Post Punch enable auto intake if rotated more than 340 deg and there is not a ball in the puncher
add controller rumble every time charged or fired
add tollerances to puncher pos control && puncher fire lockout
*/
//
//rstet timer if ball in puncher or
void IntakeAutoUpDate(){//UpDate Sensors Code
    //Puncher UpDate
    if(PuncSen.value(vex::analogUnits::pct)<PuncBallTal){
        GlobTime=0;//reset timer
        PuncBall=true;
        ComRum=false;
    }
    else{
        if(PuncherSpinToControlEnabled)           PuncBall=false;
        else{
            if(GlobTime>PuncBallTimeWait)   PuncBall=false;
            else if(GlobTime>ComRumTime)    ComRum=true;
            GlobTime=GlobTime+1;//add one to timer
        }
    }
    //FeedBall UpDate
    if(FeedSen1.value(vex::analogUnits::pct)<Feed1BallTal || FeedSen2.value(vex::analogUnits::pct)<Feed2BallTal)    FeedBall=true;
    else                                                                                                            FeedBall=false;
}
void IntakeAuto(){//Autonomous Logic Control
    if(IntakeAutoEnabled){
        IntakeAutoEnabledWas=true;
        if(!PuncBall)       IntakeSetting=IntakePctIn;
        else{
            if(!FeedBall)   IntakeSetting=IntakePctIn;
            else            IntakeSetting=IntakePctStop;
        }
    }
    else if(IntakeAutoEnabledWas){//first loop disabled
        IntakeSetting=IntakePctStop;
        IntakeAutoEnabledWas=false;
    }
}
int IntakeStateUpDate(){//Task to UpDate IntakeAutoUpDate every second in the background
    while(1){
        IntakeAutoUpDate();
        vex::task::sleep(5);
    }
}
void IntakeAutoControl(){//Controller Input To control Autonomous Logic Control
    if(Controller1.ButtonA.pressing() && !APressed){
        APressed=true;
        IntakeAutoEnabled=!IntakeAutoEnabled;//toggle intake auto enable
    }
    else if(!Controller1.ButtonA.pressing() &&APressed)    APressed=false;

    IntakeAuto();
}
//right down  hold(outfeed) && toggle(DriveMode=Baller,Autointake=true,FLiperrequested=fliperposin,)
void IntakeManualControl(){//Controller Manual OverRide
    if(Controller1.ButtonR2.pressing()){
        IntakeManualControlEnabled=true;//halt auto intake function from running
        IntakeSetting=IntakePctOut;//out feed the intake
    }

    else if(Controller1.ButtonA.pressing()){//btnR1->btnY;
        IntakeManualControlEnabled=true;
        IntakeSetting=IntakePctIn;
    }
    else if(IntakeManualControlEnabled){//first loop not manualy controlled
        IntakeAutoEnabled=false;
        IntakeManualControlEnabled=false;
        // if(!IntakeAutoEnabled)  IntakeSetting=IntakePctStop;//if not auto controlled stop intakeing
    }
}
void IntakeComRumer(){
    if(ComRum && IntakeAutoEnabled && IntakeSetting==IntakePctStop)  vex::task ComRumerTask(ComRumerFun);
}
void IntakeControl(){//OverRide Control Code
    IntakeManualControl();
    if(!IntakeManualControlEnabled) IntakeAutoControl();
    IntakeSMS(IntakeSetting);
    IntakeComRumer();
}

void PuncherChargeControl(){
    if(Controller1.ButtonR1.pressing() && !R1Pressed){
        R1Pressed=true;
        vex::task CompRumerTask(ComRumerFun);
        if(Charged && !PuncherPosSTS){//if charged && the puncherPos is not spining
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
    else if(!Controller1.ButtonR1.pressing() && R1Pressed)  R1Pressed=false;

    PuncherSpinTo(PuncherDeg,true);//spin motor to puncherDeg && set motor to spin
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

  PuncherPosSpinTo(PuncherPosDeg,true);
}

void PuncherControl(){
    PuncherPosControl();
    PuncherChargeControl();
}
//
/*void FliperManualControl(){
    if(Controller1.ButtonL1.pressing()){
        FliperManualControlEnabled=true;
        FliperSMS(100);
    }
    else if(Controller1.ButtonL2.pressing()){
        FliperManualControlEnabled=true;
        FliperSMS(-100);
    }
    else if(FliperManualControlEnabled){//first loop
        FliperSMS(0);
        FliperManualControlEnabled=false;
    }
}
void FliperFlip(){
    if(FliperRequested==FliperPosIn || FliperRequested==FliperPosInPun){//getting out of baller
        FliperRequested=FliperPosDown;
        DriveMotorInverted=true;//set drive dir to flipper
        IntakeAutoEnabled=false;//disable auto intake
    }
    else if(FliperRequested==FliperPosUpMid)    FliperRequested=FliperPosDown;
    else if(FliperRequested==FliperPosDown)     FliperRequested=FliperPosUpMid;
    if(DriveMotorInverted==false)               FliperRequested=FliperPosIn;//if in baller be in
}
void FliperPosControl(){
    if(Controller1.ButtonY.pressing() && !L1Pressed){
        L1Pressed=true;
        FliperFlip();
        FliperPosControlEnabled=true;
    }
    if(!Controller1.ButtonY.pressing() && L1Pressed)   L1Pressed=false;

    if(FliperPosControlEnabled){
        FlipMotor.startRotateTo(FliperRequested,vex::rotationUnits::deg,100,vex::velocityUnits::pct);
    }
}*/
void CapFliperControll(){//fliper control
    if(Controller1.ButtonL1.pressing()) {
        FlipMotor.spin(vex::directionType::fwd, 100, vex::velocityUnits::pct);
        manualOverride = true;
    }
    else if(Controller1.ButtonL2.pressing()) {
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

    if(!Controller1.ButtonX.pressing() && FliperMotorConBtnPressed==true){
        FliperMotorConBtnPressed=false;
        manualOverride = false;
    }
}
void FliperControl(){
    CapFliperControll();
  //  if(!FliperManualControlEnabled) FliperPosControl();
  //  FliperPosControl();
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
