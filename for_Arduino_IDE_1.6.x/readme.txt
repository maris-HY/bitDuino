bitDuinoをArduino IDE 1.6.xに対応させる

1.フォルダ構造
下のように/hardware/bitDuinoXX/avr/配下にbitDuino定義ファイル群を収容すればArduino IDEで利用するすることができます。
hardware / bitDuinoXX / avr / board.txt, platform.txt, bootloaders, cores, variants

2. bitDuino10とbitDuino13はavrdudeに渡すパラメータが異なるたフォルダに同梱できません。
上記1.のbitDuinoXXをbitDuino10, bitDuio13とする２つのフォルダを用意しavr以下を収容します。

3. 具体的な操作

	1. bitDuino10フォルダを作成します

	2. bitDuino10/配下にavrフォルダを作成します

	3. birDuino10/avr/配下に既存のフォルダbootloaders,cores,variantsをコピーします

	4. bitDuino10-boards.txtをboards.txtとリネームしてbirDuino10/avr/配下にコピーします。

	5. bitDuino10-platform.txtをplatform.txtとリネームしてbirDuino10/avr/配下にコピーします。

	6. bitDuino13についても上記1〜5でbitDuino13フォルダを作ります
