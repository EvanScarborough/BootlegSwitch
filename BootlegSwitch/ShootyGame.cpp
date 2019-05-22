#ifndef SHOOTYGAME
#define SHOOTYGAME

#include "SwitchActivity.cpp"


class EnemyPlane{
public:
  int xp = 6;
  int yp = 3;

  int timer = 0;
  
  int speed = 10;
  Color c;

  EnemyPlane(){
    timer = speed;
    c = Color(255,0,0);
    yp = rand()%5;
  }

  bool update(){
    timer--;
    if(timer <= 0){
      xp--;
      timer = speed;
    }
    if(xp < 0) return true;
    return false;
  }

  void draw(){
    Window::setPixel(Point(xp,yp),c);
  }
};

class ShootyGame: public SwitchActivity{
public:
  bool paused = false;
  int yp = 2;
  int score = 0;

  vector<EnemyPlane> enemies;
  int timeBeforeEnemy = 20;
  int spawnRate = 140;
  static const int lowestSpawnRate = 16;

  int showScoreDelay = -1;
  bool showScore = false;

  int scoreCounter = 0;
  int scd = 5;
  
  virtual int update(){
    if(paused){
      if(showScoreDelay >= 0) showScoreDelay--;
      if(showScoreDelay == 0){
        showScore = true;
      }
      if(showScore){
        if(scoreCounter < score){
          scd--;
          if(scd <= 0){
            scd = 5;
            scoreCounter++;
            Audio::tone(Audio::D,2);
          }
        }
      }
      if(Buttons::pressed(Buttons::A)){
        reset();
      }
      return NONE;
    }

    for(int i = 0; i < enemies.size(); i++){
      if(enemies.at(i).xp == 0 && enemies.at(i).yp == yp){
        Audio::clear();
        Audio::tone(Audio::A/8,10);
        Audio::tone(Audio::A/4,10);
        Audio::tone(Audio::A/8,10);
        Audio::tone(Audio::A/4,10);
        paused = true;
        showScoreDelay = 60;
      }
      if(enemies.at(i).update()){
        enemies.erase(enemies.begin()+i);
        i--;
      }
    }
    timeBeforeEnemy--;
    if(timeBeforeEnemy <= 0){
      timeBeforeEnemy = spawnRate;
      spawnRate-=2;
      if(spawnRate < lowestSpawnRate) spawnRate = lowestSpawnRate;
      enemies.push_back(EnemyPlane());
      score++;
      Audio::tone(Audio::A*7,3);
      Audio::tone(Audio::A*6,3);
      Audio::tone(Audio::A*5,3);
    }
    
    if(Buttons::pressed(Buttons::UP)){
      yp--;
    }
    if(Buttons::pressed(Buttons::DOWN)){
      yp++;
    }
    if(yp < 0) yp = 4;
    if(yp > 4) yp = 0;
    

    return NONE;
  }



  
  virtual void draw(){
    if(showScore){
      Window::clear(Color(255,255,255));
      Color scoreColor[] = {Color(0,255,0),Color(0,0,255),Color(255,255,0),Color(255,0,0),Color(0,255,255),Color(255,0,255)};
      for(int i = 0; i < scoreCounter; i++){
        int c = 0;
        Point p(i%Window::width,i/Window::width);
        while(p.y >= 5){
          p.y-=5;
          c++;
        }
        Window::setPixel(p,scoreColor[c%6]);
      }
      return;
    }
    Window::clear(Color(255,150,0));
    Window::setPixel(Point(0,yp),Color(255,255,255));
    for(int i = 0; i < enemies.size(); i++){
      enemies.at(i).draw();
    }
  }



  
  virtual void drawIcon(){
    RectangleShape rect(1,1,4,3);
    rect.draw(Color(255,150,0));
  }
  virtual void reset(){
    paused = false;
    yp = 2;
    score = 0;
    enemies.clear();
    timeBeforeEnemy = 20;
    spawnRate = 140;
    showScoreDelay = -1;
    showScore = false;
    scoreCounter = 0;
    scd = 5;
  }
};







#endif
