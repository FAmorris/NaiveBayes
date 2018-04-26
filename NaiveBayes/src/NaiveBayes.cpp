#include <iostream>
#include <cstdlib>
#include "../inc/NaiveBayes.h"
using namespace std;

i32 isInList( d64 *vPtr, d64 num, i32 numOfElement )
{
	for( i32 i = 0; i < numOfElement; i++ ){
		if( vPtr[ i ] == num){
			return 1;
		}/* end if */
	}/* end for */
	return 0;
}/* end function isInList */

NaiveBayes::NaiveBayes( i32 r, i32 c, i32 nc, i32 lm )
	: trainData( r, c, nc ), testData( r, c, nc )
{
	this->disPtr = NULL;
	this->prbPtr = NULL;

	NB_SetLanmda( lm );
	this->NB_CreatFramework();
	this->NB_Init();
}/* end constructor */

void NaiveBayes::NB_SetLanmda( i32 lm )
{
	this->lanmda = ( lm >= 0 ) ? lm : 0;
}/* end function NB_SetLanmda */

void NaiveBayes::NB_SetInput( d64 *vPtr )
{
	i32 rows = trainData.DT_GetMatrixRow();

	for( i32 i = 0; i < rows; i++ ){
		this->inPtr[ i ] = vPtr[ i ];
	}/* end for */
}/* end function NB_SetInput */

i32 NaiveBayes::NB_GetLanmda() const
{
	return this->lanmda;
}/* end function NB_GetLanmda */

void NaiveBayes::NB_CreatFramework()
{

	if( this->disPtr != NULL){
		delete this->disPtr;
	}/* end if */

	if( this->prbPtr != NULL ){
		delete this->prbPtr;
	}/* end if */

	this->disPtr = new PrbDisbTypeDef[ trainData.DT_GetNumOfClasses() + 1  ];

	if( this->disPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	this->prbPtr = new d64[ trainData.DT_GetNumOfClasses() + 1 ];

	if( this->prbPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	NB_Init();
}/*end function NB_CreatFramework */

void NaiveBayes::NB_Init()
{
	i32 temp1 = trainData.DT_GetNumOfClasses();

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

	if( this->prbPtr != NULL ){
		for( i32 i = 0; i < temp1 + 1; i++ ){
			this->prbPtr[ i ] = 0.0;
		}/* end for */
	}/* end if */
	else{
		cout << "\n算法结构未生成!" << endl;
		exit( -1 );
	}/* end else */
}/* end function NB_Init */

void NaiveBayes::NB_ProbabilityDistribution()
{
	i32 i, j, k;
	i32 counter = 0;
	d64 numberator, denominator;
	i32 noc = trainData.DT_GetNumOfClasses();
	i32 cols = trainData.DT_GetMatrixColumn();
	i32 rows = trainData.DT_GetMatrixRow();
	i32 lanmda = NB_GetLanmda();
	i32 *cPtr  = new i32[ trainData.DT_GetNumOfClasses() + 1 ];
	i32 *ccPtr = new i32[ trainData.DT_GetMatrixRow() ];
	d64 *tPtr = new d64[ trainData.DT_GetMatrixColumn() ];
	i32 *aPtr = trainData.DT_GetAimOutput();
	d64 **sPtrs = trainData.DT_GetSamples();
	
	for( i = 0; i < noc + 1; i++ ){
		cPtr[ i ] = 0;
	}/* end for */

	for( i = 0; i < cols; i++ ){
		cPtr[ aPtr[ i ] ]++;
	}/* end for */
	
	cout << "\n类别个数：" << endl;

	for( i = 1; i < noc + 1; i++ ){
		cout << cPtr[ i ] << " ";
	}
	cout << endl;

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

	cout << "\n取值个数：" << endl;

	for( i = 0; i < rows; i++ ){
		cout << ccPtr[ i ] << " ";		
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		this->disPtr[ i ].count = cPtr[ i ];
		this->disPtr[ i ].indexPtr = new i32[ cPtr[ i ] ];
		this->disPtr[ i ].pPtr = new d64[ rows ];
	}/* end for */

	cout << "\n类别样本个数：" << endl;

	for( i = 1; i < noc + 1; i++ ){
		cout << this->disPtr[ i ].count << endl;
	}

	for( i = 1; i < noc + 1; i++ ){
		k = 0;
		for( j = 0; j < cols; j++ ){
			if( aPtr[ j ] == i ){
				this->disPtr[ i ].indexPtr[ k ] = j;	
				k++;
			}/* end if */
		}/* end for */
	}/* end for */

	cout << "\n索引 : " << endl;

	for( i = 1; i < noc + 1; i++ ){
		for( j = 0; j < this->disPtr[ i ].count; j++ ){
			cout << this->disPtr[ i ].indexPtr[ j ] << " ";
		}/* end for */
		cout << endl;
	}/* end for */

	for( i = 1; i < noc + 1; i++ ){
		for( j = 0; j < rows; j++ ){
			numberator = ( d64 )( cPtr[ i ] + lanmda ) / ( cols + noc *  lanmda );
			denominator  = ( cPtr[ i ] + ccPtr[ j ] * lanmda);
			this->disPtr[ i ].pPtr[ j ] =  numberator / denominator;
		}/* end for */
	}/* end for */

	cout << "\n概率分布：" << endl;

	for( i = 1; i < noc + 1; i++ ){
		for( j = 0; j < rows; j++ ){
			cout << this->disPtr[ i ].pPtr[ j ] << " ";			
		}
	}

	delete cPtr;
	delete ccPtr;
	delete tPtr;
}/* end function NB_ProbabilityDistribution */

