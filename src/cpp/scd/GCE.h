/* GCE.h
 *
 * Created on: 06.05.2013
 * Author: cls
 */


#ifndef GCE_H_
#define GCE_H_

#include <unordered_set>

#include "SelectiveCommunityDetector.h"


namespace NetworKit {


/**
 * The Greedy Community Expansion algorithm.
 *
 * Greedily adds nodes from the shell to improve community quality.
 */
class GCE: public NetworKit::SelectiveCommunityDetector {

public:

	GCE(const Graph& G);


	std::map<node, std::set<node> >  run(std::set<unsigned int>& seeds) override;

	/**
	 * @param[in]	s	seed node
	 *
	 * @param[out]		community as a set of nodes
	 */
	std::set<node> expandSeed(node s);

protected:



};

} /* namespace NetworKit */
#endif
