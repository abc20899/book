### 简介
FFmpeg是处理多媒体内容（如音频，视频，字幕和相关元数据）的库和工具的集合。

1. ffmpeg下载,编译与安装 <br>

  ```
  git clone https://github.com/FFmpeg/FFmpeg.git
  ```

2. 库介绍  
  
  ```
  	  libavcodec     提供了更广泛的编解码器的实现。
	  libavformat    实现流协议，容器格式和基本I / O访问。
	  libavutil      包括哈希，解压缩器和各种实用程序功能。
	  libavfilter    提供了通过过滤器链改变解码的音频和视频的方法。
	  libavdevice    提供访问捕获和回放设备的抽象。
	  libswresample  实现音频混合和重采样例程。
	  libswscale     实现颜色转换和缩放例程。
	 
	  命令工具
	  ffmpeg  是一个命令行工具箱，用于操作，转换和流式传输多媒体内容。
	  ffplay  是一个简约的多媒体播放器。
	  ffprobe 是一种用于检查多媒体内容的简单分析工具。其他小工具，如aviocat，ismindex和qt-faststart。
  ```

3. 编译选项配置

  ```
   ./configure
  ./configure --help
  ./configure --list-decoders
  ./configure --list-encoders
  默认安装目录：/usr/local/bin/ffmpeg
  
  brew install fdk-aac  安装aac库
  brew install yasm     安装yasm编译器
  brew install automake fdk-aac lame libass libtool libvorbis libvpx libvo-aacenc opencore-amr openjpeg opus sdl schroedinger shtool speex texi2html theora wget x264 xvid yasm
  
  pkg-config 工具
  pkg-config --list-all 列库
  export PKG_CONFIG_PATH="/usr/local/lib/pkgconfig"  ***配置pkgconfig环境***
  pkg-config --list-all 列库
  
  ```
 
4. 配置如下：

	./configure --prefix=/Users/junzhao/ffmpeg/ffmpegInstall --enable-gpl --enable-nonfree --enable-libfdk-aac --enable-libmp3lame --enable-libspeex --enable-libx264 --enable-libx265 --enable-libxvid --enable-libzimg --enable-libzmq --enable-libzvbi --enable-version3 --enable-ffplay --enable-filter=delogo --enable-debug --disable-optimizations --enable-videotoolbox --enable-shared --enable-hardcoded-tables --enable-pthreads --cc=clang
	
	
	https://www.jianshu.com/p/8c4c8d7dd350	<br>
	./configure --prefix=/usr/local --enable-gpl --enable-nonfree --enable-libass \
	--enable-libfdk-aac --enable-libfreetype --enable-libmp3lame --enable-libopus \
	--enable-libtheora --enable-libvorbis --enable-libvpx --enable-libx264 --enable-libxvid --extra-ldflags=-L/usr/local/lib

5. 编译

```
sudo make && make install
目录
bin （ffmpeg ffplay ffprobe）
include
lib
share 文档
```

编译脚本：

[build_android_ffmpeg_cmd.sh](ffmpeg编译/build_android_ffmpeg_cmd.sh) 

[build_ffmpeg_for_android.sh](ffmpeg编译/build_ffmpeg_for_android.sh) 

[build_android.sh](ffmpeg编译/build_android.sh)  

[configure配置选项说明](ffmpeg编译/configure配置选项说明.txt)

[ffmpeg_nginx](ffmpeg编译/ffmpeg_nginx.txt)

[pkg_介绍](ffmpeg编译/pkg_介绍.txt)









