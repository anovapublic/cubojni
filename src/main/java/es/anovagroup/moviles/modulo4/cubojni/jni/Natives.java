/**
 * Anova IT Consulting 2011
 *
 * This file is licensed under the GPL version 3.
 * Please refer to the URL http://www.gnu.org/licenses/gpl-3.0.html for details.
 */

package es.anovagroup.moviles.modulo4.cubojni.jni;

public class Natives {

	private static EventListener listener;
	
	public static interface EventListener 
	{
		void OnMessage(String text);
		void GLSwapBuffers();
	}
	
	public static void setListener (EventListener listener) {
		Natives.listener = listener;
	}

	public static native int NativeRender();
	

	private static void OnMessage(String text) {
		if ( listener != null)
			listener.OnMessage(text);
	}
	
	private static void GLSwapBuffers() {
		if ( listener != null)
			listener.GLSwapBuffers();
	}
}
