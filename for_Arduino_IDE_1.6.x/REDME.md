#bitDuinoをArduino IDE 1.6.xに対応させる
<ol>
<li>
フォルダ構造<br>
下のように/hardware/bitDuinoXX/avr/配下にbitDuino定義ファイル群を収容すればArduino IDEで利用するすることができます。<br>  
hardware / bitDuinoXX / avr / board.txt, platform.txt, bootloaders, cores, variants
</li><br><li>
bitDuino10とbitDuino13はavrdudeに渡すパラメータが異なるたフォルダに同梱できません。<br>
上記１のbitDuinoXXをbitDuino10, bitDuio13とする２つのフォルダを用意しavr以下を収容します。
</li><br><li>
具体的な操作  
<ol>
<li>bitDuino10フォルダを作成します</li><br>
<li>bitDuino10/配下にavrフォルダを作成します</li><br>
<li>birDuino10/avr/配下に既存のフォルダbootloaders,cores,variantsをコピーします</li><br>
<li>bitDuino10-boards.txtをboards.txtとリネームしてbirDuino10/avr/配下にコピーします。</li><br>
<li>bitDuino10-platform.txtをplatform.txtとリネームしてbirDuino10/avr/配下にコピーします。</li><br>
<li>bitDuino13についても上記1〜5でbitDuino13フォルダを作ります</li><br>
</ol></li>
</ol>





     


  


