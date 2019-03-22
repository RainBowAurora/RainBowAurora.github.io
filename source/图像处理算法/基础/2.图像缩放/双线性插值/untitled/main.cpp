#include <opencv2/opencv.hpp>
#include <iostream>

//缩放尺寸
#define ZOOM_SIZE 512

void bilinearIntertpolatioin(cv::Mat &input_image, cv::Mat &output_image, cv::Size size);

int main(int argc, char **argv)
{
    cv::Mat srcImage;
    cv::Mat dstImage;
    srcImage = cv::imread("../../../../../../image/1.jpg");
    if(srcImage.empty()){
        std::cout << "没有找到图像" << std::endl;
        return 0;
    }

    //计算缩放尺寸
    int scalar_rows = (int)ZOOM_SIZE;
    int scalar_cols = int(ZOOM_SIZE * srcImage.rows/(double)srcImage.cols);

    cv::cvtColor(srcImage,srcImage, CV_BGR2GRAY);

    bilinearIntertpolatioin(srcImage, dstImage, cv::Size(scalar_rows, scalar_cols));
    cv::imshow("原始图", srcImage);
    cv::imshow("双线性插值", dstImage);
    cv::waitKey(0);
    return 0;
}

/**
 * 函数功能: 双线性插值缩放图像
 * 参数:
 *      input_image - 输入图像
 *      output_image - 输出图像
 *      size - 缩放尺寸
 * 备注:
 *      只能进行单通道图片缩放
 **/
void bilinearIntertpolatioin(cv::Mat &input_image, cv::Mat &output_image, cv::Size size)
{
    cv::Mat temp_image = input_image.clone();
    output_image = cv::Mat(size, temp_image.type());

    //计算缩放比例
    double scalar_rows = static_cast<double>(temp_image.rows) / size.height;
    double scalar_cols = static_cast<double>(temp_image.cols) / size.width;

    for(int rows = 0; rows < size.height; rows++){
        for(int cols = 0; cols < size.width; cols++){
           double x = (rows + 0.5) * scalar_rows - 0.5;
           double y = (cols + 0.5) * scalar_cols - 0.5;
           //防止超出图像边界
           double x0 = static_cast<uint>(x);
           x0 = x0 < 0? 0:x0;
           x0 = x0 > (temp_image.rows - 1)? (temp_image.rows - 1) : x0;
           double x1 = x0 + 1;

           double y0 = static_cast<uint>(y);
           y0 = y0 < 0? 0 : y0;
           y0 = y0 > (temp_image.cols -1)? (temp_image.cols - 1) : y0;
           double y1 = y0 + 1;
           cv::Matx12d matx = {x1 - x, x - x0};
           cv::Matx22d matd = {static_cast<double>(temp_image.at<uchar>(x0, y0)), static_cast<double>(temp_image.at<uchar>(x0, y1)),
                               static_cast<double>(temp_image.at<uchar>(x1, y0)), static_cast<double>(temp_image.at<uchar>(x1,y1))};
           cv::Matx21d maty = {y1 - y,
                               y - y0};

            auto val = matx * matd * maty;
            output_image.at<uchar>(rows, cols) = val(0, 0);
        }
    }
}
