#include "EventExplosion.hpp"

EventExplosion::EventExplosion(Vector const &vec_pos, int sprite_count) : pos(vec_pos) ,animation(sprite_count)
{
}

EventExplosion::~EventExplosion()
{
}
