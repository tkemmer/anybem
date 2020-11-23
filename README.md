# AnyBEM - Nonlocal Protein Electrostatics in Impala
[![](https://img.shields.io/github/license/tkemmer/CuNESSie.jl?style=for-the-badge)](https://github.com/tkemmer/ImplicitArrays.jl/blob/master/LICENSE)

The *AnyBEM* library provides domain-specific variants of the implicit representations and matrix-vector products from [`NESSie.jl`](https://github.com/tkemmer/nessie.jl) and [`CuNESSie.jl`](https://github.com/tkemmer/cunessie.jl) for the [Impala](https://github.com/anydsl) language.


## Getting started

### Requirements
 * [CMake 3.12](https://cmake.org) (or above)
 * [GCC](https://gcc.gnu.org/) or [Clang](https://clang.llvm.org/)
   (C++14-compatible)
 * [AnyDSL Runtime Library](https://github.com/AnyDSL/runtime)
 * [clipp](https://github.com/muellan/clipp) (optional, for tools only)
 * [Badhron](https://github.com/tkemmer/badhron) (optional, for testing only)

 ### Installation
 ```sh
 git clone https://github.com/tkemmer/anybem.git
 mkdir anydsl/build
 cd anydsl/build
 cmake ..
```

### Configuration options
Configuration options can be provided by appending the respective option-value tuples in the form `-D<option>=<value>` to the above `cmake` command:

|Option              | Values        | Description                                   |
|--------------------|---------------|-----------------------------------------------|
|`AnyBEM_BACKEND`    | **cpu**, cuda | Back end to be used for matrix multiplication |
|`AnyBEM_DEVICE`     | **0**, ...    | ID of device to be used with CUDA back end    |
|`AnyBEM_INTRINSICS` | f32, **f64**  | Floating-point precision level for intrinsics |

Default values are denoted by a bold font.


## Features

Most functionality currently provided by AnyBEM is showcased through the `anybem` tool, which is built automatically alongside the AnyBEM libraries. The tool can be found in the `tools/cli` directory.

```
NAME
AnyBEM - Nonlocal Protein Electrostatics in Impala

SYNOPSIS
        ./cli/anybem <hmo file> [--eps-omega <val>] [--eps-sigma <val>] [--eps-inf <val>]
            [--lambda <val>]

OPTIONS
        <hmo file>  Input file with a triangulated surface model and charges
        --eps-omega Dielectric constant of the solute (default: 2.000000)
        --eps-sigma Dielectric constant of the solvent (default: 78.000000)
        --eps-inf   Large-scale solvent response (default: 1.800000)
        --lambda    Correlation length scale (in Angstrom; default: 20.000000)
```
