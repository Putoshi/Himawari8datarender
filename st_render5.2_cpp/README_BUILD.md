# st_render5_cpp ビルドガイド

## 必要なソフトウェア

### 1. C++コンパイラ（以下のいずれか）

#### Option A: Visual Studio Community（推奨）
- [Visual Studio 2022 Community](https://visualstudio.microsoft.com/ja/downloads/)をダウンロード
- インストール時に「C++によるデスクトップ開発」ワークロードを選択

#### Option B: MinGW-w64
- [MSYS2](https://www.msys2.org/)をインストール
- MSYS2ターミナルで以下を実行：
  ```bash
  pacman -S mingw-w64-x86_64-gcc
  pacman -S mingw-w64-x86_64-make
  ```

#### Option C: Build Tools for Visual Studio
- [Build Tools for Visual Studio](https://visualstudio.microsoft.com/ja/downloads/#build-tools-for-visual-studio-2022)をダウンロード
- 「C++ Build Tools」を選択してインストール

### 2. netCDF ライブラリ
- [netCDF 4.9.3 for Windows](https://downloads.unidata.ucar.edu/netcdf/)をダウンロード
- デフォルトパス（C:\Program Files\netCDF 4.9.3）にインストール

## ビルド方法

### Visual Studioを使用する場合
1. `st_render5_c.vcxproj`をダブルクリック
2. ビルド構成を「Release」「x64」に設定
3. ビルド → ソリューションのビルド

### コマンドラインでビルドする場合
1. コンパイラのPATHを通す
2. `build.bat`を実行

### 手動でビルドする場合
```cmd
cd st_render5.2_cpp
mingw32-make -f Makefile.win
```

## トラブルシューティング

- netCDFが見つからない場合：
  - Makefile.winのNETCDF_PATHを修正
  
- リンクエラーが出る場合：
  - 64bit版のnetCDFと64bit版のコンパイラを使用しているか確認