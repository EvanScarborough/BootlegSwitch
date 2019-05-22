#ifndef FROGER
#define FROGER

#include "SwitchActivity.cpp"
#include "Switch.cpp"

class Frog{
public:
  Point p;
  void move(){
    if(Buttons::pressed(Buttons::UP) && p.y > 0){
      p.y--;
      Audio::tone(Audio::C/2,5);
      Audio::tone(Audio::C*3,1);
    }
    if(Buttons::pressed(Buttons::DOWN) && p.y < 4){
      p.y++;
      Audio::tone(Audio::C/2,5);
      Audio::tone(Audio::C*3,1);
    }
    if(Buttons::pressed(Buttons::LEFT) && p.x > 0){
      p.x--;
      Audio::tone(Audio::C/2,5);
      Audio::tone(Audio::C*3,1);
    }
    if(Buttons::pressed(Buttons::RIGHT) && p.x < 5){
      p.x++;
      Audio::tone(Audio::C/2,5);
      Audio::tone(Audio::C*3,1);
    }
  }
  void draw(){
    Window::setPixel(p,Color(0,255,0));
  }
};

class Lane{
public:
  virtual int update(){return 0;}
  virtual void draw(int x){}
  virtual bool isSafe(int y){
    return true;
  }
};



class CarLane: public Lane{
public:
  vector<int> cars;
  int speed = 0;
  int count = 0;
  bool dir = 0;
  int spawnPercent = 20;
  virtual int update(){
    count--;
    if(count == 0){
      if(dir){
        for(int i = cars.size()-1; i > 0; i--){
          cars.at(i) = cars.at(i-1);
        }
        if(rand()%100<spawnPercent){
          cars.at(0) = rand()%3+1;
        }
        else{
          cars.at(0) = 0;
        }
      }
      else{
        for(int i = 0; i < cars.size()-1; i++){
          cars.at(i) = cars.at(i+1);
        }
        if(rand()%100<spawnPercent){
          cars.at(cars.size()-1) = rand()%3+1;
        }
        else{
          cars.at(cars.size()-1) = 0;
        }
      }
      count = speed;
    }
    return 0;
  }
  CarLane(){
    for(int i = 0; i < 5; i++){
      cars.push_back(0);
    }
    cars.at(rand()%5)=rand()%3+1;
    speed = 40 + rand()%10;
    dir = rand()%2;
    count = speed;
  }
  virtual void draw(int x){
    Color carColors[] = {Color(255,0,0),Color(255,0,0),Color(255,0,0)};
    for(int i = 0; i < 5; i++){
      if(cars.at(i)==0) Window::setPixel(x,i,Color(0,0,0));
      else Window::setPixel(x,i,carColors[cars.at(i)-1]);
    }
  }
  virtual bool isSafe(int y){
    return cars.at(y) == 0;
  }
};




class WaterLane: public Lane{
public:
  vector<int> logs;
  int speed = 0;
  int count = 0;
  bool dir = 0;
  int spawnPercent = 40;
  virtual int update(){
    count--;
    if(count == 0){
      if(dir){
        for(int i = logs.size()-1; i > 0; i--){
          logs.at(i) = logs.at(i-1);
        }
        if(rand()%100<spawnPercent){
          logs.at(0) = 1;
        }
        else{
          logs.at(0) = 0;
        }
      }
      else{
        for(int i = 0; i < logs.size()-1; i++){
          logs.at(i) = logs.at(i+1);
        }
        if(rand()%100<spawnPercent){
          logs.at(logs.size()-1) = 1;
        }
        else{
          logs.at(logs.size()-1) = 0;
        }
      }
      count = speed;
      return dir-(dir==0);
    }
    return 0;
  }
  WaterLane(){
    for(int i = 0; i < 5; i++){
      logs.push_back(0);
    }
    logs.at(rand()%5)=1;
    logs.at(rand()%5)=1;
    logs.at(rand()%5)=1;
    speed = 70 + rand()%30;
    dir = rand()%2;
    count = speed;
  }
  virtual void draw(int x){
    for(int i = 0; i < 5; i++){
      if(logs.at(i)==0) Window::setPixel(x,i,Color(0,0,255));
      else Window::setPixel(x,i,Color(150,100,0));
    }
  }
  virtual bool isSafe(int y){
    if(y < 0 || y >= logs.size()) return false;
    return logs.at(y) == 1;
  }
};








class Froger: public SwitchActivity{
public:
  Frog frog;
  vector<Lane*> lanes;
  int state = 0;
  int stateTimer = -1;
  
  virtual int update(){
    if(state == 0){
      frog.move();
      for(int i = 0; i < lanes.size(); i++){
        int r = lanes.at(i)->update();
        if(i == frog.p.x){
          if(r == 1) frog.p.y++;
          if(r == -1) frog.p.y--;
        }
      }
      if(!lanes.at(frog.p.x)->isSafe(frog.p.y) || frog.p.y < 0 || frog.p.y >= 5){
        state = 1;
        Audio::tone(Audio::B/2,20);
        Audio::tone(Audio::E/3,10);
        Audio::tone(Audio::B/4,6);
        stateTimer = 30;
      }
      if(frog.p.x == 5){
        state = 2;
        Audio::tone(Audio::C/2,20);
        Audio::tone(Audio::C,20);
        Audio::tone(Audio::C*4,40);
        stateTimer = 30;
      }
    }
    if(state == 1){
      stateTimer--;
      if(stateTimer == 0){
        reset();
      }
    }
    if(state == 2){
      stateTimer--;
      if(stateTimer == 0){
        reset();
      }
    }
  }


  virtual void draw(){
    if(state == 0){
      Window::clear(Color(100,255,100));
      for(int i = 0; i < 6; i++){
        if(lanes.size() <= i) break;
        lanes.at(i)->draw(i);
      }
      frog.draw();
    }
    if(state == 1){
      Window::clear(Color(255,0,0));
    }
    if(state == 2){
      Window::clear(Color(0,255,0));
    }
  }


  Froger(){
    frog.p = Point(0,2);
    genLevel();
  }
  void genLevel(){
    lanes.clear();
    lanes.push_back(new Lane());
    for(int i = 0; i < 4; i++){
      if(rand()%2==0) lanes.push_back(new WaterLane());
      else lanes.push_back(new CarLane());
    }
    lanes.push_back(new Lane());
  }
  
  virtual void drawIcon(){
    RectangleShape rect(1,1,4,3);
    rect.draw(Color(0,255,0));
  }
  virtual void reset(){
    frog.p = Point(0,2);
    state = 0;
    genLevel();
    stateTimer = -1;
  }
};





#endif
