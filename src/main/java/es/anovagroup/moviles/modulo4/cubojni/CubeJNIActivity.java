/**
 * Anova IT Consulting 2011
 *
 * This file is licensed under the GPL version 3.
 * Please refer to the URL http://www.gnu.org/licenses/gpl-3.0.html for details.
 */

package es.anovagroup.moviles.modulo4.cubojni;

import es.anovagroup.moviles.modulo4.cubojni.renderer.CubeRenderer;
import android.app.Activity;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.util.Log;

public class CubeJNIActivity extends Activity {

	private static String TAG = "cubojni";
	
	static {
		System.loadLibrary("cubojni");
	}

	private GLSurfaceView view;

	/**
	 * Called when the activity is first created.
	 * 
	 * @param savedInstanceState
	 * If the activity is being re-initialized after previously being
	 * shut down then this Bundle contains the data it most recently
	 * supplied in onSaveInstanceState(Bundle). <b>Note: Otherwise it
	 * is null.</b>
	 */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		Log.i(TAG, "onCreate");
		view = new GLSurfaceView(this);
		view.setRenderer(new CubeRenderer(true));
		setContentView(view);
	}

	@Override
	protected void onResume() {
		super.onResume();
		view.onResume();
	}

	@Override
	protected void onPause() {
		super.onPause();
		view.onPause();
	}

}
