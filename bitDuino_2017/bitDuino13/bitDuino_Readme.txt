�܂肷(@maris_HY)���� bitDuino ( http://100year.cocolog-nifty.com/blog/2014/08/arduino-f0f0.html )�@
�̃t�@�C���Q(bitDuino_2014_09_09)�����҂������̂ł��B

arduino.cc �� Arduino IDE 1.6.x, IDE 1.8.x �p�ł�


2017.01.05 kimio kosaka
1. boards.txt
 �N���b�N�I�����j���[��ǉ��B
 Attiny10 8, 4, 2, 1MHz �̂S��
 ATtiny13 9.6, 4.8, 1.2MHz �̂R��

2.wiring.c
�@ATtiny10,13
  cores/wiring.c��delay�֐���`�ɐݒ�N���b�N���g���ɂ��
  ���Ԋ�l(TBASE)��؂�ւ���}�N����ǉ�

  ATtiny10
  cores/wiring.c��init�֐���`�ɐݒ�N���b�N�ɑΉ�����悤��
  CLKPSR���W�X�^���Z�b�g����}�N����ǉ��B



2016.12.27 kimio kosaka
bitDuino_2014_09_09����̕ύX�_

�P�DbitDuino10��bitDuino13�ɐ؂蕪���āC���ꂼ��Ɨ��̃t�H���_�Ɏ��e�����B

�Q�D�t�@�C���Q�̃c���[�\����1.6.x, 1.8.x�����ɕύX�����B

�R�Dboard.txt��1.6.13, 1.8.x�����ɉ��҂����B

�S�Dplatform.txt��ǉ������B
�@�@�@�@bitDuino10��bitDuino13��platform.txt��avrdude�Ɉ����n���p�����[�^�̒�`���قȂ��Ă��܂��B
�@�@�@�@���̂��߁CbitDuino10��bitDuino13��ʃt�H���_�ɐ؂蕪����K�v������܂����C

