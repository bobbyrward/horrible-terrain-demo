call "C:\Program Files\Microsoft Visual Studio 9.0\VC\vcvarsall"

@set INCLUDE=C:\devel\3rdparty\boost_1_39_0\boost\tr1\tr1;C:\devel\3rdparty\boost_1_39_0;C:\devel\include;%INCLUDE%;C:\devel\DXSDK\Include;C:\devel\DXSDK\Samples\C++\Common\Include

@set LIB=C:\devel\3rdparty\boost_1_39_0\stage\lib;C:\devel\lib;%LIB%;C:\devel\DXSDK\Lib

vcbuild /useenv

