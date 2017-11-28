#include "function.h"

using namespace std;

void implementation() {


	cv::Mat uBgr = cv::imread("C:/Users/SOGE/Pictures/Gakki02.jpg");
	if (uBgr.empty()) {
		cout << "uBbgr doesn't exist!!" << endl;
		system("pause");
	}

	cv::resize(uBgr, uBgr, cv::Size(), 256 / (double)uBgr.cols, 256 / (double)uBgr.rows);

	int width = uBgr.cols;
	int height = uBgr.rows;

	cv::Mat uLab;
	cv::Mat fLab;
	cv::cvtColor(uBgr, uLab, CV_BGR2Lab);
	uLab.convertTo(fLab, CV_64FC3, 1.0 / 255);

	// ユークリッド距離が0.15以下の画素に同じラベルを付ける
	const double threshold = 0.15;

	cv::Mat fChannels[3];
	cv::split(fLab, fChannels);

	vector<vector<int>> labelMat(height, vector<int>(width, 0));
	labelMat[0][0] = 1;
	int regionNum = 1;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			if (labelMat[x][y] == 0) {
				regionNum += 1;
				labelMat[0][0] = regionNum; // regionNumが255を超えた場合には対応していない
			};


			double lBase = fChannels[0].ptr<double>(y)[x];
			double aBase = fChannels[1].ptr<double>(y)[x];
			double bBase = fChannels[2].ptr<double>(y)[x];

			int up = -1, below = 1;
			int left = -1, right = 1;

			if (y == 0) { up = 0; }
			else if (y == height - 1) { below = 0; }

			if (x == 0) { left = 0; }
			else if (x == width - 1) { right = 0; }

			for (int dy = up; dy <= below; dy++) {
				for (int dx = left; dx <= right; dx++) {

					if (y + dy < 0 || y + dy >= height || x + dx < 0 || x + dx >= width) {
						system("pause");
					}

					double l = fChannels[0].ptr<double>(y + dy)[x + dx];
					double a = fChannels[1].ptr<double>(y + dy)[x + dx];
					double b = fChannels[2].ptr<double>(y + dy)[x + dx];
					double distance = pow(l - lBase, 2.0) + pow(a - aBase, 2.0) + powf(b - bBase, 2.0);
					distance = sqrt(distance);

					if (distance < threshold) {
						labelMat[y + dy][x + dx] = regionNum;
					}
				}
			}
		}
	}

	ofstream ofs("../by_roop_region_label.csv");
	for (int y = 0; y < labelMat.size(); y++) {
		for (int x = 0; x < labelMat.front().size(); x++) {

			int value = labelMat[y][x];

			if (x == labelMat.front().size() - 1) {
				ofs << value << endl;
			}
			else {
				ofs << value << ",";
			}
		}
	}

	cout << regionNum << endl;
}