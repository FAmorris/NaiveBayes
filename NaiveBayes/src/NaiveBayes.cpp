#include <iostream>
#include <cstdlib>
#include "../inc/NaiveBayes.h"
using namespace std;

bool isInList( d64 *vPtr, d64 num, i32 numOfElement )
{
	for( i32 i = 0; i < numOfElement; i++ ){
		if( vPtr[ i ] == num){
			return true;
		}/* end if */
	}/* end for */
	return false;
}/* end function isInList */

bool isEqual( d64 src1, d64 src2 )
{
	if( fabs( src1 - src2 ) <= PRECISION ){
		return true;
	}/* end if */
	return false;
}/* end function isEqual */

NaiveBayes::NaiveBayes( i32 r, i32 c, i32 nc, i32 lm )
	: trainData( r, c, nc ), testData( r, c, nc )
{
	this->disPtr = NULL;
	this->prbPtr = NULL;
	this->inPtr = NULL;

	this->setLanmda( lm );
	this->creatFramework();
	this->init();
}/* end constructor */

void NaiveBayes::setLanmda( i32 lm )
{
	this->lanmda = ( lm >= 0 ) ? lm : 0;
}/* end function NB_SetLanmda */

void NaiveBayes::setInput( d64 *vPtr )
{
	i32 rows = trainData.getMatrixRow();

	for( i32 i = 0; i < rows; i++ ){
		this->inPtr[ i ] = vPtr[ i ];
	}/* end for */
}/* end function NB_SetInput */

i32 NaiveBayes::getLanmda() const
{
	return this->lanmda;
}/* end function NB_GetLanmda */

d64* NaiveBayes::getInput() const
{
	return this->inPtr;
}/* end function getInput */

d64* NaiveBayes::getProbability()
{
	return this->prbPtr;
}/* end function getProbability */

void NaiveBayes::creatFramework()
{

	if( this->disPtr != NULL){
		delete this->disPtr;
	}/* end if */

	if( this->prbPtr != NULL ){
		delete this->prbPtr;
	}/* end if */

	this->disPtr = new PrbDisbTypeDef[ trainData.getNumOfClasses() + 1  ];

	if( this->disPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	this->prbPtr = new d64[ trainData.getNumOfClasses() + 1 ];

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
		cPtr[ i ] = 0;
	}/* end for */

	for( i = 0; i < cols; i++ ){
		cPtr[ aPtr[ i ] ]++;
	}/* end for */

	for( i = 0; i < rows; i++ ){
		for( j = 0; j < cols; j++ ){
			if( !isInList( tPtr, sPtrs[ i ][ j ], j ) ){
				tPtr[ j ] = sPtrs[ i ][ j ];
				counter++;
			}/* end for */
		}/* end for */
		ccPtr[ i ] = counter;
		counter = 0;
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		this->disPtr[ i ].count = cPtr[ i ];
		this->disPtr[ i ].indexPtr = new i32[ cPtr[ i ] ];
		this->disPtr[ i ].pPtr = new i32[ rows ];
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		k = 0;
		for( j = 0; j < cols; j++ ){
			if( aPtr[ j ] == i ){
				this->disPtr[ i ].indexPtr[ k ] = j;	
				k++;
			}/* end if */
		}/* end for */
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		for( j = 0; j < rows; j++ ){
			this->disPtr[ i ].pPtr[ j ] =  cPtr[ i ] + ccPtr[ j ] * lanmda;
		}/* end for */
	}/* end for */

	delete cPtr;
	delete ccPtr;
	delete tPtr;
}/* end function NB_ProbabilityDistribution */

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
		this->prbPtr[ i ] = 1.0;
	}/* end for */

	for( i32 i = 1; i < noc +1; i++ ){
		for( i32 j = 0; j < rows; j++ ){
			for( i32 n = 0; n <  this->disPtr[ i ].count; n++ ){
				if( isEqual( inPtr[ j ], sPtr[ j ][ this->disPtr[ i ].indexPtr[ n ] ] ) ){
					temp++;
				}/* end if */
			}/* end for */
			this->prbPtr[ i ] *= ( d64 )temp / this->disPtr[ i ].pPtr[ j ];
			temp = lm;
		}/* end for */
		this->prbPtr[ i ] *= ( d64 )(this->disPtr[ i ].count + lm ) / ( cols + noc * lm );
	}/*  end for */

}/* end function caculatePraobalitity*/

i32 NaiveBayes::classifyInput()
{
	i32 count = 0;
	d64 maxProbability = 0.0;
	i32 noc = this->trainData.getNumOfClasses();
	i32 *maxPtr = new i32[ noc + 1 ];

	for( i32 i = 0; i < noc; i++ ){
		maxPtr[ i ] = 0;
	}/* end for */

	this->caculateProbability();

	for( i32 i = 1; i < noc + 1; i++ ){
		if( this->prbPtr[ i ] > maxProbability ){
			maxProbability = prbPtr[ i ];
			count = 1;
			maxPtr[ count - 1 ] = i;
		}/* end if */
		else if( this->prbPtr[ i ] == maxProbability && this->prbPtr[ i ] != 0.0 ){
			count++;
			maxPtr[ count - 1 ] = i;
		}/* end if */
	}/* end for */

	return maxPtr[ rand() % count ];
}/* end function classifyInput */

ostream &operator<<( ostream &output, NaiveBayes &nb )
{
	nb.probabilityDistribution();
	output << "\n朴素贝叶斯分类结果，输入类别为：" << nb.classifyInput();
	return output;
}/* end function operator<< */

istream &operator>>( istream &input, NaiveBayes &nb )
{
	for( i32 i = 0; i < nb.trainData.getMatrixRow(); i++ ){
		input >> nb.inPtr[ i ];
	}/* end for*/
	return input;
}/* end function operator>> */
