#include <iostream>
#include <vector>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/search/search.h>
#include <pcl/search/kdtree.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>
#include <pcl/segmentation/region_growing_rgb.h>

int
main (int argc, char** argv)
{
  pcl::search::Search <pcl::PointXYZRGB>::Ptr tree = boost::shared_ptr<pcl::search::Search<pcl::PointXYZRGB> > (new pcl::search::KdTree<pcl::PointXYZRGB>);

  pcl::PointCloud <pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud <pcl::PointXYZRGB>);
  if ( pcl::io::loadPCDFile <pcl::PointXYZRGB> ("nubes/medium_clouds/medium_cloud_88.pcd", *cloud) == -1 )
  {
    std::cout << "Cloud reading failed." << std::endl;
    return (-1);
  }

  std::cout << "Size of cloud is equal to " << cloud->size() << std::endl;

  // pcl::IndicesPtr indices (new std::vector <int>);
  // pcl::PassThrough<pcl::PointXYZRGB> pass;
  // pass.setInputCloud (cloud);
  // pass.setFilterFieldName ("rgb");
  // pass.setFilterLimits (7.204687800000001e-39, 4.3491344e-39);
  // pass.filter (*indices);

  pcl::RegionGrowingRGB<pcl::PointXYZRGB> reg;
  reg.setInputCloud (cloud);
  // reg.setIndices (indices);
  reg.setSearchMethod (tree);
  reg.setDistanceThreshold (8);
  reg.setPointColorThreshold (10);
  reg.setRegionColorThreshold (6);
  reg.setMinClusterSize (10000);

  std::vector <pcl::PointIndices> clusters;
  reg.extract (clusters);
  std::cout << "Number of clusters is equal to " << clusters.size () << std::endl;
  std::cout << "First cluster has " << clusters[0].indices.size () << " points." << endl;
  // std::cout << "These are the indices of the points of the initial" <<
  // std::endl << "cloud that belong to the first cluster:" << std::endl;
  // int counter = 0;
  // while (counter < clusters[0].indices.size ())
  // {
  //   std::cout << clusters[0].indices[counter] << ", ";
  //   counter++;
  //   if (counter % 10 == 0)
  //     std::cout << std::endl;
  // }
  // std::cout << std::endl;

  pcl::PointCloud <pcl::PointXYZRGB>::Ptr colored_cloud = reg.getColoredCloud ();
  pcl::visualization::CloudViewer viewer ("Cluster viewer");
  viewer.showCloud (colored_cloud);
  while (!viewer.wasStopped ())
  {
    boost::this_thread::sleep (boost::posix_time::microseconds (100));
  }
  pcl::io::savePCDFileASCII ("clustered_cloud_88.pcd", *colored_cloud);
  std::cerr << "Saved " << colored_cloud->size () << " data points." << std::endl;


  return (0);
}