# netCDF 4.9.3 Windows インストールガイド

## 方法1: 事前ビルド版のインストール（推奨）

1. **ダウンロード**
   - [netCDF-C 4.9.3 Windows版](https://downloads.unidata.ucar.edu/netcdf-c/4.9.3/)にアクセス
   - `netCDF4.9.3-NC4-64.exe` (64bit版) をダウンロード

2. **インストール**
   - ダウンロードしたインストーラーを実行
   - インストール先は既定の `C:\Program Files\netCDF 4.9.3` のままにする
   - すべてのコンポーネントを選択してインストール

3. **環境変数の設定**（オプション）
   - システムのプロパティ → 環境変数
   - Path に `C:\Program Files\netCDF 4.9.3\bin` を追加

## 方法2: vcpkgを使用（Visual Studio向け）

1. **vcpkgのインストール**
   ```cmd
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   bootstrap-vcpkg.bat
   vcpkg integrate install
   ```

2. **netCDFのインストール**
   ```cmd
   vcpkg install netcdf-c:x64-windows
   ```

## 方法3: 簡易版 - DLLのみ

もしビルド済みのnetcdf.dllがある場合：

1. 以下のフォルダ構造を作成：
   ```
   C:\Program Files\netCDF 4.9.3\
   ├── bin\
   │   └── netcdf.dll
   ├── lib\
   │   └── netcdf.lib
   └── include\
       └── netcdf.h
   ```

2. 必要なファイルをコピー

## インストール確認

インストール後、以下のファイルが存在することを確認：
- `C:\Program Files\netCDF 4.9.3\lib\netcdf.lib`
- `C:\Program Files\netCDF 4.9.3\include\netcdf.h`
- `C:\Program Files\netCDF 4.9.3\bin\netcdf.dll`

## トラブルシューティング

- **ダウンロードリンクが見つからない場合**
  - [Unidata netCDF](https://www.unidata.ucar.edu/software/netcdf/)の公式サイトから探す
  - または[GitHub Releases](https://github.com/Unidata/netcdf-c/releases)から取得

- **インストール先を変更した場合**
  - `st_render5_c.vcxproj`内のパスを修正：
    ```xml
    <AdditionalIncludeDirectories>新しいパス\include;%(AdditionalIncludeDirectories)</AdditionalIncludeDirectories>
    <AdditionalLibraryDirectories>新しいパス\lib;%(AdditionalLibraryDirectories)</AdditionalLibraryDirectories>
    ```