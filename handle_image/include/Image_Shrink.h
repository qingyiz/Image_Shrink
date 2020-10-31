#include <math.h>
#include <sys/time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;



struct object_rect {
    int x;      /*左上角x*/
    int y;      /*左上角y*/
    int width;  /*长度*/
    int height; /*宽度*/
};

/*函数名：	resize_uniform()
 *函数功能：等比例缩放函数
 *参数：src 原始图像
 *		dst 输出目标图像
 *		dst_size 目标图像的大小
 *		effect_area 有效区域，就是非黑色区域
 */
int resize_uniform(Mat &src, Mat &dst, Size dst_size, object_rect &effect_area);


/*函数名：	crop_effect_area()
 *函数功能：等比例恢复函数
 *参数：src 等比例缩放后的图像
 *		dst 输出目标图像
 *		dst_size 等比例缩放之前的原始图像大小
 *		effect_area 等比例缩放后的有效区域
 */
int crop_effect_area(Mat &uniform_scaled, Mat &dst, Size ori_size, object_rect effect_area);
