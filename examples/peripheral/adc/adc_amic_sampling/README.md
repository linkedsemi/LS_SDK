# analog mic example

The example realizes the analog mic function through ADC and Timer.

The describes of main functional components is as follows:

1.  adc sampling use **regular** and **dma** and **pis** trigger type.
2.  the timer can config the adc sampling rate(8K or 16k) via macro of **AMIC_SAMPLE_RATE** in app_config.h, default sampling rate is **16K**.
3.  uart1 can output the adc sampling value (the original PCM stream) via 921600 .
4.  uart2 can output the ADPCM stream through ADPCM compression algorithm via 921600, if you want to use it.
5.  user can choose the appropriate format via macro of **AMIC_STREAM_FORMAT** in app_config.h, default stream format is **PCM**.
6.  hardware platform is solo board, and the adc channel is channel 1.
7.  user need build the operational amplifier circuits.

The process framework is as follows:
1.  init uart、timer、adc、gpio button interrupt.
2.  when pressed the button to start sampling, and released to stop.
3.  the uart will output PCM or ADPCM stream data(depend on user choose) when the adc sampling conversion is complete .

**Note**

1.  if the length of data sampled at one time is large, user need to increase the CPU Clock frequency to 64MHz to avoid missing data output through the uart.
2.  if use io supply power to mic, must to set the io drive capacity in order to amic stable power supply.
3.  user can use sox tool to convert PCM stream or ADPCM stream to WAV audio format.