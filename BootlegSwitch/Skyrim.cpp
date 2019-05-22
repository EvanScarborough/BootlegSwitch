#ifndef SKYRIM
#define SKYRIM

#include "SwitchActivity.cpp"


class Skyrim: public SwitchActivity{
public:
  int timer = 0;
  int state = 0;
  int score = 0;
  virtual int update(){
    if(state == 0){
      if(timer == 100){
        Audio::tone(Audio::B/4,90);
        Audio::rest(60);
        Audio::tone(Audio::B/4,40);
        Audio::rest(5);
        Audio::tone(Audio::B/4,120);
      }
      timer++;
      if(timer >= 800){
        state = 1;
        playSong();
      }
      if(Buttons::pressed(Buttons::A)){
        state = 1;
        Audio::clear();
      }
    }
    if(state == 1){
      if(Buttons::pressed(Buttons::A)){
        state = 2;
        Audio::clear();
      }
    }
    if(state == 2){
      
    }
    return NONE;
  }



  
  virtual void draw(){
    Window::clear(Color(0,0,0));
    if(state == 0){
      int b = (timer) / 7;
      if(b < 0) b = 0;
      bool L[] = {
          0,0,0,0,0,0,
          0,1,1,1,0,0,
          1,1,1,1,1,1,
          0,1,1,0,0,0,
          0,0,0,0,0,0,};
      Window::drawMap(L,Color(b,b,b));
    }
    if(state == 1){
      bool L[] = {
          0,0,1,0,0,0,
          0,1,1,1,0,0,
          0,1,0,1,0,1,
          0,1,1,1,0,1,
          1,0,1,0,0,0,};
      Window::drawMap(L,Color(150,150,150));
    }
    if(state == 2){
      
    }
  }



  
  virtual void drawIcon(){
    RectangleShape rect(1,1,4,3);
    rect.draw(Color(90,90,90));
  }
  virtual void reset(){
    timer = 0;
    state = 0;
    score = 0;
  }


  void playSong(){
    Audio::tone(Audio::B/2,130,20);
    Audio::tone(Audio::E/2,130,20);
    Audio::tone(Audio::B,130,20);
    Audio::tone(Audio::A,130,20);

    int beat = 16;
    Audio::tone(Audio::D,beat);
    Audio::tone(Audio::Cs,beat);
    Audio::tone(Audio::D,beat,beat*2);

    Audio::tone(Audio::D,beat);
    Audio::tone(Audio::Cs,beat);
    Audio::tone(Audio::D,beat,beat*2);

    Audio::tone(Audio::Cs,beat);
    Audio::tone(Audio::D,beat);
    Audio::tone(Audio::E,beat,beat);
    Audio::tone(Audio::D,beat,beat);
    Audio::tone(Audio::Cs,beat,beat);
    Audio::tone(Audio::B,beat,beat*3);

    Audio::tone(Audio::B,beat);
    Audio::tone(Audio::A,beat);
    Audio::tone(Audio::B,beat,beat*2);

    Audio::tone(Audio::B,beat);
    Audio::tone(Audio::A,beat);
    Audio::tone(Audio::B,beat,beat*2);

    Audio::tone(Audio::A,beat);
    Audio::tone(Audio::B,beat);
    Audio::tone(Audio::Cs,beat,beat);
    Audio::tone(Audio::D,beat,beat);
    Audio::tone(Audio::A,beat,beat);
    Audio::tone(Audio::B,beat,beat*3);

    Audio::tone(Audio::D,beat);
    Audio::tone(Audio::Cs,beat);
    Audio::tone(Audio::D,beat,beat);
    Audio::tone(Audio::D,beat,beat);
    Audio::tone(Audio::Cs,beat,beat);
    Audio::tone(Audio::D,beat,beat*3);

    Audio::tone(Audio::Cs,beat);
    Audio::tone(Audio::D,beat);
    Audio::tone(Audio::E,beat,beat);
    Audio::tone(Audio::D,beat,beat);
    Audio::tone(Audio::Cs,beat,beat);
    Audio::tone(Audio::B,beat,beat*3);

    Audio::tone(Audio::B,beat);
    Audio::tone(Audio::A,beat);
    Audio::tone(Audio::B,beat,beat*2);

    Audio::tone(Audio::B,beat);
    Audio::tone(Audio::A,beat);
    Audio::tone(Audio::B,beat,beat*2);

    Audio::tone(Audio::A,beat);
    Audio::tone(Audio::B,beat);
    Audio::tone(Audio::Cs,beat,beat);
    Audio::tone(Audio::D,beat,beat);
    Audio::tone(Audio::A,beat,beat);
    Audio::tone(Audio::B,beat,beat*3);
  }
};





#endif
