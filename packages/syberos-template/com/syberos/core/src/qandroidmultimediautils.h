/*!
* \file qandroidmultimediautils.h
* \brief 将从相机中取到的帧格式进行转换，转换成ARGB32格式
*
*将从相机中取到的帧格式进行转换，转换成ARGB32格式
*
*\author 桓乐乐 huanlele@syberos.com
*\version 1.0
*\date 2015/9/7
*/
#ifndef QANDROIDMULTIMEDIAUTILS_H
#define QANDROIDMULTIMEDIAUTILS_H

#include <qglobal.h>
#include <qsize.h>

QT_BEGIN_NAMESPACE

// return the index of the closest value to <value> in <list>
// (binary search)
/**
 * @brief qt_findClosestValue: 返回列表中最接近value的值的索引
 * @param list: 搜索列表
 * @param value: 比较的值
 * @return: 索引
 */
int qt_findClosestValue(const QList<int> &list, int value);

/**
 * @brief qt_sizeLessThan: 比较两个值的大小
 * @param s1: 比较值1
 * @param s2: 比较值2
 * @return : 比较结果
 */
bool qt_sizeLessThan(const QSize &s1, const QSize &s2);

/**
 * @brief qt_convert_NV21_to_ARGB32: 将NV21格式的帧转化为ARGB32的格式
 * @param yuv: NV21格式的帧的指针
 * @param rgb: ARGB32格式帧的指针
 * @param width: NV21格式的帧的宽度
 * @param height: NV21格式的帧的高度
 */
void qt_convert_NV21_to_ARGB32(const uchar *yuv, quint32 *rgb, int width, int height);

QT_END_NAMESPACE

#endif // QANDROIDMULTIMEDIAUTILS_H
