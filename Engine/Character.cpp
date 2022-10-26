#include "Character.h"

Character::Character()
{
}

Character::Character(SDL_Renderer* renderer, SDL_Event* Event,size_t*delta_time, const int screen_width, SDL_Texture* image)
{
    this->Event = Event;
    this->Renderer = renderer;
    this->delta_time = delta_time;
    values.damage = (float)atof(XMLValue(CHARACTERSETTINGSFILENAME,"damage").c_str());
    values.health= (float)atof(XMLValue(CHARACTERSETTINGSFILENAME, "health").c_str());
    std::string path= XMLValue(CHARACTERSETTINGSFILENAME, "image");
    float wProp= (float)atof(XMLValue(CHARACTERSETTINGSFILENAME, "widthProportion").c_str());
    float hProp = (float)atof(XMLValue(CHARACTERSETTINGSFILENAME, "heightProportion").c_str());
    const int nrows= atoi(XMLValue(CHARACTERSETTINGSFILENAME, "anim_rows").c_str());
    const int ncols = atoi(XMLValue(CHARACTERSETTINGSFILENAME, "anim_cols").c_str());
    const int duration = atoi(XMLValue(CHARACTERSETTINGSFILENAME, "anim_dur").c_str());
    values.speed= (float)atof(XMLValue(CHARACTERSETTINGSFILENAME, "speed").c_str());

    
    character = Sprite(renderer, image, {0,0, screen_width* wProp,screen_width * hProp});
    character.SetAnimation(ncols,nrows,(float)(1000/duration));
    mge::cout << "character" << mge::endl;
}

Character::~Character()
{
}

fvec2d Character::GetPos()
{
    return character.GetPos();
}

float Character::GetSpeed()
{
    return values.speed;
}

void Character::Draw()
{
    character.Draw();
}
void Character::Animate()
{
    (ANIMATION_DEFAULT) ? character.ResetCropX():character.Animate();   
}

void Character::UpdateEvents()
{
   QueryKeyInput();
   const fvec2d direction = {static_cast<float>(controls.RIGHT - controls.LEFT), static_cast<float>(controls.DOWN - controls.UP)};
   const fvec2d velocity = dotprod(normalize(direction),*delta_time* values.speed);
   character.SetPos(character.GetPos()+velocity);
   ANIMATION_DEFAULT = (direction.x==0)*(direction.y==0);
    
    
   if (controls.RIGHT || controls.LEFT) { character.ChangeRow(2); if (!prev_controls.RIGHT || !prev_controls.LEFT)character.SetFlip((controls.RIGHT && controls.LEFT) ? (prev_controls.RIGHT) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL : (controls.RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE); }
   if (controls.UP || controls.DOWN) { character.SetFlip(SDL_FLIP_NONE); if (!prev_controls.UP || !prev_controls.DOWN)character.ChangeRow((controls.UP && controls.DOWN) ? (prev_controls.UP) ? 0 : 1 : (controls.UP) ? 1 : 0); }

   prev_controls=controls;
}



void Character::SetHealth(const float health)
{
    values.health = health;
}

float Character::GetHealth()
{
    return values.health;
}

void Character::SetX(const float x)
{
    character.SetX(x);
}

void Character::SetY(const float y)
{
    character.SetY(y);
}

float Character::GetHeight()
{
    return character.GetH();
}

float Character::GetWidth()
{
    return character.GetW();
}

float Character::GetY()
{
    return character.GetY();
}

float Character::GetX()
{
    return character.GetX();
}

void Character::SetDamage(const float dmg)
{
    values.damage = dmg;
}

float Character::GetDamage()
{
    return values.damage;
}

Rect Character::GetBody()
{
    return character.GetBody();
}

void Character::SetBody(const Rect& bdy)
{
    character.SetBody(bdy);
}

Rect Character::GetLowerHalf()
{
    const Rect body = character.GetBody();
    return {body.x,body.y+body.h/2,body.w,body.h/2};
}

Rect Character::GetOffsetBody()
{
    return character.GetOffsetBody();
}

void Character::SetLowerHalf(const Rect& lwHlf)
{
    character.SetBody({lwHlf.x,lwHlf.y-lwHlf.h,lwHlf.w,lwHlf.h*2});
}

void Character::SetCamera(const fvec2d& offset)
{
    character.SetCamera(offset);
}

void Character::QueryKeyInput()
{
    if (Event->type == SDL_KEYDOWN)
    {

        switch (Event->key.keysym.sym)
        {
        case SDLK_w: if (!controls.UP) { controls.UP = true; } break;
        case SDLK_a:if (!controls.LEFT) { controls.LEFT = true; } break;
        case SDLK_s:if (!controls.DOWN) { controls.DOWN = true; }break;
        case SDLK_d:if (!controls.RIGHT) { controls.RIGHT = true; }break;
        }
    }
    if (Event->type == SDL_KEYUP)
    {
        switch (Event->key.keysym.sym)
        {
        case SDLK_w:controls.UP = false; break;
        case SDLK_a:controls.LEFT = false; break;
        case SDLK_s:controls.DOWN = false; break;
        case SDLK_d:controls.RIGHT = false; break;
        }
    }
    if (Event->type == SDL_MOUSEBUTTONDOWN)
    {
        switch (Event->button.button)
        {
        case SDL_BUTTON_LEFT:break;
        }
    }
    if (Event->type == SDL_MOUSEBUTTONUP)
    {
        switch (Event->button.button)
        {
        case SDL_BUTTON_LEFT:controls.STOP_SHOOT = true; break;
        }
    }
}

