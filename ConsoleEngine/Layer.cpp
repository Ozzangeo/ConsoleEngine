#include "Layer.h"

const WORD Layer::DEFAULT_COLOR = Color_NULL;
Layer::Layer() : Color(DEFAULT_COLOR), isStatic(false) {}
Layer::Layer(WORD _color, bool _isStatic) : Color(_color), isStatic(_isStatic) {}