#include <iostream>
#include "../inc/NaiveBayes.h"
using namespace std;

NaiveBayes::NaiveBayes( i32 r, i32 c, i32 nc, i32 lm )
	: nbData( r, c, nc )
{
	NB_SetLanmda( lm );
}/* end constructor */