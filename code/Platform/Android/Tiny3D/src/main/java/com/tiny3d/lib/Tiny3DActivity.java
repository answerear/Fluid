package com.tiny3d.lib;

import android.os.Bundle;
import android.telephony.TelephonyManager;

import org.libsdl.app.SDLActivity;
import com.tiny3d.lib.Tiny3DGlobal;

import java.util.List;

public class Tiny3DActivity extends SDLActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Tiny3DGlobal.Instance().init(this);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        // Forward results to EasyPermissions
    }
}

//import android.app.Activity;
//import android.os.Bundle;

//public class Tiny3DActivity extends Activity {
//
//    Tiny3DGLSurfaceView mView;
//
//    @Override protected void onCreate(Bundle savedInstanceState) {
//        super.onCreate(savedInstanceState);
//        mView = new Tiny3DGLSurfaceView(getApplication());
//        setContentView(mView);
//    }
//
//    @Override protected void onPause() {
//        super.onPause();
//        mView.onPause();
//    }
//
//    @Override protected void onResume() {
//        super.onResume();
//        mView.onResume();
//    }
//}


