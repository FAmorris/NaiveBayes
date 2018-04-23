#ifndef __NAIVEBAYES_H
#define __NAIVEBAYES_H

#include "Data.h"

typedef struct{
	d64 **xPtrs;
	d64 **pPtrs;
}PrbDisbTypeDef, *PrbDisbTypeDefPtr;

class NaiveBayes{
public :
	NaiveBayes( i32 r = 0, i32 c = 0, i32 nc = 0, i32 lm = 0 );
	
	void NB_CaculationProbability();
	void NB_DifferClassesTotalCal();
	void NB_SetLanmda( i32 lm );

	i32 NB_ClassifyInput( d64 *vPtr, i32 numOfElement ) const;
	i32 NB_GetLanmda() const;

	Data nbData;
private :
	d64 *prbPtr;
	i32 *cntPtr;
	i32 lanmda;
	PrbDisbTypeDefPtr disPtr;
};
#endif  /* __NAIVEBAYES_H */
