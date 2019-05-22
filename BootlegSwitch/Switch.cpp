#ifndef Switch
#define Switch

#include <Arduino.h>

#include <StandardCplusplus.h>
#include <Adafruit_NeoPixel.h>
#include <map>
#include <vector>
#include <queue>


using namespace std;

class Point{
public:
  int x = 0;
  int y = 0;
  Point(int xx, int yy){
    x = xx;
    y = yy;
  }
  Point(){}
};


class Color{
public:
  int r = 0;
  int g = 0;
  int b = 0;
  Color(){}
  Color(int rr, int gg, int bb){
    while(rr > 255) rr-=255;
    while(rr < 0) rr+=255;
    while(gg > 255) gg-=255;
    while(gg < 0) gg+=255;
    while(bb > 255) bb-=255;
    while(bb < 0) bb+=255;
    r = rr; g = gg; b = bb;
  }
  void set(Color c){
    r = c.r;
    g = c.g;
    b = c.b;
  }
  Color getScaled(int brightness){
    return Color(r*brightness/255,g*brightness/255,b*brightness/255);
  }
//  void print(){
//    Serial.print(r); Serial.print(" ");Serial.print(g); Serial.print(" ");Serial.println(b);
//  }
};


class Window{
public:
	static const int pixelPin = A12;
	
	static int width;
	static int height;
	static Adafruit_NeoPixel* screen;
  static bool isValid(int x, int y){return x >= 0 && x < width && y >= 0 && y < height;}
  static bool isValid(Point p){return p.x >= 0 && p.x < width && p.y >= 0 && p.y < height;}

  static Color color;
  static void setColor(Color c){color.set(c);}

  static int brightness;

  static Color** pixels;
  
	static void begin(int w, int h){
    width = w;
    height = h;
    screen = new Adafruit_NeoPixel(w*h, pixelPin, NEO_GRB + NEO_KHZ800);
		screen->begin();
    setBrightness(brightness);
    
    pixels = new Color*[w];
    for(int i = 0; i < w; i++){
      pixels[i] = new Color[h];
    }
    
	}

  static display(){
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        Color c = pixels[i][j];//.getScaled(brightness);
        screen->setPixelColor(j*width+i,screen->Color(c.r,c.g,c.b));
      }
    }
    screen->show();
  }
  
  static void setBrightness(int b){
    if(b < 0) b = 0;
    if(b > 255) b = 255;
    brightness = b;
    screen->setBrightness(b);
  }

  static void clear(Color c){
    for(int i = 0; i < width; i++){
      for(int j = 0; j < height; j++){
        pixels[i][j].set(c);
      }
    }
  }
  static void clear(){clear(Color(0,0,0));}

  static void setPixel(int x, int y, Color c){if(!isValid(x,y))return;pixels[x][y].set(c);}
  static void setPixel(Point p, Color c){if(!isValid(p))return;pixels[p.x][p.y].set(c);}
  static void drawMap(bool* m, int n, Color c){
    for(int i = 0; i < n; i++){
      Point p(i%width,i/width);
      if(!isValid(p)) break;
      if(m[i]) setPixel(p,c);
    }
  }
  static void drawMap(bool* m, Color c){drawMap(m,width*height,c);}
};




class Buttons{
public:
  static const int UP = 2;
  static const int RIGHT = 3;
  static const int DOWN = 4;
  static const int LEFT = 5;

  static const int A = 9;
  static const int B = 10;
  static const int HOME = 8;

  static std::map<int,bool> buttonLock;

  static void update(){
    for(auto a:buttonLock){
      if(!digitalRead(a.first)){
        //buttonLock.insert(a.first,false);
        buttonLock[a.first] = false;
      }
    }
  }

  static void begin(){
    pinMode(UP,INPUT);
    pinMode(RIGHT,INPUT);
    pinMode(DOWN,INPUT);
    pinMode(LEFT,INPUT);
  
    pinMode(A,INPUT);
    pinMode(B,INPUT);
    pinMode(HOME,INPUT);
  }

  static bool down(int b){
    return digitalRead(b);
  }

  static bool pressed(int b){
    if(buttonLock.find(b) == buttonLock.end()){
      buttonLock[b] = false;
    }
    if(digitalRead(b)){
      bool ret = digitalRead(b) && !buttonLock[b];
      buttonLock[b] = true;
      return ret;
    }
    return false;
  }
};












enum NoteType{TONE,REST};
class Note{
public:
  NoteType type = TONE;
  double frequency;
  int time;
  Note(double freq, int t){
    frequency = freq;
    time = t;
  }
  Note(int t){
    type = REST;
    time = t;
  }
  void play(int audioPin){
    if(type==TONE) tone(audioPin,frequency);
    
  }
};

class Audio{
public:
  static const int audioPin = A8;
  static queue<Note> notes;

  static void begin(){
    pinMode(audioPin,OUTPUT);
  }
  
  static void clear(){
    while(!notes.empty()){
      notes.pop();
    }
  }
  static void tone(double freq, int t){
    notes.push(Note(freq,t));
    if(notes.size() == 1){
      notes.front().play(audioPin);
    }
  }
  static void tone(double freq, int t, int rafter){
    notes.push(Note(freq,t));
    if(notes.size() == 1){
      notes.front().play(audioPin);
    }
    rest(rafter);
  }
  static void rest(int t){
    notes.push(Note(t));
  }
  
  static void update(){
    if(notes.empty()) return;
    notes.front().time--;
    if(notes.front().time <= 0){
      notes.pop();
      noTone(audioPin);
      if(!notes.empty()){
        notes.front().play(audioPin);
      }
    }
  }



  static const double Gs = 415.305;
  static const double G = 391.995;
  static const double Fs = 369.994;
  static const double F = 349.228;
  static const double E = 329.628;
  static const double Ds = 311.127;
  static const double D = 293.665;
  static const double Cs = 277.183;
  static const double C = 261.626;
  static const double B = 246.942;
  static const double As = 233.082;
  static const double A = 220.000;
};










class Letter{
public:
  
  static void draw(char n, Color c){
    if(n == 'A'){
      bool L[] = {
        0,0,1,0,0,0,
        0,1,0,1,0,0,
        1,0,0,0,1,0,
        1,1,1,1,1,0,
        1,0,0,0,1,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'B'){
      bool L[] = {
        1,1,1,1,0,0,
        1,0,0,0,1,0,
        1,1,1,1,0,0,
        1,0,0,0,1,0,
        1,1,1,1,0,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'E'){
      bool L[] = {
        1,1,1,1,1,0,
        1,0,0,0,0,0,
        1,1,1,0,0,0,
        1,0,0,0,0,0,
        1,1,1,1,1,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'I'){
      bool L[] = {
        1,1,1,1,1,0,
        0,0,1,0,0,0,
        0,0,1,0,0,0,
        0,0,1,0,0,0,
        1,1,1,1,1,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'M'){
      bool L[] = {
        1,0,0,0,1,0,
        1,1,0,1,1,0,
        1,0,1,0,1,0,
        1,0,0,0,1,0,
        1,0,0,0,1,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'N'){
      bool L[] = {
        1,0,0,0,1,0,
        1,1,0,0,1,0,
        1,0,1,0,1,0,
        1,0,0,1,1,0,
        1,0,0,0,1,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'O'){
      bool L[] = {
        0,1,1,1,0,0,
        1,0,0,0,1,0,
        1,0,0,0,1,0,
        1,0,0,0,1,0,
        0,1,1,1,0,0,};
        Window::drawMap(L,c);
    }
    else if(n == 'T'){
      bool L[] = {
        1,1,1,1,1,0,
        0,0,1,0,0,0,
        0,0,1,0,0,0,
        0,0,1,0,0,0,
        0,0,1,0,0,0,};
        Window::drawMap(L,c);
    }
    
  }

};


class RectangleShape{
public:
  int top = 0;
  int left = 0;
  int width = 0;
  int height = 0;

  RectangleShape(){}
  RectangleShape(int l, int t, int w, int h){
    top = t; left = l; width = w; height = h;
  }
  
  void draw(Color c){
    for(int i = left; i < left+width; i++){
      for(int j = top; j < top+height; j++){
        Window::setPixel(i,j,c);
      }
    }
  }
};



#endif
