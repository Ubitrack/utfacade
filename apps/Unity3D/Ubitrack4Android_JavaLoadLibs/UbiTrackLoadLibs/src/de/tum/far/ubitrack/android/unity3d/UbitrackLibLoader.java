package de.tum.far.ubitrack.android.unity3d;
import org.opencv.android.OpenCVLoader;

import android.os.Bundle;
import android.util.Log;

import com.unity3d.player.UnityPlayerNativeActivity;


public class UbitrackLibLoader extends UnityPlayerNativeActivity {

	static String TAG = "ubitrack";
	static{
		
		Log.i(TAG,"gnustl_shared");
		loadLibrary("gnustl_shared");
		
		Log.i(TAG,"loading opencv");
		 if (!OpenCVLoader.initDebug()) {
			 Log.e(TAG,"OpenCVLoader.initDebug");
		        // Handle initialization error
		    }
		 Log.i(TAG,"opencv loaded");
		 
		 
		Log.i(TAG,"log4cpp");
		loadLibrary("log4cpp");		
		Log.i(TAG,"utCore");
		loadLibrary("utCore");
		Log.i(TAG,"utVision");
		loadLibrary("utVision");
		Log.i(TAG,"utDataflow");
		loadLibrary("utDataflow");
		Log.i(TAG,"Ubitrack");
		loadLibrary("Ubitrack");
		Log.i(TAG,"ubitrack_dotnet_swig");
		loadLibrary("ubitrack_dotnet_swig");		
		
		
	}
	
	public static boolean loadLibrary(String paramString)
	{
		try
		{
			System.loadLibrary(paramString);			
			return true;
		}
		catch (UnsatisfiedLinkError localUnsatisfiedLinkError)
		{			
			Log.e(TAG,"loadLibrary", localUnsatisfiedLinkError);
		} 
		return false;
	}
	
	  protected void onCreate(Bundle savedInstanceState) {

	    // call UnityPlayerActivity.onCreate()
	    super.onCreate(savedInstanceState);
   
	    
	  }
} 
