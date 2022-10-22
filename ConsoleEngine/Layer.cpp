#include "Layer.h"

const WORD Layer::DEFAULT_COLOR = Color_NULL;
Layer::Layer() : color(DEFAULT_COLOR), isStatic(false) {}
Layer::Layer(WORD _color, bool _isStatic) : color(_color), isStatic(_isStatic) {}
Layer::~Layer() {}