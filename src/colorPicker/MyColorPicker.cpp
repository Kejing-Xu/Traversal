#include "cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

MyColorPicker::MyColorPicker(double increment)
  : saturation(0.5), increment(increment) { }

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(0, saturation, 0.5);
  saturation += increment;
  if (saturation >= 1) { saturation -= 1; }
  return pixel;
}
