#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "defs.h"
#include "query.h"
#include <vector>
#include <tuple>

namespace py = pybind11;

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

PYBIND11_MODULE(frechet_distance_module, m) {
    py::class_<Curve>(m, "Curve");
    m.def("compute_single_threshold", &compute_single_threshold, py::arg("source"), py::arg("target"), py::arg("distance"),
          "A function that checks Fréchet distance between two Curves is below the provided threshold.");
}
