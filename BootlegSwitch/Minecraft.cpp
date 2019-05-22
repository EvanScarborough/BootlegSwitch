#ifndef MINECRAFT
#define MINECRAFT

#include "SwitchActivity.cpp"

class BlockType{
};

class Minecraft: public SwitchActivity{
public:
  int state = 0;
  
  virtual int update(){
    if(state == 0){

      state = 1;
    }
  }



  
  virtual void draw(){
    
  }



  
  virtual void drawIcon(){
    RectangleShape rect(1,1,4,3);
    rect.draw(Color(135,85,0));
    rect = RectangleShape(1,1,4,1);
    rect.draw(Color(0,250,0));
  }
  virtual void reset(){
    state = 0;
  }
};





#endif
