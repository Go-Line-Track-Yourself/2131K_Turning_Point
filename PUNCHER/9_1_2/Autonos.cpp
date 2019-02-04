void AutFunBlueBack(){

    Drive(15);
    IntakeSMS(100);
    Drive(2,75);
    vex::task::sleep(95);
    IntakeSMS(0);
    Drive(-21);
    Drive(-6,50);
    Drive(2);
    Turn(-18.5);
    Drive(47);
    Puncher();
    PuncherPosAut(90);
    IntakeSMS(100);
    vex::task::sleep(300);
    Puncher();
    Drive(20);

}
void AutFunBlueFront(){

//Turn(18.5); left
Drive(15);
IntakeSMS(80);
Drive(2,75);
vex::task::sleep(95);
IntakeSMS(0);
Drive(-21);
Turn(-16.5);
Drive(1.5);
Puncher();
PuncherPosAut(90);
IntakeSMS(100);
vex::task::sleep(600);
Drive(1,75);
Puncher();
Turn(-1);
Drive(21);
Drive(-8);
Turn(12.5);
Drive(4);
PuncherPosAut(0);
Puncher();

}

void AutFunRedBack(){
    Drive(15);
    IntakeSMS(100);
    Drive(2,75);
    vex::task::sleep(95);
    IntakeSMS(0);
    Drive(-21);
    Drive(-6,50);
    Drive(2);
    Turn(17.5);
    Drive(47);
    Turn(-2);
    Puncher();
    PuncherPosAut(90);
    IntakeSMS(100);
    vex::task::sleep(300);
    Puncher();
    Drive(20);
}
void AutFunRedFront(){

  Drive(15);
  IntakeSMS(80);
  Drive(2,75);
  vex::task::sleep(95);
  IntakeSMS(0);
  Drive(-20);
  Turn(17.7);
  Drive(5.5,60);
  Puncher();
  PuncherPosAut(90);
  Drive(1);
  IntakeSMS(100);
  vex::task::sleep(600);
  Puncher();
  Turn(.3);
  Drive(23.5);

}
void Skills(){

  Drive(8,50);
  Puncher();
  vex::task::sleep(100);
  Turn(.2);
  Drive(27);
  Drive(-34.5);
  Turn(-18.5);
  Drive(-3,50);
  Drive(23);
  Drive(2,70);
  IntakeSMS(100);
  vex::task::sleep(300);
  IntakeSMS(0);
  vex::task::sleep(1000);
  Drive(.5);
  Turn(16.5);
  Drive(4);
  IntakeSMS(100);
  vex::task::sleep(500);
  Puncher();
  IntakeSMS(0);
  Turn(1);
  Drive(27);
  Drive(-13);
  Turn(-17.5);
  Drive(-4);
  Flip(280);
  Flip(0);
  Drive(25);
  Turn(35.5);
  Drive(-3);
  Flip(280);
  Flip(0);
  Drive(-.3);
  Turn(-18.3);
  Drive(12);
  Drive(-27);
  Turn(-18.5);
  Drive(5);
  Turn(18.5);
  Drive(-15);
  Turn(-18.5);
  Drive(9,50);
  Flip(280);
  Drive(-86);

  /*Drive(28);
  vex::task::sleep(95);
  IntakeSMS(80);
  vex::task::sleep(400);
  IntakeSMS(0);
  Drive(-22.5);
  Turn(16.5);
  Drive(4.75,60);
  Puncher();
  IntakeSMS(100);
  PuncherPosAut(90);
  Drive(1,50);
  vex::task::sleep(600);
  Puncher();
  Turn(.8);
  IntakeSMS(0);
  Drive(23.5);
  Drive(-60);
  Turn(18.25);
  Drive(6,50);
  Drive(-87,100);*/



}
