## pythonFlu - Python wrapping for OpenFOAM C++ API
## Copyright (C) 2010- Alexey Petrov
## Copyright (C) 2009-2010 Pebble Bed Modular Reactor (Pty) Limited (PBMR)
## 
## This program is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.
## 
## See https://vulashaka.svn.sourceforge.net/svnroot/vulashaka
##
## Author : Alexey PETROV
##


#---------------------------------------------------------------------------
from src.finiteVolume.finiteVolume.fvm.fvmDdt import *
from src.finiteVolume.finiteVolume.fvm.fvmD2dt2 import *
from src.finiteVolume.finiteVolume.fvm.fvmDiv import *
from src.finiteVolume.finiteVolume.fvm.fvmSup import *
from src.finiteVolume.finiteVolume.fvm.fvmLaplacian import *


#---------------------------------------------------------------------------
ddt = fvm_ddt

d2dt2 = fvm_d2dt2

div = fvm_div

laplacian = fvm_laplacian

Sp = fvm_Sp


#---------------------------------------------------------------------------
