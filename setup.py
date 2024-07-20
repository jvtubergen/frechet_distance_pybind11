from setuptools import setup, Extension
import pybind11

ext_modules = [
    Extension(
        'frechet_distance_module',
        [
	        "src/pybind11.cpp",
	        "src/frechet_light.cpp",
	        "src/frechet_naive.cpp",
	        "src/geometry_basics.cpp",
	        "src/filter.cpp",
	        "src/orth_range_search.cpp",
	        "src/parser.cpp",
	        "src/query.cpp",
	        "src/times.cpp",
	        "src/curve.cpp",
        ]
    )
]

setup(
    name='frechet_distance_module',
    version='0.1',
    ext_modules=ext_modules,
)