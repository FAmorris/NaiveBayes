#include <iostream>
#include <cstdlib>
#include "../inc/Data.h"
using namespace std;

Data::Data( i32 r, i32 c, i32 nc )
{
	this->aPtr = NULL;
	this->spPtrs = NULL;
	this->sqPtr = NULL;

	DT_SetMatrixRow( r );
	DT_SetMatrixColumn( c );
	DT_SetNumOfClasses( nc );

	if( r > 0 || c > 0 ){
		DT_CreatFramework();
	}/* end if */
	else{
		cout << "\n数据存储结构在构造函数中未生成，若需要生成请设置参数。" << endl;
	}/* end else */
}/* end constructor Data */

i32 Data::DT_IsInList( i32 element, i32 numOfElement ) const
{
	i32 i;

	for( i = 0; i < numOfElement; i++ ){
		if( this->sqPtr[ i ]  == element ){
			return 1;
		}/* end	if */
	}/* end for */

	return 0;

}/* end function DT_IsInList */

i32 Data::DT_IsInData( d64 *dPtr ) const
{
	i32 r, c;
	i32 temp1 = DT_GetMatrixRow();
	i32 temp2 = DT_GetMatrixColumn();

	for( c = 0; c < temp2; c++ ){
		for( r = 0; r < temp1; r++ ){
			if( fabs( this->spPtrs[ r ][ c ] - dPtr[ r ] ) < 0.00001 ){
				return 1;
			}/* end if */
		}/* end for */
	}/* end for */

	return 0;
}/* end function DT_IsInData */

void Data::DT_SetMatrixRow( i32 r )
{
	this->row = ( r > 0 ) ? r : 0;
}/* end function DT_SetMatrixRow */

void Data::DT_SetMatrixColumn( i32 c )
{
	this->column = ( c > 0 ) ? c : 0;
}/* end function DT_SetMatrixColumn */

void Data::DT_SetNumOfClasses( i32 nc )
{
	this->numOfClasses = ( nc > 0 ) ? nc : 0;
}/* end function DT_SetNumOfClasses */

i32 Data::DT_GetMatrixRow( ) const
{
	return this->row;
}/* end function DT_GetMatrixRow */

i32 Data::DT_GetMatrixColumn( ) const
{
	return this->column;
}/* end function DT_GetMatrixColumn */

i32 Data::DT_GetNumOfClasses( ) const
{
	return this->numOfClasses;
}/* end function DT_GetNumOfClasses */

void Data::DT_CreatFramework( )
{
	i32 i;
	i32 temp1 = DT_GetMatrixColumn();
	i32 temp2 = DT_GetMatrixRow();

	if( this->aPtr != NULL ){
		delete this->aPtr;
	}/* end if */

	if( this->sqPtr != NULL ){
		delete this->sqPtr;
	}/* end if */

	if( this->spPtrs != NULL ){
		for( i = 0; i < temp2; i++ ){
			if( this->spPtrs[ i ] != NULL ){
				delete this->spPtrs[ i ];
			}/* end if */
		}/* end for */

		delete this->spPtrs;
	}/* end if */

	this->aPtr = new i32[ temp1 ];

	if( this->aPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	this->sqPtr = new i32[ temp1];

	if( this->sqPtr == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	this->spPtrs = new d64 *[  temp2 ];

	if( this->spPtrs == NULL ){
		cout << "\n内存不足！" << __LINE__ << endl;
		exit( -1 );
	}/* end if */

	for( i = 0; i < temp2; i++ ){
		this->spPtrs[ i ] = new d64[ temp1 ];
		if ( this->spPtrs[ i ] == NULL ){
			cout << "\n内存不足！" << __LINE__ << endl;
			exit( -1 );
		}/* end if */
	}/* end for */
}/* end function DT_CreatFramework */

void Data::DT_Init()
{
	i32 temp1 = DT_GetMatrixColumn();
	i32 temp2 = DT_GetMatrixRow();
	i32 r, c;

	if ( this->spPtrs != NULL ){
		for ( r = 0; r < temp2; r++ ){
			for ( c = 0; c < temp1; c++ ){
				this->spPtrs[ r ][ c ] = 0.0;
			}/* end inner for */

			this->sqPtr[ r ] = r;
			this->aPtr[ r ] = 0;

		}/* end outer for */
	}/* end if */
	else cout << "\n数据存储结构不存在！" << endl;
}/* end function DT_Init */

void Data::DT_SortSequence( i32 dim )
{
	i32 i, j, temp1;
	i32 temp2 = DT_GetMatrixColumn();
	
	if( dim < 0 ){
		cout << "\n输入错误 " << endl;
		return;
	}/* end if */
	
	if ( this->spPtrs != NULL && this->sqPtr != NULL ){
		for ( i = 1; i < temp2; i++ ){
			for ( j = 0; j < temp2 - 1; j++ ){
				if ( this->spPtrs[ dim ][ this->sqPtr[ i ] ] > this->spPtrs[ dim ][ this->sqPtr[ i + 1 ] ] ){
					temp1 = this->sqPtr[ i ];
					this->sqPtr[ i ] = this->sqPtr[ i + 1 ];
					 this->sqPtr[ i + 1 ] = temp1;
				}/* end if */
			}/* end inner for */
		}/* end outer for */
	}/* end if */
	else cout << "\n数据结构不存在！" << endl;
}/* end function DT_SortSequence */

void Data::DT_RandSequence()
{
	i32 temp1 = DT_GetMatrixColumn();
	i32 i, temp2;

	for( i = 0; i < temp1; i++ ){
		this->sqPtr[ i ] = 0;
	}/* end for */

	i = 0;

	do{
		temp2 = rand() % temp1;
		if( !DT_IsInList( temp2, i ) ){
			this->sqPtr[ i ] = temp2;
			i++;
		}/* end if */
	}while( i < temp1 );
}/* end function DT_RandSequence */

void Data::DT_GetData( d64 *vPtr, i32 c ) const
{
	i32 i;
	i32 temp = DT_GetMatrixRow();

	for( i = 0; i < temp; i++ ){
		vPtr[ i ] = this->spPtrs[ i ][ c ];
	}/*end for */
}/* end function DT_GetData */

void Data::DT_GetSequence( i32 *vPtr ) const
{
	i32 i;
	i32 temp = DT_GetMatrixColumn();

	for( i = 0; i < temp; i++ ){
		vPtr[ i ] = this->sqPtr[ i ];
	}/* end for */
}/* end function DT_GetSequence */

Data::~Data()
{
	i32 i;
	i32 temp = DT_GetMatrixRow();
	delete this->sqPtr;
	delete this->aPtr;
	
	for( i = 0; i < temp; i++ ){
		delete this->spPtrs[ i ];
	}/* end for	*/

	delete this->spPtrs;
}/* end deconstuctor */