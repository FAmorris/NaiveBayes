#include <cstdlib>
#include <iomanip>
#include "../inc/Data.h"
/**
 * @brief	Data类的构造函数，用于对成员变量的初始化
 * @param i32 r 数据矩阵行数
 * @param i32 c 数据矩阵列数
 * @param i32 nc 样本类别个数
 * @retval  无
 */
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
	else cout << "\n数据存储结构在构造函数中未生成，若需要生成请设置参数。" << endl;
}/* end constructor Data */

/**
 * @brief	判断元素是否存在序列当中
 * @param i32 element 要判断的元素
 * @param i32 numOfElement 序列长度
 * @retval  无
 */
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

/**
 * @brief	判断样本点是否存在样本集合中
 * @param d64 *dPtr 样本点数据指针
 * @retval  无
 */
i32 Data::isInData( d64 *dPtr ) const
{
	i32 r, c;
	i32 temp1 = this->getMatrixRow();
	i32 temp2 = this->getMatrixColumn();
	d64 error = 0.0;

	for( c = 0; c < temp2; c++ ){
		for( r = 0; r < temp1; r++ ){
			error += ( this->spPtrs[ r ][ c ] - dPtr[ r ] );
		}/* end for */
		if( error < PRECISION ) return c;
		error = 0.0;
	}/* end for */
	return -1;
}/* end function DT_IsInData */

/**
 * @brief	设置矩阵行数
 * @param i32 r 行数
 * @retval  无
 */
void Data::setMatrixRow( i32 r )
{
	this->row = ( r > 0 ) ? r : 0;
}/* end function DT_SetMatrixRow */

/**
 * @brief	设置矩阵列数
 * @param i32 c 列数
 * @retval  无
 */
void Data::setMatrixColumn( i32 c )
{
	this->column = ( c > 0 ) ? c : 0;
}/* end function DT_SetMatrixColumn */

/**
 * @brief	设置样本类别个数
 * @param i32 nc 类别个数
 * @retval  无
 */
void Data::setNumOfClasses( i32 nc )
{
	this->numOfClasses = ( nc > 0 ) ? nc : 0;
}/* end function DT_SetNumOfClasses */

/**
 * @brief	读取矩阵行数
 * @param 无
 * @retval  i32 类型数据 行数
 */
i32 Data::getMatrixRow( ) const
{
	return this->row;
}/* end function DT_GetMatrixRow */

/**
 * @brief	读取矩阵列数
 * @param 无
 * @retval  i32 类型数据 列数
 */
i32 Data::getMatrixColumn( ) const
{
	return this->column;
}/* end function DT_GetMatrixColumn */

/**
 * @brief	读取样本集合类别个数
 * @param 无
 * @retval  i32 类型数据 类别个数
 */
i32 Data::getNumOfClasses( ) const
{
	return this->numOfClasses;
}/* end function DT_GetNumOfClasses */

/**
 * @brief	读取样本集合中样本点所属类别
 * @param 无
 * @retval  i32 类型指针
 */
i32 *Data::getAimOutput() const
{
	return this->aPtr;
}/* end function DT_GetAimOutput */

/**
 * @brief	读取样本集合所有样本点
 * @param 无
 * @retval  d64 类型二维指针
 */
d64 **Data::getSamples() const
{
	return this->spPtrs;
}/* end function DT_GetSamples */

/**
 * @brief	生成数据存储框架
 * @param 无
 * @retval  无
 */
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

/**
 * @brief	初始化数据存储框架
 * @param 无
 * @retval  无
 */
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

/**
 * @brief	根据指定维度对样本数据进行排序
 * @param i32 dim 维度
 * @retval  无
 */
void Data::sortSequence( i32 dim )
{
	i32 i, j, temp1;
	i32 temp2 = this->getMatrixColumn();
	
	if( dim < 0 ){
		cout << "\n输入错误 " << endl;
		return;
	}/* end if */
	
	/* 按指定维度对样本数据进行升序排序 */
	if ( this->spPtrs != NULL && this->sqPtr != NULL ){
		for ( i = 1; i < temp2; i++ ){
			for ( j = 0; j < temp2 - 1; j++ ){
				if ( this->spPtrs[ dim ][ this->sqPtr[ i ] ] > this->spPtrs[ dim ][ this->sqPtr[ i + 1 ] ] ){ /* 根据当前维度进行比较 */
					temp1 = this->sqPtr[ i ];
					this->sqPtr[ i ] = this->sqPtr[ i + 1 ]; /* 将索引顺序序列进行调换 */
					 this->sqPtr[ i + 1 ] = temp1;
				}/* end if */
			}/* end inner for */
		}/* end outer for */
	}/* end if */
	else cout << "\n数据结构不存在！" << endl;
}/* end function DT_SortSequence */

/**
 * @brief	生成一个随机索引序列
 * @param 无
 * @retval  无
 */
void Data::randSequence()
{
	i32 temp1 = this->getMatrixColumn();
	i32 i, temp2;

	for( i = 0; i < temp1; i++ ){
		this->sqPtr[ i ] = 0; /* 初始化为0 */
	}/* end for */

	i = 0;

	do{
		temp2 = rand() % temp1; /* 生成随机数 */
		if( !this->isInList( temp2, i ) ){ /* 判断随机数是否存在序列当中 */
			this->sqPtr[ i ] = temp2;
			i++;
		}/* end if */
	}while( i < temp1 );
}/* end function randSequence */

/**
 * @brief	读取样本集合中一个样本点
 * @param d64 *vPtr 读取后数据存储数组
 * @param i32 c 样本点在样本集合中的索引
 * @retval  无
 */
void Data::getData( d64 *vPtr, i32 c ) const
{
	i32 i;
	i32 temp = this->getMatrixRow();

	for( i = 0; i < temp; i++ ){
		vPtr[ i ] = this->spPtrs[ i ][ c ];
	}/*end for */
}/* end function DT_GetData */

/**
 * @brief	读取样本索引序列
 * @param i32*vPtr 读取后存储数组
 * @retval  无
 */
void Data::getSequence( i32 *vPtr ) const
{
	i32 i;
	i32 temp = this->getMatrixColumn();

	for( i = 0; i < temp; i++ ){
		vPtr[ i ] = this->sqPtr[ i ];
	}/* end for */
}/* end function DT_GetSequence */

/**
 * @brief	析构函数，释放内存
 * @param 无
 * @retval  无
 */
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

/**
 * @brief	输出流重载函数，用于显示样本数据
 * @param ostream &output 标准输出流类引用
 * @param cost Data &dt Data 类常引用
 * @retval  ostream & 标准输出流引用
 */
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

/**
 * @brief	输入流重载函数，用于输入样本集合数据
 * @param istream &input 标准输入流类引用
 * @param Data &dt Data 类引用
 * @retval  istream & 标准输出流引用
 */
istream &operator>>( istream &input, Data &dt )
{
	i32 i, j;
	i32 temp1 = dt.getMatrixRow();
	i32 temp2 = dt.getMatrixColumn();

	if( dt.spPtrs == NULL ){
		cout << "\n数据存储结构不存在！" << endl;
		return input;
	}/* end if */

	cout << "\n输入样本输入(个数：" << temp2  << "，维数："<< temp1 << ")" << endl;

	for( i = 0; i < temp2; i++ ){
		for( j = 0; j < temp1; j++ ){
			input >>dt.spPtrs[ j ][ i ];
		}/* end inner for */
	}/*end outer for */

	cout << endl;
	cout << "\n输入样本类别（类别：1 - " << dt.getNumOfClasses() << "):" << endl;

	for( i = 0; i < temp2; i++ ){
		input >> dt.aPtr[ i ];
	}/* end for */
	cout << endl;
	return input;
}/* end function operator>> */