#ifndef __DATA_H
#define __DATA_H

#include <iostream>
#include "UserType.h"
using namespace std;

class Data{
	friend ostream &operator<<( ostream &, const Data & );
	friend istream &operator>>( istream &, Data & );

public :
	Data( i32 = 0, i32 = 0, i32 = 0 );
	~Data();

	void DT_SetMatrixRow( i32 r );
	void DT_SetMatrixColumn( i32 c );
	void DT_SetNumOfClasses( i32 nc );

	void DT_GetData( d64 *vPtr, i32 c ) const;
	void DT_GetSequence( i32 *vPtr ) const;
	i32 DT_GetMatrixRow( ) const;
	i32 DT_GetMatrixColumn( ) const;
	i32 DT_GetNumOfClasses( ) const;
	i32 DT_IsInData( d64 *dPtr ) const;
	i32 DT_IsInList( i32 element, i32 numOfElement ) const;

	void DT_SortSequence( i32 dim );
	void DT_RandSequence( );
	void DT_CreatFramework( );
	void DT_Init();

private :
	i32 row;
	i32 column;
	i32 numOfClasses;

	d64 **spPtrs;
	i32 *aPtr;
	i32 *sqPtr;
};

#endif /* __DATA_H */
