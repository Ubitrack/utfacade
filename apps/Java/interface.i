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

#ifdef SWIGCSHARP

%include "arrays_csharp.i";

// These typemaps cause parameters of type TYPE named ARGNAME to become IntPtr in C#.
%define %cs_marshal_intptr(TYPE, ARGNAME...)
        %typemap(ctype)  TYPE ARGNAME "void*"
        %typemap(imtype) TYPE ARGNAME "IntPtr"
        %typemap(cstype) TYPE ARGNAME "IntPtr"
        %typemap(in)     TYPE ARGNAME %{ $1 = ($1_ltype)$input; /* IntPtr */ %}
        %typemap(csin)   TYPE ARGNAME "$csinput"
       
        %typemap(out)    TYPE ARGNAME %{ $result = $1; %}
        %typemap(csout, excode=SWIGEXCODE) TYPE ARGNAME {
                IntPtr cPtr = $imcall;$excode
                return cPtr;
        }
        %typemap(csvarout, excode=SWIGEXCODE2) TYPE ARGNAME %{
                get {
                        IntPtr cPtr = $imcall;$excode
                        return cPtr;
                }
        %}

        %typemap(ctype)  TYPE& ARGNAME "void**"
        %typemap(imtype) TYPE& ARGNAME "ref IntPtr"
        %typemap(cstype) TYPE& ARGNAME  "ref IntPtr"
        %typemap(in)     TYPE& ARGNAME %{ $1 = ($1_ltype)$input; %}
        %typemap(csin)   TYPE& ARGNAME "ref $csinput"
%enddef 


#else 

%include "arrays_java.i";

#endif



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

/* Needed for array access to be possible from Java. */
#ifdef SWIGJAVA

%array_functions(signed char, byteArray);

#endif


/* needed for stl strings to be accessible as target language strings */

%include "std_string.i";


/* Wrap Ubitrack exceptions for static Ubitrack methods (not in SimpleFacade!) */
#ifdef SWIGJAVA
%javaexception("java.lang.Exception") generateDataflow {
  try {
     $action
  } catch (const Ubitrack::Util::Exception& e) {
    jclass clazz = jenv->FindClass("java/lang/Exception");
    std::ostringstream msg;
    msg << "Ubitrack error: " << e.what();
    jenv->ThrowNew(clazz, msg.str().c_str());
  }
}
#endif


/* C/C++ declarations to be wrapped.  The paths are relative to the
working directory of swig, which is the directory where the invoking
SConscript file resides.  Attention: The order of includes matters!
Declarations must come before their usage, otherwise, SWIG will
generate generic type wrapper classes of style SWITTYPE_p_<xxx>. */

%include utFacade/utFacade.h
%include utFacade/Config.h
%include utCore.h

%include utFacade/SimpleVectorTypes.h

%include utFacade/SimpleDatatypes.h
%include utFacade/SimpleFacade.h

%include utUtil/Logging.h




#ifdef SWIGCSHARP
%extend Ubitrack::Facade::SimpleImage {
	%apply unsigned char OUTPUT[] {unsigned char * where};
	
		void copyImageData( unsigned char* where )
	{ memcpy( where, $self->imageData, $self->imageSize ); }
	
	%cs_marshal_intptr(void*)
	void * getDataPointer( )
	{ return $self->imageData; }
	
	void copyImageDataToARGB32Pointer( void * where, int texWidth, int texHeight, const unsigned char alpha )
	{ 
		unsigned int* where2 = (unsigned int*) where;
		const unsigned int a = unsigned int(alpha) << 24;
		
		for (int i = 0; i < $self->height; i++)
        {
			unsigned int* where3 = where2 + i * texWidth;
			unsigned char* bytePointer = $self->imageData + i * $self->widthStep;
			for (int j = 0; j < $self->width; j++)
			{
				const unsigned int r = *bytePointer;
				bytePointer++;
				const unsigned int g = *bytePointer;
				bytePointer++;
				const unsigned int b = *bytePointer;
				bytePointer++;
				*where3 = a |  r << 16 | g << 8 | b;
				++where3;
				
			}
		}
		
	}
	/*
	void copyImageDataToBGRA32Pointer( void * where, int texWidth, int texHeight )
	{ 
		unsigned char* where2 = (unsigned char*) where;
		unsigned char* bytePointer = $self->imageData;
		for (int i = 0; i < $self->height; i++)
        {
			int baseStartindex = i * $self->width;
            int baseOtherindex = i * texWidth;
			for (int j = 0; j < $self->width; j++)
			{
				int startindex = (baseStartindex + j) * 3;
				int otherindex = (baseOtherindex + j) * 4;

				where2[otherindex+0] = bytePointer[startindex + 2];
				where2[otherindex+1] = bytePointer[startindex + 1];
				where2[otherindex+2] = bytePointer[startindex + 0];
				where2[otherindex+3] = 255;
				
			}
		}
		
	}*/
	
	
	
	}
	
	
	
	
#endif

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
