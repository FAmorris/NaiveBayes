#include <cstdlib>
#include <iomanip>
#include "../inc/Data.h"

Data::Data( i32 r, i32 c, i32 nc )
{
	this->aPtr = NULL;
	this->spPtrs = NULL;
	this->sqPtr = NULL;

	this->setMatrixRow( r );
	this->setMatrixColumn( c );
	this->setNumOfClasses( nc );

	if( r > 0 || c > 0 ){
		this->creatFramework();
	}/* end if */
	else{
		cout << "\n数据存储结构在构造函数中未生成，若需要生成请设置参数。" << endl;
	}/* end else */
}/* end constructor Data */

bool Data::isInList( i32 element, i32 numOfElement ) const
{
	i32 i;

	for( i = 0; i < numOfElement; i++ ){
		if( this->sqPtr[ i ]  == element ){
			return true;
		}/* end	if */
	}/* end for */

	return false;

}/* end function DT_IsInList */

bool Data::isInData( d64 *dPtr ) const
{
	i32 r, c;
	i32 temp1 = this->getMatrixRow();
	i32 temp2 = this->getMatrixColumn();

	for( c = 0; c < temp2; c++ ){
		for( r = 0; r < temp1; r++ ){
			if( fabs( this->spPtrs[ r ][ c ] - dPtr[ r ] ) < 0.00001 ){
				return true;
			}/* end if */
		}/* end for */
	}/* end for */

	return false;
}/* end function DT_IsInData */

void Data::setMatrixRow( i32 r )
{
	this->row = ( r > 0 ) ? r : 0;
}/* end function DT_SetMatrixRow */

void Data::setMatrixColumn( i32 c )
{
	this->column = ( c > 0 ) ? c : 0;
}/* end function DT_SetMatrixColumn */

void Data::setNumOfClasses( i32 nc )
{
	this->numOfClasses = ( nc > 0 ) ? nc : 0;
}/* end function DT_SetNumOfClasses */

i32 Data::getMatrixRow( ) const
{
	return this->row;
}/* end function DT_GetMatrixRow */

i32 Data::getMatrixColumn( ) const
{
	return this->column;
}/* end function DT_GetMatrixColumn */

i32 Data::getNumOfClasses( ) const
{
	return this->numOfClasses;
}/* end function DT_GetNumOfClasses */

i32 *Data::getAimOutput() const
{
	return this->aPtr;
}/* end function DT_GetAimOutput */

d64 **Data::getSamples() const
{
	return this->spPtrs;
}/* end function DT_GetSamples */

void Data::creatFramework( )
{
	i32 i;
	i32 temp1 = this->getMatrixColumn();
	i32 temp2 = this->getMatrixRow();

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

	this->init();
}/* end function DT_CreatFramework */

void Data::init()
{
	i32 temp1 = this->getMatrixColumn();
	i32 temp2 = this->getMatrixRow();
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

void Data::sortSequence( i32 dim )
{
	i32 i, j, temp1;
	i32 temp2 = this->getMatrixColumn();
	
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

void Data::randSequence()
{
	i32 temp1 = this->getMatrixColumn();
	i32 i, temp2;

	for( i = 0; i < temp1; i++ ){
		this->sqPtr[ i ] = 0;
	}/* end for */

	i = 0;

	do{
		temp2 = rand() % temp1;
		if( !this->isInList( temp2, i ) ){
			this->sqPtr[ i ] = temp2;
			i++;
		}/* end if */
	}while( i < temp1 );
}/* end function DT_RandSequence */

void Data::getData( d64 *vPtr, i32 c ) const
{
	i32 i;
	i32 temp = this->getMatrixRow();

	for( i = 0; i < temp; i++ ){
		vPtr[ i ] = this->spPtrs[ i ][ c ];
	}/*end for */
}/* end function DT_GetData */

void Data::getSequence( i32 *vPtr ) const
{
	i32 i;
	i32 temp = this->getMatrixColumn();

	for( i = 0; i < temp; i++ ){
		vPtr[ i ] = this->sqPtr[ i ];
	}/* end for */
}/* end function DT_GetSequence */

Data::~Data()
{
	i32 i;
	i32 temp = this->getMatrixRow();
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
	i32 r = dt.getMatrixRow();
	i32 c = dt.getMatrixColumn();

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
	i32 temp1 = dt.getMatrixRow();
	i32 temp2 = dt.getMatrixColumn();

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