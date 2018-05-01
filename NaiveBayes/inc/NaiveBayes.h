/**
   ******************************************************************************************************************************************************
   * @file			NaiveBayes.h
   * @author		Morris
   * @version		V1.0.0
   * @date			2018年4月30日20:46:22 在VS2017上DeBug模式最终编译运行。
   * @brief			统计学习方法中的朴素贝叶斯算法（分类）
   ******************************************************************************************************************************************************
   * @attention  （1）算法在计算概率概率分布时采用贝叶斯估计法进行参数估计，默认情况下采用拉普拉斯
   *						平滑即λ = 1，当λ = 0时参数估计法为极大似然估计法。
   *                      （2）对于设置样本点类别时，应当从1-n的正整数来表示，并且样本数据应为数字。
   *                      （3）通过李航的《统计学习方法：朴素贝叶斯》一节中的例子对算法进行验证，其中S=1,M=2,L=3
   *						类别-1改为1, 类别1改为2, 计算结果相同。
   *				  （4）该算法原理可参考我的博客，转载请说明出处，在不收取他人费用的情况下可以随意传播
   *						博客地址：https://blog.csdn.net/weixin_41592704/article/details/80159107
   *
   *******************************************************************************************************************************************************
   */

#ifndef __NAIVEBAYES_H
#define __NAIVEBAYES_H

#include "Data.h"
#include <iostream>
using namespace std;
typedef struct{
	i32 *indexPtr; /* 样本在数据矩阵中的列索引 */
	i32 count; /* 属于某一类的样本个数 */
	i32 *pPtr; /* 贝叶斯估计法中条件概率的分母 */
}PrbDisbTypeDef, /* 概率分布结构体 */
*PrbDisbTypeDefPtr; /* 概率分布结构体指针 */

class NaiveBayes{
	friend ostream &operator<<( ostream &output, NaiveBayes &nb ); /* 标准输出流重载，输出需要分类数据点所属类别 */
	friend istream &operator>>( istream &input, NaiveBayes &nb); /* 标准输入流重载， 用于输入需要分类的数据点 */
public :
	NaiveBayes( i32 r, i32 c, i32 nc, i32 lm = 1 ); /* 算构造函数 */
	~NaiveBayes(); /* 算法析构函数 */

	void setLanmda( i32 lm ); /* 设置贝叶斯估计法中的参数λ */
	void creatFramework(); /* 为算法分配内存 */
	void init(); /* 初始化算法内存 */
	void setInput( d64 *vPtr ); /* 输入需分类的数据点 */
	void caculateProbability(); /* 计算输入属于各类的概率 */
	i32 getLanmda() const; /* 读取参数λ */
	i32 classifyInput(); /* 对输入进行分类 */
	Data trainData; /* 样本数据 */
	Data testData; /* 测试样本数据 */
private :
	d64 *inPtr; /* 存储单个数据点一维数组指针 */
	d64 *prbPtr; /* 存储属于各类别概率一维数组指针 */
	i32 lanmda; /* 贝叶斯估计法中的参数λ*/
	PrbDisbTypeDefPtr disPtr; /* 存储各类别的概率分布 */
	d64 *getInput() const; /* 读取输入*/
	d64 *getProbability(); /* 读取概率 */
	void probabilityDistribution(); /* 计算概率分布 */
}; /* 朴素贝叶斯算法类 */
#endif  /* __NAIVEBAYES_H */
