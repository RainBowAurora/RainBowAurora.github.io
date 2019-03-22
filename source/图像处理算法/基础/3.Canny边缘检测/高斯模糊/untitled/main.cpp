#include <iostream>
#include <opencv2/opencv.hpp>

#define ZOOM_SIZE 512

//卷积操作函数
void convolution(cv::Mat &input_image, cv::Mat &output_image, double **kernel, int size);
//高斯核生成
void getOneGuassionArray(int size, double sigma, double **gauss);

int main(int argc, char **argv)
{
    cv::Mat srcImage; //原始图
    cv::Mat dstImage; //自己编写输出的高斯模糊图
    cv::Mat gaussImage; //官方高斯模糊输出图

    int size = 3;    //高斯核尺寸
    double sigma = 0.6; //模糊程度

    srcImage = cv::imread("../../../../../../image/1.jpg", 0);
    if(srcImage.empty()){
        std::cout << "图像读取错误" << std::endl;
        return 0;
    }
    //计算缩放尺寸
    int scalar_row = (int)ZOOM_SIZE;
    int scalar_col = (int)(ZOOM_SIZE * srcImage.rows / (double)srcImage.cols);
    cv::resize(srcImage, srcImage, cv::Size(scalar_row, scalar_col));
    cv::imshow("原始图", srcImage);

    //动态数组生成
    double **gauss_kernel = new double*[size];
    for(int i = 0; i < size; i++){
        gauss_kernel[i] = new double[size];
    }

    //获取高斯核
    getOneGuassionArray(size, sigma, gauss_kernel);
    //卷积
    convolution(srcImage, dstImage, gauss_kernel, size);
    //官方高斯函数
    cv::GaussianBlur(srcImage, gaussImage, cv::Size(3,3), 0.6);

    cv::imshow("高斯模糊",dstImage);
    cv::imshow("官方高斯模糊", gaussImage);

    cv::waitKey(0);
    return 0;
}

/**
* 功能: 对图像进行卷积操作
* 参数:
*      input_image - 输入图像
*
**/
void convolution(cv::Mat &input_image, cv::Mat &output_image, double **kernel, int size)
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


/**
* 功能: 求解高斯核
* 参数:
*      sigma - σ(标准差)
*      size - 高斯矩阵大小(只能是奇数)
**/
void getOneGuassionArray(int size, double sigma, double **gauss)
{
    double pi = 3.1415927;
    //中心位置
    int center = size/2;
    double sum = 0.0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
        gauss[i][j] = exp(-(pow((i-center),2) + pow((j-center),2))/(2*pow(sigma,2))) / (2*pi*pow(sigma,2));
        sum += gauss[i][j];
        }
    }
    //归一化
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            gauss[i][j] = gauss[i][j] / sum;
        }
    }
}

