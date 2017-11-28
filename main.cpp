#include "function.h"

using namespace std;

int main(int argc, char** argv) {

	cv::Mat src = cv::imread("C:/Users/SOGE/Pictures/Suzu01.jpg");
	if (src.empty()) {
		cerr << "src doen't exist!!" << endl;
		system("pause");
		return -1;
	}

	cv::resize(src, src, cv::Size(), 512 / double(src.cols), 512 / double(src.rows));
	cv::Mat subtImg(src.size(), src.type());
	const int clusterNum = 6; /*5以上を指定してください*/

	vector<vector<double>> clusterInfo; /*色の重要性を決めるために使用*/

	k_means_color_subtraction(src, /*&*/subtImg, clusterNum, /*&*/clusterInfo);
	select_principal_color_themes(subtImg, clusterNum, clusterInfo);
	//implementaion();

	return 0;
}