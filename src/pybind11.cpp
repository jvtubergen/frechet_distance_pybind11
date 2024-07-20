#include "defs.h"
#include "query.h"
#include <vector>
#include <tuple>

using PointList = std::vector<std::tuple<double, double>>;

// Convert a vector of tuples (with doubles) into a Curve object.
Curve curveFromPointList(std::vector<std::tuple<double, double>> ps)
{
    Points points = {};
    for (auto p: ps) {
		double a = std::get<0>(p);
		double b = std::get<1>(p);
        Point _p = Point { a, b };
        points.push_back(_p);
    }

    Curve c = Curve(points);
    return c;
}

// Compute whether the Fréchet distance between two curves are below a given distance threshold.
bool compute_single_threshold(PointList source, PointList target, distance_t distance) 
{
	Curve c1 = curveFromPointList(source);
	Curve c2 = curveFromPointList(target);
   
	Query query(""); // Not using curve directory, but have to provide one.
	query.setSourceCurve(c1);
	query.setQueryCurve(c2, distance);
	query.setAlgorithm("light");
	query.getReady();
	query.run();

	Results results = query.getResults();
	// assert(results.size() == 1);
    // We compute one result (because one query/target curve), and can find one valid candidate (the source curve).
	return results[0].curve_ids.size() == 1;
}
