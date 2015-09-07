/*
 * KruskalMSF.cpp
 *
 *  Created on: 03.09.2015
 *      Author: Henning
 */

#include "KruskalMSF.h"
#include "BfsSpanningForest.h"
#include "../structures/UnionFind.h"

namespace NetworKit {

struct MyEdge {
	node from;
	node to;
	edgeweight weight;

	MyEdge(node u, node v, edgeweight ew) {
		from = u;
		to = v;
		weight = ew;
	}

	MyEdge() {
		from = none;
		to = none;
		weight = 0;
	}

	bool operator<(const MyEdge& other) {
		return this->weight > other.weight; // Note the switch in the operator!
	}
};


NetworKit::KruskalMSF::KruskalMSF(const Graph& G): SpanningForest(G) {

}

void NetworKit::KruskalMSF::run() {
	if (true || G.isWeighted()) { // FIXME: remove true when SpanningForest is fixed!
		count z = G.upperNodeIdBound();
		forest = G.copyNodes();
		UnionFind uf(z);

		// sort edges in decreasing weight order
		std::vector<MyEdge> sortedEdges; // (m);
		G.forEdges([&](node u, node v, edgeweight ew, edgeid eid) {
//			INFO("insert edge (", u, ", ", v, ") with weight ", ew);
			MyEdge myEdge(u, v, ew);
			sortedEdges.push_back(myEdge);
		});
		std::sort(sortedEdges.begin(), sortedEdges.end());

		// process in decreasing weight order
		for (auto e: sortedEdges) {
			node u = e.from;
			node v = e.to;
//			INFO("process edge (", u, ", ", v, ") with weight ", e.weight);

			// if edge does not close cycle, add it to tree
			if (uf.find(u) != uf.find(v)) {
				forest.addEdge(u, v);
				uf.merge(u, v);
			}
		}
	}
	else {
		BfsSpanningForest sf(G);
		forest = sf.generate();
	}
}

} /* namespace NetworKit */