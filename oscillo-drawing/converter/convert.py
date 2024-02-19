## coding: UTF-8
import cv2
import sys
from PIL import Image, ImageFilter

output_dir = "images_done/" #エッジ検出した画像ファイルの置き場
args = sys.argv # osdファイル名
NumberOfImages = 0 #画像枚数

###
# edge detector
###
file_dir = "images/"
print("##########################################################################################")
print("start canny edge detector")
try:
    # 画像枚数カウント
    for i in range(100000):
        img = Image.open(file_dir + "{0:05d}.png".format(i + 1))
        NumberOfImages += 1

except:
    print("")

print("count: {}".format(NumberOfImages))
for i in range(NumberOfImages):
    gray_scale = cv2.imread(file_dir + "{0:05d}.png".format(i + 1), cv2.IMREAD_GRAYSCALE) # グレースケールにする
    canny_img = cv2.Canny(gray_scale, 50, 110) # ケニー法によるエッジ検出

    cv2.imwrite(output_dir + "{0:05d}.png".format(i + 1), canny_img) #エッジ検出した画像を書き出す
    print("processing... : {} / {}".format(i + 1, NumberOfImages))

cv2.waitKey(1000)
cv2.destroyAllWindows()
print("complete canny edge detector")
print("##########################################################################################")
###
# edge detector
###

###
# convert image to text(osd) file
###
print("start convert image to text")
# print("count(convert text): {}".format(NumberOfImages))
im = Image.open(output_dir + "{0:05d}.png".format(1))
width, height = im.size # 画像サイズ
print("Size	{}x{}".format(width, height))
f = open("../data/{}.osd".format(args[1]), "w") # osdファイルを生成
f.write("{}\n".format(NumberOfImages)) # osdファイルの一行目に画像枚数を書く

for i in range(NumberOfImages):
    im = Image.open(output_dir + "{0:05d}.png".format(i + 1))
    imgdata = im.getdata() # ピクセルデータ(配列)
    NumberOfDot = 0 # オシロに表示する点の数
    # インターレース方式で描画したいので奇数行と偶数行を分ける
    LK = ""#奇数
    LG = ""#偶数
    for y in range(height):
        y_cache = y * width
        for x in range(width):
            pixdata = imgdata[y_cache + x - 1]# int 0-255
            if(pixdata == 255): # エッジを描いているピクセル
                NumberOfDot += 1
                if(y%2 == 0):
                    LK = LK + ("{} {} {}\n".format(x - 1, x - 1, y))
                else:
                    LG = LG + ("{} {} {}\n".format(x - 1, x - 1, y))
    f.write("{}\n{}{}".format(NumberOfDot, LK , LG)) # 画像一枚ごとosdファイルに書き込む
    print("processing... : {} / {}".format(i + 1, NumberOfImages))

f.close()
print("complete convert image to text")
print("##########################################################################################")
###
# convert image to text(osd) file
###