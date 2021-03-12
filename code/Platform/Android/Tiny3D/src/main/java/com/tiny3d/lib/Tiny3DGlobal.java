package com.tiny3d.lib;

import android.Manifest;
import android.app.Application;
import android.app.Activity;
import android.app.ExpandableListActivity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;

import java.io.File;
import java.io.FileFilter;
import java.text.DecimalFormat;
import java.util.Random;

public class Tiny3DGlobal {
    private static Tiny3DGlobal sInstance = new Tiny3DGlobal();

    private Context mAppContext = null;
    private Application mApplication = null;
    private Activity mActivity = null;
    private TelephonyManager mTelephonyMgr = null;
    private int mScreenWidth = 0;
    private int mScreenHeight = 0;
    private float mScreenDPI = 0;

    private Tiny3DGlobal() {

    }

    public static Tiny3DGlobal Instance() {
        return sInstance;
    }

    public void init(Context context) {
        mAppContext = context.getApplicationContext();
        mActivity = (Activity) context;
        mApplication = mActivity.getApplication();

        mTelephonyMgr = (TelephonyManager) mActivity.getSystemService(Context.TELEPHONY_SERVICE);

//        if (mTelephonyMgr != null)
//        {
//            if (ActivityCompat.checkSelfPermission(mActivity, Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED)
//            {
//                // TODO: Consider calling
//                //    ActivityCompat#requestPermissions
//                // here to request the missing permissions, and then overriding
//                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
//                //                                          int[] grantResults)
//                // to handle the case where the user grants the permission. See the documentation
//                // for ActivityCompat#requestPermissions for more details.
//                ActivityCompat.requestPermissions(mActivity, new String[]{Manifest.permission.READ_PHONE_STATE}, 10002121);
//            }
//        }

        DisplayMetrics dm = mApplication.getResources().getDisplayMetrics();
        mScreenWidth = dm.widthPixels;
        mScreenHeight = dm.heightPixels;
        mScreenDPI = (float) dm.densityDpi;
    }

    public String getApkPath() {
        return mAppContext.getPackageResourcePath();
    }

    public String getSoftwareVersion() {
        String version = null;
        String build = null;

        try {
            PackageInfo pkgInfo = mAppContext.getPackageManager().getPackageInfo(mApplication.getPackageName(), 0);
            version = pkgInfo.versionName;
            build = String.valueOf(pkgInfo.versionCode);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return version + "." + build;
    }

    public int getScreenWidth() {
        return mScreenWidth;
    }

    public int getScreenHeight() {
        return mScreenHeight;
    }

    public float getScreenDPI() {
        return mScreenDPI;
    }

    private static final FileFilter CPU_FILTER = new FileFilter() {
        @Override
        public boolean accept(File pathname) {
            String path = pathname.getName();
            //regex is slow, so checking char by char.
            if (path.startsWith("cpu")) {
                for (int i = 3; i < path.length(); i++) {
                    if (path.charAt(i) < '0' || path.charAt(i) > '9') {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
    };

    public int getCPUCores() {
        if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.GINGERBREAD_MR1) {
            // Gingerbread doesn't support giving a single application access to both cores, but a
            // handful of devices (Atrix 4G and Droid X2 for example) were released with a dual-core
            // chipset and Gingerbread; that can let an app in the background run without impacting
            // the foreground application. But for our purposes, it makes them single core.
            return 1;
        }
        int cores;
        try {
            cores = new File("/sys/devices/system/cpu/").listFiles(CPU_FILTER).length;
        } catch (SecurityException e) {
            cores = 0;
        } catch (NullPointerException e) {
            cores = 0;
        }
        return cores;
    }

    public String getDeviceIMEI()
    {
        StringBuffer strBufIMEI = new StringBuffer("");
        try
        {
//            if (ActivityCompat.checkSelfPermission(mActivity, Manifest.permission.READ_PHONE_STATE) != PackageManager.PERMISSION_GRANTED)
//            {
//                // TODO: Consider calling
//                //    ActivityCompat#requestPermissions
//                // here to request the missing permissions, and then overriding
//                //   public void onRequestPermissionsResult(int requestCode, String[] permissions,
//                //                                          int[] grantResults)
//                // to handle the case where the user grants the permission. See the documentation
//                // for ActivityCompat#requestPermissions for more details.
//                ActivityCompat.requestPermissions(mActivity, new String[]{Manifest.permission.READ_PHONE_STATE}, 10002121);
//            }
//            else
            {
                String strIMEI = mTelephonyMgr.getDeviceId();
                if (strIMEI != null)
                {
                    strBufIMEI.append(strIMEI);
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }

        if (strBufIMEI.equals("")) {
            Random random = new Random(System.currentTimeMillis());
            DecimalFormat decimalFormat = new DecimalFormat("0");
            float randomFloat = Math.abs(random.nextLong()%10000000000000000.0f);
            String randomString = String.valueOf(decimalFormat.format(randomFloat));
            strBufIMEI.append(randomString);
            for (int i = strBufIMEI.length(); i < 16; i++) {
                strBufIMEI.insert(0, '0');
            }
        }

        return strBufIMEI.toString();
    }

    public static String GetApkPath()
    {
        return Tiny3DGlobal.Instance().getApkPath();
    }

    public static String GetSoftwareVersion()
    {
        return Tiny3DGlobal.Instance().getSoftwareVersion();
    }

    public static int GetScreenWidth()
    {
        return Tiny3DGlobal.Instance().getScreenWidth();
    }

    public static int GetScreenHeight()
    {
        return Tiny3DGlobal.Instance().getScreenHeight();
    }

    public static float GetScreenDPI()
    {
        return Tiny3DGlobal.Instance().getScreenDPI();
    }

    public static String GetDeviceName()
    {
        return Build.MODEL;
    }

    public static String GetOSVersion()
    {
        return Build.VERSION.RELEASE;
    }

    public static int GetCPUCores()
    {
        return Tiny3DGlobal.Instance().getCPUCores();
    }

    public static String GetDeviceID()
    {
        return Tiny3DGlobal.Instance().getDeviceIMEI();
    }
}
