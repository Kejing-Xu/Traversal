
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include "cs225/HSLAPixel.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG IceCream;
  IceCream.readFromFile("IceCream.png");
  FloodFilledImage MyCream(IceCream);
  DFS dfs1(IceCream,Point(0,0),0.1);
  DFS dfs2(IceCream,Point(500,500),0.1);

  BFS bfs1(IceCream, Point(0,0),0.1);
  BFS bfs2(IceCream,Point(500,500),0.1);

  MyColorPicker myCP(0.1);
  RainbowColorPicker rainbow(10);

  MyCream.addFloodFill(dfs1, myCP);
  MyCream.addFloodFill(dfs2, myCP);

 MyCream.addFloodFill(bfs1,rainbow);
 MyCream.addFloodFill(bfs2,rainbow);
  
  Animation animation = MyCream.animate(1000);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("../myFloodFill.png");

  return 0;
}
