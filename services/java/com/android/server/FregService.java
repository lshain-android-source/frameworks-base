
package com.android.server;

import android.os.IFregService;
import android.content.Context;
import android.util.Slog;

public class FregService extends IFregService.Stub {

	private static final String TAG = "FregService";
    private final Context mContext;

	private int mDevice;

	public FregService( Context context ){
		mContext = context;
		mDevice = initNative( );
	}

	public void setVal( int val ){
		if( mDevice == 0 ){
			Slog.v( TAG, "setVal mDevice == 0!" );
			return;
		}

		setValNative( mDevice, val );
	}

	public int getVal( ){
		if( mDevice == 0 ){
			Slog.v( TAG, "getVal mDevice == 0!" );
			return 0;
		}

		return getValNative( mDevice );
	}

	private static native int initNative( );
	private static native void setValNative( int device, int val );
	private static native int getValNative( int device );
}
