/**
   ******************************************************************************************************************************************************
   * @file			Data.h
   * @author		Morris
   * @version		V1.0
   * @date			2018年4月30日20:46:22 在VS2017上DeBug模式最终编译运行。
   * @brief			样本数据存储类
   ******************************************************************************************************************************************************
   * @attention  （1）Data类中成员属性 sqPtr 以及相关操作成员函数在对于算法对样本排序时使用。
   *                      （2）样本数据以矩阵的形式存储在类中。
   *                      （3）对于成员函数中返回值为指针的函数，返回的是私有成员属性的指针，主要是考虑到
   *					大容量样本数据读取速度问题，在使用时应当确保不修改所返回指针指向内存的内容。
   *
   *******************************************************************************************************************************************************
   */
#ifndef __DATA_H
#define __DATA_H

#include <iostream>
#include "UserType.h"
using namespace std;

class Data{
	friend ostream &operator<<( ostream &, const Data & ); /* 输出流运算符重载，显示样本数据 */
	friend istream &operator>>( istream &, Data & ); /* 输入流运算符重载，输入样本数据 */

public :
	Data( i32 r, i32 c, i32 nc ); /* 构造函数 */
	~Data();/* 析构函数 */

	void setMatrixRow( i32 r ); /* 设置矩阵行数 */
	void setMatrixColumn( i32 c ); /* 设置矩阵列数，等于样本容量N */
	void setNumOfClasses( i32 nc ); /* 设置样本类别个数 */

	void getData( d64 *vPtr, i32 c ) const; /* 从数据矩阵中读取1个样本数据 */
	void getSequence( i32 *vPtr ) const; /* 读取排序后样本数据 */
	i32 getMatrixRow( ) const; /* 读取矩阵行数 */
	i32 getMatrixColumn( ) const; /* 读取矩阵行数 */
	i32 getNumOfClasses( ) const; /* 读取样本类别个数 */
	i32 isInData( d64 *dPtr ) const; /* 判断数据是否在样本数据当中 */
	i32 *getAimOutput() const; /* 读取样本类别 */
	d64 **getSamples() const; /* 读取样本数据 */

	void sortSequence( i32 dim ); /* 按维度对数据升序排序 */
	void randSequence(); /* 生成随机序列 */
	void creatFramework( ); /* 生成数据存储框架 */
	void init(); /* 初始化数据框架 */

private :
	i32 row;/* 矩阵行数 */
	i32 column; /* 矩阵列数 */
	i32 numOfClasses; /* 样本类别数 */
	d64 **spPtrs; /* 数据矩阵二维数组指针 */
	i32 *aPtr; /* 样本类别数组 */
	i32 *sqPtr; /* 索引序列顺序数组，朴素贝叶斯当中未使用 */
	bool isInList( i32 element, i32 numOfElement ) const; /* 判断元素是否在列表当中 */
}; /* 数据存储类 */

#endif /* __DATA_H */
/****************************************************************************** END HEAD FILE ***************************************************************************/