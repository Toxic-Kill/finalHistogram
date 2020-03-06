#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat src_Mat = cv::imread("D:\\Files\\2.jpg");//读取文件
	float histgram[256] = { 0 };//建立容量为256的数组，并初始化为0
	int height = src_Mat.rows;
	int width = src_Mat.cols;
	for (int i = 0; i < height; i++)//遍历像素
	{
		for (int j = 0; j < width; j++)
		{
			int greyValue = (src_Mat.at<Vec3b>(i, j)[0] * 0.1140 + src_Mat.at<Vec3b>(i, j)[1] * 0.5870 + src_Mat.at<Vec3b>(i, j)[2] * 0.2989);//计算灰度值
			histgram[greyValue]++;//写入数组中计数
		}
	}
	for (int m = 0; m < 256; m++)
	{
		histgram[m] = histgram[m] / (height*width);//计算各灰度出现概率
	}
	cv::Mat M1(600, 800, CV_8UC3, Scalar(0, 0, 0));//创建图像
	cv::Point pt1, pt2, pt3;//建立x，y轴
	pt1.x = 0;
	pt1.y = 599;
	pt2.x = 799;
	pt2.y = 599;
	pt3.x = 0;
	pt3.y = 0;
	line(M1, pt1, pt2, CV_RGB(255, 0, 0), 1, 8, 0);//画出x轴
	line(M1, pt1, pt3, CV_RGB(255, 0, 0), 1, 8, 0);//画出y轴
	for (int n = 0; n < 256; n++)//画出各灰度所对应的线段
	{
		cv::Point pt4, pt5;
		pt4.x = 3 * n - 1;
		pt4.y = 599;
		pt5.x = 3 * n - 1;
		pt5.y = 600 - histgram[n] * 600;
		line(M1, pt4, pt5, CV_RGB(255, 0, 0), 1, 8, 0);
	}
	cv::imshow("histogram", M1);//显示直方图
	waitKey(0);
}