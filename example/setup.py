# Available at setup time due to pyproject.toml
from pybind11.setup_helpers import Pybind11Extension
from setuptools import setup

__version__ = "0.0.1.dev0"


ext_modules = [
    Pybind11Extension(
        "Test",
        ["src/main.cpp"],
        extra_compile_args = ['-O2', '-Wall']
    ),
]

setup(
    name="Test",
    version=__version__,
    ext_modules=ext_modules,
    install_requires=[
        'pybind11==2.10.3'
    ],
    package_data={
        "Test":["py.typed"],
    },
    packages=["Test"],
    zip_safe=False,
    python_requires=">=3.8",
)
