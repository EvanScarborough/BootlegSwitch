#ifndef ACTIVITY
#define ACTIVITY

#include "Switch.cpp"



class SwitchActivity{
public:
  virtual int update(){return NONE;}
  virtual void draw(){}
  virtual void drawIcon(){}
  virtual void reset(){}

  static const int NONE = 0;
  static const int HOME = -1;
};





class StartupActivity: public SwitchActivity{
public:
  string s = "NINTEMBO";
  int t = 25;
  int l = 0;
  
  virtual int update(){
    l++;
    if(l >= (s.size())*t){
      return HOME;
    }
    return NONE;
  }
  
  virtual void draw(){
    Window::clear(Color(255,0,0));
    
    int charOn = l / t;
    if(charOn >= s.size()) charOn = s.size()-1;
    Letter::draw(s.at(charOn),Color(255,255,255));
  }
  virtual void drawIcon(){}
  virtual void reset(){l=0;}

};




class HomeActivity: public SwitchActivity{
public:
  int activityOn = 0;
  bool playing = false;

  vector<SwitchActivity*>* activities;

  HomeActivity(vector<SwitchActivity*>* a){
    activities = a;
  }

  bool askReset = false;
  
  virtual int update(){
    if(activities->size() == 0) return NONE;

    if(playing){
      int ret = activities->at(activityOn)->update();
      if(ret == HOME || Buttons::pressed(Buttons::HOME)){
        playing = false;
        Audio::clear();
        Audio::tone(Audio::C*8,5);
        Audio::tone(Audio::C*6,5);
        Audio::tone(Audio::C*5,5);
        Audio::tone(Audio::C*4,5);
      }
      return ret;
    }

    if(Buttons::down(Buttons::HOME)){
      if(Buttons::pressed(Buttons::UP)){
        Window::setBrightness(Window::brightness + 3);
      }
      if(Buttons::pressed(Buttons::DOWN)){
        Window::setBrightness(Window::brightness - 3);
      }
    }

    if(askReset){
      if(Buttons::pressed(Buttons::B)){
        askReset = false;
      }
      if(Buttons::pressed(Buttons::A)){
        askReset = false;
        activities->at(activityOn)->reset();
        Audio::tone(Audio::C*8,5);
        Audio::tone(Audio::C*6,5);
        Audio::tone(Audio::C*5,5);
        Audio::tone(Audio::C*4,5);
      }
      return NONE;
    }

    if(Buttons::pressed(Buttons::LEFT)){
      activityOn--;
      Audio::tone(Audio::C,2);
    }
    if(Buttons::pressed(Buttons::RIGHT)){
      activityOn++;
      Audio::tone(Audio::C,2);
    }
    if(activityOn < 0) activityOn = activities->size()-1;
    if(activityOn >= activities->size()) activityOn = 0;

    if(Buttons::pressed(Buttons::A)){
      Audio::tone(Audio::C*4,5);
      Audio::tone(Audio::C*5,5);
      Audio::tone(Audio::C*6,5);
      Audio::tone(Audio::C*8,5);
      playing = true;
    }
    
    if(Buttons::pressed(Buttons::B)){
      Audio::tone(Audio::C,5);
      Audio::rest(3);
      Audio::tone(Audio::C,5);
      askReset = true;
    }
    
    return NONE;
  }
  virtual void draw(){
    if(playing){
      activities->at(activityOn)->draw();
      return;
    }
    Window::clear(Color(255,255,255));
    Serial.println(activities->size());
    if(activities->size() > 0) activities->at(activityOn)->drawIcon();
    if(askReset){
      RectangleShape rect(4,0,2,2);
      rect.draw(Color(0,255,0));
      rect = RectangleShape(4,2,2,2);
      rect.draw(Color(255,0,0));
      return;
    }
  }
  virtual void drawIcon(){}
  virtual void reset(){}
};




#endif
