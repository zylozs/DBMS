#include "NormalForm.h"

ClosureSet* NormalForm::findClosureSet(ClosureSet* set, Relation* rel, int closureSize, int startIter)
{
	//Closing if statement (prevents infinite recursion) [so we hope]
	if (closureSize - startIter == 1)
	{
		Permutation perm(rel->attributes[startIter]);
		*set += perm;
		return set;
	}
}