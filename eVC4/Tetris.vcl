<html>
<body>
<pre>
<h1>ビルドのログ</h1>
<h3>
--------------------構成 : Tetris - Win32 (WCE ARMV4I) Release_CH--------------------
</h3>
<h3>コマンド ライン</h3>
Creating command line "rc.exe /l 0x804 /fo"ARMV4IRelease_CH/resource_CH.res" /d UNDER_CE=500 /d _WIN32_WCE=500 /d "UNICODE" /d "_UNICODE" /d "NDEBUG" /d "WCE_PLATFORM_STANDARDSDK_500" /d "THUMB" /d "_THUMB_" /d "ARM" /d "_ARM_" /d "ARMV4I" /r "F:\Programming\Tetris\resource_CH.rc"" 
一時ファイル "C:\DOCUME~1\WATA\LOCALS~1\Temp\RSP44.tmp" を作成し、次の内容を記録します
[
/nologo /W3 /D _WIN32_WCE=500 /D "ARM" /D "_ARM_" /D "WCE_PLATFORM_STANDARDSDK_500" /D "ARMV4I" /D UNDER_CE=500 /D "UNICODE" /D "_UNICODE" /D "NDEBUG" /D "LANG_CH" /Fp"ARMV4IRelease_CH/Tetris.pch" /YX /Fo"ARMV4IRelease_CH/" /QRarch4T /QRinterwork-return /O2 /MC /c 
"F:\Programming\Tetris\tetris.c"
]
Creating command line "clarm.exe @C:\DOCUME~1\WATA\LOCALS~1\Temp\RSP44.tmp" 
一時ファイル "C:\DOCUME~1\WATA\LOCALS~1\Temp\RSP45.tmp" を作成し、次の内容を記録します
[
commctrl.lib coredll.lib /nologo /base:"0x00010000" /stack:0x10000,0x1000 /entry:"WinMainCRTStartup" /incremental:no /pdb:"ARMV4IRelease_CH/AppMain_CH.pdb" /nodefaultlib:"libc.lib /nodefaultlib:libcd.lib /nodefaultlib:libcmt.lib /nodefaultlib:libcmtd.lib /nodefaultlib:msvcrt.lib /nodefaultlib:msvcrtd.lib" /out:"ARMV4IRelease_CH/AppMain_CH.exe" /subsystem:windowsce,5.00 /MACHINE:THUMB 
.\ARMV4IRelease_CH\tetris.obj
.\ARMV4IRelease_CH\resource_CH.res
]
コマンド ライン "link.exe @C:\DOCUME~1\WATA\LOCALS~1\Temp\RSP45.tmp" の作成中
<h3>アウトプット ウィンドウ</h3>
リソースをコンパイル中...
F:\Programming\Tetris\resource_CH.rc (36): error RC2104 : undefined keyword or key name: ｿｪﾊｼ






rc.exe の実行エラー



<h3>結果</h3>
AppMain_CH.exe - エラー 1、警告 0
</pre>
</body>
</html>
