#include "NormalForm.h"
#include <iostream>

ClosureSet NormalForm::findClosureSet(Relation rel, int closureSize)
{
	return findPermutations(Permutation() , rel, closureSize);
}

ClosureSet NormalForm::findPermutations(Permutation prefix, Relation rel, int closureSize)
{
	Relation tmpRel = rel;
	ClosureSet set;
	if (closureSize == 0)
	{
		set += prefix;
		return set;
	}

	for each (char c in tmpRel.attributes)
	{
		set += findPermutations(prefix + Permutation(c), Relation(tmpRel.attributes.substr(1)), closureSize - 1);
	}
}