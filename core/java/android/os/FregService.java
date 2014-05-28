
package android.os;

import android.util.Log;

public final class FregService {
    private static final String TAG = "FregService";
    private final IFregService mService;

	public FregService( IFregService service ){
		mService = service;
	}

	public int getVal( )
	{
		if( mService != null ){
			int val = 0;

			try {
				val = mService.getVal( );
			}
			catch (RemoteException e) {
				return 0;
			}

			return val;
		}

		return 0;
	}

	public void setVal( int val )
	{
		if( mService != null ){
			try {
				mService.setVal( val );
			}
			catch (RemoteException e) {
			}
		}
	}
}
