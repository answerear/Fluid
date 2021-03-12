package com.tiny3d.framework;

import com.tiny3d.lib.Tiny3DActivity;

import org.libsdl.app.SDLActivity;

/**
 * Created by aaronwang on 2018/1/6.
 */

public class FrameworkActivity extends Tiny3DActivity {
    static {
        System.loadLibrary("T3DPlatform");
        System.loadLibrary("T3DCore");
        System.loadLibrary("FrameworkApp");
    }

    protected String getMainSharedObject() {
        return "libFrameworkApp.so";
    }

    protected String getMainFunction() {
        return "main";
    }
}
