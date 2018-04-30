/**
   ******************************************************************************************************************************************************
   * @file			NaiveBayes.h
   * @author		Morris
   * @version		V1.0
   * @date			2018年4月30日20:46:22 在VS2017上DeBug模式最终编译运行。
   * @brief			统计学习方法中的朴素贝叶斯算法（分类）
   ******************************************************************************************************************************************************
   * @attention  （1）
   *                      （2）
   *                      （3）
   *
   *******************************************************************************************************************************************************
   */

#ifndef __NAIVEBAYES_H
#define __NAIVEBAYES_H

#include "Data.h"
#include <iostream>
using namespace std;
typedef struct{
	i32 *indexPtr;
	i32 count;
	i32 *pPtr;
}PrbDisbTypeDef, *PrbDisbTypeDefPtr;

class NaiveBayes{
	friend ostream &operator<<( ostream &output, NaiveBayes &nb );
	friend istream &operator>>( istream &input, NaiveBayes &nb);
public :
	NaiveBayes( i32 r, i32 c, i32 nc, i32 lm = 1 );
	
	void setLanmda( i32 lm );
	void creatFramework();
	void init();
	void setInput( d64 *vPtr );
	void caculateProbability();
	i32 getLanmda() const;
	i32 classifyInput();
	Data trainData;
	Data testData;
private :
	d64 *inPtr;
	d64 *prbPtr;
	i32 lanmda;
	PrbDisbTypeDefPtr disPtr;
	d64 *getInput() const;
	d64 *getProbability();
	void probabilityDistribution();
};
#endif  /* __NAIVEBAYES_H */
