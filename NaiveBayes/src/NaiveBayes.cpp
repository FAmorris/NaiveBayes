#include <iostream>
#include <cstdlib>
#include "../inc/NaiveBayes.h"
using namespace std;

/**
 * @brief   判断两个double类型小数是否相等
 * @param d64 src1 数据1
 * @param d64 src2 数据2
 * @retval bool类型
 */
bool isEqual( d64 src1, d64 src2 )
{
	if( fabs( src1 - src2 ) <= PRECISION ){
		return true;
	}/* end if */
	return false;
}/* end function isEqual */

/**
 * @brief   判断元素是否在列表当中
 * @param d64 *vPtr 一维数组指针
 * @param d64 num 要判断的数据
 * @param i32 numOfElement 数组长度
 * @retval bool类型
 */
bool isInList( d64 *vPtr, d64 num, i32 numOfElement )
{
	for( i32 i = 0; i < numOfElement; i++ ){
		if( isEqual( vPtr[ i ], num ) ) return true;
	}/* end for */
	return false;
}/* end function isInList */

/**
 * @brief  构造函数
 * @param i32 r 数据矩阵行数
 * @param i32 c 数据矩阵列数
 * @param i32 nc 类别个数
 * @param i32 lm 贝叶斯估计法中的参数λ，默认值为1
 * @retval 无
 */
NaiveBayes::NaiveBayes( i32 r, i32 c, i32 nc, i32 lm )
	: trainData( r, c, nc ), testData( r, c, nc )
{
	this->disPtr = NULL;
	this->prbPtr = NULL;
	this->inPtr = NULL;

	this->setLanmda( lm ); /* 设置λ */
	this->creatFramework(); /* 分配内存 */
	this->init(); /*初始化分配到的内存 */
}/* end constructor */

/**
 * @brief   设置λ 
 * @param i32 lm 参数λ 
 * @retval 无
 */
void NaiveBayes::setLanmda( i32 lm )
{
	this->lanmda = ( lm >= 0 ) ? lm : 0; /* 判断输入是否大于0 */
}/* end function NB_SetLanmda */

/**
 * @brief   输入样本点
 * @param d64 *vPtr 样本点一维数组指针 
 * @retval 无
 */
void NaiveBayes::setInput( d64 *vPtr )
{
	i32 rows = trainData.getMatrixRow();

	for( i32 i = 0; i < rows; i++ ){
		this->inPtr[ i ] = vPtr[ i ];
	}/* end for */
}/* end function NB_SetInput */

/**
 * @brief   读取λ 
 * @param 无
 * @retval i32 类型数据
 */
i32 NaiveBayes::getLanmda() const
{
	return this->lanmda;
}/* end function NB_GetLanmda */

/**
 * @brief   读取所输入的样本点数据 
 * @param 无
 * @retval d64 类型指针
 */
d64* NaiveBayes::getInput() const
{
	return this->inPtr;
}/* end function getInput */

/**
 * @brief   读取所输入的样本点数据属于各类别的概率 
 * @param 无
 * @retval d64 类型指针
 */
d64* NaiveBayes::getProbability()
{
	return this->prbPtr;
}/* end function getProbability */

/**
 * @brief   分配算法所需内存 
 * @param 无
 * @retval 无
 */
void NaiveBayes::creatFramework()
{

	if( this->disPtr != NULL){
		delete this->disPtr;
	}/* end if */

	if( this->prbPtr != NULL ){
		delete this->prbPtr;
	}/* end if */

	this->disPtr = new PrbDisbTypeDef[ trainData.getNumOfClasses() + 1  ]; /* 从索引1- n 开始存储类别1 - n的概率分布 */

	if( this->disPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	this->prbPtr = new d64[ trainData.getNumOfClasses() + 1 ]; /* 从索引1- n 开始存储类别1 - n的概率 */

	if( this->prbPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	if( this->inPtr != NULL ){
		delete this->inPtr;
	}/* end if */

	this->inPtr = new d64[ this->trainData.getMatrixRow() ];

	this->init();
}/*end function NB_CreatFramework */

/**
 * @brief   初始化算法所需内存 
 * @param 无
 * @retval 无
 */
void NaiveBayes::init()
{
	i32 temp1 = trainData.getNumOfClasses();

	if( this->disPtr != NULL ){
		for( i32 i = 0; i < temp1 + 1; i++ ){
			this->disPtr[ i ].indexPtr = NULL;
			this->disPtr[ i ].count = 0;
			this->disPtr[ i ].pPtr = NULL;
		}/* end for */
	}/* end if */
	else{ 
		cout << "\n算法结构未生成!" << endl;
		exit( -1 );
	}/* end else */
}/* end function NB_Init */

/**
 * @brief   统计计算概率分布所需的参数 
 * @param 无
 * @retval 无
 */
void NaiveBayes::probabilityDistribution()
{
	i32 i, j, k;
	i32 counter = 0;
	i32 noc = this->trainData.getNumOfClasses();
	i32 cols = this->trainData.getMatrixColumn();
	i32 rows = this->trainData.getMatrixRow();
	i32 lanmda = this->getLanmda();
	i32 *cPtr  = new i32[ trainData.getNumOfClasses() + 1 ];
	i32 *ccPtr = new i32[ trainData.getMatrixRow() ];
	d64 *tPtr = new d64[ trainData.getMatrixColumn() ];
	i32 *aPtr = this->trainData.getAimOutput();
	d64 **sPtrs = this->trainData.getSamples();
	
	for( i = 0; i < noc + 1; i++ ){
		cPtr[ i ] = 0; /* 初始化临时数组 */
	}/* end for */

	for( i = 0; i < cols; i++ ){
		cPtr[ aPtr[ i ] ]++; /* 统计样本集合中各类别样本个数 */
	}/* end for */

	
	for( i = 0; i < rows; i++ ){
		for( j = 0; j < cols; j++ ){
			if( !isInList( tPtr, sPtrs[ i ][ j ], j ) ){
				tPtr[ j ] = sPtrs[ i ][ j ]; /* 可能取值集合，只是为了统计出可能取值的个数 */
				counter++; /* 统计样本点向量各元素的可能取值个数 */
			}/* end for */
		}/* end for */
		ccPtr[ i ] = counter; /* 存储可能取值个数 */
		counter = 0;
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		this->disPtr[ i ].count = cPtr[ i ]; /* 存储属于类别i的样本点个数 */
		this->disPtr[ i ].indexPtr = new i32[ cPtr[ i ] ]; /* 分配用于存储属于类别i的样本点索引数组 */
		this->disPtr[ i ].pPtr = new i32[ rows ]; /* 用于存储样本向量各元素条件概率所需参数 */
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		k = 0;
		for( j = 0; j < cols; j++ ){
			if( aPtr[ j ] == i ){
				this->disPtr[ i ].indexPtr[ k ] = j;	 /* 存储属于类别i的索引 */
				k++;
			}/* end if */
		}/* end for */
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		for( j = 0; j < rows; j++ ){
			this->disPtr[ i ].pPtr[ j ] =  cPtr[ i ] + ccPtr[ j ] * lanmda; /* 计算条件概率分母，并存储 */
		}/* end for */
	}/* end for */

	/* 释放临时分配的内存 */
	delete cPtr;
	delete ccPtr;
	delete tPtr;
}/* end function probabilityDistribution */

/**
 * @brief   计算输入点属于各个类别的概率 
 * @param 无
 * @retval 无
 */
void NaiveBayes::caculateProbability()
{
	d64 *inPtr = this->getInput();
	i32 noc = this->trainData.getNumOfClasses();
	i32 rows = this->trainData.getMatrixRow();
	i32 cols = this->trainData.getMatrixColumn();
	d64 **sPtr = this->trainData.getSamples();
	i32 lm = this->getLanmda();
	i32 temp = lm;

	for ( i32 i = 0; i < noc + 1; i++ ){
		this->prbPtr[ i ] = 1.0; /* 概率初始化为1，用于乘法 */
	}/* end for */

	for( i32 i = 1; i < noc +1; i++ ){
		for( i32 j = 0; j < rows; j++ ){
			for( i32 n = 0; n <  this->disPtr[ i ].count; n++ ){
				if( isEqual( inPtr[ j ], sPtr[ j ][ this->disPtr[ i ].indexPtr[ n ] ] ) ){
					temp++; /* 统计各个样本集合中第n个元素与输入点第n个元素相等的样本个数 */
				}/* end if */
			}/* end for */
			this->prbPtr[ i ] *= ( d64 )temp / this->disPtr[ i ].pPtr[ j ]; /* 第n个元素的条件概率 */
			temp = lm;
		}/* end for */
		this->prbPtr[ i ] *= ( d64 )(this->disPtr[ i ].count + lm ) / ( cols + noc * lm ); /* 计算属于类别i的概率 */
	}/*  end for */

}/* end function caculatePraobalitity*/

/**
 * @brief   对输入点进行分类 
 * @param 无
 * @retval i32 类型，表示输入点所属类别，0表示样本数据中无输入点所属类别（只有极大似然估计法才可能出现0）
 */
i32 NaiveBayes::classifyInput()
{
	i32 count = 0;
	d64 maxProbability = 0.0;
	i32 noc = this->trainData.getNumOfClasses();
	i32 *maxPtr = new i32[ noc + 1 ]; /* 用于统计最大的概率*/

	for( i32 i = 0; i < noc + 1; i++ ){
		maxPtr[ i ] = 0;
	}/* end for */

	this->caculateProbability(); /* 计算概率 */

	for( i32 i = 1; i < noc + 1; i++ ){
		if( this->prbPtr[ i ] > maxProbability ){
			maxProbability = prbPtr[ i ];
			count = 1;
			maxPtr[ count - 1 ] = i; /* 记录概率最大的类别 */
		}/* end if */
		else if( this->prbPtr[ i ] == maxProbability && this->prbPtr[ i ] != 0.0 ){
			count++;
			maxPtr[ count - 1 ] = i; /* 记录概率最大且相同的所有类别 */
		}/* end if */
	}/* end for */

	return maxPtr[ rand() % count ]; /* 在n个最大类别中随机选取一个类别作为输入的类别 */
}/* end function classifyInput */

/**
 * @brief   析构函数
 * @param 无
 * @retval 无
 */
NaiveBayes::~NaiveBayes()
{
	/* 释放内存 */
	delete this->inPtr;
	delete this->prbPtr;
	delete this->disPtr;
}/* end deconstructor */

/**
 * @brief	输出流符号重载函数，用于显示输入点所属类别
 * @param ostream &output 标准输出流类引用
 * @param NaiveBayes &nb 朴素贝叶斯类引用
 * @retval  ostream & 标准输出流引用，目的是为了“>>”符号连用
 */
ostream &operator<<( ostream &output, NaiveBayes &nb )
{
	nb.probabilityDistribution(); /* 计算概率分布 */
	output << "\n朴素贝叶斯分类结果，输入类别为：" << nb.classifyInput();
	return output;
}/* end function operator<< */

/**
 * @brief	输入流重载函数，用于输入样本点数据
 * @param istream &input 标准输入流类引用
 * @param NaiveBayes &nb朴素贝叶斯类引用
 * @retval  istream & 标准输出流引用，目的是为了“>>”符号连用
 */
istream &operator>>( istream &input, NaiveBayes &nb )
{
	for( i32 i = 0; i < nb.trainData.getMatrixRow(); i++ ){
		input >> nb.inPtr[ i ];
	}/* end for*/
	return input;
}/* end function operator>> */
