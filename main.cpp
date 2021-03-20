#include <simplecpp>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
using namespace simplecpp;

//movingObject.h
#ifndef _MOVINGOBJECT_INCLUDED_
#define _MOVINGOBJECT_INCLUDED_

#include <simplecpp>
#include <vector>
#include <composite.h>
#include <sprite.h>

using namespace simplecpp;

class MovingObject : public Sprite {
  vector<Sprite*> parts;
  public: double vx, vy;
  double ax, ay;
  bool paused;
  void initMO(double argvx, double argvy, double argax, double argay, bool argpaused=true) {
    vx=argvx; vy=argvy; ax=argax; ay=argay; paused=argpaused;
  }
 public:
 MovingObject(double argvx, double argvy, double argax, double argay, bool argpaused=true)
    : Sprite() {
    initMO(argvx, argvy, argax, argay, argpaused);
  }
 MovingObject(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : Sprite() {
   double angle_rad = angle_deg*PI/180.0;
   double argvx = speed*cos(angle_rad);
   double argvy = -speed*sin(angle_rad);
   initMO(argvx, argvy, argax, argay, argpaused);
  }
  void set_vx(double argvx) { vx = argvx; }
  void set_vy(double argvy) { vy = argvy; }
  void set_ax(double argax) { ax = argax; }
  void set_ay(double argay) { ay = argay; }
  double getXPos();
  double getYPos();
  void reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta);

  void pause() { paused = true; }
  void unpause() { paused = false; }
  bool isPaused() { return paused; }

  void addPart(Sprite* p) {
    parts.push_back(p);
  }
  void nextStep(double t);
  void getAttachedTo(MovingObject *m);
};

#endif

//MovingObject.cpp

void MovingObject::nextStep(double t) {
  if(paused) { return; }
  //cerr << "x=" << getXPos() << ",y=" << getYPos() << endl;
  //cerr << "vx=" << vx << ",vy=" << vy << endl;
  //cerr << "ax=" << ax << ",ay=" << ay << endl;

  for(size_t i=0; i<parts.size(); i++){
    parts[i]->move(vx*t, vy*t);
  }
  vx += ax*t;
  vy += ay*t;
} // End MovingObject::nextStep()

double MovingObject::getXPos() {
  return (parts.size() > 0) ? parts[0]->getX() : -1;
}

double MovingObject::getYPos() {
  return (parts.size() > 0) ? parts[0]->getY() : -1;
}

void MovingObject::reset_all(double argx, double argy, double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) {
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(argx, argy);
  }
  double angle_rad = angle_deg*PI/180.0;
  double argvx = speed*cos(angle_rad);
  double argvy = -speed*sin(angle_rad);
  vx = argvx; vy = argvy; ax = argax; ay = argay; paused = argpaused;
} // End MovingObject::reset_all()

void MovingObject::getAttachedTo(MovingObject *m) {
  double xpos = m->getXPos();
  double ypos = m->getYPos();
  for(size_t i=0; i<parts.size(); i++){
    parts[i]->moveTo(xpos, ypos);
  }
  initMO(m->vx, m->vy, m->ax, m->ay, m->paused);
}

//coin.h
#ifndef __COIN_H__
#define __COIN_H__



class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void resetCoin();

}; // End class Coin

#endif

//lasso.h
#ifndef __LASSO_H__
#define __LASSO_H__

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X-PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y-100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 0.05

#define RELEASE_ANGLE_STEP_DEG 20
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360-RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 100

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90

#define BOMB_SPEED 60
#define MAGNET_SPEED 120

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 50
#define COIN_SIZE 5
#define BOMB_SIZE 8

#define MAGNET_SIZE 7
#define MAG_DISTANCE_LIMIT 100

class Bomb : public MovingObject {
  double bomb_start_x;
  double bomb_start_y;
  double release_speed;
  double release_angle_deg;
  double bomb_size;
  double bomb_ax;
  double bomb_ay;

  //moving parts
  Circle bomb_circle;

  public :
    Bomb (double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    bomb_ax = argax;
    bomb_ay = argay;
    initBomb();
  }

  void initBomb();
  void resetBomb();

}; // End class Bomb

void Bomb :: initBomb(){
  bomb_start_x = PLAY_X_START + rand()%PLAY_X_WIDTH;
  bomb_start_y = PLAY_Y_HEIGHT - rand()%PLAY_Y_HEIGHT;
  bomb_circle.reset(bomb_start_x, bomb_start_y, BOMB_SIZE);
  bomb_circle.setColor(COLOR("black"));
  bomb_circle.setFill(true);
  addPart(&bomb_circle);

}

void Bomb :: resetBomb(){
  double bomb_speed = 60*(1 + rand()%3);
  double bomb_angle_deg = 10*(rand()%30);
  bomb_start_x = PLAY_X_START + rand()%PLAY_X_WIDTH;
  bomb_start_y = PLAY_Y_HEIGHT - rand()%PLAY_Y_HEIGHT;
  bomb_ax = 0;
  bomb_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(bomb_start_x, bomb_start_y, bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);
}// End class Bomb functions

class Random_Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Random_Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void resetCoin();

}; // End class Random_Coin



void Random_Coin::initCoin() {
  coin_start_x = PLAY_X_START+rand()%PLAY_X_WIDTH;
  coin_start_y = PLAY_Y_HEIGHT-rand()%PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("yellow"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Random_Coin::resetCoin() {
  double coin_speed = COIN_SPEED*(1+rand()%2);
  double coin_angle_deg = 10*(rand()%30);
  coin_start_x = PLAY_X_START+rand()%PLAY_X_WIDTH;
  coin_start_y = PLAY_Y_HEIGHT-rand()%PLAY_Y_HEIGHT;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

class Magnet : public MovingObject {
  double magnet_start_x;
  double magnet_start_y;
  double release_speed;
  double release_angle_deg;
  double magnet_ax;
  double magnet_ay;

  // Moving parts
  Circle magnet_circle;

 public:
 Magnet(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    magnet_ax = argax;
    magnet_ay = argay;
    initMagnet();
  }

  void initMagnet();
  void resetMagnet();

}; // End class magnet

void Magnet::initMagnet() {
  magnet_start_x = PLAY_X_START+rand()%PLAY_X_WIDTH;
  magnet_start_y = PLAY_Y_HEIGHT-rand()%PLAY_Y_HEIGHT;
  magnet_circle.reset(magnet_start_x, magnet_start_y, MAGNET_SIZE);
  magnet_circle.setColor(COLOR("red"));
  magnet_circle.setFill(true);
  addPart(&magnet_circle);
}

void Magnet::resetMagnet() {
  double magnet_speed = MAGNET_SPEED*(1+rand()%2);
  double magnet_angle_deg = 10*(rand()%30);
  magnet_start_x = PLAY_X_START+rand()%PLAY_X_WIDTH;
  magnet_start_y = PLAY_Y_HEIGHT-rand()%PLAY_Y_HEIGHT;
  magnet_ax = 0;
  magnet_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(magnet_start_x, magnet_start_y, magnet_speed, magnet_angle_deg, magnet_ax, magnet_ay, paused, rtheta);
}

class Lasso : public MovingObject {
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_line;
  Line lasso_band;

  // State info
  public:
  bool lasso_looped;
  Random_Coin *the_coin1;
  Random_Coin *the_coin2;
  Random_Coin *the_coin3;
  Bomb *the_bomb;
  Magnet *the_magnet;

  void initLasso();
 public:
 Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }

  int num_coins;
  void draw_lasso_band();
  void yank();
  void loopit();
  void addAngle(double angle_deg);
  void addSpeed(double speed);

  void nextStep(double t);
  void check_for_coin1(Random_Coin *coinPtr);
  void check_for_coin2(Random_Coin *coinPtr);
  void check_for_coin3(Random_Coin *coinPtr);
  void check_for_bomb(Bomb *bombPtr);
  void check_for_magnet(Magnet *magnetPtr);
  int getNumCoins() { return num_coins; }

  int level_number;

  bool magnetised;
  void magnetise();
  void demagnetise();

  //magnet timer
  int magnet_timer;

}; // End class Lasso

#endif

//coin.h

void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("yellow"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin() {
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}

//lasso.cpp

void Lasso::draw_lasso_band() {
  double len = (release_speed/MAX_RELEASE_SPEED)*LASSO_BAND_LENGTH;
  double arad = release_angle_deg*PI/180.0;
  double xlen = len*cos(arad);
  double ylen = len*sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x-xlen), (lasso_start_y+ylen));
  lasso_band.setThickness(LASSO_THICKNESS);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso() {
  lasso_start_x = (PLAY_X_START+LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT-LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("red"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setColor(COLOR("black"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;
  the_coin1 = NULL;
  the_coin2 = NULL;
  the_coin3 = NULL;
  the_bomb = NULL;

  the_magnet = NULL;
  magnet_timer = 0;
  magnetised = false;
  num_coins = 0;
  level_number = 1;

  lasso_line.reset(lasso_start_x, lasso_start_y, lasso_start_x, lasso_start_y);
  lasso_line.setColor(COLOR("black"));

  lasso_band.setColor(COLOR("blue"));
  draw_lasso_band();

} // End Lasso::initLasso()

void Lasso::yank() {
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE/2);
  lasso_loop.setFill(true);
  lasso_looped = false;
  if(the_coin1 != NULL) {
    num_coins++;
    the_coin1->resetCoin();
    the_coin1=NULL;//bug1
  }
  if(the_coin2 != NULL) {
    num_coins++;
    the_coin2->resetCoin();
    the_coin2=NULL;
  }
  if(the_coin3 != NULL){
    num_coins++;
    the_coin3->resetCoin();
    the_coin3 = NULL;
  }
  if(the_bomb != NULL){
    if(num_coins>1) num_coins -= 2;
    else num_coins = 0;
    the_bomb->resetBomb();
    the_bomb=NULL;
  }
  if(the_magnet != NULL){
    the_magnet->resetMagnet();
    the_magnet = NULL;
  }

} // End Lasso::yank()

void Lasso::loopit() {
  if(lasso_looped || isPaused()) { return; } // Already looped or paused
  lasso_loop.reset(getXPos(), getYPos(), LASSO_RADIUS);
  lasso_loop.setFill(false);
} // End Lasso::loopit()

void Lasso::addAngle(double angle_deg) {
  release_angle_deg += angle_deg;
  if(release_angle_deg < MIN_RELEASE_ANGLE_DEG) { release_angle_deg = MIN_RELEASE_ANGLE_DEG; }
  if(release_angle_deg > MAX_RELEASE_ANGLE_DEG) { release_angle_deg = MAX_RELEASE_ANGLE_DEG; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) {
  release_speed += speed;
  if(release_speed < MIN_RELEASE_SPEED) { release_speed = MIN_RELEASE_SPEED; }
  if(release_speed > MAX_RELEASE_SPEED) { release_speed = MAX_RELEASE_SPEED; }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime) {
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if(getYPos() > PLAY_Y_HEIGHT || getYPos() < 0) { yank(); }
  if(getXPos() < PLAY_X_START || getXPos() > WINDOW_X) {yank();}
  lasso_line.reset(lasso_start_x, lasso_start_y, getXPos(), getYPos());
} // End Lasso::nextStep()

void Lasso::check_for_coin1(Random_Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin1 = coinPtr;
    the_coin1->getAttachedTo(this);
  }
} // End Lasso::check_for_coin1()

void Lasso::check_for_coin2(Random_Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin2 = coinPtr;
    the_coin2->getAttachedTo(this);
  }
} // End Lasso::check_for_coin2()

void Lasso::check_for_coin3(Random_Coin *coinPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  double xdiff = (lasso_x - coin_x);
  double ydiff = (lasso_y - coin_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_coin3 = coinPtr;
    the_coin3->getAttachedTo(this);
  }
} // End Lasso::check_for_coin3()

void Lasso::check_for_bomb(Bomb *bombPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double bomb_x = bombPtr->getXPos();
  double bomb_y = bombPtr->getYPos();
  double xdiff = (lasso_x - bomb_x);
  double ydiff = (lasso_y - bomb_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    the_bomb = bombPtr;
    the_bomb->getAttachedTo(this);
  }
} // End Lasso::check_for_bomb()

void Lasso::check_for_magnet(Magnet *magnetPtr) {
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double magnet_x = magnetPtr->getXPos();
  double magnet_y = magnetPtr->getYPos();
  double xdiff = (lasso_x - magnet_x);
  double ydiff = (lasso_y - magnet_y);
  double distance = sqrt((xdiff*xdiff)+(ydiff*ydiff));
  if(distance <= LASSO_RADIUS) {
    magnetPtr->getAttachedTo(this);
    the_magnet = magnetPtr;
    magnetise();
  }
} // End Lasso::check_for_magnet()

void Lasso::magnetise(){
  magnet_timer = 400;//lasts for 20 seconds
  magnetised = true;
}

void Lasso::demagnetise(){
  magnet_timer = 0;
  magnetised = false;
}

void retry(Lasso *lassoPtr){
  lassoPtr->level_number = 1;
  lassoPtr->num_coins = 0;
  if(lassoPtr->magnetised) lassoPtr->demagnetise();
  lassoPtr->yank();
  //resetting level, magnet and score
}

void retry_text(Lasso *lassoPtr){
  Text retry1(400, 200, "YOU LOST");
  Text retry2(400, 235, "Press: r to retry");
  Text retry3(400, 270, "Press: q to quit");
  Rectangle retry_rect(400, 235, 180, 90);

  XEvent e;
    while(true){
      nextEvent(e);
      char c = charFromEvent(e);

      switch(c){
        case 'r': retry(lassoPtr);
        break;

        case 'q': exit(0);
        break;
      }
      if(c=='r' ) break;
    }
}

void congrats(Lasso *lassoPtr){
  Text congrats1(400, 200, "CONGRATULATIONS");
  Text congrats2(400, 235, "Press: q to quit");
  Text congrats3(400, 270, "Press: p to play again");
  Rectangle congrats_rect(400, 235, 250, 90);

  XEvent e;
    while(true){
      nextEvent(e);
      char c = charFromEvent(e);

      switch(c){
        case 'q': exit(0);
        break;

        case 'p': retry(lassoPtr);
        break;
      }
      if(c=='p' || c=='q') break;
    }
}

void next_level(Lasso *lassoPtr){
  lassoPtr->num_coins=0;
  if(lassoPtr->magnetised) lassoPtr->demagnetise();
  //resetting score and magnet
}

void next_level_text(Lasso *lassoPtr){
  Text nextLevel1(400, 200, "YOU HAVE FINISHED THE LEVEL");
  Text nextLevel2(400, 235, "Press: p to play next level");
  Text nextLevel3(400, 270, "Press: q to quit");
  Rectangle nextLevelRect(400, 235, 250, 90);

  XEvent e;
    while(true){
      nextEvent(e);
      char c = charFromEvent(e);


      switch(c){
        case 'q': exit(0);
        break;

        case 'p': next_level(lassoPtr);
        break;
      }
      if(c=='p' || c=='q') break;
    }
}

void help(){

  Text help_index1(400,200,"press: t to shoot");
  Text help_index2(400,235,"press: y to yank , l to loop");
  Text help_index3(400,270,"press: [ to add angle, ] to decrease angle");
  Text help_index4(400,305,"press:- to decrease speed , = to add speed" );
  Text help_index5(400,340,"don't catch bombs , catch magnets and coins");
  Text return_to_game(400,375,"PRESS r to return");
  Rectangle r(400,290,300,195);

  XEvent e;
  while(true){
  nextEvent(e);
  char c = charFromEvent(e);
    if(c == 'r') break;
  }
  return;
}

main_program {

  int Score_Needed = 2;

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  double release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  Text help_text1(50,50,"press h for");
  Text help_text2(50,70,"HELP");

  //level_indicator
  char Level_Indicator[256];
  sprintf(Level_Indicator,"LEVEL: %d",lasso.level_number);
  Text Level_Number(50, 100, Level_Indicator);

  //time_indicator
  int time_scaled = 500*(4-lasso.level_number);
  char time_string[256];
  sprintf(time_string, "TIME LEFT: %d", time_scaled/20);
  Text time_remaining(500, 520, time_string);

  //cmd indicator
  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);

  //score indicator
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+50, coinScoreStr);

  //required score indicator
  char ScoreNeededStr[256];
  sprintf(ScoreNeededStr, "SCORE NEEDED: %d", Score_Needed*lasso.level_number);
  Text ScoreNeededText(500, 550, ScoreNeededStr);

  //magnet timer
  char magnetStr[256];
  sprintf(magnetStr,"Time left on magnet: %d",lasso.magnet_timer/20);
  Text MagnetTimeLeft(500, 580, magnetStr);

  paused = true; rtheta = true;
  double coin_speed = COIN_SPEED*(1+rand()%2);
  double coin_angle_deg = 10*(1+rand()%30);
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Random_Coin coin1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Random_Coin coin2(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Random_Coin coin3(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

  double bomb_speed = BOMB_SPEED*(1+rand()%3);
  double bomb_angle_deg = 10*(1+rand()%30);
  double bomb_ax = 0;
  double bomb_ay = COIN_G;
  Bomb bomb(bomb_speed, bomb_angle_deg, bomb_ax, bomb_ay, paused, rtheta);

  double magnet_speed = MAGNET_SPEED;
  double magnet_angle_deg = 10*(1+rand()%30);
  double magnet_ax = 0;
  double magnet_ay = COIN_G;
  Magnet magnet(magnet_speed, magnet_angle_deg, magnet_ax, magnet_ay, paused, rtheta);

  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit

  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
      if(!lasso.lasso_looped&&!lasso.isPaused()){
	  lasso.check_for_coin1(&coin1);
	  lasso.check_for_coin2(&coin2);
	  lasso.check_for_coin3(&coin3);
	  lasso.check_for_bomb(&bomb);
	  lasso.check_for_magnet(&magnet);
      lasso.lasso_looped = true;
    }
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case '-':
	if(lasso.isPaused()) { lasso.addSpeed(-RELEASE_SPEED_STEP); }
	break;
	  case 'h':
    help();
    break;
      case '=':
	if(lasso.isPaused()) { lasso.addSpeed(+RELEASE_SPEED_STEP); }
	break;
      case 'q':
	exit(0);
      default:
	break;
      }
    }

    //making coins get attracted to lasso
    if(lasso.magnetised){
      lasso.magnet_timer -=3;
      double lasso_x = lasso.getXPos();
      double lasso_y = lasso.getYPos();
      double coin1_x = coin1.getXPos(), coin2_x = coin2.getXPos(), coin3_x = coin3.getXPos();
      double coin1_y = coin1.getYPos(), coin2_y = coin2.getYPos(), coin3_y = coin3.getYPos();
      double xdiff1 = (lasso_x - coin1_x), xdiff2 = (lasso_x - coin2_x), xdiff3 = (lasso_x - coin3_x);
      double ydiff1 = (lasso_y - coin1_y), ydiff2 = (lasso_y - coin2_y), ydiff3 = (lasso_y - coin3_y);
        if(sqrt(xdiff1*xdiff1+ydiff1*ydiff1) < MAG_DISTANCE_LIMIT){
                coin1.vx += 1.2*xdiff1; coin1.vy += 1.2*ydiff1;
        }
        if(sqrt(xdiff2*xdiff2+ydiff2*ydiff2) < MAG_DISTANCE_LIMIT){
                coin2.vx += 1.2*xdiff2; coin1.vy += 1.2*ydiff2;
        }
        if(sqrt(xdiff3*xdiff3+ydiff3*ydiff3) < MAG_DISTANCE_LIMIT){
                coin3.vx += 1.2*xdiff3; coin3.vy += 1.2*ydiff3;
        }

      if(lasso.magnet_timer < 1) lasso.demagnetise();
    }

    sprintf(magnetStr,"Time left on magnet: %d",lasso.magnet_timer/20);
    MagnetTimeLeft.setMessage(magnetStr);


    lasso.nextStep(stepTime);

    coin1.nextStep(stepTime);
    if(coin1.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin1.unpause();
      }
    }

    if(coin1.getYPos() > PLAY_Y_HEIGHT || coin1.getYPos() <0) {
      coin1.resetCoin();
      last_coin_jump_end = currTime;
    }

    if(coin1.getXPos() < PLAY_X_START || coin1.getXPos() > WINDOW_X){
      coin1.resetCoin();
      last_coin_jump_end = currTime;
    }

    coin2.nextStep(stepTime);
    if(coin2.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin2.unpause();
      }
    }

    if(coin2.getYPos() > PLAY_Y_HEIGHT || coin2.getYPos() <0) {
      coin2.resetCoin();
      last_coin_jump_end = currTime;
    }

    if(coin2.getXPos() < PLAY_X_START || coin2.getXPos() > WINDOW_X){
      coin2.resetCoin();
      last_coin_jump_end = currTime;
    }

    coin3.nextStep(stepTime);
    if(coin3.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	coin3.unpause();
      }
    }

    if(coin3.getYPos() > PLAY_Y_HEIGHT || coin3.getYPos() <0) {
      coin3.resetCoin();
      last_coin_jump_end = currTime;
    }

    if(coin3.getXPos() < PLAY_X_START || coin3.getXPos() > WINDOW_X){
      coin3.resetCoin();
      last_coin_jump_end = currTime;
    }

    bomb.nextStep(stepTime);
    if(bomb.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	bomb.unpause();
      }
    }

    if(bomb.getYPos() > PLAY_Y_HEIGHT || bomb.getYPos() <0) {
      bomb.resetBomb();
      last_coin_jump_end = currTime;
    }

    if(bomb.getXPos() < PLAY_X_START || bomb.getXPos() > WINDOW_X){
      bomb.resetBomb();
      last_coin_jump_end = currTime;
    }

        magnet.nextStep(stepTime);
    if(magnet.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	magnet.unpause();
      }
    }

    if(magnet.getYPos() > PLAY_Y_HEIGHT || magnet.getYPos() <0 ) {
      magnet.resetMagnet();
      last_coin_jump_end = currTime;
    }

    if(magnet.getXPos() < PLAY_X_START || magnet.getXPos() > WINDOW_X){
      magnet.resetMagnet();
      last_coin_jump_end = currTime;
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);

    stepCount++;
    currTime += stepTime;
    wait(stepTime);

    time_scaled -= 3;
    sprintf(time_string, "TIME LEFT: %d", time_scaled/20);
    time_remaining.setMessage(time_string);

    //changing levels
    if(lasso.getNumCoins() >= Score_Needed*lasso.level_number){
        lasso.level_number++;
        if(lasso.level_number == 4) congrats(&lasso);
        else next_level_text(&lasso);
        //resetting objects
        coin1.resetCoin();
        coin2.resetCoin();
        coin3.resetCoin();
        bomb.resetBomb();
        magnet.resetMagnet();
        //level text changer
        sprintf(Level_Indicator,"LEVEL: %d",lasso.level_number);
        Level_Number.setMessage(Level_Indicator);
        time_scaled = 500*(4-lasso.level_number);
        //score needed text changer
        sprintf(ScoreNeededStr, "SCORE NEEDED: %d", Score_Needed*lasso.level_number);
        ScoreNeededText.setMessage(ScoreNeededStr);

    }
    if(time_scaled < 1){
        if(lasso.getNumCoins() < Score_Needed*lasso.level_number){
          retry_text(&lasso);
          time_scaled = 500*(4-lasso.level_number);
          //resetting objects
          coin1.resetCoin();
          coin2.resetCoin();
          coin3.resetCoin();
          bomb.resetBomb();
          magnet.resetMagnet();
          //level text changer
          sprintf(Level_Indicator,"LEVEL: %d",lasso.level_number);
          Level_Number.setMessage(Level_Indicator);
          time_scaled = 500*(4-lasso.level_number);
          //score needed text changer
          sprintf(ScoreNeededStr, "SCORE NEEDED: %d", Score_Needed*lasso.level_number);
          ScoreNeededText.setMessage(ScoreNeededStr);

        }
    }

  } // End for(;;)

  wait(3);
} // End main_program
