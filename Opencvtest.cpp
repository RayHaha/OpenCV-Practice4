// Opencvtest.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include<fstream>
#include<string.h>
#include <time.h>

using namespace cv;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Mat image = imread("lena.bmp");
	Mat grayimage;
	Mat thimage;
	Mat dimage;
	Mat eimage;
	Mat oimage;
	Mat cimage;
	Mat himage;
	Mat jimage;
	Mat kimage;
	cvtColor(image,grayimage, CV_BGR2GRAY);
	cvtColor(image,thimage, CV_BGR2GRAY);
	cvtColor(image,dimage, CV_BGR2GRAY);
	cvtColor(image,eimage, CV_BGR2GRAY);
	cvtColor(image,oimage, CV_BGR2GRAY);
	cvtColor(image,cimage, CV_BGR2GRAY);
	cvtColor(image,himage, CV_BGR2GRAY);
	cvtColor(image,jimage, CV_BGR2GRAY);
	cvtColor(image,kimage, CV_BGR2GRAY);
	int pixel = 0;

	Mat dilation(Mat thimage, Mat dimage);
	Mat erosion(Mat thimage, Mat eimage);


	for(int i=0; i<grayimage.rows; i++){
		for(int j=0; j<grayimage.cols; j++){
			pixel = grayimage.at<uchar>(i,j);
			if(pixel >= 128){
				thimage.at<uchar>(i,j) = 255;
				dimage.at<uchar>(i,j) = 255;
				eimage.at<uchar>(i,j) = 255;
				oimage.at<uchar>(i,j) = 255;
				cimage.at<uchar>(i,j) = 255;
				jimage.at<uchar>(i,j) = 255;
				kimage.at<uchar>(i,j) = 255;
			}else{
				thimage.at<uchar>(i,j) = 0;
				dimage.at<uchar>(i,j) = 0;
				eimage.at<uchar>(i,j) = 0;
				oimage.at<uchar>(i,j) = 0;
				cimage.at<uchar>(i,j) = 0;
				jimage.at<uchar>(i,j) = 0;
				kimage.at<uchar>(i,j) = 0;
			}
		}
	}


	//dilation
	dimage = dilation(thimage, dimage);
	imshow("dilation",dimage);
	imwrite("dilation.bmp",dimage);
	//erosion
	eimage = erosion(thimage, eimage);
	imshow("erosion",eimage);
	imwrite("erosion.bmp",eimage);
	//opening
	oimage = erosion(thimage, oimage);
	oimage = dilation(eimage, oimage);
	imshow("opening",oimage);
	imwrite("opening.bmp",oimage);
	//closing
	cimage= dilation(thimage, cimage);
	cimage = erosion(dimage, cimage);
	imshow("closing",cimage);
	imwrite("closing.bmp",cimage);

	//Hit and Miss
	//j
	bool stay = true;
	for(int i=0; i<thimage.rows-1; i++){
		for(int j=1; j<thimage.cols; j++){
			pixel = thimage.at<uchar>(i,j);
			if(pixel==255){
				stay = true;
				int check1 = thimage.at<uchar>(i,j-1);
				int check2 = thimage.at<uchar>(i+1,j);
				if(check1==0 || check2==0){
					stay = false;
				}
				if(stay == false){
					jimage.at<uchar>(i,j) = 0;
				}
			}
		}
	}

	//k
	for(int i=0; i<thimage.rows; i++){
		for(int j=0; j<thimage.cols; j++){
			pixel = thimage.at<uchar>(i,j);
			if(pixel == 255){
				thimage.at<uchar>(i,j) = 0;
				kimage.at<uchar>(i,j) = 0;
			}else{
				thimage.at<uchar>(i,j) = 255;
				kimage.at<uchar>(i,j) = 255;
			}
		}
	}
	for(int i=1; i<thimage.rows; i++){
		for(int j=0; j<thimage.cols-1; j++){
			pixel = thimage.at<uchar>(i,j);
			stay = true;
			int check1 = thimage.at<uchar>(i-1,j);
			int check2 = thimage.at<uchar>(i-1,j+1);
			int check3 = thimage.at<uchar>(i,j+1);
			if(check1==0 || check2==0 || check3==0){
				stay = false;
			}
			if(stay==false){
				kimage.at<uchar>(i,j) = 0;
			}else{
				kimage.at<uchar>(i,j) = 255;
			}
		}
	}

	//h
	for(int i=0; i<thimage.rows; i++){
		for(int j=0; j<thimage.cols; j++){
			himage.at<uchar>(i,j) = 0;
		}
	}
	for(int i=0; i<thimage.rows; i++){
		for(int j=0; j<thimage.cols; j++){
			int checkj = jimage.at<uchar>(i,j);
			int checkk = kimage.at<uchar>(i,j);
			if(checkj==255 && checkk==255){
				himage.at<uchar>(i,j) = 255;
			}
		}
	}
	imshow("Hit and Miss",himage);
	imwrite("Hit and Miss.bmp",himage);

	waitKey(0);
	return 0;
}

Mat dilation(Mat thimage, Mat dimage){

	//dilation
	int pixel = 0;
	int check = 0;
	for(int i=2; i<thimage.rows-2; i++){
		for(int j=2; j<thimage.cols-2; j++){
			pixel = thimage.at<uchar>(i,j);
			if(pixel == 255){
				for(int k=0; k<5; k++){
					for(int l=0; l<5; l++){
						if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

						}else{
							check = thimage.at<uchar>(i-2+k,j-2+l);
							if(check!=255){
								dimage.at<uchar>(i-2+k,j-2+l) = 255 ;
							}
						}
					}
				}
			}
		}
	}

	return dimage;
}

Mat erosion(Mat thimage, Mat eimage){

	//erosion
	int pixel = 0;
	int check = 0;
	bool stay = true;
	for(int i=2; i<thimage.rows-2; i++){
		for(int j=2; j<thimage.cols-2; j++){
			pixel = thimage.at<uchar>(i,j);
			if(pixel == 255){
				stay = true;
				for(int k=0; k<5; k++){
					for(int l=0; l<5; l++){
						if((k==0&&l==0)||(k==0&&l==4)||(k==4&&l==0)||(k==4&&l==4)){

						}else{
							check = thimage.at<uchar>(i-2+k,j-2+l);
							if(check!=255){
								stay = false;
							}
						}
					}
				}
				if(stay==false){
					eimage.at<uchar>(i,j) = 0 ;
				}
			}
		}
	}

	return eimage;
}