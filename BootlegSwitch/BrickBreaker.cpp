#ifndef BREAKER
#define BREAKER

#include "SwitchActivity.cpp"
#include "Switch.cpp"

class Block {
  public:
    Point pos;
    int Live = 1;

    Block(int x, int y) {
      pos = Point(x, y);
    }

    void draw() {
      Window::setPixel(pos, Color(255, 0, 0));
    }
};

class Breaker: public SwitchActivity {
  public:
    int brickX = 0;
    int brickY = 4;
    int ballX = 0;
    int ballY = 3;
    int ballUp = 1;
    int ballDown = 0;
    int ballLeft = 0;
    int ballRight = 1;
    int Lose = 0;
    int Level = 1;

    vector<Block> blocks;

    int updateTimer = 50;
    int UPDATETIME = 50  - Level * 2;

    virtual int update() {
      //

      updateTimer--;
      if (updateTimer <= 0) {

        // Update
        if (ballUp == 1 && ballRight == 1 && ballY != 0  && ballX != 5) {
          ballX += 1;
          ballY -= 1;

        }
        if (ballDown == 1 && ballRight == 1 && ballY != 4  && ballX != 5) {
          ballX += 1;
          ballY += 1;
        }
        if (ballDown == 1 && ballLeft == 1 && ballY != 4  && ballX != 0) {
          ballX -= 1;
          ballY += 1;
        } if (ballUp == 1 && ballLeft == 1 && ballY != 0  && ballX != 0) {
          ballX -= 1;
          ballY -= 1;
        }

        if (ballY == 0) {
          ballUp = 0;
          ballDown = 1;
        }
        if (ballY == 4) {
          ballUp = 1;
          ballDown = 0;
        } if (ballX == 0) {
          ballRight = 1;
          ballLeft = 0;
        } if (ballX == 5) {
          ballRight = 0;
          ballLeft = 1;
        }
        if (ballY == brickY && ballX == brickX + 1) {
          ballDown = 0;
          ballUp = 1;
          ballX += 1;
          ballY -= 1;
          Audio::tone(Audio::D*6, 3);
        Audio::tone(Audio::D*2, 3);

        }
        if (ballY == brickY && ballX == brickX) {

          ballDown = 0;
          ballUp = 1;

          ballY -= 1;
          Audio::tone(Audio::D*6, 3);
        Audio::tone(Audio::D*2, 3);

        }
        if (ballY == 4) {
          Lose = 1;
        }
        if (blocks.size() == 0) {
          Level += 1;
          UPDATETIME = 50  - Level * 2;
          reset();
        }




        for (int i = 0; i < blocks.size(); i++) {
          if (ballX == blocks.at(i).pos.x && ballY == blocks.at(i).pos.y) {
            ballUp = 0;
            ballDown = 1;
            blocks.erase(blocks.begin() + i);
            i--;
             Audio::tone(Audio::G*2, 3);
        Audio::tone(Audio::G, 3);

          }
        }
        //        if (ballX == Block.pos.x && ballY == Block.pos.y) {
        //          ballUp = 0;
        //          ballDown = 1;
        //        }









        updateTimer = UPDATETIME;
      }




      if (Buttons::pressed(Buttons::RIGHT)) {
        brickX += 1;
        Audio::tone(Audio::C*4, 3);
        Audio::tone(Audio::C*8, 3);
      }
      if (Buttons::pressed(Buttons::LEFT)) {
        brickX -= 1;
        Audio::tone(Audio::C*8, 3);
        Audio::tone(Audio::C*4, 3);
      }
      if (brickX == 5) {
        brickX = 4;
      }
      if (brickX == -1) {
        brickX = 0;
      }








    }

    virtual void draw() {
      Window::clear(Color(0, 0, 0));

      RectangleShape rect(brickX, brickY, 2, 1);
      rect.draw(Color(255, 255, 0));

      for (int i = 0; i < blocks.size(); i++) {
        blocks.at(i).draw();
      }

      rect = RectangleShape(ballX, ballY, 1, 1);
      rect.draw(Color(0, 0, 255));


    }

    virtual void drawIcon() {
      RectangleShape rect(1, 1, 4, 3);
      rect.draw(Color(0, 0, 0));


      rect =  RectangleShape(2, 3, 2, 1);
      rect.draw(Color(255, 255, 0));

      rect = RectangleShape(3, 2, 1, 1);
      rect.draw(Color(0, 0, 255));

      rect = RectangleShape(1, 1, 4, 1);
      rect.draw(Color(255, 0, 0));

    }

    Breaker() {
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
          blocks.push_back(Block(i, j));
        }
      }
    }
    virtual void reset() {
      blocks.clear();
      brickX = 0;
      brickY = 4;
      ballX = 0;
      ballY = 3;
      ballUp = 1;
      ballDown = 0;
      ballLeft = 0;
      ballRight = 1;
      Lose = 0;
      for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 2; j++) {
          blocks.push_back(Block(i, j));
        }
      }
    }
};





#endif
