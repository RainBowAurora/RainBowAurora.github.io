---
title: 01 OpenCV-Mat
date: 2019-02-19 22:14:31
tags:
 Opencv
Categories:
- 图像处理
mp3: https://link.hhtjim.com/163/31134621.mp3
cover: img/opencv/01/show.jpg
---

# 起源
OpenCV作为一个强大的开源计算机库,从早期的OpenCV1.x版本中,图像处理是通过lplimage(该名称源于另一个开源库Intel image Processing Library)结构来实现,早期的OpenCV完全是C的编程风格,lplimage结构是OpenCV矩阵运算的数据结构.到了OpenCV2.0版本,OpenCV开源库引入了面向对象的编程思想,大量的源代码用C++重新构建,Mat类(Matix矩阵的缩写),是OpenCV用于处理图像而引入的一个封装类,从功能上来讲,Mat类在lplimage结构基础上进一步增强,并且引入了C++高级特性,如果你要查看Mat定义的话可以到源代码目录下`opencv/modules/core/include/opencv2/core/mat.hpp`进行查看,你会发现其设计十分全面具体,基本覆盖了计算机视觉库对于图像处理的基本要求.

# 构造函数
OpenCV包含有许多类型的构造函数,能够很方便用户的使用:

1. 默认构造函数(无参构造函数)
```
Mat::Mat()
```
2. 使用行数 列书 图像类型 初始化的构造的函数
```
Mat::Mat(int rows, int cols, int type)
```
3. 使用size类型初始化图像大小的构造函数
```
Mat::Mat(Size size, int type)
```
4. 使用行数和列书设定图像大小,并且使用Scalar设置图像初始值
```
Mat::Mat(int rows, int cols, int type, const Scalar &s)
```
5. 使用Size初始化图像大小,使用Scalar设置图像初始值
```
Mat::Mat(Size size, int type, const Scalar &s)
```
6. 拷贝构造函数,属于浅拷贝
```
Mat::Mat(const Mat &m)
```
7. 使用行数列数设置图像大小,不创建图像数据所需的内存,直接使用data所指内存,图像的步长由Setp决定
```
Mat::Mat(int rows, int cols, int type, void *data, size_t step=AUTO_STEP)
```
8. 使用Size指定图像大小,不创建图像数据所需的内存,直接使用data所指的内存,图像的步长由setp决定
```
Mat::Mat(Size size, int type, void *data, size_t step=AUTO_SETP)
```
9. 图像ＲＯＩ
```
Mat::Mat(const Mat &m, const Rect &roi)
```
10. 图像ＲＯＩ
```
Mat::Mat(const Mat &m, const Range& rowRange, const Range& colRange)
```

# 常用的成员函数
OpenCV中有非常多的成员函数，基本能够满足大多数用户的使用，下面我们就来介绍一些常用的函数，以及他们的用法，如果想了解更加细致的解释，建议参考[Opencv官方网站](https://docs.opencv.org/master/d9/df8/tutorial_root.html)
## Mat::Create
创建新的矩阵数据
```
void Mat::create(int rows, int cols, int type)
void Mat::create(Size size, int type)
void Mat::create(int ndims, const int* sizes, inttype)
```
> rows-新的行数
> cols-新的列数
> size-替代新矩阵的大小规格
> sizes-指定一个新的矩阵形状的整数数组
> rype-新矩阵的类型
> ndims-新数组的维数


## Mat::resize
重新分配图像大小
```
void Mat::resize(size_t sz)
void Mat::resize(size_t sz, const Scalar &s)
```
> sz-新的行数
> s-分配新添加的元素的值


## Mat::adjustROI
调整子矩阵大小及其在父矩阵中的位置
```
Mat &Mat::adjustROI(int dtop, int dbottom, int dleft, int dright)
```
> dtop-顶部子矩阵向上的平移量
> dbottom-底部子矩阵边界向下的平移量
> dleft-左边子矩阵边界向左的平移量
> dright-右边子矩阵向右的平移量


## Mat::total
返回数组元素的总数
```
size_t Mat::total() const
```


## Mat::isContinuous
判断矩阵是否连续
```
bool Mat::isContinuous() const
```


## Mat::elemSize
返回矩阵元素的大小(以字节为单位)
```
size_t Mat::elemSize() const
```
> 该方法返回以字节为单位的矩阵元素通道大小，例如：
> 如果矩阵的类型是CV\_16SC，该方法返回3\*sizeof(short)或者６．



## Mat::depth
返回一个矩阵的深度
```
int Mat::depth() const
```
> 该方法返回矩阵元素深度（每个单独通道类型）：

符号|类型|取值范围
:----:|:-------------:|:--:
CV\_8U|8位无符号整数|0.....255
CV\_8S|8位符号整数|-128.....127
CV16\_U|16位无符号整数|0....65535
CV16\_S|16位符号整数|-32768....32767
CV32\_S|32位符号整数|-21473648....21473647
CV32\_F|32位浮点数|-FLT\_MAX....FLT\_MAX
CV64\_F|64浮点数|-DBL\_MAX....DBL\_MAX



## Mat::channels
返回矩阵通道的数目
```
int Mat::channels() const
```


## Mat::setp1
返回矩阵归一化迈出的一步
```
size_t const Mat::setp1()
```
> 该方法返回以矩阵setp除以Mat::elemSize1().他对快速访问矩阵元素很有用



## Mat::size
返回一个矩阵的大小
```
Size Mat::size() const
```
> 该方法返回一个矩阵的大小：Size(cols, rows)，若据很超过二维则返回(-1, -1)



## Mat::empty
如果数组没有elemens，则返回true，常用于判断图片是否被读取
```
bool Mat::empty()
```



## Mat::ptr
返回指定矩阵行的指针
```
uchar *Mat::ptr(int i=0)
uconst uchar* Mat::ptr(int i=0) const
template<typename _Tp> _Tp* Mat::ptr(int i=0)
template<typename _Tp> const _Tp* Mat::ptr(int i=0) const
```
> i-一个基于０行的索引



## Mat::at
返回指定数组元素的引用
```
template<typename T> T& Mat::at(int i) const
template<typename T> const T&Mat::at(int i) const
template<typename T> T& Mat::at(int i, int j) const
template<typename T> const T&Mat::at(int i, int j) const
template<typename T> T& Mat::at(Pointpt)
template<typename T> const T&Mat::at(Point pt) const
template<typename T> T&Mat::at(int i, int j, int k)
template<typename T> const T&Mat::at(int i, int j, int k) const
template<typename T> T&Mat::at(constint* idx)
template<typename T> constT&Mat::at(const int* idx) const
```
> i-0维度索引
> j-1唯独索引
> k-2维度索引
> pt-Point(i,j)作为指定元素的位置
> idx-Mat::dims数组的索引



## Mat::begin
返回矩阵迭代器，并设置为第一矩阵元
```
template<typename _Tp>MatIterator_<_Tp> Mat::begin()
template<typename _Tp>MatConstIterator_<_Tp> Mat::begin() const
```


## Mat::end
返回矩阵迭代器，并将其设置为最后元素的矩阵单元．
```
template<typename _Tp>MatIterator_<_Tp> Mat::end()
template<typename _Tp>MatConstIterator_<_Tp> Mat::end() const
```

# 拓展
有时在进行面试的时候，面试官提出一些有关编程方面的问题，让我们不许使用Opencv的Mat类．通常会提出数据类型转换问题,下面我们就此开始.
## Mat与数组之间互相转换
**数组转Mat**
```
unsigned char buff[height][width];
cv::Mat img(height, width, CV_8UC1, (unsigned char*)buff);
```

**Mat转数组**
1. 将Mat中的内容传递给数组，如果Mat中的数据是连续的，那么我们传递到一维vector我们可以这样：
```
std::vector<uchar> array(mat.total());
if(mat.isContinuous()){
	array = mat.data;
}
```
2. 同样的，传递到一维数组我们可以：
```
unsigned char *arry = new unsigned char[mat.total()];
if(mat.isContinuous()){
	array = mat.data;
}
```

3. 对于二维度vector传值:
```
uchar **array = new uchar*[mat.rows];
for(int i = 0; i < mat.rows; ++i){
	array[i] = new uchar[mat.cols];
}
for(int i = 0; i < mat.rows; ++i){
	array[i] = mat.ptr<uchar>(i);
}
```
## Mat与vector互相转换
1. Mat转vector
```
template<typename _Tp>
vector<_Tp> convertMat2Vector(const Mat &mat)
{
	return (vector<_Tp>)(mat.reshape(1, 1)); //通道数不变，按行转为一行
}
```
2. vector转Mat
```
template<typename _Tp>
cv::Mat convertVector2Mat(vector<_Tp> v, int channels, int rows)
{
	cv::Mat mat = cv::Mat(v);
	cv::Mat dest = mat.reshape(channels, rows).clone();　//必须clone一份，否则出现错误
	return dest;
}
```

