#include <cstdlib>
#include <iomanip>
#include "../inc/Data.h"

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

	DT_Init();
}/* end function DT_CreatFramework */

void Data::DT_Init()
{
	i32 temp1 = DT_GetMatrixColumn();
	i32 temp2 = DT_GetMatrixRow();
	i32 r, c;

	if ( this->spPtrs != NULL ){
		for ( c = 0; c < temp1; c++ ){
			for ( r = 0; r < temp2; r++ ){
				this->spPtrs[ r ][ c ] = 0.0;
			}/* end inner for */

			this->sqPtr[ c ] = c;
			this->aPtr[ c ] = 0;

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

ostream &operator<<( ostream &output, const Data &dt )
{
	i32 i, j, n;
	i32 temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
	i32 r = dt.DT_GetMatrixRow();
	i32 c = dt.DT_GetMatrixColumn();

	if( dt.spPtrs == NULL || dt.aPtr == NULL ){
		if( !dt.spPtrs ) output << "\n样本数据不存在!" << endl;
		if( !dt.aPtr ) output << "\n样本输出不存在！" << endl;
		return output;
	}/* end if */

	temp1 = c / 10;
	temp2 = c % 10;

	if( temp1 != 0 ){
		
		for( n = 0; n < temp1; n++ ){
			output << "\n样本输入：" << temp3 << "-" << temp4 + 10 << endl;
			for( i = 0; i < r + 1; i++ ){

				if( i == r ) output << "\n样本输出：" << endl;

				for( j = temp3; j < temp4 + 10; j++ ){
					if ( i < r ) output << setprecision( 3 ) << fixed << dt.spPtrs[ i ][ j ] << " ";
					else output << setprecision( 3 ) << fixed << dt.aPtr[ j ] << " ";
				}/* end for */
				output << endl;
			}/* end for */
			output << endl;

			temp3 = temp4 + 10;
			temp4 += 10;
		}/*end for */
		output << endl;
	}/* end if */

	if( temp2 != 0 ){
		output << "\n样本输入：" << temp3 << "-" << temp4 + temp2 << endl;
		for( i = 0; i < r + 1; i++ ){
			if( i == r ) output << "\n样本输出：" << endl;

			for( j = temp3; j < temp4 + temp2; j++ ){

				if( i < r ) output << setprecision( 3 ) << fixed << dt.spPtrs[ i ][ j ] << " ";
				else output << setprecision( 3 ) << fixed << dt.aPtr[ j ] << " ";
			}/* end inner for */
			output << endl;
		}/* end outer for*/
		output << endl;
	}/*end if */
	return output;
}/* end function operator<< */

istream &operator>>( istream &input, Data &dt )
{
	i32 i, j;
	i32 temp1 = dt.DT_GetMatrixRow();
	i32 temp2 = dt.DT_GetMatrixColumn();

	if( dt.spPtrs == NULL ){
		cout << "\n数据存储结构不存在！" << endl;
		return input;
	}/* end if */

	cout << "\n输入样本输入：" << endl;

	for( i = 0; i < temp2; i++ ){
		for( j = 0; j < temp1; j++ ){
			input >>dt.spPtrs[ j ][ i ];
		}/* end inner for */
	}/*end outer for */

	cout << endl;
	cout << "\n输入样本输出：" << endl;

	for( i = 0; i < temp2; i++ ){
		input >> dt.aPtr[ i ];
	}/* end for */
	cout << endl;
	return input;
}/* end function operator>> */