#include <cmath>
#include <iterator>
#include <iostream>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(){
  /** @todo [Part 1] */
  traversal=NULL;
  finished=true;
}

ImageTraversal::Iterator::Iterator(ImageTraversal &traversal, Point start){
  this->traversal=&traversal;
  this->start=start;
  current = traversal.peek();
  finished=false;
}

ImageTraversal::Iterator::~Iterator() {
	if (traversal != NULL)
  delete traversal;
	traversal = NULL;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  Point curtop = traversal->pop();
  	traversal->setVisit(curtop.x, curtop.y);
  	
  	Point right(curtop.x + 1, curtop.y);
  	Point below(curtop.x, curtop.y + 1);
  	Point left(curtop.x - 1, curtop.y);
  	Point above(curtop.x, curtop.y - 1);
  	HSLAPixel & startingPixel = traversal->passPng()->getPixel(start.x, start.y);

  	if ( right.x < traversal->passPng()->width() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(right.x, right.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(right);
  		}
  	}
  	
  	if ( below.y < traversal->passPng()->height() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(below.x, below.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(below);
  		}
  	}
  	
  	if ( left.x < traversal->passPng()->width() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(left.x, left.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(left);
  		}
  	}
  	
  	if ( above.y < traversal->passPng()->height() ) {
  		HSLAPixel & pixelInQuestion = traversal->passPng()->getPixel(above.x, above.y);
  		double delta = calculateDelta(startingPixel, pixelInQuestion);
  		if (delta < traversal->getTolerance()) {
  			traversal->add(above);
  		}
  	}
  	while ( !(traversal->empty()) && (traversal->getVisited(traversal->peek().x, traversal->peek().y))) {
  		traversal->pop();
  	}
  	if (traversal->empty()) {
  		finished = true;
  		return *this;
  	}
  	current = traversal->peek();
  	return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return current;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return !(finished && other.finished);
}

ImageTraversal::~ImageTraversal(){
}