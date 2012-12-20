#ifndef __UBITRACK_CONFIG_H_INCLUDED__
#define __UBITRACK_CONFIG_H_INCLUDED__
#define UBITRACK_COMPONENTS_PATH "/home/mh/wd/Ubitrack/lib/ubitrack"
#define UBITRACK_COMPONENTS_RELAVIVEPATH "ubitrack"
#ifndef HAVE_GLEW 
#undef HAVE_GLEW
#endif
#ifndef HAVE_FREEGLUT 
#undef HAVE_FREEGLUT
#endif
#ifndef HAVE_LAPACK 
#define HAVE_LAPACK
#endif
#ifndef HAVE_OPENCV 
#define HAVE_OPENCV
#endif
#ifndef HAVE_COIN 
#undef HAVE_COIN
#endif
#ifndef HAVE_DIRECTSHOW 
#undef HAVE_DIRECTSHOW
#endif
#endif
