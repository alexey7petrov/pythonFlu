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
## See https://csrcs.pbmr.co.za/svn/nea/prototypes/reaktor/pyfoam
##
## Author : Alexey PETROV
##


#--------------------------------------------------------------------------------
#to use wrapped unit to uncomment next two line and rename class componentReference to componentReference_

#from componentReferenceList_ import *
#componentReferenceList = PtrList_componentReference



#--------------------------------------------------------------------------------
class componentReference:
    def __init__( self, *args ):
        #- Construct from components
        try:
            self._init__with_6_param( *args )
            return
        except AssertionError:
            pass
        #- - Construct from dictionary
        try:
            self._init__with_2_param( *args )
            return
        except AssertionError:
            pass
        
        #- - Construct from self
        try:
            self._init__self( *args )
            return
        except AssertionError:
            pass
        
        raise AssertionError()
        
        
    #-----------------------------------------------------------------------------  
    def _init__with_6_param(self, *args):
        if len(args) != 6:
           raise AssertionError( "len( args ) != 6" )
        
        argc = 0
        from Foam.finiteVolume import fvMesh
        if args[ argc ].__class__ != fvMesh:
           raise AssertionError( "args[ argc ].__class__ != fvMesh" )
        mesh = args[ argc ]; argc +=1
        
        from Foam.finiteVolume import word
        if args[ argc ].__class__ != word:
           raise AssertionError( "args[ argc ].__class__ != word" )
        patchName = args[ argc ]; argc +=1
        
        try:
           faceIndex = int( args[ argc ] )
        except ValueError:
           raise AttributeError("The third arg is not label")
        argc +=1
        
        try:
           dir_ = int( args[ argc ] )
        except ValueError:
           raise AttributeError("The fourth arg is not direction")
        if dir_ < 0 or dir_>255:
           raise AttributeError("The fourth arg is not direction") 
        argc +=1
        
        try:
           value = float( args[ argc ] )
        except ValueError:
           raise AttributeError ("The fifth arg is not scalar")
        
        from Foam.OpenFOAM import polyPatchID
        self.patchID_ = polyPatchID( patchName, mesh.boundaryMesh() )
        self.faceIndex_ = faceIndex
        self.dir_ = dir_
        self.value_ = value
        self.checkPatchFace(mesh)
        
        
    #-----------------------------------------------------------------------------
    def _init__with_2_param( self, *args ):
        if len(args) != 2:
           raise AssertionError( "len( args ) != 2" )
        argc = 0
        
        from Foam.finiteVolume import fvMesh
        if args[ argc ].__class__ != fvMesh:
           raise AssertionError( "args[ argc ].__class__ != fvMesh" )
        mesh = args[ argc ]; argc +=1
        
        from Foam.finiteVolume import dictionary
        if args[ argc ].__class__ != dictionary:
           raise AssertionError( "args[ argc ].__class__ != dcitionary" )
        dict_ = args[ argc ]
        
        from Foam.OpenFOAM import polyPatchID, word, readLabel, readScalar
        self.patchID_ = polyPatchID( dict_.lookup( word( "patch" ) ), mesh.boundaryMesh() )
        self.faceIndex_ = readLabel( dict_.lookup( word( "face" ) ) )
        self.dir_ = self.getDir( dict_ )
        self.value_ = readScalar( dict_.lookup( word( "value" ) ) )
        self.checkPatchFace(mesh)
    
    
    #----------------------------------------------------------------------------
    def _init__self(self, *args):
        if len(args) != 1:
           raise AssertionError( "len( args ) != 1" )
        
        argc = 0
        if args[ argc ].__class__ != self.__class__:
           raise AssertionError( "args[ argc ].__class__ != self.__class__" )
        clone = args[ argc ]
        
        self.patchID_ = clone.patchID_
        self.faceIndex_ = clone.faceIndex_
        self.dir_ = clone.dir_
        self.value_ = clone.value_
        
        
        
    #------------------------------------------------------------------------------    
    #- Create direction given a name
    def getDir( self, dict_ ):
        from Foam.OpenFOAM import dictionary
        if dict_.__class__ != dictionary:
           raise AttributeError( "dict_.__class__ != dictionary" )
        
        from Foam.OpenFOAM import word
        dirName = str( word( dict_.lookup( word( "direction" ) ) ) )
        
        if dirName == "x" or dirName == "X":
           from Foam.OpenFOAM import vector
           return vector.X
        elif dirName == "y" or dirName == "Y":
           from Foam.OpenFOAM import vector
           return vector.Y
        elif dirName == "z" or dirName == "Z":
           from Foam.OpenFOAM import vector
           return vector.Z
        else:
           raise IOError("Direction %s not recognize. Use x,y or z " %dirName )
     
     
    #-----------------------------------------------------------------------------
    #- Check if patch face is in range
    def checkPatchFace( self, mesh ):

        from Foam.finiteVolume import fvMesh
        if mesh.__class__ != fvMesh:
           raise AssertionError( " mesh.__class__ != fvMesh " )
        
        if not self.patchID_.active() or  self.faceIndex_ >= mesh.boundaryMesh()[self.patchID_.index()].ext_size():
           raise AssertionError ("Non-existing patch or index out of range ")
        
        pass
     
     
    #-----------------------------------------------------------------------------
    # - clone
    def clone( self ):
         return componentReference( self )
    
    #-----------------------------------------------------------------------------
    #- Return patch index
    def patchIndex( self ):
        return self.patchID_.index()
    
    
    #------------------------------------------------------------------------------
    #- Return face index
    def faceIndex( self ):
        return self.faceIndex_
        
    
    #-------------------------------------------------------------------------------
    #- Return direction
    def dir( self ):
        return self.dir_
    
    
    #--------------------------------------------------------------------------------
    #- Return value
    def value( self ):
        return self. value_


#------------------------------------------------------------------------------------
class iNew:
    def __init__( self, mesh_ ):
       from Foam.finiteVolume import fvMesh
       if mesh_.__class__ != fvMesh:
          raise AssertionError( " mesh_.__class__ != fvMesh " )
       
       self.mesh_ = mesh_


    #---------------------------------------------------------------------------------
    def __call__(self, is_):
       #from Foam.OpenFOAM import Istream, ITstream
       #if is_.__class__ != Istream or is_.__class__ != ITstream:
       #   raise AssertionError( "is_.__class__ != Istream" )
       
       from Foam.OpenFOAM import dictionary
       crDict = dictionary(is_)
       
       return componentReference( self.mesh_, crDict )
       

#--------------------------------------------------------------------------------------          
def componentReferenceList( is_, inewt):
    #from Foam.OpenFOAM import ITstream
    #if is_.__class__ != ITstream or is_.__class__ != Istream:
    #   raise AssertionError( "is_.__class__ != Istream" )
    
    if inewt.__class__ != iNew:
       raise AssertionError( "inewt.__class__ != iNew" )
    
    is_.fatalCheck("PtrList<T>::read(Istream& is, const INew& inewt)")
    
    from Foam.OpenFOAM import token
    firstToken = token(is_);
   
    is_.fatalCheck("PtrList<T>::read(Istream& is, const INew& inewt) : reading first token" )
    
    result = []
    if firstToken.isLabel():
       #  Read size of list
       s = firstToken.labelToken()
       
       # Read beginning of contents
       listDelimiter = is_.readBeginList("PtrList")
       
       if s:
          if listDelimiter == token.BEGIN_LIST:
             for index in range(s):
                 result.append( inewt( is_ ) )
                 is_.fatalCheck( "PtrList<T>::read(Istream& is, const INew& inewt) : reading entry" )
          else:
             tmp = inewt( is_ )
             result.append( tmp )
             is_.fatalCheck( "PtrList<T>::read(Istream& is, const INew& inewt) : reading the single entry" ) 

             for index in range(s):
                 result.append( tmp.clone() )
                    
       is_.readEndList("PtrList")
    
    elif firstToken.isPunctuation():
       if firstToken.pToken() != token.BEGIN_LIST:
          raise IOError("incorrect first token, '(', found %s" %firstToken.info() )
       
       lastToken = token (is_)
       
       sllPtrs = []
       
       while not ( lastToken.isPunctuation() and lastToken.pToken() == token.END_LIST ):
          is_.putBack( lastToken )
          sllPtrs.append( inewt(is_) )
          is_ >> lastToken
       
       for index in range( len( sllPtrs ) ):
           result.append( sllPtrs[ index ] )
       
    else:
       raise IOError("incorrect first token, expected <int> or '(', found %s" %firstToken.info() )

    return result