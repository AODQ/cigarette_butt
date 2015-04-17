#include "Cigarette_Butt.h"
#include <SDL.h>

double pi = 3.1416;

int main ( int argc, char* argv[] ) {
  cig::Set_Up();
  cig::Text::Load_Font("courier.ttf", 12);

  SDL_WM_SetCaption( "Example Cigarette Booty", nullptr );

  cig::Object* t_[200];
  cig::Sprite* example_sprite = new cig::Sprite("whatever.png");
  for ( int i = 0; i != 200; ++ i )
    t_[i] = cig::Add_Obj(new cig::Object(example_sprite, i, 250, 250));

  cig::Text* ei_text = cig::Add_Text(
      new cig::Text("Example Text!!111",cig::Create_Colour(255,255,255),15,15,1));

  cig::Mixer::Load_Song("Menu Theme.mp3");
  cig::Mixer::Play_Music(0);

  int rot = 0;
  while ( rot != 50000 ) {
    cig::Refresh_Screen();
    for ( int i = 0; i != 200; ++ i ) {
      t_[i]->Set_Pos_X(50 + std::cos(double(rot*i*i)*pi/180.0)*20000*pi/180.0);
      t_[i]->Set_Pos_Y(50 + std::sin(double(rot*i-i)*pi/180.0)*40000*pi/180.0);
    }
    SDL_Delay(20);
    rot += 1;
  }

  delete example_sprite;
  cig::Clean_Up();
  return 0;
}