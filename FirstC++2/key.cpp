#include "key.h"

// À‘Ì‚Ìì¬
Keyboard Key::key_;
Keyboard::State Key::state_;

void Key::update()
{
    // “ü—Íî•ñ‚ğXV
    state_ = key_.GetState();
}