package br.edu.ifba.gsort.emile;

import android.os.Build;
import android.os.StrictMode;
import android.app.Activity;
import android.content.Intent;

import java.lang.reflect.Method;

public class WebViewController {
    public WebViewController(final Activity activity, final long id) {
        Intent intent = new Intent(activity, WebViewActivity.class);
        activity.startActivity(intent);
    }

    public static void disableDeathOnFileUriExposure() {
        if (Build.VERSION.SDK_INT >= 24) {
           try {
              Method m = StrictMode.class.getMethod("disableDeathOnFileUriExposure");
              m.invoke(null);
           } catch(Exception e) {
              e.printStackTrace();
           }
        }
    }
}
