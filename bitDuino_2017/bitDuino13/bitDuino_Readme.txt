まりす(@maris_HY)氏の bitDuino ( http://100year.cocolog-nifty.com/blog/2014/08/arduino-f0f0.html )　
のファイル群(bitDuino_2014_09_09)を改編したものです。

arduino.cc の Arduino IDE 1.6.x, IDE 1.8.x 用です


2017.01.05 kimio kosaka
1. boards.txt
 クロック選択メニューを追加。
 Attiny10 8, 4, 2, 1MHz の４種
 ATtiny13 9.6, 4.8, 1.2MHz の３種

2.wiring.c
　ATtiny10,13
  cores/wiring.cのdelay関数定義に設定クロック周波数による
  時間基準値(TBASE)を切り替えるマクロを追加

  ATtiny10
  cores/wiring.cのinit関数定義に設定クロックに対応するように
  CLKPSRレジスタをセットするマクロを追加。



2016.12.27 kimio kosaka
bitDuino_2014_09_09からの変更点

１．bitDuino10とbitDuino13に切り分けて，それぞれ独立のフォルダに収容した。

２．ファイル群のツリー構造を1.6.x, 1.8.x向けに変更した。

３．board.txtを1.6.13, 1.8.x向けに改編した。

４．platform.txtを追加した。
　　　　bitDuino10とbitDuino13のplatform.txtはavrdudeに引き渡すパラメータの定義が異なっています。
　　　　このため，bitDuino10とbitDuino13を別フォルダに切り分ける必要がありました，

