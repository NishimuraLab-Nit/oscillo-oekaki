# オシロお絵描き

## About  
オシロスコープで絵を描く

## Usage  
素材をconverter/originalDataに入れる。  
ffmpegを使って動画や画像を256x256pixに変換する。  
動画の場合はフレームレートを指定して画像にする。  
・静止画の場合  
`ffmpeg -i "画像.png" -s 256x256 images/%05d.png`  
・動画の場合  
`ffmpeg -i "ビデオ.mp4" -s 256x256 -r 24 images/%05d.png`  

エッジ検出する。  
`python3 convert.py <ファイル名>`  

回路を組むか基板を積む。  

コンパイルする。  
`gcc -o <paint or movie> oscillo-<paint or movie>.c -lpigpio`  

描画する。  
・静止画の場合  
`sudo ./paint`  
・動画の場合  
`sudo ./movie`  
実行すると、入力ウィザードになるので、ファイル名、フレームレート(動画の場合)を入力する。  

## KiCadプロジェクトについて  
Raspberry Pi Hatを作るプロジェクト。  
ブレボ上で組んでもいいが、これを発注して楽できる。  