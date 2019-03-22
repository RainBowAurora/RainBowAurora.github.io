#include <iostream>
#include <opencv2/opencv.hpp>

//图像卷积操作
void convolution(cv::Mat &input_image, cv::Mat &output_image, double kernel[][3], int size);

int main(int argc, char **argv[])
{
    cv::Mat srcImage;
    cv::Mat dstImage;

   srcImage = cv::imread("../../../../../../image/1.jpg", 0);
    if(srcImage.empty()){
        std::cout << "图像读取错误" << std::endl;
        return 0;
    }
    //自定义卷及核,这里直接选取 size = 3, sigma = 0.6 所生成的高斯卷积核
    //卷积后会使图像变模糊
    double kernel[3][3] = {0.0276818,   0.111015,   0.0276818,
                            0.111015,   0.445213,   0.111015,
                            0.0276818,  0.111015,   0.0276818};

    //卷积
    convolution(srcImage, dstImage, kernel, 3);

    cv::imshow("卷积图像", dstImage);
    cv::waitKey(0);
    return 0;
}


/**
* 功能: 对图像进行卷积操作
* 参数:
*      input_image - 输入图像
*
**/
void convolution(cv::Mat &input_image, cv::Mat &output_image, double kernel[][3], int size)
{
  //找出卷积核的中心点
  int center = size / 2;
  cv::Mat temp_image = input_image.clone();
  output_image = cv::Mat(temp_image.size(), temp_image.type());
  for(int rows = 0; rows < temp_image.rows; rows++){
    for(int cols = 0; cols < temp_image.cols; cols++){
        double dst_pixel_value = 0.0;
      for(int i = -size/2; i <= size/2; i++){
        for(int j = -size/2; j <= size/2; j++){
           int row = rows + i;
           int col = cols + j;
           //限幅，防止超出图片范围
           row = row >= temp_image.rows - 1 ? row - 1 : row;
           row = row < 0 ? 0:row;
           col = col >= temp_image.cols - 1? col - 1 : col;
           col = col < 0 ? 0 : col;
           dst_pixel_value += temp_image.at<uchar>(row,col) * kernel[center+i][center+j];
        }
      }
      output_image.at<uchar>(rows, cols) = static_cast<uchar>(dst_pixel_value);
    }
  }
}
