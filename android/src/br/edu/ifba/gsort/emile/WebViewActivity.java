package br.edu.ifba.gsort.emile;

import android.app.Activity;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.webkit.SslErrorHandler;
import android.net.http.SslError;
import android.util.Log;
import android.webkit.CookieManager;
import android.view.View;
import android.os.Bundle;

public class WebViewActivity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        WebView m_webView = new WebView(this);
        m_webView.setWebViewClient(new MyWebViewClient());
        m_webView.getSettings().setJavaScriptEnabled(true);
        m_webView.getSettings().setDomStorageEnabled(true);
        m_webView.loadUrl("https://suap.ifba.edu.br");
        setContentView(m_webView);
    }

    public static native void sendCookies(String cookies);

    private class MyWebViewClient extends WebViewClient {
        @Override
        public void onReceivedSslError(WebView view, SslErrorHandler handler, SslError error) {
            if (error.getUrl().equals("https://suap.ifba.edu.br/"))
                handler.proceed();
            else
                super.onReceivedSslError(view, handler, error);
        }

        public void onLoadResource(WebView view, String url) {
//            Log.e("", "onLoadResource: " + url);
            CookieManager cookieManager = CookieManager.getInstance();
//            Log.e("", "Has cookies? " + cookieManager.hasCookies());
//            Log.e("", "cookie: " + cookieManager.getCookie("https://suap.ifba.edu.br/"));
            if (url.equals("https://suap.ifba.edu.br/accounts/login/?next=/"))
                loggedIn = true;
            if (loggedIn && url.equals("https://suap.ifba.edu.br/static/djtools/jquery-1.6.2/css/jquery.ui.all.css")) {
                sendCookies(cookieManager.getCookie("https://suap.ifba.edu.br/"));
                finish();
            }
        }

        private boolean loggedIn = false;
    }
}
