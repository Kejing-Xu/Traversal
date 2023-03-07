#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"

/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  tolerance_=tolerance;
  png_=png;
  start_=start;
  traversal.push(start);
  visited.resize(png_.width());
  for (unsigned i = 0; i < visited.size(); i++) {
    visited[i].resize(png_.height());
      for (unsigned j = 0; j < visited[i].size(); j++) {
        visited[i][j] = false;
      }
  }
  visited[start.x][start.y] = true;
}

DFS::~DFS(){
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS * dfs = new DFS(png_, start_, tolerance_);
  return ImageTraversal::Iterator(*dfs, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point top = traversal.top();
	traversal.pop();
	return top;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return traversal.top();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return traversal.empty();
}


bool DFS::getVisited(unsigned x, unsigned y) {
    return visited[x][y];
}
void DFS::setVisit(unsigned x, unsigned y) {
    visited[x][y] = true;
}
PNG * DFS::passPng() {
    return &png_;
}
double DFS::getTolerance() {
  return tolerance_;
}
