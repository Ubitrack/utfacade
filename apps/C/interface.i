/* Arbitrary module name */

%module (directors="1") ubitrack


/* Includes that will be added to the generated
xxx_wrap.c/xxx_wrap.cpp wrapper file. They will not be interpreted by
SWIG */

%{
#include <string>
#include <sstream>
#include <utFacade/Config.h>
#include <utFacade/SimpleFacade.h>
#include <utUtil/Logging.h>
#include <utUtil/Exception.h>
%}

%include "typemaps.i";
%include "std_vector.i"

/* Generate directors for C++ classes for which cross language polymorphism
shall be provided. This is especially needed for enabling C++ code to callback
Java methods.  This must come before the C/C++ declarations to be wrapped. */

%feature("director") SimplePoseReceiver;
%feature("director") SimpleErrorPoseReceiver;
%feature("director") SimpleMatrix3x4Receiver;
%feature("director") SimpleMatrix4x4Receiver;
%feature("director") SimpleDistanceReceiver;
%feature("director") SimpleButtonReceiver;
%feature("director") SimpleStringReceiver;
%feature("director") SimpleImageReceiver;
%feature("director") SimpleDataflowObserver;

%feature("director") SimplePosition2DReceiver;
%feature("director") SimplePosition2DListReceiver;
%feature("director") SimplePosition3DReceiver;
%feature("director") SimpleErrorPosition3DReceiver;
%feature("director") SimplePositionList3DReceiver;
%feature("director") SimpleErrorPositionList3DReceiver;

/* Needed to transfer memory ownership to Java, e.g. for C++ factory methods 
which create and return objects that are not known/owned/used in C++ code */

%newobject Ubitrack::Facade::SimpleFacade::getSimplePullSinkPose( const char * );







%include "carrays.i";

%array_class(double, doubleArrayClass);
%array_class(unsigned char, byteArrayClass);


/* needed for stl strings to be accessible as target language strings */

%include "std_string.i";


/* C/C++ declarations to be wrapped.  The paths are relative to the
working directory of swig, which is the directory where the invoking
SConscript file resides.  Attention: The order of includes matters!
Declarations must come before their usage, otherwise, SWIG will
generate generic type wrapper classes of style SWITTYPE_p_<xxx>. */

%include ../../src/utFacade/utFacade.h
%include ../../src/utFacade/Config.h
%include ../../../utcore/src/utCore.h

%include ../../src/utFacade/SimpleVectorTypes.h

%include ../../src/utFacade/SimpleDatatypes.h
%include ../../src/utFacade/SimpleFacade.h

%include ../../../utcore/src/utUtil/Logging.h




/* also wrap the dataflow generation (pattern matching) */
%inline %{
namespace Ubitrack { namespace Graph {
	std::string generateDataflow( const std::string& query );
	std::string dataflowToGraphviz( const std::string& dataflow );
}}
%}


%template(SimplePosition3DValue_Vector) std::vector<SimplePosition3DValue>;
%template(SimpleErrorPosition3DValue_Vector) std::vector<SimpleErrorPosition3DValue>;
%template(SimplePosition2DValue_Vector) std::vector<SimplePosition2DValue>;
