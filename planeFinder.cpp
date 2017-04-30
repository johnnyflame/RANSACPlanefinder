#include "SimplePly.h"
#include <iostream>

int main (int argc, char *argv[]) {

  // Check the commandline arguments.
  if (argc != 6) {
    std::cout << "Usage: planeFinder <input file> <output file> <number of planes> <point-plane threshold> <number of RANSAC trials>" << std::endl;
    return -1;
  }
  int nPlanes = atoi(argv[3]);
  double threshold = atof(argv[4]);
  int nTrials = atoi(argv[5]);

  std::cout << "Searching for " << nPlanes << " planes" << std::endl;
  std::cout << "Using a point-plane threshold of " << threshold << " units" << std::endl;
  std::cout << "Applying RANSAC with " << nTrials << " trials" << std::endl;  

  // Storage for the point cloud.
  SimplePly ply;

  // Read in the data from a PLY file
  std::cout << "Reading PLY data from " << argv[1] << std::endl;
  if (!ply.read(argv[1])) {
    std::cout << "Could not read PLY data from file " << argv[1] << std::endl;
    return -1;
  }
  std::cout << "Read " << ply.size() << " points" << std::endl;

  // Recolour points - here we are just doing colour based on index
  std::cout << "Recolouring points" << std::endl;
  std::vector<Eigen::Vector3i> colours;
  colours.push_back(Eigen::Vector3i(255,0,0));
  colours.push_back(Eigen::Vector3i(0,255,0));
  colours.push_back(Eigen::Vector3i(0,0,255));
  // Can add more colours as needed

  size_t planeSize = ply.size()/nPlanes;
  for (size_t ix = 0; ix < ply.size(); ++ix) {
    size_t planeIx = ix / planeSize;
    size_t colourIx = planeIx % colours.size(); // May need to recycle colours
    ply[ix].colour = colours[colourIx];
  }

  // Write the resulting (re-coloured) point cloud to a PLY file.
  std::cout << "Writing PLY data to " << argv[2] << std::endl;
  if (!ply.write(argv[2])) {
    std::cout << "Could not write PLY data to file " << argv[2] << std::endl;
    return -2;
  }

  return 0;
}
