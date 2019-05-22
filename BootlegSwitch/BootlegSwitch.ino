#include "Switch.cpp"
#include "SwitchActivity.cpp"
#include "ShootyGame.cpp"
#include "Skyrim.cpp"
#include "Minecraft.cpp"
#include "BrickBreaker.cpp"
#include "Froger.cpp"

int Window::width = 6;
int Window::height = 5;
int Window::brightness = 10;
Adafruit_NeoPixel* Window::screen = new Adafruit_NeoPixel();
Color** Window::pixels;// = Color[6][5];
Color Window::color = Color(255,255,255);

std::map<int,bool> Buttons::buttonLock = std::map<int,bool>();
queue<Note> Audio::notes = queue<Note>();

int loopTime = 10;

vector<SwitchActivity*> games;






void setup() {
  Serial.begin(9600);
  Buttons::begin();
  Window::begin(6,5);
  Audio::begin();

  Audio::tone(Audio::C*4,5);
  Audio::tone(Audio::C*5,5);
  Audio::tone(Audio::C*6,5);
  Audio::tone(Audio::C*8,5);

  // register games
  games.push_back(new ShootyGame());
  games.push_back(new Froger());
  //games.push_back(new Minecraft());
  games.push_back(new Skyrim());
  games.push_back(new Breaker());
}











SwitchActivity* homeActivity = new HomeActivity(&games);

SwitchActivity* activity = new StartupActivity();



void loop() {
  int t = millis();
  Audio::update();
  Buttons::update();

  if(activity == nullptr){
    Window::clear(Color(255,0,0));
  }
  else{
    int result = activity->update();
    activity->draw();
    if(result == SwitchActivity::HOME){
      activity = homeActivity;
    }
  }
  Window::display();

  t = millis() - t;
  delay(loopTime-t);
}







