#ifndef _CIG_BUTT_H__
#define _CIG_BUTT_H__

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_TTF.h>
#include <vector>
#include <string>
#include <fstream>


namespace cig {
  // 10 digits + 26 characters + left shift + control + space + tab
  // 40

  class Sprite {
  protected:
    SDL_Surface* surface;
    void Load_Surface(const char* img_name);
  public:
    int R_Width() const;
    int R_Height() const;

    virtual SDL_Rect* R_Frame(); // just returns nullptr... for use in animation
    virtual SDL_Rect* R_Frame(int);

    SDL_Surface* R_Surface();
    Sprite(const char* img_name);
    Sprite();
    ~Sprite();
  };

  class Animation : public Sprite {
    // animation width/height is for each sprite.
    // speed is 1 frame = 1 unit: 100 units = 100 
    // frame per iteration for example
    int anim_width, anim_height, anim_speed;
    std::vector<SDL_Rect> frames;

    void Refresh_Frames();
  public:
    int R_Anim_Width() const;
    int R_Anim_Height() const;
    int R_Anim_Speed() const;
    int R_Frame_Size() const;

    void Set_Anim_Width(int);
    void Set_Anim_Height(int);
    void Set_Anim_Speed(int);

    SDL_Rect* R_Frame(int);

    Animation(const char* img_name, int a_width, int a_height, int a_speed);
    ~Animation();
  };

  using Hitbox = SDL_Rect;

  class Object {
    int pos_x, pos_y;
    float vel_x, vel_y, rot;
    Hitbox hitbox;
    Animation* sprite;
    int current_frame, it_frame;
    int layer;

    bool is_animation;
  public:
    bool Mouse_On();
    bool Collision(Object*);

    Hitbox* R_Hitbox();
    int R_Pos_X() const;
    int R_Pos_Y() const;
    float R_Vel_X() const;
    float R_Vel_Y() const;
    int R_Frame() const;
    int R_Layer() const;

    void Set_Pos_X(int);
    void Set_Pos_Y(int);
    void Set_Vel_X(float);
    void Set_Vel_Y(float);
    void Set_Frame(int);
    

    SDL_Rect* R_Next_Frame(bool iterate_frame);

    Animation* R_Animation();

    Object(Sprite* img, int l, int x = 0, int y = 0);
    Object(Sprite* img, Hitbox hit, int l, int x = 0, int y = 0);
    Object(Animation* img, int l, int x = 0, int y = 0);
    Object(Animation* img, Hitbox hit, int l, int x = 0, int y = 0);
    ~Object();
  };

  using Colour = SDL_Color;

  class Text {
    std::string text;
    SDL_Surface* message;
    int pos_x, pos_y;
    Colour colour;
    bool static_pos;

    void Refresh_Message();
  public:
    Text(std::string text, Colour colour, int x, int y, bool static_position);
    ~Text();

    std::string R_Text() const;
    int R_Pos_X() const;
    int R_Pos_Y() const;
    Colour R_Colour() const;
    SDL_Surface* R_Surface() const;
    bool R_Static() const;

    void Set_Text(std::string);
    void Set_Pos_X(int);
    void Set_Pos_Y(int);
    void Set_Colour(Colour color);

    static TTF_Font* font;
    static void Load_Font(const char*, int pt_size);
  };

  void Set_Up();
  void Clean_Up();

  struct GUI {
    Sprite* spr;
    int pos_x, pos_y;
  };

  enum Spr_Layer { Pre_Background, Background, Pre_Foreground, Foreground };
  Object* Add_Obj(Object* obj);
  GUI* Add_Spr(GUI* spr, Spr_Layer layer); // sprites don't move with the camera.
  Text* Add_Text(Text* txt);

  void Refresh_Keys();
  void Refresh_Screen();

  Hitbox Create_Hitbox(int x, int y, int w, int h);
  Colour Create_Colour(int r, int g, int b);
  // vars

  extern unsigned char* keys;
  extern int camera_offset_x,
      camera_offset_y;
  extern bool mouse_left, mouse_right, scroll_up, scroll_down;
  extern int mouse_x, mouse_y;
  extern std::vector<std::vector<Object*>> objs;
  extern std::vector<GUI*> sprs[4];
  extern std::vector<Text*> texts;
  extern SDL_Surface* window;

  extern std::ofstream debug;

  // For mixer, you need to keep track of two variables:
  // first one is an integer that represents offset in sounds/music.
  // this means you can not unload sounds/music.

  // You also have to keep track of channels if you want to pause
  // certain channels.
  namespace Mixer {
    extern const int Max_channels;
    extern int channel_playing[255];

    extern std::vector<Mix_Chunk*> sounds;
    extern std::vector<Mix_Music*> music;
    
    void Set_Up();

    int Load_Sound(const char* fname);
    int Load_Song (const char* fname);

    int Play_Sound(int i);
    void Play_Music(int i);

    void Pause_Music();
    void Play_Music();

    bool Sound_Done(int channel);
    // flip between pause and play
    void Stop_Channel(int ch);
    void Pause_Channel(int ch);
    void Start_Channel(int ch);
    void Flip_Channel(int ch);
  };
};

#endif