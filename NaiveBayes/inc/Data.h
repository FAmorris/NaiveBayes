#ifndef __DATA_H
#define __DATA_H

#include <iostream>
#include "UserType.h"
using namespace std;

class Data{
	friend ostream &operator<<( ostream &, const Data & );
	friend istream &operator>>( istream &, Data & );

public :
	Data( i32 r, i32 c, i32 nc );
	~Data();

	void setMatrixRow( i32 r );
	void setMatrixColumn( i32 c );
	void setNumOfClasses( i32 nc );

	void getData( d64 *vPtr, i32 c ) const;
	void getSequence( i32 *vPtr ) const;
	i32 getMatrixRow( ) const;
	i32 getMatrixColumn( ) const;
	i32 getNumOfClasses( ) const;
	bool isInData( d64 *dPtr ) const;
	bool isInList( i32 element, i32 numOfElement ) const;
	i32 *getAimOutput() const;
	d64 **getSamples() const;

	void sortSequence( i32 dim );
	void randSequence( );
	void creatFramework( );
	void init();

private :
	i32 row;
	i32 column;
	i32 numOfClasses;

	d64 **spPtrs;
	i32 *aPtr;
	i32 *sqPtr;
};

#endif /* __DATA_H */
