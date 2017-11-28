#pragma once

#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

void implementaion();
void k_means_color_subtraction(cv::Mat src, cv::Mat &dst, const int clusterNum, std::vector<std::vector<double>> &clusterInfo);
void select_principal_color_themes(cv::Mat src, const int clusterNum, std::vector<std::vector<double>> clusterInfo);